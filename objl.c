#include "objl.h"

Obj load(char *file)
{
    FILE *p;
    p = fopen(file, "r");
    
    if (p == NULL) {
        printf("Could not open %s\n", file);
        exit(1);
    }
    
    Obj model;
    model = malloc(sizeof(struct Obj));
    model->vertices = NULL;
    model->normals = NULL;
    model->faces = NULL;
    
    while(1) {
        char aux[128];
        int flag = fscanf(p, "%s", aux);
        
        if (flag == EOF)
            break;
        else if (strcmp(aux, "v") == 0)
            addv(p, model);
        else if (strcmp(aux, "vn") == 0)
            addvn(p, model);
        else if (strcmp(aux, "f") == 0)
            addf(p, model);
    }
    
    fclose(p);
    return model;
}

void unload(Obj model);

void addv(FILE *p, Obj obj)
{
    float xtemp, ytemp, ztemp;
    Obj_v vertex, aux;
    vertex = malloc(sizeof(struct Obj_v));
    obj->num_v++;
    
    fscanf(p, "%f %f %f\n", &xtemp, &ytemp, &ztemp);
    vertex->index = obj->num_v;
    vertex->vx = xtemp;
    vertex->vy = ytemp;
    vertex->vz = ztemp;
    vertex->next = NULL;
    
    aux = obj->vertices;
    if (aux == NULL) {
        obj->vertices = vertex;
    } else {
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = vertex;
    }
}

void addvn(FILE *p, Obj obj)
{
    float xtemp, ytemp, ztemp;
    Obj_vn normal, aux;
    normal = malloc(sizeof(struct Obj_vn));
    obj->num_vn++;
    
    fscanf(p, "%f %f %f\n", &xtemp, &ytemp, &ztemp);
    normal->index = obj->num_v;
    normal->vnx = xtemp;
    normal->vny = ytemp;
    normal->vnz = ztemp;
    normal->next = NULL;
    
    aux = obj->normals;
    if (aux == NULL) {
        obj->normals = normal;
    } else {
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = normal;
    }
}

void addf(FILE *p, Obj obj)
{
    unsigned int vtemp[4], ttemp[4], ntemp[4];
    Obj_f face, aux;
    face = malloc(sizeof(struct Obj_f));
    obj->num_f++;
    
    for (int i = 0; i < 4; i++)
        fscanf(p, "%d/%d/%d", &vtemp[i], &ttemp[i], &ntemp[i]);
    face->index = obj->num_f;
    for (int i = 0; i < 4; i++)
        face->vertices[i] = vtemp[i];
    for (int i = 0; i < 4; i++)
        face->textures[i] = ttemp[i];
    for (int i = 0; i < 4; i++)
        face->normals[i] = ntemp[i];
    face->next = NULL;
    
    aux = obj->faces;
    if (aux == NULL) {
        obj->faces = face;
    } else {
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = face;
    }
}
