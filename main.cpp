#include <GL/glut.h>
#include "draw.h"
#include "main.h"



// Função callback chamada para fazer o desenho
void handle_redraw(void) {
    // Constantes* do braço
    const float arm_length     = 4.5;
    const float forearm_length = 3.0;
    
    const float arm_diameter = 0.4;
    const float joint_diameter = arm_diameter*4/3;
    //!*

    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Inicializa sistema de coordenadas de projeção
    gluPerspective(fov, aspect_ratio, 0.1, 500); // Especifica a projeção perspectiva

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(eye_dist, 0,  0,   // Especifica posição do observador
              0,        0,  0.,  // Especifica posição do alvo
              0,        0,  1 ); // Especifica direção cima (como o eixo y)

    // Desativa as texturas se precisar
    GLuint metal_texture = apply_textures ? metal_tex_id : INVALID_TEXTURE;

    glPushMatrix();
        // Muda de referencial
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    
        // Aplica rotações (pan)
        glRotatef(view_rot_x, 1, 0, 0);
        glRotatef(view_rot_z, 0, 1, 0);
    
        // Desenha pescoço (cone)
        draw_neck();
    
        // Desenha cabeça
        glTranslatef(0.0f, 37.0f, 0.0f);
        draw_head();
    glPopMatrix();

    glPushMatrix();
        // Aplica rotações (pan)
        glRotatef(view_rot_x, 0, 1, 0);
        glRotatef(view_rot_z, 0, 0, 1);
    
        // Seta a cor para branco
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glPushMatrix(); // Desenha braço esquerdo (pro robô)
            glRotatef(arm_angle, 0.0f, 0.0f, 1.0f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glScalef(10, 10, 10);
            draw_whole_arm(metal_texture, arm_diameter, joint_diameter, arm_length,
        	               forearm_length, forearm_angle, clamp_y_angle, clamp_z_angle);
        glPopMatrix();
        glPushMatrix(); // Desenha braço direito (pro robô)
            glRotatef(-arm_angle, 0.0f, 0.0f, 1.0f);
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glScalef(10, 10, 10);
            draw_whole_arm(metal_texture, arm_diameter, joint_diameter, arm_length,
        	               forearm_length, forearm_angle, clamp_y_angle, clamp_z_angle);
        glPopMatrix();
    glPopMatrix();


    // Mostra mudanças renderizadas
    glutSwapBuffers();
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

// Inicializa os parâmetros de renderização
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

