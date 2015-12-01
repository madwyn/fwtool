#ifndef FWT_FDAT_IMAGE_DEF_H
#define FWT_FDAT_IMAGE_DEF_H


#include <stdint.h>


typedef struct {
    uint32_t    model;
    uint8_t     name[32];
} MODEL_TYPE;

#define NUM_MODEL_TYPE  71

#ifdef __cplusplus
extern "C" {
#endif

void get_model_type(const uint32_t model, MODEL_TYPE *model_type);

#ifdef __cplusplus
}
#endif


#endif //FWT_FDAT_IMAGE_DEF_H
