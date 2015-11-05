#ifndef FWT_FILE_HH
#define FWT_FILE_HH

#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

namespace fw {

using namespace std;

inline bool
fs_exists(const string &name) {
    struct stat buffer;
    return (0 == stat(name.c_str(), &buffer));
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
