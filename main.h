#include <GL/glut.h>
#include "draw.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define DEFAULT_FOV 50
#define ESC 27


// define se usa texturas ou não
bool apply_textures = true;

// coisas de perspectiva
GLfloat fov = DEFAULT_FOV;

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

// Inicializa parâmetros de iluminação
void init_lighting(void) {
    const GLfloat luz_ambiente[4] = { 0.6,   0.6, 0.6, 1.0 };
    const GLfloat luz_difusa[4]   = { 0.9,   0.9, 0.9, 1.0 };
    const GLfloat posicao_luz[4]  = { 0.0, 500.0, 0.0, 0.0 };

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
    //glFrontFace(GL_CW);
}

//[]
void init_rendering() {
    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita blending para usar alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering

    init_textures();
    init_lighting();
}

