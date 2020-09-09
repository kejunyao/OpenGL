/**
 * Shader工具类
 *
 * @author kejunyao
 * @since 2020年09月09日
 */
#ifndef OPENGL_SHADERUTILS_H
#define OPENGL_SHADERUTILS_H

#include <GLES2/gl2.h>

static int loadShader(int shaderType, const char *code) {
    // 创建Shader
    int shader = glCreateShader(shaderType);
    // 加载Shader资源
    glShaderSource(shader, 1, &code, 0);
    // 编译Shader
    glCompileShader(shader);
    return shader;
}

static int createProgram(const char *vertex, const char *fragment) {
    int vertexShader = loadShader(GL_VERTEX_SHADER, vertex);
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragment);
    int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}

#endif //OPENGL_SHADERUTILS_H
