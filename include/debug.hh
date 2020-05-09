#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <string>

#define LOG(...)                                                               \
    do                                                                         \
    {                                                                          \
        std::string file = __FILE__;                                           \
        file = file.substr(file.find_last_of('/') + 1);                        \
        printf("(%s:%d) %s: ", file.c_str(), __LINE__, __FUNCTION__);          \
        printf(__VA_ARGS__);                                                   \
    } while (0)

#define ERROR_CASE(X)                                                          \
    case X:                                                                    \
        return #X

inline std::string get_gl_error_string()
{
    int code = glGetError();
    switch (code)
    {
        ERROR_CASE(GL_NO_ERROR);
        ERROR_CASE(GL_INVALID_ENUM);
        ERROR_CASE(GL_INVALID_VALUE);
        ERROR_CASE(GL_INVALID_OPERATION);
        ERROR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION);
        ERROR_CASE(GL_OUT_OF_MEMORY);
        ERROR_CASE(GL_STACK_UNDERFLOW);
        ERROR_CASE(GL_STACK_OVERFLOW);
    }
    std::cerr << "glGetError code was not matched (" << code << ")\n";
    exit(1);
}

#undef ERROR_CASE
