#include "Renderer.h"
#include "GraphicsBuffers.h"
#include "Shader.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout
            << "[OpenGL Error] (" << error << "): "
            << function << " "
            << file << ":" << line
            << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear(const float color[4]) const
{
    GLCall(glClearColor(color[0], color[1], color[2], color[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& EBO, const Shader& shader) const
{
    shader.Bind();
    VAO.Bind();
    EBO.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr));
}
