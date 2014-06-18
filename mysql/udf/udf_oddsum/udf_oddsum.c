#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

my_bool oddsum_init(UDF_INIT *init, UDF_ARGS *args, char *message) {

    if (args->arg_count != 1 || args->arg_type[0] != INT_RESULT) {
        return 1;
    }

    init->ptr = (char *)(malloc(sizeof(longlong)));
    bzero((void*)init->ptr, sizeof(longlong));
    return 0;
}

void oddsum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
    if (!args->args[0])
        return;

    longlong new_value= *((longlong*)args->args[0]);

    if (new_value % 2) {
        longlong *current_sum= (longlong *)initid->ptr;
        *current_sum+= new_value;
    }
}

void oddsum_clear(UDF_INIT* initid, char* is_null __attribute__((unused)),
    char* message __attribute__((unused))) { 
    bzero((void*)initid->ptr, sizeof(longlong));
}

void oddsum_deinit(UDF_INIT *init) {
    if (init->ptr) {
        free(init->ptr);
    }
}

longlong oddsum(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)),
        char* is_null, char* error __attribute__((unused))) {
    return *(longlong *)initid->ptr;
}

