#ifndef FWT_FILE_HH
#define FWT_FILE_HH

#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

namespace fw {

using namespace std;

inline bool
fs_exists(const string &name) {
    struct stat st;
    return (0 == stat(name.c_str(), &st));
}


inline size_t
fs_size(const string &name) {
    struct stat st;
    stat(name.c_str(), &st);
    return st.st_size;
}


inline bool
fs_cp(FILE *file_in, size_t len, FILE *file_out) {
    uint8_t *buf = (uint8_t *)malloc(BUFSIZ);
    if (nullptr != buf) {
        size_t io_len = 0;

        while (len > 0) {
            io_len = (len > BUFSIZ) ? BUFSIZ : len;

            fread(buf,  io_len, 1, file_in);
            fwrite(buf, io_len, 1, file_out);

            len -= io_len;
        }

        return true;
    }

    return false;
}


inline bool
fs_save_to(FILE *file_in, size_t len, const char * const file_name) {
    bool ret = false;

    FILE *file_out = fopen(file_name, "wb");

    if (nullptr != file_out) {
        ret = fs_cp(file_in, len, file_out);

        fclose(file_out);
    }

    return ret;
}


inline bool
fs_append_to(const char * const file_name, FILE *file_out) {
    bool ret = false;

    FILE *file_in = fopen(file_name, "rb");

    if (nullptr != file_in) {
        size_t len = fs_size(file_name);

        ret = fs_cp(file_in, len, file_out);

        fclose(file_in);
    }

    return ret;
}


inline size_t
fs_ls_count(DIR *dir) {
    struct dirent *entry = nullptr;
    size_t         count = 0;

    while ((entry = readdir(dir)) != nullptr) {
        ++count;
    }

    rewinddir(dir);

    return count;
}


inline int
fs_compare_name(const void *const a, const void *const b) {
    return strcmp((*(struct dirent **) a)->d_name, (*(struct dirent **) b)->d_name);
}


inline struct dirent **
fs_ls_sort(DIR *dir) {
    struct dirent **list = nullptr;
    struct dirent *entry = nullptr;

    size_t count = fs_ls_count(dir);

    if (count > 0) {
        list = (dirent **)malloc(count * sizeof(dirent *));

        if (nullptr != list) {
            count = 0;

            while ((entry = readdir(dir)) != nullptr) {
                list[count++] = entry;
            }

            qsort(list, count, sizeof(dirent *), fs_compare_name);
        }
    }

    rewinddir(dir);

    return list;
}


inline const char *
rfind_slash(const char * const path) {
    for (const char *cur = path + strlen(path) - 1; cur >= path; --cur) {
        if (('/' == *cur) || ('\\' == *cur)) {
            return cur;
        }
    }

    return nullptr;
}


inline const char *
get_base_name(const char * const path_full) {
    return rfind_slash(path_full) + 1;
}


inline string
get_dir_name(const string &path_full) {
    return path_full.substr(0, rfind_slash(path_full.c_str()) - path_full.c_str());
}

}


#endif //FWT_FILE_HH
