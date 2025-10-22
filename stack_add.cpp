#include <math.h>
#include <stdio.h>
#include <cassert>
#include "stack_add.h"


bool IsNAN(type_stack n) {

     return (n != n);

}

bool ComparisonWithZero(type_stack n) {

    return (fabs(n) <= SMALL_CONST);
}

bool CompareSuccess(type_stack n1, type_stack n2) {

    return ComparisonWithZero(n1 - n2);
}

size_t Getline(char** buff ,size_t size_buff) {

    assert(buff != NULL);

    *buff = (char*)calloc(size_buff, sizeof(char));

    assert(*buff != NULL);

    int c = getchar();
    size_t index = 0;

    while ((c != '\n')) {

           if (size_buff == 0) {

                char* add_buff = (char*)realloc(buff, 2 * SIZE_BUFF * sizeof(char));

                if (add_buff == NULL) {

                    free(*buff);
                    return NULL;

                }

                *buff = add_buff;
                size_buff = SIZE_BUFF;

           }

           *((*buff) + index) = c;
           size_buff--;

           c = getchar();
           index++;

    }

    *((*buff) + index) = '\0';

    return index;

}

bool El_1_More_El_2(type_stack n1, type_stack n2) {
    return (n1 - n2) > SMALL_CONST;
}

bool El_1_Less_El_2(type_stack n1, type_stack n2) {
    return (n2 - n1) > SMALL_CONST;
}
