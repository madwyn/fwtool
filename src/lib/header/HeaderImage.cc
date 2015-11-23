#include <string.h>
#include "HeaderImage.hh"
#include "../util/print_tool.h"


namespace fw {


bool HeaderImage::valid(const uint8_t *const data) {
    const FDAT_IMAGE_HEADER * header = (const FDAT_IMAGE_HEADER *)data;
    return (0 == memcmp(header->magic, FDAT_IMAGE_MAGIC, FDAT_IMAGE_MAGIC_LEN));
}


}
