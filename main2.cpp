#define _CRT_SECURE_NO_WARNINGS
//^ não sei praq serve, tirei e não deu nada

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glut.h>
#include "load_texture.h"
#include "shapes.h"

#define UNUSED(x) (void) x
#define PI 3.141592654
#define ESC 27


GLuint metal_tex_id;
const char* metal_tex_path = "./assets/metalTexture1.bmp";

bool apply_textures = true;

// coisas da garra
float cylinder_diameter = 0.3;
float sphere_diameter   = 0.4;
float arm_size        = 4.5;
float forearm_size    = 3.0;
float hand_size       = 2.0;
float clamp_part_size = 1.0;
float base_diameter = 2.0;
float base_height   = 0.5;

// coisas de perspectiva(?)
float eye_dist = 20.0;
float view_rot_x = 0.0;
float view_rot_z = 15.0;

// coisas da garra
float arm_angle     = 90.0;
float forearm_angle = 90.0;
float hand_angle    = 0.0;
float clamp_z_angle = 0.0;
float clamp_y_angle = 0.0;


void init_rendering(void) {
    sphere_quadric   = gluNewQuadric();
    cylinder_quadric = gluNewQuadric();

    metal_tex_id = load_texture(metal_tex_path);
}

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
    }
    glutPostRedisplay();
}

void handle_window_resize(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
}

void handle_redraw(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    GLfloat eye_x, eye_y, eye_z;
    eye_x = eye_dist * cos(view_rot_z*PI / 180) * cos(view_rot_x*PI / 180);
    eye_y = eye_dist * cos(view_rot_z*PI / 180) * sin(view_rot_x*PI / 180);
    eye_z = eye_dist * sin(view_rot_z*PI / 180);
    
    GLuint texture = apply_textures ? metal_tex_id : INVALID_TEXTURE;

    glLoadIdentity(); {
        gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 0, view_rot_z < 90 ? 1. :-1.);

        //drawing color
        glColor3f(1.0f, 1.0f, 1.0f);

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

        //move to clamp referential
        glTranslatef(0.0f, 0.0f, forearm_size + sphere_diameter / 5);
        glRotatef(clamp_z_angle, 0.0f, 0.0f, 1.0f);

        //draws the clamp sphere
        draw_sphere(texture, sphere_diameter);
        glTranslatef(0.0f, 0.0f, sphere_diameter / 2);
    }

    glPushMatrix(); //draws top part of clamp
        glRotatef(clamp_y_angle + 60, 0.0f, 1.0f, 0.0f);
    
        draw_cylinder(texture, cylinder_diameter / 3, clamp_part_size);
        glTranslatef(0.0f, 0.0f, clamp_part_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
    
        draw_cylinder(texture, cylinder_diameter / 3, clamp_part_size);
        glTranslatef(0.0f, 0.0f, clamp_part_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(-60, 0.0f, 1.0f, 0.0f);
        draw_cone(texture, cylinder_diameter / 3, clamp_part_size);
    glPopMatrix();

    glPushMatrix(); //draws bottom part of clamp
        glRotatef(-clamp_y_angle - 60, 0.0f, 1.0f, 0.0f);
    
        draw_cylinder(texture, cylinder_diameter / 3, clamp_part_size);
        glTranslatef(0.0f, 0.0f, clamp_part_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
    
        draw_cylinder(texture, cylinder_diameter / 3, clamp_part_size);
        glTranslatef(0.0f, 0.0f, clamp_part_size + sphere_diameter / 15);
        draw_sphere(texture, sphere_diameter / 3);
    
        glTranslatef(0.0f, 0.0f, sphere_diameter / 15);
        glRotatef(60, 0.0f, 1.0f, 0.0f);
        draw_cone(texture, cylinder_diameter / 3, clamp_part_size);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Garra");

    glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering
    init_rendering();


    glutDisplayFunc(handle_redraw);
    glutKeyboardFunc(handle_keyboard);
    glutSpecialFunc(handle_special_keys);
    glutReshapeFunc(handle_window_resize);

    glutMainLoop();
}

