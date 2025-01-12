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

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    
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
// Função que desenha um cone de cabeça pra baixo
void draw_inverted_cone(GLuint tex_id, float diameter, float height) {
    glPushMatrix();
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        draw_cone(tex_id, diameter, height);
    glPopMatrix();
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

// Função para desenhar o pescoço do robô
void draw_neck() { //! usar draw_cone(), aceitar argumentos
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
        glBindTexture(GL_TEXTURE_2D, rugged_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(rugged_quadric, true);
        gluCylinder(rugged_quadric, 10.0f, 7.5f, 21.5f, 72, 72);
        glTranslatef(0.0f, 0.0f, 21.5f);

        glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, rusted_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(rusted_quadric, true);
        gluCylinder(rusted_quadric, 7.5f, 2.0f, 17.0f, 72, 72);
    glPopMatrix();
}

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

// Função para desenhar as joiaszinhas no pescoço do robô
void draw_necklace() { //! aceitar argumentos
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    //! fazer for (+=90)
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(210.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 1);
    glPopMatrix();

    //! fazer for (+=90)
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 4);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(165.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 3);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(255.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 4);
    glPopMatrix();

    //! fazer for (+=45)?
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(300.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(345.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 3);
    glPopMatrix();
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

// Função pra desenhar a coroinha no topo da cabeça do robô
void draw_crown() { //! aceitar argumentos
    // Desenha a base da coroa
    glPushMatrix(); //! usar alguma coisa melhorzinha
        glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, rusted_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0f, 0.0f, 3.0f);
        gluCylinder(rusted_quadric, 0.1f, 10.0f, 2.0f, 72, 72);
        glTranslatef(0.0f, 0.0f, 2.0f);
        glBindTexture(GL_TEXTURE_2D, golden_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(golden_quadric, true);
        gluDisk(golden_quadric, 0.0f, 10.0f, 72, 72);
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glPopMatrix();

    // Desenha as partes da coroa
    //! usar for (+=45)
    glPushMatrix();
        glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(165.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(210.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(255.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(300.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
    glPushMatrix();
        glRotatef(345.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 5.0f, 9.0f);
        draw_crown_portion(2.0f, 5.0f, 6.0f, 5.0f);
    glPopMatrix();
}

// Função pra desenhar a cabeça toda do robô
void draw_head() {
    // Desenha haste para os olhos (paralelepipedo)
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    draw_cube(golden_tex_id, 30.0f, 3.0f, 1.5f);

    // Desenha olhos (esferas)
    glColor4f(1.0f, 1.0f, 0.3f, 0.8f);
    glPushMatrix();
        glTranslatef(-25.0, 0, 2.0);
        glBindTexture(GL_TEXTURE_2D, glass_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(glass_quadric, true);
        gluSphere(glass_quadric, 3.0f, 72, 72);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(25.0, 0, 2.0);
        glBindTexture(GL_TEXTURE_2D, glass_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(glass_quadric, true);
        gluSphere(glass_quadric, 3.0f, 72, 72);
    glPopMatrix();

    // Desenha bastões (cilindros e esferas) do pescoço
    draw_necklace();

    // Desenha bastões (cilindros e esferas) das antenas
    glPushMatrix();
        glTranslatef(15.0f, 2.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 5.0f, 1.5, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-15.0f, 2.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 5.0f, 1.5, 4);
    glPopMatrix();

    // Desenha coroa
    draw_crown();

    // Desenha capacete (elipsoide transparente)
    glColor4f(0.4f, 0.4f, 0.4f, 0.5f);
    glEnable(GL_CULL_FACE);
    glPushMatrix();
        glScalef(1.0f, 0.4f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, glass_tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluQuadricTexture(glass_quadric, true);
        gluSphere(glass_quadric, 40.0f, 72, 72);
    glPopMatrix();
    glDisable(GL_CULL_FACE);
}

void draw_arm(float arm_diameter, float joint_diameter, float arm_length,
              float forearm_length, float forearm_angle) {
    glColor3f(.5,.5,.5); //draws the arm
        draw_cylinder(rugged_tex_id, arm_diameter, arm_length);
    glColor3f(1, 1, 1);
        
    //move to forearm referential
    glTranslatef(0.0f, 0.0f, arm_length + joint_diameter / 5);
    glRotatef(forearm_angle, 0.0f, 1.0f, 0.0f);
    
    //draws the elbow
    draw_sphere(metal_tex_id, joint_diameter);

    glColor3f(.5,.5,.5); //draws the forearm
        glTranslatef(0.0f, 0.0f, joint_diameter / 5);
        draw_cylinder(rugged_tex_id, arm_diameter, forearm_length);
    glColor3f(1, 1, 1);
}

void draw_clamp(float joint_diameter,
                float finger_diameter,
                float finger_length,
                float clamp_y_angle) {
    //draws the clamp sphere (joint)
    draw_sphere(metal_tex_id, joint_diameter);

    //move to finger referential
    glTranslatef(0.0f, 0.0f, joint_diameter / 2);

    glColor3f(.9,.3,.3);
    glPushMatrix(); //draws top finger of clamp
        glRotatef(clamp_y_angle + 60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cylinder(metal_tex_id, finger_diameter, finger_length);

        glTranslatef(0.0f, 0.0f, finger_length + joint_diameter / 15);
        draw_sphere(metal_tex_id, joint_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, joint_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cylinder(metal_tex_id, finger_diameter, finger_length);

        glTranslatef(0.0f, 0.0f, finger_length + joint_diameter / 15);
        draw_sphere(metal_tex_id, joint_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, joint_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cone(metal_tex_id, finger_diameter, finger_length);
    glPopMatrix();

    glPushMatrix(); //draws bottom finger of clamp
        glRotatef(-(clamp_y_angle + 60), 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cylinder(metal_tex_id, finger_diameter, finger_length);

        glTranslatef(0.0f, 0.0f, finger_length + joint_diameter / 15);
        draw_sphere(metal_tex_id, joint_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, joint_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cylinder(metal_tex_id, finger_diameter, finger_length);

        glTranslatef(0.0f, 0.0f, finger_length + joint_diameter / 15);
        draw_sphere(metal_tex_id, joint_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, joint_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cone(metal_tex_id, finger_diameter, finger_length);
    glPopMatrix();
    glColor3f(1,1,1);
}

void draw_whole_arm(float arm_diameter, float joint_diameter, float arm_length,
                    float forearm_length, float forearm_angle,
                    float clamp_y_angle, float clamp_z_angle) {
    // Desenha braço
    draw_arm(arm_diameter, joint_diameter, arm_length, forearm_length, forearm_angle);

    // Desenha garra
    glTranslatef(0.0f, 0.0f, forearm_length + joint_diameter / 5);
    glRotatef(clamp_z_angle, 0.0f, 0.0f, 1.0f);
    
    draw_clamp(joint_diameter, arm_diameter/3, forearm_length/3, clamp_y_angle);
}

