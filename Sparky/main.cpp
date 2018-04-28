#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

int main(void)
{
    using namespace sparky;
    using namespace graphics;
    using namespace maths;
    
    
    Window window("Hello Sparky", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    
    const char *vertexPath = "/Users/justinrussell/Library/Mobile Documents/com~apple~CloudDocs/Xcode Projects/Sparky/Sparky/src/shaders/basic.vert";
    const char *fragmentPath = "/Users/justinrussell/Library/Mobile Documents/com~apple~CloudDocs/Xcode Projects/Sparky/Sparky/src/shaders/basic.frag";
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    Shader shader(vertexPath, fragmentPath);
    shader.enable();
    
    while (!window.closed()) {
        window.clear();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        window.update();
    }
    
    return 0;
}
