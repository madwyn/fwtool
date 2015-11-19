#ifndef FWT_HEADERFACTORY_HH
#define FWT_HEADERFACTORY_HH

#include <map>
#include <string>
#include <memory>

#include "Header.hh"


namespace fw {


using std::map;
using std::string;
using std::unique_ptr;


typedef map<HDR_GEN, Header *> HeaderMap;


class HeaderFactory {
public:
    static unique_ptr<Header> get(const string &file_name) {
        return get_instance()->_get_header(file_name);
    }

    static unique_ptr<Header> get(const uint8_t *buf, size_t buf_len) {
        return get_instance()->_get_header(buf, buf_len);
    }

    ~HeaderFactory() {
        _dest();
    }

private:
    HeaderFactory() {_init();}

    void _init(void);
    void _dest(void);

    // loop among registered cyphers, check matching block
    static unique_ptr<Header> _get_header(const uint8_t *data, size_t data_len);
    static unique_ptr<Header> _get_header(const string &file_name);

    static HeaderFactory *get_instance(void) {
        if (nullptr == _instance) {
            _instance = new HeaderFactory();
        }

        return _instance;
    }

    static HeaderMap      _header_map;
    static HeaderFactory *_instance;
    static size_t         _max_blk_len;  // the max block length
};


}


#endif //FWT_HEADERFACTORY_HH
