#define _CRT_SECURE_NO_WARNINGS
//^ não sei praq serve, tirei e não deu nada

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "load_texture.h"
#include "shapes.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define ESC 27


GLuint metal_tex_id;
const char* metal_tex_path = "./assets/metalTexture1.bmp";

bool apply_textures = true;

// coisas da garra
float diameterCylinder = 0.3;
float diameterSphere = 0.4;
float sizeArm = 4.5;
float sizeForearm = 3.0;
float sizeHand = 2.0;
float sizeClampPart = 1.0;
float diameterBase = 2.0;
float heightBase = 0.5;

// coisas de perspectiva(?)
float eye_dist = 20.0;
float viewAngleX = 0.0;
float viewAngleZ = 15.0;

// coisas da garra
float angleArm = 90.0;
float angleForearm = 90.0;
float angleHand = 0.0;
float angleClampZ = 0.0;
float angleClampY = 0.0;


void init_rendering(void) {
    sphere_quadric   = gluNewQuadric();
    cylinder_quadric = gluNewQuadric();

    metal_tex_id = load_texture(metal_tex_path);
}

void handle_special_keys(int key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
        case GLUT_KEY_UP:
            if (viewAngleZ > 0) viewAngleZ -= 3;
	    break;
        case GLUT_KEY_DOWN:
            if (viewAngleZ < 180) viewAngleZ += 3;
	    break;
        case GLUT_KEY_LEFT:
            viewAngleX += 3;
            break;
        case GLUT_KEY_RIGHT:
            viewAngleX -= 3;
            break;
    }
    glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
        case ESC: exit(0);
        case 't': //Use texture or not
            apply_textures ^= 1;
            glutPostRedisplay();
            break;
        case '1': //Increase arm angle
            angleArm += 3;
            if (angleArm >= 360) angleArm = 0;
            glutPostRedisplay();
            break;
        case '2': //Decrease arm angle
            angleArm -= 3;
            if (angleArm <= 0) angleArm = 360;
            glutPostRedisplay();
            break;
        case '3': //Increase forearm angle
            if (angleForearm < 90) angleForearm += 3;
            glutPostRedisplay();
            break;
        case '4': //Decrease forearm angle
            if (angleForearm > -90) angleForearm -= 3;
            glutPostRedisplay();
            break;
        case '5': //Increase clamp angle y axis
            if (angleClampY < 60) angleClampY += 3;
            glutPostRedisplay();
            break;
        case '6': //Decrease clamp angle y axis
            if (angleClampY > 0) angleClampY -= 3;
            glutPostRedisplay();
            break;
    }
}

void handle_window_resize(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
}

void handle_redraw(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    GLfloat eyeX, eyeY, eyeZ;
    eyeX = eye_dist * cos(viewAngleZ*PI / 180) * cos(viewAngleX*PI / 180);
    eyeY = eye_dist * cos(viewAngleZ*PI / 180) * sin(viewAngleX*PI / 180);
    eyeZ = eye_dist * sin(viewAngleZ*PI / 180);
    
    GLuint texture = apply_textures ? metal_tex_id : INVALID_TEXTURE;

    glLoadIdentity(); {
        gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 0, viewAngleZ < 90 ? 1. :-1.);

        //drawing color
        glColor3f(1.0f, 1.0f, 1.0f);

        //draws the base
        drawCylinder(texture, diameterBase, heightBase);
        glTranslatef(0.0f, 0.0f, heightBase);
        drawDisk(texture, diameterCylinder, diameterBase);

        //move to arm referential
        glRotatef(angleArm, 0.0f, 0.0f, 1.0f);

        //draws the arm
        drawCylinder(texture, diameterCylinder, sizeArm);

        //move to forearm referential
        glTranslatef(0.0f, 0.0f, sizeArm + diameterSphere / 5);
        glRotatef(angleForearm, 0.0f, 1.0f, 0.0f);

        //draws the forearm
        drawSphere(texture, diameterSphere);
        glTranslatef(0.0f, 0.0f, diameterSphere / 5);
        drawCylinder(texture, diameterCylinder, sizeForearm);

        //move to clamp referential
        glTranslatef(0.0f, 0.0f, sizeForearm + diameterSphere / 5);
        glRotatef(angleClampZ, 0.0f, 0.0f, 1.0f);

        //draws the clamp sphere
        drawSphere(texture, diameterSphere);
        glTranslatef(0.0f, 0.0f, diameterSphere / 2);
    }

    glPushMatrix(); //draws top part of clamp
        glRotatef(angleClampY + 60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(texture, diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(texture, diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(texture, diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(texture, diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
        drawCone(texture, diameterCylinder / 3, sizeClampPart);
    glPopMatrix();

    glPushMatrix(); //draws bottom part of clamp
        glRotatef(-angleClampY - 60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(texture, diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(texture, diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(texture, diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(texture, diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
        drawCone(texture, diameterCylinder / 3, sizeClampPart);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Garra");

    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);
    glutReshapeFunc(handle_window_resize);

    glutMainLoop();
}

