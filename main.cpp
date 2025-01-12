#include <GL/glut.h>
#include "draw.h"
#include "main.h"


void draw_leg(float width, float height) {
    float wheel_size = width*.7;

    float _width  = width - 1;
    float _height = height - wheel_size;

    glTranslatef(0, 0, -_height);

    glPushMatrix();
    glColor3f(.7, .7, .7);
        draw_inverted_cone(metal_tex_id, _width, 10);
        draw_cylinder(rugged_tex_id, _width, _height);

        glTranslatef(0, 0, _height);
        draw_cone(metal_tex_id, _width, 10);
    glColor3f(1., 1., 1.);
    glPopMatrix();

    glTranslatef(0, 0, -wheel_size);
    glPushMatrix();
    glColor3f(.3, .3, .3);
        glScalef(1.5, 1, .8);

        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glTranslatef(0, 0, wheel_size);

        draw_inverted_cone(glass_tex_id, wheel_size, 5);

        glTranslatef(0, 0, -wheel_size*1.95);
        draw_cylinder(metal_tex_id, wheel_size, wheel_size*1.95);
        draw_cone(glass_tex_id, wheel_size, 5);
    glColor3f(1., 1., 1.);
    glPopMatrix();
}

void draw_torso(float width, float height) {
    float diff = 15;

    glPushMatrix();
        glTranslatef(0, 0, -diff/2);
        draw_cone(metal_tex_id, width, diff);

        glTranslatef(0, 0, -(height-diff));
        draw_cylinder(metal_tex_id, width, height - diff);

        draw_inverted_cone(metal_tex_id, width, diff);
    glPopMatrix();

    glColor3f(.3, .3, .3);
        glTranslatef(width-2, 0, -height/2);
        draw_cube(golden_tex_id, 4, 10, 15);
    glColor3f(1., 1., 1.);
}

// Função callback chamada para fazer o desenho
void handle_redraw(void) {
    // Constantes do braço //!
    const float arm_length     = 3.5;
    const float forearm_length = 2.5;
    
    const float arm_diameter = 0.4;
    const float joint_diameter = arm_diameter*4/3;

    // Constantes do torso
    const float torso_height = 55;
    const float torso_width = torso_height*5/7;

    // Constantes das pernas
    const float leg_height = torso_height*3/2;
    const float leg_width = torso_width/2;

    // Constantes gerais
    const float height_offset = 50;


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
              0,        0,  0,   // Especifica posição do alvo
              0,        0,  1 ); // Especifica direção cima (como o eixo y)

    glPushMatrix(); // Cabeça
        // Muda de referencial
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    
        // Aplica rotações (pan)
        glRotatef(view_rot_x, 1, 0, 0);
        glRotatef(view_rot_z, 0, 1, 0);

        // Aplica translação especial
        glTranslatef(0, height_offset, robot_displacement);
        // Aplica as rotações especiais
        glRotatef(head_twist, 0, 1, 0);
        glRotatef(head_angle, 1, 0, 0);
    
        // Diminui a cabeça pra ficar mais proporcional
        glScalef(.6, .6, .6);

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
    
        // Aplica translação especial
        glTranslatef(robot_displacement, 0, height_offset);

        // Seta a cor para branco
        glColor3f(1.0f, 1.0f, 1.0f);

        // Torso e braços
        glPushMatrix();
            glRotatef(torso_angle, 0, 0, 1);

            // Torso
            glPushMatrix(); // Desenha torso do robô
                glScalef(.7, .9, 1);
                draw_torso(torso_width, torso_height);
            glPopMatrix();

            // Braços
            glPushMatrix(); // Desenha braço esquerdo (pro robô)
                glTranslatef(torso_width/4, torso_width/2, -torso_height/2);
                glRotatef(left_arm_angle, 0.0f, 0.0f, 1.0f);
                glRotatef(90, 0.0f, 1.0f, 0.0f);
                glScalef(10, 10, 10);
                draw_whole_arm(arm_diameter, joint_diameter, arm_length, forearm_length,
                               left_forearm_angle, left_clamp_y_angle, left_clamp_z_angle);
            glPopMatrix();
            glPushMatrix(); // Desenha braço direito (pro robô)
                glTranslatef(torso_width/4, -torso_width/2, -torso_height/2);
                glRotatef(-right_arm_angle, 0.0f, 0.0f, 1.0f);
                glRotatef(90, 0.0f, 1.0f, 0.0f);
                glScalef(10, 10, 10);
                draw_whole_arm(arm_diameter, joint_diameter, arm_length, forearm_length,
                               right_forearm_angle, right_clamp_y_angle, right_clamp_z_angle);
            glPopMatrix();
        glPopMatrix();

        // Pernas
        glPushMatrix(); // Desenha perna esq
            glScalef(1, .9, 1);
            glTranslatef(0, torso_width/2, -torso_height);
            draw_leg(leg_width, leg_height);
        glPopMatrix();
        glPushMatrix(); // Desenha perna dir
            glScalef(1, .9, 1);
            glTranslatef(0, -torso_width/2, -torso_height);
            draw_leg(leg_width, leg_height);
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
    glutInitWindowSize(600, 500);
    glutCreateWindow("Robô");

    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutReshapeFunc(handle_window_resize);
    glutMouseFunc(handle_mouse);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);

    glutMainLoop();
}

