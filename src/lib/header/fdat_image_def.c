#include <string.h>
#include "fdat_image_def.h"


// model table (0xffffffff = model_type unknown to date)
MODEL_TYPE _g_model_type[NUM_MODEL_TYPE] = {
        {0x00000000, "Model Type unknown"},
        {0xffffffff, "DSLR-A560"},
        {0xffffffff, "DSLR-A580"},
        {0x10300202, "SLT-A33"},
        {0xffffffff, "SLT-A35"},
        {0x21030008, "SLT-A37"},
        {0x10300203, "SLT-A55"},
        {0x21030006, "SLT-A57"},
        {0xffffffff, "SLT-A58"},
        {0x12030012, "SLT-A65"},	//10.
        {0x12030011, "SLT-A77"},
        {0x22030010, "SLT-A99"},
        {0xffffffff, "Hasselblad HV"},
        {0x10300206, "NEX-3"},
        {0x11300223, "NEX-C3"},
        {0x21030010, "NEX-F3"},
        {0xffffffff, "NEX-3N"},
        {0x10300205, "NEX-5"},
        {0x12030023, "NEX-5N"},
        {0x22030014, "NEX-5R"},		//20.
        {0x22030020, "NEX-5T"},
        {0x22030018, "NEX-6"},
        {0x12030024, "NEX-7"},
        {0x12030024, "Hasselblad Lunar"},
        {0x10300211, "NEX-VG10"},
        {0xffffffff, "NEX-VG20"},
        {0xffffffff, "NEX-VG30"},
        {0xffffffff, "NEX-VG900"},
        {0x22010015, "NEX-EA50"},
        {0x11010009, "NEX-FS100"},	//30.
        {0x21010061, "NEX-FS700"},
        {0xffffffff, "ILCE-3000"},
        {0xffffffff, "ILCE-5000"},
        {0xffffffff, "ILCE-6000"},
        {0x41030013, "ILCE-7"},
        {0x41030034, "ILCE-7R"},
        {0xffffffff, "SEL-16F28"},
        {0xffffffff, "SEL-20F28"},
        {0x11A08015, "SEL-24F18Z"},
        {0x11A08014, "SEL-30M35"},	//40.
        {0x11A08016, "SEL-50F18"},
        {0xffffffff, "SEL-1018"},
        {0xffffffff, "SEL-P1650"},
        {0xffffffff, "SEL-1670Z"},
        {0x10A08011, "SEL-1855"},
        {0x10A08011, "SEL-P18105G"},
        {0x10A08013, "SEL-18200"},
        {0xffffffff, "SEL-18200LE"},
        {0xffffffff, "SEL-P18200"},
        {0x10A08013, "SEL-55210"},	//50.
        {0xffffffff, "SEL-F35F28Z"},
        {0xffffffff, "SEL-F55F18Z"},
        {0xffffffff, "SEL-F2470Z"},
        {0xffffffff, "SEL-F2870"},
        {0xffffffff, "SEL-F70200G"},
        {0x10A00001, "LA-EA1"},
        {0xffffffff, "LA-EA2"},
        {0xffffffff, "LA-EA3"},
        {0xffffffff, "LA-EA4"},
        {0xffffffff, "DSC-RX1"},	//60.
        {0xffffffff, "DSC-RX1R"},
        {0xffffffff, "DSC-RX10"},
        {0xffffffff, "DSC-RX100"},
        {0xffffffff, "Hasselblad Stellar"},
        {0xffffffff, "DSC-RX100M2"},
        {0x32020080, "DSC-QX10"},
        {0x32020070, "DSC-QX100"},	//67
        {0xffffffff, "ILCE-7S"},
        {0xffffffff, "ILCE-7M2"},
        {0x51030034, "ILCE-7RM2"},  //70
        {0xffffffff, "ILCE-7SM2"},
};

size_t _g_num_model_type = sizeof(_g_model_type)/sizeof(MODEL_TYPE);

void get_model_type(const uint32_t model, MODEL_TYPE *model_type) {
    memset(model_type, 0, sizeof(MODEL_TYPE));

    for (int i = 0; i < _g_num_model_type; ++i) {
        if (model == _g_model_type[i].model) {
            memcpy(model_type, &_g_model_type[i], sizeof(MODEL_TYPE));
        }
    }
}
