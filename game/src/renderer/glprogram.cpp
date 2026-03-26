#include "glprogram.h"

GLProgram::GLProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvalPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    // Tess
    std::string tessControlCode;
    std::string tessEvalCode;
    //
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // Tess
    std::ifstream tcShaderFile;
    std::ifstream teShaderFile;
    //
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // Tess
    tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    //
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
        if (tessControlPath != nullptr)
        {
            tcShaderFile.open(tessControlPath);
            std::stringstream tcShaderStream;
            tcShaderStream << tcShaderFile.rdbuf();
            tcShaderFile.close();
            tessControlCode = tcShaderStream.str();
        }
        if (tessEvalPath != nullptr)
        {
            teShaderFile.open(tessEvalPath);
            std::stringstream teShaderStream;
            teShaderStream << teShaderFile.rdbuf();
            teShaderFile.close();
            tessEvalCode = teShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    this->check_compile_errors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    this->check_compile_errors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if (geometryPath != nullptr)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        this->check_compile_errors(geometry, "GEOMETRY");
    }
    // Tesselation control 
    unsigned int tessControl;
    if (tessControlPath != nullptr)
    {
        const char* tcShaderCode = tessControlCode.c_str();
        tessControl = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessControl, 1, &tcShaderCode, NULL);
        glCompileShader(tessControl);
        this->check_compile_errors(tessControl, "TESSELATION CONTROL");
    }
    // Tesselation eval
    unsigned int tessEval;
    if (tessEvalPath != nullptr)
    {
        const char* teShaderCode = tessEvalCode.c_str();
        tessEval = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tessEval, 1, &teShaderCode, NULL);
        glCompileShader(tessEval);
        this->check_compile_errors(tessEval, "TESSELATION CONTROL");
    }
    // shader Program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    if (geometryPath != nullptr)
        glAttachShader(this->id, geometry);
    if (tessControlPath != nullptr)
        glAttachShader(this->id, tessControl);
    if (tessEvalPath != nullptr)
        glAttachShader(this->id, tessEval);
    glLinkProgram(this->id);
    this->check_compile_errors(this->id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
        glDeleteShader(geometry);
    if (tessControlPath != nullptr)
        glDeleteShader(tessControl);
    if (tessEvalPath != nullptr)
        glDeleteShader(tessEval);
}

void GLProgram::use(void) const
{
    glUseProgram(this->id);
}

void GLProgram::unuse(void) const
{
    glUseProgram(0);
}

uint GLProgram::getProgramId(void) const
{
    return this->id;
}

GLProgram::~GLProgram()
{
    glDeleteProgram(this->id);
}

void GLProgram::set_bool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void GLProgram::set_int(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void GLProgram::set_float(const std::string& name, float value) const
{
    glUniform1f(glad_glGetUniformLocation(this->id, name.c_str()), value);
}

void GLProgram::set_vec2(const std::string& name, const v2& value) const
{
    glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void GLProgram::set_vec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(this->id, name.c_str()), x, y);
}

void GLProgram::set_vec3(const std::string& name, const v3& value) const
{
    glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void GLProgram::set_vec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z);
}

void GLProgram::set_vec4(const std::string& name, const v4& value) const
{
    glUniform4fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void GLProgram::set_vec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w);
}

void GLProgram::set_mat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLProgram::set_mat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLProgram::set_mat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLProgram::check_compile_errors(GLuint shader, std::string type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}



