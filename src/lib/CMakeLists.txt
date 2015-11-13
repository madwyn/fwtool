project(libfwtool)

set(fw_archive_SRCS
        archive/ZipFile.cc
        archive/ZipFile.hh
        archive/HeaderMagic.cc
        archive/HeaderMagic.hh
        archive/FirmwareData.cc
        archive/FirmwareData.hh
        archive/DataChunk.cc
        archive/DataChunk.hh
        archive/FDAT.cc
        archive/FDAT.hh
)

set(fw_crypto_SRCS
        crypto/Cypher.cc
        crypto/Cypher.hh
        crypto/CypherAES.cc
        crypto/CypherAES.hh
        crypto/CypherSHA1.cc
        crypto/CypherSHA1.hh
        crypto/CypherFactory.cc
        crypto/CypherFactory.hh
)

set(libfwtool_SRCS
        pack.cc
        pack.h
        ${fw_archive_SRCS}
        ${fw_crypto_SRCS}
)

include_directories(
        ${libcodemsg_SOURCE_DIR}
        ${libcodemsg_BINARY_DIR}
        ${zlib_SOURCE_DIR}
        ${mbedtls_INCLUDE_DIR}
)

add_library(libfwtool ${libfwtool_SRCS})

# specify the libs to be linked
target_link_libraries(libfwtool
        libcodemsg
        zlibstatic
        minizip
        mbedcrypto
)
