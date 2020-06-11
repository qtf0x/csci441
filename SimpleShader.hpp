/** @file SimpleShader.hpp
 * @brief Sets up a default Gourad Shader with vertex position and color inputs
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 09 Jun 2020
 * @version 2.0
 *
 * @copyright MIT License Copyright (c) 2020 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file will only work with OpenGL 4.1
 *	@warning NOTE: This header file depends upon glm
 *	@warning NOTE: This header file depends upon GLEW
 */

#ifndef __CSCI441_SIMPLESHADER_H__
#define __CSCI441_SIMPLESHADER_H__

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "ShaderUtils.hpp"

////////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
 * @brief CSCI441 Helper Functions for OpenGL
 */
namespace CSCI441 {
    /** @namespace SimpleShader
     * @brief CSCI441 Helper Functions for OpenGL Shaders
     */
    namespace SimpleShader {
        void enableFlatShading();
        void enableSmoothShading();

        /** @brief Registers a simple Gourad shader for 2-Dimensional drawing
         *
         */
        void setupSimpleShader2();

        /**
         *
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b) colors
         * @return generated Vertex Array Object Descriptor (vaod)
         */
        GLuint registerVertexArray2(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);
        /** @brief Updates GL_ARRAY_BUFFER fo the corresponding VAO
         *
         * @desc Copies the data for the vertex positions and colors from CPU RAM to the GPU for the already registered
         * VAO.  The data is copied in to the GL_ARRAY_BUFFER VBO for this VAO.  When function completes, the passed
         * VAO is currently bound.
         *
         * @warning Requires that the same number of vertex points, or less, are passed as when the VAO was registered
         *
         * @param VAOD Vertex Array Object Descriptor
         * @param VERTEX_POINTS vector of vertex (x,y) locations
         * @param VERTEX_COLORS vector of vertex (r,g,b) colors
         */
        void updateVertexArray2(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);

        /** @brief Sets the Projection Matrix
         *
         * @param projectionMatrix
         */
        void setProjectionMatrix(glm::mat4 projectionMatrix);

        void pushTransformation(glm::mat4 transformationMatrix);

        void popTransformation();

        void draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT);
    }
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Internal implementations

namespace CSCI441_INTERNAL {
    namespace SimpleShader {
        void enableFlatShading();
        void enableSmoothShading();
        void setupSimpleShader2();
        GLuint registerVertexArray2(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);
        void updateVertexArray2(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS);
        void setProjectionMatrix(glm::mat4 projectionMatrix);
        void pushTransformation(glm::mat4 transformationMatrix);
        void popTransformation();
        void draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT);

        GLboolean smoothShading = true;
        GLint shaderProgramHandle = -1;
        GLint modelLocation = -1;
        GLint viewLocation = -1;
        GLint projectionLocation = -1;
        GLint vertexLocation = -1;
        GLint colorLocation = -1;

        std::vector<glm::mat4> transformationStack;
        glm::mat4 modelMatrix(1.0);
    }
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Outward facing function implementations

inline void CSCI441::SimpleShader::enableFlatShading() {
    CSCI441_INTERNAL::SimpleShader::enableFlatShading();
}
inline void CSCI441::SimpleShader::enableSmoothShading() {
    CSCI441_INTERNAL::SimpleShader::enableSmoothShading();
}

inline void CSCI441::SimpleShader::setupSimpleShader2() {
    CSCI441_INTERNAL::SimpleShader::setupSimpleShader2();
}

inline GLuint CSCI441::SimpleShader::registerVertexArray2(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    return CSCI441_INTERNAL::SimpleShader::registerVertexArray2(VERTEX_POINTS, VERTEX_COLORS);
}

inline void CSCI441::SimpleShader::updateVertexArray2(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    CSCI441_INTERNAL::SimpleShader::updateVertexArray2(VAOD, VERTEX_POINTS, VERTEX_COLORS);
}

inline void CSCI441::SimpleShader::setProjectionMatrix(glm::mat4 projectionMatrix) {
    CSCI441_INTERNAL::SimpleShader::setProjectionMatrix(projectionMatrix);
}

inline void CSCI441::SimpleShader::pushTransformation(glm::mat4 transformationMatrix) {
    CSCI441_INTERNAL::SimpleShader::pushTransformation(transformationMatrix);
}

inline void CSCI441::SimpleShader::popTransformation() {
    CSCI441_INTERNAL::SimpleShader::popTransformation();
}

inline void CSCI441::SimpleShader::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    CSCI441_INTERNAL::SimpleShader::draw(PRIMITIVE_TYPE, VAOD, VERTEX_COUNT);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Inward facing function implementations

inline void CSCI441_INTERNAL::SimpleShader::enableFlatShading() {
    smoothShading = false;
}
inline void CSCI441_INTERNAL::SimpleShader::enableSmoothShading() {
    smoothShading = true;
}

inline void CSCI441_INTERNAL::SimpleShader::setupSimpleShader2() {
    std::string vertex_shader_src = "#version 410 core\n \
                                    \n \
                                    uniform mat4 model;\n \
                                    uniform mat4 view;\n \
                                    uniform mat4 projection;\n \
                                    \n \
                                    layout(location=0) in vec2 vPos;\n \
                                    layout(location=1) in vec3 vColor;\n \
                                    \n \
                                    layout(location=0) ";
    vertex_shader_src += (smoothShading ? "" : "flat ");
    vertex_shader_src += "out vec4 fragColor;\n \
                                    \n \
                                    void main() {\n \
                                        gl_Position = projection * view * model * vec4(vPos, 0.0, 1.0);\n \
                                        fragColor = vec4(vColor, 1.0);\n \
                                    }";
    const char* vertexShaders[1] = { vertex_shader_src.c_str() };

    std::string fragment_shader_src = "#version 410 core\n \
                                      \n \
                                      layout(location=0) ";
    fragment_shader_src += (smoothShading ? "" : "flat ");
    fragment_shader_src += " in vec4 fragColor;\n \
                                      \n \
                                      layout(location=0) out vec4 fragColorOut;\n \
                                      \n \
                                      void main() {\n \
                                          fragColorOut = fragColor;\n \
                                      }";
    const char* fragmentShaders[1] = { fragment_shader_src.c_str() };

    GLuint vertexShaderHandle = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource(vertexShaderHandle, 1, vertexShaders, nullptr);
    glCompileShader(vertexShaderHandle);
    ShaderUtils::printLog(vertexShaderHandle);

    GLuint fragmentShaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShaderHandle, 1, fragmentShaders, nullptr);
    glCompileShader(fragmentShaderHandle);
    ShaderUtils::printLog(fragmentShaderHandle);

    shaderProgramHandle = glCreateProgram();
    glAttachShader(shaderProgramHandle, vertexShaderHandle);
    glAttachShader(shaderProgramHandle, fragmentShaderHandle);
    glLinkProgram(shaderProgramHandle);
    ShaderUtils::printLog(shaderProgramHandle);

    glDetachShader(shaderProgramHandle, vertexShaderHandle);
    glDeleteShader(vertexShaderHandle);

    glDetachShader(shaderProgramHandle, fragmentShaderHandle);
    glDeleteShader(fragmentShaderHandle);

    ShaderUtils::printShaderProgramInfo(shaderProgramHandle);

    modelLocation       = glGetUniformLocation(shaderProgramHandle, "model");
    viewLocation        = glGetUniformLocation(shaderProgramHandle, "view");
    projectionLocation  = glGetUniformLocation(shaderProgramHandle, "projection");

    vertexLocation      = glGetAttribLocation(shaderProgramHandle, "vPos");
    colorLocation       = glGetAttribLocation(shaderProgramHandle, "vColor");

    glUseProgram(shaderProgramHandle);

    glm::mat4 identity(1.0);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &identity[0][0]);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &identity[0][0]);
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &identity[0][0]);
}

inline GLuint CSCI441_INTERNAL::SimpleShader::registerVertexArray2(const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    GLuint vaod;
    glGenVertexArrays(1, &vaod);
    glBindVertexArray(vaod);

    GLuint vbod;
    glGenBuffers(1, &vbod);
    glBindBuffer(GL_ARRAY_BUFFER, vbod);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*VERTEX_POINTS.size()*2 + sizeof(GLfloat)*VERTEX_COLORS.size()*3, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*VERTEX_POINTS.size()*2, &VERTEX_POINTS[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*VERTEX_POINTS.size()*2, sizeof(GLfloat)*VERTEX_COLORS.size()*3, &VERTEX_COLORS[0]);

    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat)*VERTEX_POINTS.size()*2));

    return vaod;
}



inline void CSCI441_INTERNAL::SimpleShader::updateVertexArray2(const GLuint VAOD, const std::vector<glm::vec2>& VERTEX_POINTS, const std::vector<glm::vec3>& VERTEX_COLORS) {
    glBindVertexArray(VAOD);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*VERTEX_POINTS.size()*2, &VERTEX_POINTS[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*VERTEX_POINTS.size()*2, sizeof(GLfloat)*VERTEX_COLORS.size()*3, &VERTEX_COLORS[0]);
}

inline void CSCI441_INTERNAL::SimpleShader::setProjectionMatrix(glm::mat4 projectionMatrix) {
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

inline void CSCI441_INTERNAL::SimpleShader::pushTransformation(glm::mat4 transformationMatrix) {
    transformationStack.emplace_back(transformationMatrix);

    modelMatrix *= transformationMatrix;
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);
}

inline void CSCI441_INTERNAL::SimpleShader::popTransformation() {
    glm::mat4 lastTransformation = transformationStack.back();
    transformationStack.pop_back();

    modelMatrix *= glm::inverse( lastTransformation );
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &modelMatrix[0][0]);
}

inline void CSCI441_INTERNAL::SimpleShader::draw(const GLint PRIMITIVE_TYPE, const GLuint VAOD, const GLuint VERTEX_COUNT) {
    glBindVertexArray(VAOD);
    glDrawArrays(PRIMITIVE_TYPE, 0, VERTEX_COUNT);
}

#endif //__CSCI441_SIMPLESHADER_H__
