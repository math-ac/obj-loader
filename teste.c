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
    
    printf("Teste das faces-------\n");
    Obj_f leitor = model->faces;
    for (int i = 0; i < model->num_f; i++) {
        printf("id da face: %d\n", leitor->index);
        for (int j = 0; j < 4; j++)
            printf("v: %d \t| vt: %d \t| vn: %d\n", leitor->vertices[j], leitor->textures[j], leitor->normals[j]);
    leitor = leitor->next;
    }

    return 0;
}
