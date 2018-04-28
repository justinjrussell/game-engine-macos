#include "shader.h"

namespace sparky { namespace graphics {
    
    Shader::Shader(const char* vertPath, const char* fragPath)
        : m_VertPath(vertPath), m_FragPath(fragPath)
    {
        m_ShaderID = load();
    }
    
    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }
    
    GLuint Shader::load()
    {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        
        std::string vertSourceString = FileUtils::read_file(m_VertPath);
        std::string fragSourceString = FileUtils::read_file(m_FragPath);
        
        const char* vertSource = vertSourceString.c_str();
        const char* fragSource = fragSourceString.c_str();
        
        glShaderSource(vertex, 1, &vertSource, NULL);
        glCompileShader(vertex);
        
        GLint vertex_compiled;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_compiled);
        if (vertex_compiled == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            std::cout << "Failed to compile vertex shader" << std::endl << &error[0] << std::endl;
            glDeleteShader(vertex);
            return 0;
        }
        
        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);
        
        GLint fragment_compiled;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_compiled);
        if (fragment_compiled == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            std::cout << "Failed to compile fragment shader" << std::endl << &error[0] << std::endl;
            glDeleteShader(fragment);
            return 0;
        }
        
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        
        GLint program_compiled;
        glGetProgramiv(program, GL_LINK_STATUS, &program_compiled);
        if(program_compiled == GL_FALSE)
        {
            GLint length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetProgramInfoLog(program, length, &length, &error[0]);
            std::cout << "Failed to link program" << std::endl << &error[0] << std::endl;
            return 0;
        }
        
        glValidateProgram(program);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        return program;
    }
    
    void Shader::enable() const
    {
        glUseProgram(m_ShaderID);
    }
    
    void Shader::disable() const
    {
        glUseProgram(0);
    }
}}
