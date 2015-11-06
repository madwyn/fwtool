#include "ZipFile.hh"

#include "../util/file.hh"
#include "../util/dir.h"

namespace fw {

MSG_CODE ZipFile::_extract_all(const string &dir_dst) {
    auto _stop = []() {
        return false;
    };

    auto _extract = [this, &dir_dst](const char *path_in_zip) {
        MSG_CODE ret = MSG_OK;

        printf("extract file %s\n", path_in_zip);

        // detect if it's a file or directory
        // extract the base name
        const char *base_name = get_base_name(path_in_zip);

        // generate the full path to create
        string full_path = (dir_dst.length() > 0) ? (dir_dst + "/" + path_in_zip) : path_in_zip;

        // full path is a directory
        if ('\0' == *base_name) {
            // create the directory, full_path is dir name
            MKDIR(full_path.c_str());
        } else { // base name is a file
            // extract the dir name
            string dir_name = get_dir_name(full_path);

            // test if the dir name exists
            if (!fs_exists(dir_name)) {
                // if parent directory doesn't exist, create that first
                MKDIR(dir_name.c_str());
            }

            ret = _extract_cur(full_path);
        }

        return ret;
    };

    return _loop(_extract, _stop);
}



MSG_CODE ZipFile::_open(const string &file_name) {
    MSG_CODE ret = MSG_OK;

    // check file exists
    if (fs_exists(file_name)) {

        // load file
        file = unzOpen64(file_name.c_str());

        // file can be open
        if (nullptr != file) {
            // check zip information
            int err = unzGetGlobalInfo64(file, &info_g);

            if (UNZ_OK != err) {
                ret = ZIP_FILE_INFO_INVALID;
            }
        } else {
            ret = ZIP_FILE_INVALID;
        }
    } else {
        ret = ZIP_FILE_NOT_EXIST;
    }

    return ret;
}

void ZipFile::_close(void) {
    if (nullptr != file) {
        unzClose(file);
        file = nullptr;
    }
}

MSG_CODE ZipFile::_loop(auto func, auto stop) {
    auto ret = MSG_OK;

    if (nullptr != file) {
        // set to head
        if (UNZ_OK == unzGoToFirstFile(file)) {
            unz_file_info64 file_info;

            char *path_in_zip = (char *)malloc(ZIP_MAX_PATH);

            if (nullptr != path_in_zip) {

                for (auto err = UNZ_OK; (UNZ_END_OF_LIST_OF_FILE != err) && !stop(); ) {
                    // get the current file
                    err = unzGetCurrentFileInfo64(file, &file_info, path_in_zip, ZIP_MAX_PATH, nullptr, 0, nullptr, 0);

                    if (UNZ_OK == err) {
                        // process the file
                        ret = func(path_in_zip);

                        if (MSG_OK != ret) {
                            break;
                        }

                        err = unzGoToNextFile(file);
                    } else {
                        ret = ZIP_FILE_ERR_GET_CUR_INFO;
                        break;
                    }
                }

                free(path_in_zip);
            }

        } else {
            ret = ZIP_FILE_ERR_LOCATE_FIRST;
        }
    } else {
        ret = ZIP_FILE_NOT_READY;
    }

    return ret;
}

MSG_CODE ZipFile::_extract_cur(const string &file_dst) {
    MSG_CODE ret = MSG_OK;

    // open file with null password
    int err = unzOpenCurrentFilePassword(file, nullptr);

    // file can be open
    if (UNZ_OK == err) {
        // create file
        FILE *file_out = fopen(file_dst.c_str(), "wb");

        if (nullptr != file_out) {
            // allocate buffer for reading the content
            void *buf = malloc(ZIP_BUF_LEN);

            if (nullptr != buf) {
                // extract file
                do {
                    // read data
                    err = unzReadCurrentFile(file, buf, ZIP_BUF_LEN);

                    // err is the length of data been read if > 0
                    if (err > 0) {
                        // write buffer content to file
                        if (1 != fwrite(buf, err, 1, file_out)) {
                            ret = UNZIP_ERR_WRITE_BUF_TO_FILE;
                            break;
                        }
                    } else if (err < 0) { // err is the error code if < 0
                        ret = UNZIP_ERR_READ_FILE_TO_BUF;
                        break;
                    }
                } while (err > 0);  // err is the number of bytes read

                // free buffer
                free(buf);
            } else {
                ret = UNZIP_ERR_ALLOCATE_BUF;
            }

            // close output file
            fclose(file_out);
        } else {
            ret = UNZIP_ERR_CREATE_OUTPUT_FILE;
        }

        // close current zip file
        unzCloseCurrentFile(file);
    } else {
        ret = UNZIP_ERR_OPEN_CUR_ZIP_FILE;
    }

    return ret;
}

#define FWD_FILE_NAME_PREFIX "FirmwareData"

MSG_CODE ZipFile::extract(const string &file_in, const string &dir_dst, string &file_name_fwd) {
    MSG_CODE ret = _open(file_in);

    if (MSG_OK == ret) {
        ret = _search(FWD_FILE_NAME_PREFIX, file_name_fwd);

        if (MSG_OK == ret) {
            ret = _extract_all(dir_dst);

            if (MSG_OK == ret) {
                file_name_fwd = dir_dst + file_name_fwd;
            }
        }

        _close();
    }

    return ret;
}

MSG_CODE ZipFile::_search(const string &name, string &path_in_zip) {
    auto got = false;

    auto stop = [&got]() {
        return got;
    };

    auto match = [&name, &got, &path_in_zip](const char *cur_name) {
        // use the base name only?
        const char *base_name = get_base_name(cur_name);
        if (nullptr != strstr(base_name, name.c_str())) {
            got = true;
            path_in_zip = cur_name;
        }
        return MSG_OK;
    };

    return _loop(match, stop);
}


}
