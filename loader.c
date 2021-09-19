/*
 * Author: Matheus Amorim Constancio
 *
 * A simple .obj loader and render in OpenGL
 * 
 * Rotate the model with: a, d, w, s
 * Zoom in: i
 * Zoom out: o
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "objl.h"

Obj model;
GLfloat x_rotate, y_rotate, z_rotate, zoom = -40.5;

void init()
{
    GLfloat ambient_light[4] = {0.2, 0.2, 0.2, 0.0}; 
    GLfloat diffused_light[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat specular_light[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[4] = {0.5, 1.0, 1.0, 1.0};
    GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0}; 
    GLint material_spec = 10;

    glClearColor(0.0, 0.45, 1.0, 0.0);

    glShadeModel(GL_FLAT);

    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMateriali(GL_FRONT, GL_SHININESS, material_spec);

    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, ambient_light);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffused_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    Obj_v v1, v2, v3, v4;
    Obj_vn normal;
    Obj_f face = model->faces;
    
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, zoom);
    glRotatef(x_rotate, 1.0, 0.0, 0.0);
    glRotatef(y_rotate, 0.0, 1.0, 0.0);
    glRotatef(z_rotate, 0.0, 0.0, 1.0);
    glEnable(GL_NORMALIZE);

    for (int i = 0; i < model->num_f; i++) {
        glBegin(GL_QUADS);

        normal = findvn(model, i + 1);
        if (normal != NULL)
            glNormal3f(normal->vnx, normal->vny, normal->vnz);

        v1 = findv(model, face->vertices[0]);
        v2 = findv(model, face->vertices[1]);
        v3 = findv(model, face->vertices[2]);
        v4 = findv(model, face->vertices[3]);

        glColor3f(0.2, 0.1, 0.6);

        glVertex3f(v1->vx, v1->vy, v1->vz);
        glVertex3f(v2->vx, v2->vy, v2->vz);
        glVertex3f(v3->vx, v3->vy, v3->vz);
        glVertex3f(v4->vx, v4->vy, v4->vz);

        glEnd();

        face = face->next;
    }

    glFlush();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) 
        return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLdouble)x / (GLdouble)y, 10.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        x_rotate = ((int)x_rotate + 5) % 360;
        glutPostRedisplay();
        break;
    case 's':
        x_rotate = ((int)x_rotate - 5) % 360;
        glutPostRedisplay();
        break;
    case 'a':
        y_rotate = ((int)y_rotate + 5) % 360;
        glutPostRedisplay();
        break;
    case 'd':
        y_rotate = ((int)y_rotate - 5) % 360;
        glutPostRedisplay();
        break;
    case 'i':
        zoom += 0.5;
        glutPostRedisplay();
        break;
    case 'o':
        zoom -= 0.5;
        glutPostRedisplay();
        break;
    case 'q':
        unload(model);
        printf("Model unloaded from memory.\n");
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./load <object file>\n");
        return 1;
    }

    model = load(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[1]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
