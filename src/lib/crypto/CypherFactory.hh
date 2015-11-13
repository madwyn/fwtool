#ifndef FWT_CYPHERFACTORY_HH
#define FWT_CYPHERFACTORY_HH

#include <map>
#include <string>
#include <memory>

#include "Cypher.hh"
#include "../util/print_tool.h"

namespace fw {


using std::map;
using std::string;
using std::unique_ptr;

typedef map<ENC_METHOD, Cypher *> CypherMap;

class CypherFactory {
public:
    static unique_ptr<Cypher> get(const string &file_name) {
        return get_instance()->_get_cypher(file_name);
    }

    static unique_ptr<Cypher> get(const uint8_t *buf, size_t buf_len) {
        return get_instance()->_get_cypher(buf, buf_len);
    }

    ~CypherFactory() {
        _dest();
    }

    static size_t max_sec_len;

private:
    CypherFactory() {_init();}

    void _init(void);
    void _dest(void);

    // loop among registered cyphers, check matching block
    static unique_ptr<Cypher> _get_cypher(const uint8_t *buf, size_t buf_len);
    static unique_ptr<Cypher> _get_cypher(const string &file_name);

    static CypherFactory *get_instance(void) {
        if (nullptr == _instance) {
            _instance = new CypherFactory();
        }

        return _instance;
    }

    static CypherMap      _cypher_map;
    static CypherFactory *_instance;
};

}



#endif //FWT_CYPHERFACTORY_HH
