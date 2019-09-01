//
// Created by jordan on 23/08/19.
//

#ifndef CHESS_SPRITERENDERER_H
#define CHESS_SPRITERENDERER_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"


class SpriteRenderer {
    public:
        // Constructor (inits shaders/shapes)
        SpriteRenderer(Shader &shader);
        // Destructor
        ~SpriteRenderer();
        // Renders a defined quad textured with given sprite
        void DrawSprite(Texture2D &texture, glm::vec2 position,
                        glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                        glm::vec3 color = glm::vec3(1.0f));

        //Draws an portion of an image.
        void DrawScaledImage(Texture2D &texture, glm::vec2 position,
                     glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                     glm::vec3 color = glm::vec3(1.0f));

    private:
        // Render state
        Shader shader;
        GLuint quadVAO;
        // Initializes and configures the quad's buffer and vertex attributes
        void initRenderData();

};


#endif //CHESS_SPRITERENDERER_H
