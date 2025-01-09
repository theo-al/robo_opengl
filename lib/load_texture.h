#include "RgbImage.h"
#include "GL/glut.h"

//Makes the image into a texture, and returns the id of the texture
GLuint load_texture(const char* filename) {
    GLuint textureId;

    RgbImage theTexMap(filename); //Image with texture

    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D, //Always GL_TEXTURE_2D
        0,                      //0 for now
        GL_RGB,                 //Format OpenGL uses for image
        theTexMap.GetNumCols(), //Width 
        theTexMap.GetNumRows(), //Height
        0,                      //The border of the image
        GL_RGB,                 //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE,       //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers
        theTexMap.ImageData()   //The actual pixel data
    );
    return textureId; //Returns the id of the texture
}

