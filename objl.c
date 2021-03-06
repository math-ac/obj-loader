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
    model->num_v = 0;
    model->num_vn = 0;
    model->num_f = 0;
    
    while(1) {
        char aux[128];
        int flag = fscanf(p, "%s", aux);
        
        if (flag == EOF)
            break;
        else if (strcmp(aux, "v") == 0)
            addv(model, p);
        else if (strcmp(aux, "vn") == 0)
            addvn(model, p);
        else if (strcmp(aux, "f") == 0)
            addf(model, p);
    }
    
    fclose(p);
    return model;
}

void unload(Obj obj)
{
    rmv(obj);
    rmvn(obj);
    rmf(obj);
    free(obj);
}

void addv(Obj obj, FILE *p)
{
    float xtemp = 0., ytemp = 0., ztemp = 0.;
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

void addvn(Obj obj, FILE *p)
{
    float xtemp = 0., ytemp = 0., ztemp = 0.;
    Obj_vn normal, aux;
    normal = malloc(sizeof(struct Obj_vn));
    obj->num_vn++;
    
    fscanf(p, "%f %f %f\n", &xtemp, &ytemp, &ztemp);
    normal->index = obj->num_vn;
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

void addf(Obj obj, FILE *p)
{
    unsigned int vtemp[4], ntemp[4];
    Obj_f face, aux;
    face = malloc(sizeof(struct Obj_f));
    obj->num_f++;
    
    for (int i = 0; i < 4; i++)
        fscanf(p, "%d//%d", &vtemp[i], &ntemp[i]);
    face->index = obj->num_f;
    for (int i = 0; i < 4; i++)
        face->vertices[i] = vtemp[i];
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

void rmv(Obj obj)
{
    Obj_v rm = obj->vertices;
    Obj_v aux = rm->next;
    
    while (rm != NULL) {
        free(rm);
        rm = aux;
        if (aux != NULL)
            aux = aux->next;
    }
    
    return;
}

void rmvn(Obj obj)
{
    Obj_vn rm = obj->normals;
    Obj_vn aux = rm->next;
    
    while (rm != NULL) {
        free(rm);
        rm = aux;
        if (aux != NULL)
            aux = aux->next;
    }
    
    return;
}

void rmf(Obj obj)
{
    Obj_f rm = obj->faces;
    Obj_f aux = rm->next;
    
    while (rm != NULL) {
        free(rm);
        rm = aux;
        if (aux != NULL)
            aux = aux->next;
    }
    
    return;
}

void listv(Obj obj)
{
    printf("Vertices-----\n");
    Obj_v aux = obj->vertices;
    for (int i = 0; i < obj->num_v; i++) {
        printf("Vertex id: %d\n", aux->index);
        printf("x: %f\t| y: %f\t| z: %f\n", aux->vx, aux->vy, aux->vz);
    aux = aux->next;
    }
}

void listvn(Obj obj)
{
    printf("Normals-------\n");
    Obj_vn aux = obj->normals;
    for (int i = 0; i < obj->num_vn; i++) {
        printf("Normal id: %d\n", aux->index);
        printf("x: %f\t| y: %f\t| z: %f\n", aux->vnx, aux->vny, aux->vnz);
    aux = aux->next;
    }
}

void listf(Obj obj)
{
    printf("Faces-------\n");
    Obj_f aux = obj->faces;
    for (int i = 0; i < obj->num_f; i++) {
        printf("Face id: %d\n", aux->index);
        for (int j = 0; j < 4; j++)
            printf("v: %d\t| vn: %d\n", aux->vertices[j], aux->normals[j]);
    aux = aux->next;
    }
}

Obj_v findv(Obj obj, unsigned int n)
{
    Obj_v aux;
    aux = obj->vertices;
    for (int i = 0; i < obj->num_v; i++) {
        if (aux->index == n)
            return aux;
        aux = aux->next;
    }
    
    return NULL;
}

Obj_vn findvn(Obj obj, unsigned int n)
{
    Obj_vn aux;
    aux = obj->normals;
    for (int i = 0; i < obj->num_vn; i++) {
        if (aux->index == n)
            return aux;
        aux = aux->next;
    }
    
    return NULL;
}

Obj_f findf(Obj obj, unsigned int n)
{
    Obj_f aux;
    aux = obj->faces;
    for (int i = 0; i < obj->num_vn; i++) {
        if (aux->index == n)
            return aux;
        aux = aux->next;
    }
    
    return NULL;
}

