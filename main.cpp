#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "draw.h"
#include "main.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define ESC 27


// coisas de perspectiva
GLfloat eye_dist = 200;
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

// Fun��o callback chamada para fazer o desenho
void handle_redraw(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de proje��o
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Inicializa sistema de coordenadas de proje��o
    gluPerspective(fov, aspect_ratio, 0.1, 500); // Especifica a proje��o perspectiva

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(  0,  0,  eye_dist,  // Especifica posi��o do observador
                0,  30, 0,         // Especifica posi��o do alvo
                0,  1,  0       ); // Especifica dire��o cima (como o eixo y)

    // Aplica rota��es (pan)
    glRotatef(view_rot_x, 1, 0, 0);
    glRotatef(view_rot_y, 0, 1, 0);

    // Desenha pesco�o (cone)
    draw_neck();

    // Desenha cabe�a
    glTranslatef(0.0f, 37.0f, 0.0f);
    draw_head();

    // Mostra mudan�as renderizadas
    glutSwapBuffers();
}

// Programa Principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGBA |
                        GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cabe�a de Rob�");

    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutReshapeFunc(handle_window_resize);
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);

    glutMainLoop();
}

