/*
 * Author: Matheus Amorim Constancio
 *
 * A simple .obj loader and render in OpenGL
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "objl.h"

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glFlush();
}

void render(Obj obj)
{
    Obj_v vertice;
    Obj_vn normal;
    Obj_f face;
    face = obj->faces;
    for (int i = 0; i < obj->num_f; i++) {
        normal = findvn(obj, i + 1);
        float vet_n[] = {normal->vnx, normal->vny, normal->vnz};
        glNormal3fv(vet_n);
        for (int j = 0; j < 4; j++) {
            vertice = findv(obj, face->vertices[j]);
            float vet_v[] = {vertice->vx, vertice->vy, vertice->vz};
            glBegin(GL_QUADS);
            glVertex3fv(vet_v);
            glEnd();
        }
        face = face->next;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    render();
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./load [object file]\n");
        return 1;
    }
    
    Obj model;
    model = load(argv[1]);
    
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mezanino");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
