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
GLfloat eye_dist = 20.0;
GLfloat view_rot_x = 0.0;
GLfloat view_rot_z = 15.0;


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
    // coisas da garra
    const float arm_size     = 4.5;
    const float forearm_size = 3.0;
    const float hand_size    = 2.0;
    const float finger_size  = 1.1;
    
    const float base_diameter = 2.0;
    const float base_height   = 0.5;
    
    const float cylinder_diameter = 0.4;
    const float sphere_diameter = cylinder_diameter*4/3;

    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect_ratio, 1.0, 50.0);

    // Gira o ponto de visão em volta do objeto de acordo com o ângulo
    GLfloat eye_x, eye_y, eye_z, up = view_rot_z < 90 ? 1. :-1.;
    eye_x = eye_dist * cos(view_rot_z*PI / 180) * cos(view_rot_x*PI / 180);
    eye_y = eye_dist * cos(view_rot_z*PI / 180) * sin(view_rot_x*PI / 180);
    eye_z = eye_dist * sin(view_rot_z*PI / 180);
    

    // Especifica sistema de coordenadas do modelo
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Inicializa sistema de coordenadas do modelo
    gluLookAt(eye_x, eye_y, eye_z, // Especifica posição do observador
              0,     0,     0,     // Especifica posição do alvo
              0,     0,     up);   // Especifica direção cima (como o eixo z, dependendo)

    //desativa as texturas se precisar
    GLuint texture = apply_textures ? metal_tex_id : INVALID_TEXTURE;

    /* Braço e base */
    glColor3f(1.0f, 1.0f, 1.0f); //drawing color: white
    
    //draws the base
    draw_cylinder(texture, base_diameter, base_height);
    glTranslatef(0.0f, 0.0f, base_height);
    draw_disk(texture, cylinder_diameter, base_diameter);
    
    //move to arm referential
    glRotatef(arm_angle, 0.0f, 0.0f, 1.0f);
    
    //draws the arm
    draw_cylinder(texture, cylinder_diameter, arm_size);
    
    //move to forearm referential
    glTranslatef(0.0f, 0.0f, arm_size + sphere_diameter / 5);
    glRotatef(forearm_angle, 0.0f, 1.0f, 0.0f);
    
    //draws the forearm
    draw_sphere(texture, sphere_diameter);
    glTranslatef(0.0f, 0.0f, sphere_diameter / 5);
    draw_cylinder(texture, cylinder_diameter, forearm_size);
    
    /* Garra */
    glTranslatef(0.0f, 0.0f, forearm_size + sphere_diameter / 5); //move to clamp base referential
    glRotatef(clamp_z_angle, 0.0f, 0.0f, 1.0f); //move to clamp base referential
    
    draw_sphere(texture, sphere_diameter); //draws the clamp sphere

    //move to proper clamp referential
    glTranslatef(0.0f, 0.0f, sphere_diameter / 2);

    glPushMatrix(); //draws top part of clamp
        glRotatef(clamp_y_angle + 60, 0.0f, 1.0f, 0.0f); //! 60 mágico
    
        draw_cylinder(texture, cylinder_diameter / 3, finger_size);
        glTranslatef(0.0f, 0.0f, finger_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f); //! 60 mágico
    
        draw_cylinder(texture, cylinder_diameter / 3, finger_size);
        glTranslatef(0.0f, 0.0f, finger_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cone(texture, cylinder_diameter / 3, finger_size);
    glPopMatrix();

    glPushMatrix(); //draws bottom part of clamp
        glRotatef(-(clamp_y_angle + 60), 0.0f, 1.0f, 0.0f); //! 60 mágico
    
        draw_cylinder(texture, cylinder_diameter / 3, finger_size);
        glTranslatef(0.0f, 0.0f, finger_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f); //! 60 mágico
    
        draw_cylinder(texture, cylinder_diameter / 3, finger_size);
        glTranslatef(0.0f, 0.0f, finger_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f); //! 60 mágico
        draw_cone(texture, cylinder_diameter / 3, finger_size);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Garra");

    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering
    init_rendering();

    glutDisplayFunc(handle_redraw);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);
    glutReshapeFunc(handle_window_resize);

    glutMainLoop();
}

