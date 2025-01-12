#pragma once

#include <GL/glut.h>
#include "load_texture.h"

//! ter um quadric vazio e fazer bind nas texturas uma vez só (e ir passando)

const GLuint INVALID_TEXTURE = (GLuint) -1;

// coisas de textura
GLuint rugged_tex_id;
GLuint rusted_tex_id;
GLuint golden_tex_id;
GLuint glass_tex_id;
GLuint metal_tex_id;

GLUquadric* rugged_quadric;
GLUquadric* rusted_quadric;
GLUquadric* golden_quadric;
GLUquadric* glass_quadric;
GLUquadric* sphere_quadric;
GLUquadric* cylinder_quadric;

// Inicializa texturas
void init_textures(void){
    const char* rugged_tex_path = "./assets/texture_rugged_metal.bmp";
    const char* rusted_tex_path = "./assets/texture_rusted_metal.bmp";
    const char* golden_tex_path = "./assets/texture_golden_metal.bmp";
    const char* glass_tex_path  = "./assets/texture_glass.bmp";
    const char* metal_tex_path  = "./assets/metalTexture1.bmp";

    // ver se precisa >
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    // ^ e se mudar de lugar
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    sphere_quadric   = gluNewQuadric();
    cylinder_quadric = gluNewQuadric();
    metal_tex_id     = load_texture(metal_tex_path);
    
    rugged_quadric = gluNewQuadric();
    rugged_tex_id  = load_texture(rugged_tex_path);

    rusted_quadric = gluNewQuadric();
    rusted_tex_id  = load_texture(rusted_tex_path);

    golden_quadric = gluNewQuadric();
    golden_tex_id  = load_texture(golden_tex_path);

    glass_quadric = gluNewQuadric();
    glass_tex_id  = load_texture(glass_tex_path);
}


// funções de desenho básicas

// Função que desenha um cilindro
void draw_cylinder(GLuint tex_id, float diameter, float length) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, true);
    } else {
        gluQuadricTexture(cylinder_quadric, false);
    }
    gluCylinder(cylinder_quadric, diameter, diameter, length, 40.0, length*30.0);
}

// Função que desenha um cone
void draw_cone(GLuint tex_id, float diameter, float length) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, true);
    } else {
        gluQuadricTexture(cylinder_quadric, false);
    }
    gluCylinder(cylinder_quadric, diameter, 0, length, 40.0, length*30.0);
}

// Função que desenha um disco
void draw_disk(GLuint tex_id, float diameterInner, float diameterOuter) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(cylinder_quadric, true);
    } else {
        gluQuadricTexture(cylinder_quadric, false);
    }
    gluDisk(cylinder_quadric, diameterInner, diameterOuter, 40.0, 30.0);
}

// Função que desenha uma esfera
void draw_sphere(GLuint tex_id, float diameter) {
    if (tex_id != INVALID_TEXTURE) {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(sphere_quadric, true);
    } else {
        gluQuadricTexture(sphere_quadric, false);
    }
    gluSphere(sphere_quadric, diameter, 40.0, 40.0);
}

// Função que desenha um cubo
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


// funções específicas do robô

// Função que desenha um bastão com uma luz no final
void draw_rod(float diam_start, float diam_end, float lenght, float radius, int color) {
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, golden_tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluQuadricTexture(golden_quadric, true);
    gluCylinder(golden_quadric, diam_start, diam_end, lenght, 72, 72);
    glTranslatef(0.0f, 0.0f, lenght+radius);
    switch (color) { //! trocar pra ...v e passar a lista direto
        case 1: glColor4f(1.0f, 0.0f, 0.0f, 0.7f); break;
        case 2: glColor4f(0.0f, 1.0f, 0.0f, 0.7f); break;
        case 3: glColor4f(0.0f, 0.0f, 1.0f, 0.7f); break;
        case 4: glColor4f(1.0f, 1.0f, 0.0f, 0.7f); break;
    }
    glBindTexture(GL_TEXTURE_2D, glass_tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluQuadricTexture(glass_quadric, true);
    gluSphere(glass_quadric, radius, 72, 72);
}

// Função que desenha parte da coroa
void draw_crown_portion(float base, float top, float length, float height) {
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, golden_tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-base, 0, 0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-top, length, height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(top, length, height);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(base, 0, 0);
    glEnd();
}

