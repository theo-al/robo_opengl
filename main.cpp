#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "draw.h"
#include "main.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define DEFAULT_FOV 50
#define ESC 27

// coisas de perspectiva
GLfloat view_rot_x = 0;
GLfloat view_rot_y = 0;

// Callback para teclas especiais
void handle_special_keys(int key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
      case GLUT_KEY_UP:    view_rot_x += 6; break;
      case GLUT_KEY_DOWN:  view_rot_x -= 6; break;
      case GLUT_KEY_LEFT:  view_rot_y -= 6; break;
      case GLUT_KEY_RIGHT: view_rot_y += 6; break;
    }
    glutPostRedisplay();
}

// Função callback chamada para fazer o desenho
void handle_redraw(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Inicializa sistema de coordenadas de projeção
    gluPerspective(fov, aspect_ratio, 0.1, 500); // Especifica a projeção perspectiva

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(  0,  0,  200,  // Especifica posição do observador
                0,  30, 0,    // Especifica posição do alvo
                0,  1,  0  ); // Especifica direção cima (como o eixo y)

    // Desenha esfera no fundo/background
    if (mostrar_bola) {
        glPushMatrix();
            glTranslatef(10.0, 0, -80.0f);
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            glutSolidSphere(30.0f, 72, 72);
        glPopMatrix();
    }

    // Aplica rotações (pan)
    glRotatef(view_rot_x, 1, 0, 0);
    glRotatef(view_rot_y, 0, 1, 0);

    // Desenha pescoço (cone)
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
    glTranslatef(0.0f, 37.0f, 0.0f);

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

    // Desenha bastões (cilindros e esferas)
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(75.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 4);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(165.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 3);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(210.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, -7.0f, 0.0f);
        glRotatef(255.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
        draw_rod(1.0f, 0.5f, 25.0f, 1.5, 4);
    glPopMatrix();
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
    glPushMatrix();
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

    // Desenha cabeça (elipsoide transparente)
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

    glutSwapBuffers();
}

// Programa Principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGBA |
                        GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cabeça de Robô");

    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutReshapeFunc(handle_window_resize);
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);

    glutMainLoop();
}

