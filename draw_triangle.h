#pragma once
# include "stdlib.h"
# include "stdio.h"
// mostly taken from https://stackoverflow.com/questions/40061276/how-to-draw-a-triangle-with-sdl2-and-opengl
// more modern version (v410) taken from https://www.lighthouse3d.com/cg-topics/code-samples/opengl-3-3-glsl-1-5-sample/

// Glew is not used during ES use
#ifdef IMGUI_IMPL_OPENGL_ES2
#include <SDL_opengles2.h>
#else
#include "GL/glew.h" // must be included before opengl
#include <SDL_opengl.h>
#endif

const char* EnumToErrorStringGL(GLenum glErr)
{
    switch (glErr)
    {
    case GL_NO_ERROR: return "GL_NO_ERROR"; break;
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM"; break;
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE"; break;
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY"; break;
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW"; break;
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW"; break;
    }
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)
int printOglError(const char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int retCode = 0;
    
    glErr = glGetError();
    if (glErr == GL_NO_ERROR) {
        printf("No glError in file %s @ line %d: %s\n", file, line, EnumToErrorStringGL(glErr));
        return retCode;
    }
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, EnumToErrorStringGL(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

static const GLchar* vertex_shader_source =
"#version 120\n"
"attribute vec2 coord2d;\n"
"void main() {\n"
"    gl_Position = vec4(coord2d, 0.0, 1.0);\n"
"}\n";

static const GLchar* fragment_shader_source =
"#version 120\n"
"void main() {\n"
"    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

static const GLchar* vertex_shader_source_410 =
"#version 410\n"
"in vec2 coord2d;\n"
"void main()\n"
"{\n"
"    gl_Position =  vec4(coord2d, 0.0, 1.0) ;\n"
"}\n";

static const GLchar* fragment_shader_source_410 =
"#version 410\n"
"out vec4 outputF; //Note the omission of a \"location\" requires c++ call to glBindFragDataLocation\n"
"void main()\n"
"{\n"
"    outputF = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";


static GLfloat vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

GLuint common_get_shader_program (const char* vertex_shader_source, const char* fragment_shader_source)
{
    GLchar* log = NULL;
    GLint log_length, success;
    GLuint fragment_shader, program, vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source_410, NULL);
    glCompileShader(vertex_shader);
    
    // retrive & report compiler messages
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
    log = (GLchar*)malloc(log_length);
    if (log_length > 0) {
        glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
        printf("vertex shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source_410, NULL);
    glCompileShader(fragment_shader);
    // retrive & report compiler messages
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = (GLchar*)realloc(log, log_length);
        glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
        printf("fragment shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Link shaders, noting here we define data passed to/from shaders */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glBindFragDataLocation(program, 0, "outputF"); // Because we didn't define "location zero" on the vertex shader output variable, we have to specify it here.
    glLinkProgram(program);
    
    // retrive & report compiler messages
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = (GLchar*)realloc(log, log_length);
        glGetProgramInfoLog(program, log_length, NULL, log);
        printf("shader link log:\n\n%s\n", log);
    }
    if (!success) {
        printf("shader link error");
        exit(EXIT_FAILURE);
    }

    /* Cleanup. */
    free(log);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}


void draw_triangle_setup(GLuint &program, GLint & attribute_coord2d, GLuint &vbo, GLuint &vao)
{
    /* Shader setup. */
    program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    // Get shader inputs.
    attribute_coord2d = glGetAttribLocation(program, "coord2d");

    // Array Object Setup
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    /* Buffer setup. */
    glGenBuffers(1, &vbo); // not right kind after upgrade
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribute_coord2d);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
