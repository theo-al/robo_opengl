#include <iostream>
#include <cstdlib>

#include <GL/glut.h>

#define UNUSED(x) (void) x
#define PI 3.141592654
#define DEFAULT_FOV 50
#define ESC 27


// coisas de perspectiva
GLfloat fov = DEFAULT_FOV;
GLfloat eye_dist = 200;
GLfloat view_rot_x = 0;
GLfloat view_rot_z = 0;

GLfloat aspect_ratio;

// estado dos braços
float left_arm_angle     = 65.0;
float left_forearm_angle = 45.0;
float left_hand_angle    = 30.0;
float left_clamp_z_angle = 0.0;
float left_clamp_y_angle = 0.0;

float right_arm_angle     = 65.0;
float right_forearm_angle = 45.0;
float right_hand_angle    = 0.0;
float right_clamp_z_angle = 0.0;
float right_clamp_y_angle = 0.0;

// estado do robô
float robot_displacement = 0;
float torso_angle = 0;
float head_angle = 0;
float head_twist = 0;


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

      case 'w': robot_displacement += 1; break;
      case 's': robot_displacement -= 1; break;

      case 'e': torso_angle -= 1; break;
      case 'c': torso_angle += 1; break;

      case 'q':
          if (head_angle > -87) head_angle -= 3;
          break;
      case 'z':
          if (head_angle < 87) head_angle += 3;
          break;

      case 'a':
          if (head_twist > -120) head_twist -= 3;
          break;
      case 'd':
          if (head_twist < 120) head_twist += 3;
          break;


      case '1': //Increase arm angle
          if (right_arm_angle < 180) right_arm_angle += 3;
          break;
      case '2': //Decrease arm angle
          if (right_arm_angle > 0) right_arm_angle -= 3;
          break;
      case '3': //Increase forearm angle
          if (right_forearm_angle < 90) right_forearm_angle += 3;
          break;
      case '4': //Decrease forearm angle
          if (right_forearm_angle > -90) right_forearm_angle -= 3;
          break;
      case '5': //Increase clamp angle y axis
          if (right_clamp_y_angle < 60) right_clamp_y_angle += 3;
          break;
      case '6': //Decrease clamp angle y axis
          if (right_clamp_y_angle > 0) right_clamp_y_angle -= 3;
          break;

      case '7': //Increase arm angle
          if (left_arm_angle < 180) left_arm_angle += 3;
          break;
      case '8': //Decrease arm angle
          if (left_arm_angle > 0) left_arm_angle -= 3;
          break;
      case '9': //Increase forearm angle
          if (left_forearm_angle < 90) left_forearm_angle += 3;
          break;
      case '0': //Decrease forearm angle
          if (left_forearm_angle > -90) left_forearm_angle -= 3;
          break;
      case '-': //Increase clamp angle y axis
          if (left_clamp_y_angle < 60) left_clamp_y_angle += 3;
          break;
      case '=': //Decrease clamp angle y axis
          if (left_clamp_y_angle > 0) left_clamp_y_angle -= 3;
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

