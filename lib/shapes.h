#include <GL/glut.h>

const GLuint INVALID_TEXTURE = (GLuint) -1;

GLUquadric *sphere_quadric;
GLUquadric *cylinder_quadric;

//! ter um quadric vazio e fazer bind nas texturas uma vez só (e ir passando)
//! aí tirar a maioria dessas globais daqui

void draw_cylinder(GLuint tex_id, float diameter, float length) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluCylinder(cylinder_quadric, diameter, diameter, length, 40.0, length*30.0);
}

void draw_cone(GLuint tex_id, float diameter, float length) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluCylinder(cylinder_quadric, diameter, 0, length, 40.0, length*30.0);
}

void draw_disk(GLuint tex_id, float diameterInner, float diameterOuter) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, 1);
    } else {
        gluQuadricTexture(cylinder_quadric, 0);
    }
    gluDisk(cylinder_quadric, diameterInner, diameterOuter, 40.0, 30.0);
}

void draw_sphere(GLuint tex_id, float diameter) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(sphere_quadric, 1);
    } else {
        gluQuadricTexture(sphere_quadric, 0);
    }
    gluSphere(sphere_quadric, diameter, 40.0, 40.0);
}

void draw_cube(GLuint tex_id, float lenghtX, float lenghtY, float height) {
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS); // Face posterior
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, -height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, -height);
    glEnd();
    glBegin(GL_QUADS); // Face frontal
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, height);
    glEnd();
    glBegin(GL_QUADS); // Face lateral esquerda
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, -height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
    glEnd();
    glBegin(GL_QUADS); // Face lateral direita
        glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, -height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, lenghtY, height);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
    glEnd();
    glBegin(GL_QUADS); // Face superior
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-lenghtX, lenghtY, -height);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-lenghtX, lenghtY, height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(lenghtX, lenghtY, height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(lenghtX, lenghtY, -height);
    glEnd();
    glBegin(GL_QUADS); // Face inferior
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-lenghtX, -lenghtY, -height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(lenghtX, -lenghtY, -height);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(lenghtX, -lenghtY, height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-lenghtX, -lenghtY, height);
    glEnd();
}

