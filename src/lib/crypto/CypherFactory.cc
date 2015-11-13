#include "CypherFactory.hh"

#include "CypherAES.hh"
#include "CypherSHA1.hh"
#include "../archive/FDAT.hh"

namespace fw {

void CypherFactory::_init(void) {
    _cypher_map[ENC_AES]  = new CypherAES();
    _cypher_map[ENC_SHA1] = new CypherSHA1();

    max_blk_len = 0;

    for (auto const it : _cypher_map) {
        if (it.second->blk_len() > max_blk_len) {
            max_blk_len = it.second->blk_len();
        }
    }
}

void CypherFactory::_dest(void) {
    for (auto it : _cypher_map) {
        delete it.second;
    }

    _cypher_map.clear();
    delete _instance;
}

unique_ptr<Cypher> CypherFactory::_get_cypher(const uint8_t *data, size_t data_len) {
    size_t   buf_len = 0;
    uint8_t *buf     = nullptr;

    for (auto const it : _cypher_map) {
        buf_len = it.second->blk_len();
        buf = (uint8_t *)malloc(buf_len);
        if (nullptr != buf) {
            memcpy(buf, data, buf_len);

            // decode the message
            if (MSG_OK == it.second->dec(data, buf_len, buf)) {
                // verify the decrypted header
                if (fw::FDAT::valid(buf)) {
                    // create the instance
                    return it.second->create();
                }
            }

            free(buf);
        }
    }

    return nullptr;
}


unique_ptr<Cypher> CypherFactory::_get_cypher(const string &file_name) {
    unique_ptr<Cypher> cypher = nullptr;

    FILE *file = fopen(file_name.c_str(), "rb");

    if (nullptr != file) {
        // read head
        uint8_t *buf = (uint8_t *)malloc(max_blk_len);

        // the actual length
        size_t data_len = fread(buf, 1, max_blk_len, file);

        // reading OK
        if (!ferror(file)) {
            // read block length amount of data
            if (data_len == max_blk_len) {
                cypher = _get_cypher(buf, data_len);
            }
        }

        free(buf);
        fclose(file);
    }

    return cypher;
}


CypherMap      CypherFactory::_cypher_map;
CypherFactory *CypherFactory::_instance = nullptr;
size_t         CypherFactory::max_blk_len = 0;


}
