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
GLfloat eye_dist   = 20;
GLfloat view_rot_x = 0;
GLfloat view_rot_z = 15;


// Callback para teclas especiais
void handle_special_keys(int key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
      case GLUT_KEY_UP:
          if (view_rot_z > 0) view_rot_z -= 3;
          break;
      case GLUT_KEY_DOWN:
          if (view_rot_z < 180) view_rot_z += 3;
          break;
      case GLUT_KEY_LEFT:  view_rot_x += 3; break;
      case GLUT_KEY_RIGHT: view_rot_x -= 3; break;
    }
    glutPostRedisplay();
}

void handle_redraw(void) {
    // Constantes* do braço
    const float arm_length     = 4.5;
    const float forearm_length = 3.0;
    
    const float arm_diameter = 0.4;
    const float joint_diameter = arm_diameter*4/3;
    //!*

    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect_ratio, 0.1, 50.0);

    // Gira o ponto de visão em volta do objeto de acordo com o ângulo
    GLfloat eye_x = eye_dist * cos(view_rot_z*PI / 180) * cos(view_rot_x*PI / 180),
            eye_y = eye_dist * cos(view_rot_z*PI / 180) * sin(view_rot_x*PI / 180),
            eye_z = eye_dist * sin(view_rot_z*PI / 180);
    GLfloat up = view_rot_z < 90 ? 1. : -1.;

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(eye_x, eye_y, eye_z, // Especifica posição do observador
              0,     0,     0,     // Especifica posição do alvo
              0,     0,     up);   // Especifica direção cima (como o eixo z, dependendo)

    // Desativa as texturas se precisar
    GLuint metal_texture = apply_textures ? metal_tex_id : INVALID_TEXTURE;

    // Seta a cor para branco
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Desenha braço
    glRotatef(arm_angle, 0.0f, 0.0f, 1.0f); //move to arm referential
    draw_whole_arm(metal_texture, arm_diameter, joint_diameter, arm_length,
                   forearm_length, forearm_angle, clamp_y_angle, clamp_z_angle);

    // Mostra mudanças renderizadas
    glutSwapBuffers();
}

// Programa Principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Garra");

    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutReshapeFunc(handle_window_resize);
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);

    glutMainLoop();
}

