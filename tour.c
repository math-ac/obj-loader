/*
 * Author: Matheus Amorim Constancio
 *
 * A tour through a loaded model
 *
 * Move with: a, d, w, s
 * Camera: arrow keys
 * Zoom in: i
 * Zoom out: o
 */

#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "objl.h"

Obj model;
float h_angle = 0.0, v_angle = 0.0, p_aspect;
float x_eye = -3.0, y_eye = 5.0, z_eye = 15.0;
float zoom = 100.0;
float dx = 0.0, dy = 0.0, dz = -1.0;
float r = 0.5, g = 0.1, b = 0.25;
int grid_on = 1;

void init()
{
    float ambient[] = {0.5, 0.5, 0.5, 1.0};
    float mt_specular[] = {0.5, 0.5, 0.5, 1.0};
    int mt_shine = 10;
    float light0[4][4] = {
        {0.1, 0.1, 0.1, 1.0},
        {0.8, 0.8, 0.8, 1.0},
        {1.0, 1.0, 1.0, 1.0},
        {0.0, 0.0, 1.0, 1.0}
    };

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mt_specular);
    glMateriali(GL_FRONT, GL_SHININESS, mt_shine);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);
}
void grid()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);

    for(int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f((float)i, 0.0, -50.0);
        glVertex3f((float)i, 0.0, 50.0);
        glEnd();
    }

    for(int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50.0, 0.0, (float)i);
        glVertex3f(50.0, 0.0, (float)i);
        glEnd();
    }

    glPopMatrix();
}
void display()
{
    Obj_v v1, v2, v3, v4;
    Obj_vn normal;
    Obj_f face = model->faces;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(r, g, b);

    for (int i = 0; i < model->num_f; i++) {
        glBegin(GL_POLYGON);

        normal = findvn(model, i + 1);
        if (normal != NULL)
            glNormal3f(normal->vnx, normal->vny, normal->vnz);

        v1 = findv(model, face->vertices[0]);
        v2 = findv(model, face->vertices[1]);
        v3 = findv(model, face->vertices[2]);
        v4 = findv(model, face->vertices[3]);

        glVertex3f(v1->vx, v1->vy, v1->vz);
        glVertex3f(v2->vx, v2->vy, v2->vz);
        glVertex3f(v3->vx, v3->vy, v3->vz);
        glVertex3f(v4->vx, v4->vy, v4->vz);

        glEnd();

        face = face->next;
    }

    if (grid_on)
        grid();

    glutSwapBuffers();
}

void visual_parameters()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(zoom, p_aspect, 0.001, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(x_eye, y_eye, z_eye,
              x_eye + dx, y_eye + dy, z_eye + dz,
              0.0, 1.0, 0.0);
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    p_aspect = (float)w / (float)h;

    visual_parameters();
}

void mouse(int button, int state, int x, int y)
{
    if (button == 4) {
        zoom += 0.5;
        printf("scroll out\t-> zoom: %f\n", zoom);
    } else if (button == 3) {
        zoom -= 0.5;
        printf("scroll in\t-> zoom: %f\n", zoom);
    }

    visual_parameters();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    srand(time(0));
    float speed = 0.25;

    switch (key) {
    case 'd':
        x_eye += -dz * speed;
        z_eye += dx * speed;
        printf("d\t-> x: %f |\ty: %f |\tz: %f\n", x_eye, y_eye, z_eye);
        break;
    case 'a':
        x_eye -= -dz * speed;
        z_eye -= dx * speed;
        printf("a\t-> x: %f |\ty: %f |\tz: %f\n", x_eye, y_eye, z_eye);
        break;
    case 'w':
        x_eye += dx * speed;
        y_eye += dy * speed;
        z_eye += dz * speed;
        printf("w\t-> x: %f |\ty: %f |\tz: %f\n", x_eye, y_eye, z_eye);
        break;
    case 's':
        x_eye -= dx * speed;
        y_eye -= dy * speed;
        z_eye -= dz * speed;
        printf("s\t-> x: %f |\ty: %f |\tz: %f\n", x_eye, y_eye, z_eye);
        break;
    case 'i':
        zoom -= 0.5;
        printf("i\t-> zoom: %f\n", zoom);
        break;
    case 'o':
        zoom += 0.5;
        printf("o\t-> zoom: %f\n", zoom);
        break;
    case 'g':
        grid_on = !grid_on;
        if (grid_on)
            printf("Grid on\n");
        else
            printf("Grid off\n");
        break;
    case 'c':
        r = (float)rand() / (float)RAND_MAX;
        g = (float)rand() / (float)RAND_MAX;
        b = (float)rand() / (float)RAND_MAX;
        printf("c->\t red: %f |\tgreen: %f |\tred: %f\n", r, g, b);
        break;
    case 'q':
        unload(model);
        printf("Model unloaded from memory.\n");
        exit(0);
        break;
    default:
        break;
    }

    visual_parameters();
    glutPostRedisplay();
}

void special_keyboard(int key, int xx, int yy)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        h_angle -= 0.05;
        dx = sin(h_angle);
        dz = -cos(h_angle);
        printf("left\t-> dx: %f |\tdy: %f |\tdz: %f |\th_angle: %f\n", dx, dy, dz, h_angle);
        break;
    case GLUT_KEY_RIGHT:
        h_angle += 0.05;
        dx = sin(h_angle);
        dz = -cos(h_angle);
        printf("right\t-> dx: %f |\tdy: %f |\tdz: %f |\th_angle: %f\n", dx, dy, dz, h_angle);
        break;
    case GLUT_KEY_UP:
        if (v_angle > 1.0)
            break;
        v_angle += 0.05;
        dy = sin(v_angle);
        printf("up\t-> dx: %f |\tdy: %f |\tdz: %f |\tv_angle: %f\n", dx, dy, dz, v_angle);
        break;
    case GLUT_KEY_DOWN:
        if (v_angle < -1.0)
            break;
        v_angle -= 0.05;
        dy = sin(v_angle);
        printf("down\t-> dx: %f |\tdy: %f |\tdz: %f |\tv_angle: %f\n", dx, dy, dz, v_angle);
        break;
    }

    visual_parameters();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./tour <object file>\n");
        return 1;
    }

    model = load(argv[1]);

    system("clear");
    printf("Model loaded with --------------------\n");
    printf("Vertices:\t%d\n", model->num_v);
    printf("Normals:\t%d\n", model->num_vn);
    printf("Faces:\t\t%d\n", model->num_f);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 350);
    glutCreateWindow(argv[1]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    init();
    glutMainLoop();
}
