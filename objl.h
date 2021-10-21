#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Obj *Obj;
typedef struct Obj_v *Obj_v;
typedef struct Obj_vn *Obj_vn;
typedef struct Obj_f *Obj_f;


struct Obj {
    unsigned int num_v;
    unsigned int num_vn;
    unsigned int num_f;
    Obj_v vertices;
    Obj_vn normals;
    Obj_f faces;
};

struct Obj_v {
    unsigned int index;
    float vx;
    float vy;
    float vz;
    Obj_v next;
};

struct Obj_vn {
    unsigned int index;
    float vnx;
    float vny;
    float vnz;
    Obj_vn next;
};

struct Obj_f {
    unsigned int index;
    unsigned int vertices[4];
    unsigned int normals[4];
    Obj_f next;
};

Obj load(char *file);
void unload(Obj obj);
void addv(Obj obj, FILE *p);
void addvn(Obj obj, FILE *p);
void addf(Obj obj, FILE *p);
void rmv(Obj obj);
void rmvn(Obj obj);
void rmf(Obj obj);
void listv(Obj obj);
void listvn(Obj obj);
void listf(Obj obj);
Obj_v findv(Obj obj, unsigned int n);
Obj_vn findvn(Obj obj, unsigned int n);
Obj_f findf(Obj obj, unsigned int n);
