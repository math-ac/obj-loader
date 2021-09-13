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
    
    printf("Number of vertices: %d\n", model->num_v);
    printf("Number of normals: %d\n", model->num_vn);
    printf("Number of faces: %d\n", model->num_f);
    
    return 0;
}
