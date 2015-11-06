#ifndef FWT_ZIPFILE_HH
#define FWT_ZIPFILE_HH

#include <string>
#include <message_def.h>
#include <unzip.h>

namespace fw {

using std::string;

// the max path length in a zip file
#define ZIP_MAX_PATH 256
#define ZIP_BUF_LEN  1048576

class ZipFile {
public:
    MSG_CODE extract(const string &file_in, const string &dir_dst, string &file_name_fwd);

private:
    MSG_CODE _open(const string &file_name);    // open a zip file
    void     _close(void);                      // close the zip file, must be called after a success open

    MSG_CODE _search(const string &name, string &path_in_zip);  // search name in the zip file, return the path inside the zip
    MSG_CODE _extract_cur(const string &file_dst);              // extract current file
    MSG_CODE _extract_all(const string &dir_dst);               // extract all files
    MSG_CODE _loop(auto func, auto stop);                       // a breakable loop which you can stop at any time

    unzFile           _file = nullptr;  // the zip file context
    unz_global_info64 _info_g;          // the zip file global info
};

}

#endif //FWT_ZIPFILE_HH
