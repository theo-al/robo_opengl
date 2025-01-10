#include <GL/glut.h>

const GLuint INVALID_TEXTURE = (GLuint) -1;

GLUquadric *sphere_quadric;
GLUquadric *cylinder_quadric;

//! ter um quadric vazio e fazer bind nas texturas uma vez só (e ir passando)
//! aí tirar a maioria dessas globais daqui

void drawCylinder(GLuint texture, float diameter, float length) {
    if (texture != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluCylinder(cylinder_quadric, diameter, diameter, length, 40.0, length*30.0);
}

void drawCone(GLuint texture, float diameter, float length) {
    if (texture != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluCylinder(cylinder_quadric, diameter, 0, length, 40.0, length*30.0);
}

void drawDisk(GLuint texture, float diameterInner, float diameterOuter) {
    if (texture != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluDisk(cylinder_quadric, diameterInner, diameterOuter, 40.0, 30.0);
}

void drawSphere(GLuint texture, float diameter) {
    if (texture != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(sphere_quadric, 1);
    } else {
        gluQuadricTexture(sphere_quadric, 0);
    }
    gluSphere(sphere_quadric, diameter, 40.0, 40.0);
}

