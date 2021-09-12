#include <stdio.h>
#include <stdlib.h>

#include "objl.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./loader [object file]\n");
        return 1;
    }
    
    Obj model;
    model = load(argv[1]);
    
    system("clear");
    
    printf("Quantidade de vértices: %d\n", model->num_v);
    printf("Quantidade de normais: %d\n", model->num_vn);
    printf("Quantidade de faces: %d\n", model->num_f);
    
    listvn(model);

    return 0;
}
