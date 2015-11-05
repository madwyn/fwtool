#ifndef FWT_ZIPFILE_HH
#define FWT_ZIPFILE_HH

#include <string>
#include <message_def.h>

namespace fw {

using std::string;

class ZipFile {
public:
    MSG_CODE extract(const string &file_name);

//    MSG_CODE create(const string &dir_name);
};

}

#endif //FWT_ZIPFILE_HH
