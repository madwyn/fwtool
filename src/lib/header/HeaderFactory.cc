#include "HeaderFactory.hh"
#include "Header1st.hh"
#include "Header2nd.hh"
#include "Header3rd.hh"


namespace fw {


void HeaderFactory::_init(void) {
    _header_map[GEN_1ST] = new Header1st();
    _header_map[GEN_2ND] = new Header2nd();
    _header_map[GEN_3RD] = new Header3rd();

    _max_blk_len = 0;

    for (auto const it : _header_map) {
        if (it.second->get_blk_len() > _max_blk_len) {
            _max_blk_len = it.second->get_blk_len();
        }
    }
}


void HeaderFactory::_dest(void) {
    for (auto it : _header_map) {
        delete it.second;
    }

    _header_map.clear();
    delete _instance;
}


unique_ptr<Header> HeaderFactory::_get_header(const uint8_t *data, size_t data_len) {
    for (auto const it : _header_map) {
        if (MSG_OK == it.second->valid(data, data_len)) {
            // create the instance
            return it.second->create();
        }
    }

    return nullptr;
}


unique_ptr<Header> HeaderFactory::_get_header(const string &file_name) {
    unique_ptr<Header> header = nullptr;

    FILE *file = fopen(file_name.c_str(), "rb");

    if (nullptr != file) {
        // read head
        uint8_t *buf = (uint8_t *)malloc(_max_blk_len);

        // the actual length
        size_t data_len = fread(buf, 1, _max_blk_len, file);

        // reading OK
        if (!ferror(file)) {
            // read block length amount of data
            if (data_len == _max_blk_len) {
                header = _get_header(buf, data_len);
            }
        } else {
            printf("can not read file\n");
        }

        free(buf);
        fclose(file);
    }

    return header;
}


HeaderMap      HeaderFactory::_header_map;
HeaderFactory *HeaderFactory::_instance   = nullptr;
size_t         HeaderFactory::_max_blk_len = 0;


}
