#ifndef FWT_TYPE_H
#define FWT_TYPE_H

#include <string.h>

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

/**
 * convert string name to corresponding enum when starts with
 */
inline int STRING_TO_ENUM_STARTS(const char *enum_name, const char ** str_arr, int str_num) {
    for (int i = 0; i < str_num; ++ i) {
        if (enum_name == strstr(enum_name, str_arr[i])) {
            return i;
        }
    }

    return -1;
}

/**
 * convert string name to corresponding enum when starts with
 */
inline int STRING_TO_ENUM_CONTAINS(const char *enum_name, const char ** str_arr, int str_num) {
    for (int i = 0; i < str_num; ++ i) {
        if (strstr(enum_name, str_arr[i])) {
            return i;
        }
    }

    return -1;
}

/**
 * convert string name to corresponding enum when matches
 */
inline int STRING_TO_ENUM(const char *enum_name, const char ** str_arr, int str_num) {
    for (int i = 0; i < str_num; ++ i) {
        if (!strcmp(str_arr[i], enum_name)) {
            return i;
        }
    }

    return -1;
}


#endif //FWT_TYPE_H
