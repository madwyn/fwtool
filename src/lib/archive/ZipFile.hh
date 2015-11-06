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
    unzFile           file = nullptr;
    unz_global_info64 info_g;
    MSG_CODE extract(const string &file_in, const string &dir_dst, string &file_name_fwd);

private:
    MSG_CODE _open(const string &file_name);
    void     _close(void);

    MSG_CODE _search(const string &name, string &path_in_zip);
    MSG_CODE _extract_cur(const string &file_dst);
    MSG_CODE _extract_all(const string &dir_dst);
    // a breakable loop which you can stop at any time
    MSG_CODE _loop(auto func, auto stop);
};

}

#endif //FWT_ZIPFILE_HH
