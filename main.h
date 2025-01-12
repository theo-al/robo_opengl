#include <iostream>
#include <cstdlib>

#include <GL/glut.h>

#define UNUSED(x) (void) x
#define PI 3.141592654
#define DEFAULT_FOV 50
#define ESC 27


// define se usa texturas ou não
bool apply_textures = true;

// coisas de perspectiva
GLfloat fov = DEFAULT_FOV;
GLfloat eye_dist = 200;
GLfloat view_rot_x = 0;
GLfloat view_rot_z = 0;

GLfloat aspect_ratio;

// coisas da garra
float arm_angle     = 90.0;
float forearm_angle = 90.0;
float hand_angle    = 0.0;
float clamp_z_angle = 0.0;
float clamp_y_angle = 0.0;



// Função callback chamada para gerenciar eventos do mouse
void handle_mouse(int button, int state, int x, int y) {
    UNUSED(x); UNUSED(y);
    if (state != GLUT_DOWN) return;

    switch (button) {
      case GLUT_LEFT_BUTTON: // Zoom-in
        if (fov >= 10) fov -= 5;
        break;
      case GLUT_RIGHT_BUTTON: // Zoom-out
        if (fov <= 130) fov += 5;
        break;
      case GLUT_MIDDLE_BUTTON: fov = DEFAULT_FOV; break;
    }
    glutPostRedisplay();
}

// Callback para teclas especiais
void handle_special_keys(int key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
      case GLUT_KEY_UP:    view_rot_x += 6; break;
      case GLUT_KEY_DOWN:  view_rot_x -= 6; break;
      case GLUT_KEY_LEFT:  view_rot_z -= 6; break;
      case GLUT_KEY_RIGHT: view_rot_z += 6; break;
    }
    glutPostRedisplay();
}

// Callback para o teclado
void handle_keyboard(unsigned char key, int x, int y) {
    UNUSED(x); UNUSED(y);

    std::cout << key << std::endl;
    switch (key) {
      case ESC: exit(0); //Exit

      case 't': //Use texture or not
          apply_textures ^= 1;
          break;
      case '1': //Increase arm angle
          arm_angle += 3;
          if (arm_angle >= 360) arm_angle = 0;
          break;
      case '2': //Decrease arm angle
          arm_angle -= 3;
          if (arm_angle <= 0) arm_angle = 360;
          break;
      case '3': //Increase forearm angle
          if (forearm_angle < 90) forearm_angle += 3;
          break;
      case '4': //Decrease forearm angle
          if (forearm_angle > -90) forearm_angle -= 3;
          break;
      case '5': //Increase clamp angle y axis
          if (clamp_y_angle < 60) clamp_y_angle += 3;
          break;
      case '6': //Decrease clamp angle y axis
          if (clamp_y_angle > 0) clamp_y_angle -= 3;
          break;
      default: return;
    }
    glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void handle_window_resize(GLsizei w, GLsizei h) {
    GLfloat _w = w;
    GLfloat _h = h ?: 1; // Para prevenir uma divisão por zero

    glViewport(0, 0, w, h); // Especifica o tamanho da viewport
    aspect_ratio = _w/_h;   // Calcula a correção de aspecto
}

