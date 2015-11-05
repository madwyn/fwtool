#ifndef FWT_PACK_H
#define FWT_PACK_H

#ifdef __cplusplus
extern "C" {
#endif

int
unpack(const char *const file_input, const char *const dir_output);

const char *
get_last_err(void);

#ifdef __cplusplus
}
#endif

#endif //FWT_PACK_H
