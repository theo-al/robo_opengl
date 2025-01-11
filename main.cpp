#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "load_texture.h"
#include "shapes.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define ESC 27


const char* rugged_tex_path = "./assets/texture_rugged_metal.bmp";
const char* rusted_tex_path = "./assets/texture_rusted_metal.bmp";
const char* golden_tex_path = "./assets/texture_golden_metal.bmp";
const char* glass_tex_path  = "./assets/texture_glass.bmp";
const char* metal_tex_path  = "./assets/metalTexture1.bmp";

GLuint rugged_tex_id;
GLuint rusted_tex_id;
GLuint golden_tex_id;
GLuint glass_tex_id;
GLuint metal_tex_id;

GLUquadric* rugged_quadric;
GLUquadric* rusted_quadric;
GLUquadric* golden_quadric;
GLUquadric* glass_quadric;

GLfloat angle = 45;
GLfloat rot_x = 0;
GLfloat rot_y = 0;
GLfloat aspect_ratio;

int fundo = 0;


// Função callback chamada para gerenciar eventos do mouse
void handle_mouse(int button, int state, int x, int y) {
    UNUSED(x); UNUSED(y);

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) { // Zoom-in
            if (angle >= 10) angle -= 5;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) { // Zoom-out
            if (angle <= 130) angle += 5;
        }
    }
    glutPostRedisplay();
}

// Callback para teclas especiais
void handle_special_keys(int key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
        case GLUT_KEY_UP:    rot_x += 6; break;
        case GLUT_KEY_DOWN:  rot_x -= 6; break;
        case GLUT_KEY_LEFT:  rot_y -= 6; break;
        case GLUT_KEY_RIGHT: rot_y += 6; break;
    }
    glutPostRedisplay();
}

// Callback para o teclado
void handle_keyboard(unsigned char key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
        case ESC: exit(0); break;
        case 'f':
            fundo = ~fundo;
            glutPostRedisplay();
            break;
        default: return;
    }
}

// Função callback chamada quando o tamanho da janela é alterado 
void handle_window_resize(GLsizei w, GLsizei h) {
    GLfloat _w = w;
    GLfloat _h = h ?: 1; // Para prevenir uma divisão por zero

    glViewport(0, 0, w, h); // Especifica o tamanho da viewport
    aspect_ratio = _w/_h;   // Calcula a correção de aspecto
}

// Inicializa texturas
void init_rendering() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    rugged_quadric = gluNewQuadric();
    rugged_tex_id  = load_texture(rugged_tex_path);

    rusted_quadric = gluNewQuadric();
    rusted_tex_id  = load_texture(rusted_tex_path);

    golden_quadric = gluNewQuadric();
    golden_tex_id  = load_texture(golden_tex_path);

    glass_quadric = gluNewQuadric();
    glass_tex_id  = load_texture(glass_tex_path);
}

// Inicializa parâmetros de iluminação
void init_lighting(void) {
    GLfloat luz_ambiente[4] = { 0.6,   0.6, 0.6, 1.0 };
    GLfloat luz_difusa[4]   = { 0.9,   0.9, 0.9, 1.0 };
    GLfloat posicao_luz[4]  = { 0.0, 500.0, 0.0, 0.0 };

    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Ativa o uso da luz ambiente 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

    // Define os parâmetros das fontes de luz
    glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

    glEnable(GL_LIGHTING);   // Habilita o uso de iluminação
    glEnable(GL_LIGHT0);     // Habilita as fontes de luz
    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering
    //glFrontFace(GL_CW);

    // Habilita blending para usar alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    switch (color) {
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

// Função callback chamada para fazer o desenho
void handle_redraw(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Inicializa sistema de coordenadas de projeção
    gluPerspective(angle, aspect_ratio, 0.1, 500); // Especifica a projeção perspectiva

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(0, 0, 200, 0, 30, 0, 0, 1, 0); // Especifica posição do observador e do alvo

    // Desenha esfera no fundo/background
    if (fundo) {
        glPushMatrix();
            glTranslatef(10.0, 0, -80.0f);
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            glutSolidSphere(30.0f, 72, 72);
        glPopMatrix();
    }

    // Aplica rotações (pan)
    glRotatef(rot_x, 1, 0, 0);
    glRotatef(rot_y, 0, 1, 0);

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

    init_lighting();
    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutReshapeFunc(handle_window_resize);
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);

    glutMainLoop();
}

