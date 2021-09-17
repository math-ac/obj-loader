/*
 * Author: Matheus Amorim Constancio
 *
 * A simple .obj loader and render in OpenGL
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "objl.h"

Obj model;
GLfloat xRotated, yRotated, zRotated;

void init()
{
    glClearColor(0.0, 0.45, 1.0, 0.0);
}

void render()
{
    Obj_v v1, v2, v3, v4;
    Obj_vn normal;
    Obj_f face;
    face = model->faces;
    
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    for (int i = 0; i < model->num_f; i++) {
        glBegin(GL_QUADS);
        
        normal = findvn(model, i + 1);
        if (normal != NULL)
            glNormal3f(normal->vnx, normal->vny, normal->vnz);
        
        v1 = findv(model, face->vertices[0]);
        v2 = findv(model, face->vertices[1]);
        v3 = findv(model, face->vertices[2]);
        v4 = findv(model, face->vertices[3]);
        
        glColor3f(0.6, 0.7, 0.2);
        
        glVertex3f(v1->vx, v1->vy, v1->vz);
        glVertex3f(v2->vx, v2->vy, v2->vz);
        glVertex3f(v3->vx, v3->vy, v3->vz);
        glVertex3f(v4->vx, v4->vy, v4->vz);
        
        glEnd();

        face = face->next;
    }
    //glEnd();
    glFlush();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) 
        return;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,(GLdouble)x /(GLdouble)y, 10.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void animation(void)
{
    yRotated += 0.01;
    xRotated += 0.02;
    render();
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./load <object file>\n");
        return 1;
    }
    
    model = load(argv[1]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[1]);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);
    //glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
