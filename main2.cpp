#define _CRT_SECURE_NO_WARNINGS
//^ não sei praq serve, tirei e não deu nada

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "load_texture.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define ESC 27


const char* filenameTexMetal1 = "./assets/metalTexture1.bmp";

GLuint _textureIdMetal1;
GLuint _textureIdSphere;
GLuint _textureIdCylinder;

GLUquadric *quadSphere;
GLUquadric *quadCylinder;

bool textureOn = true;

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
    quadSphere   = gluNewQuadric();
    quadCylinder = gluNewQuadric();
    _textureIdMetal1 = load_texture(filenameTexMetal1);

    _textureIdCylinder = _textureIdMetal1;
    _textureIdSphere   = _textureIdMetal1;
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
            textureOn = !textureOn;
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

void drawCylinder(float diameter, float lenght) {
    if (textureOn) {
        glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(quadCylinder, 1);
    } else {
        gluQuadricTexture(quadCylinder, 0);
    }

    gluCylinder(quadCylinder, diameter, diameter, lenght, 40.0, lenght*30.0);
}

void drawCone(float diameter, float lenght) {
    if (textureOn) {
        glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(quadCylinder, 1);
    } else {
        gluQuadricTexture(quadCylinder, 0);
    }
    gluCylinder(quadCylinder, diameter, 0, lenght, 40.0, lenght*30.0);
}

void drawDisk(float diameterInner, float diameterOuter) {
    if (textureOn) {
        glBindTexture(GL_TEXTURE_2D, _textureIdCylinder);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(quadCylinder, 1);
    } else {
        gluQuadricTexture(quadCylinder, 0);
    }
    gluDisk(quadCylinder, diameterInner, diameterOuter, 40.0, 30.0);
}

void drawSphere(float diameter) {
    if (textureOn) {
        glBindTexture(GL_TEXTURE_2D, _textureIdSphere);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(quadSphere, 1);
    } else {
        gluQuadricTexture(quadSphere, 0);
    }
    gluSphere(quadSphere, diameter, 40.0, 40.0);
}

void handle_redraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    GLfloat eyeX, eyeY, eyeZ;
    eyeX = eye_dist * cos(viewAngleZ*PI / 180) * cos(viewAngleX*PI / 180);
    eyeY = eye_dist * cos(viewAngleZ*PI / 180) * sin(viewAngleX*PI / 180);
    eyeZ = eye_dist * sin(viewAngleZ*PI / 180);

    glLoadIdentity(); {
        gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 0, viewAngleZ < 90 ? 1. :-1.);

        //drawing color
        glColor3f(1.0f, 1.0f, 1.0f);

        //draws the base
        drawCylinder(diameterBase, heightBase);
        glTranslatef(0.0f, 0.0f, heightBase);
        drawDisk(diameterCylinder, diameterBase);

        //move to arm referential
        glRotatef(angleArm, 0.0f, 0.0f, 1.0f);

        //draws the arm
        drawCylinder(diameterCylinder, sizeArm);

        //move to forearm referential
        glTranslatef(0.0f, 0.0f, sizeArm + diameterSphere / 5);
        glRotatef(angleForearm, 0.0f, 1.0f, 0.0f);

        //draws the forearm
        drawSphere(diameterSphere);
        glTranslatef(0.0f, 0.0f, diameterSphere / 5);
        drawCylinder(diameterCylinder, sizeForearm);

        //move to clamp referential
        glTranslatef(0.0f, 0.0f, sizeForearm + diameterSphere / 5);
        glRotatef(angleClampZ, 0.0f, 0.0f, 1.0f);

        //draws the clamp sphere
        drawSphere(diameterSphere);
        glTranslatef(0.0f, 0.0f, diameterSphere / 2);
    }

    glPushMatrix(); //draws top part of clamp
        glRotatef(angleClampY + 60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
        drawCone(diameterCylinder / 3, sizeClampPart);
    glPopMatrix();

    glPushMatrix(); //draws bottom part of clamp
        glRotatef(-angleClampY - 60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
    
        drawCylinder(diameterCylinder / 3, sizeClampPart);
        glTranslatef(0.0f, 0.0f, sizeClampPart + diameterSphere / 15);
        drawSphere(diameterSphere / 3);
    
        glTranslatef(0.0f, 0.0f, diameterSphere / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
        drawCone(diameterCylinder / 3, sizeClampPart);
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
