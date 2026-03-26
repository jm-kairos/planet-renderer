#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <fstream>
#include <sstream>
#include <iostream>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../defines.h"

struct GLProgram {

	GLProgram(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr);
    ~GLProgram(void);

	void use(void) const;
    void unuse(void) const;
    uint getProgramId(void) const;
	// utility uniform functions
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
    void set_vec2(const std::string& name, const v2& value) const;
    void set_vec2(const std::string& name, float x, float y) const;
    void set_vec3(const std::string& name, const v3& value) const;
    void set_vec3(const std::string& name, float x, float y, float z) const;
    void set_vec4(const std::string& name, const v4& value) const;
    void set_vec4(const std::string& name, float x, float y, float z, float w) const;
    void set_mat2(const std::string& name, const glm::mat2& mat) const;
    void set_mat3(const std::string& name, const glm::mat3& mat) const;
    void set_mat4(const std::string& name, const glm::mat4& mat) const;

private:
    void check_compile_errors(GLuint shader, std::string type) const;
private:
    uint id;
};

#endif /* GLPROGRAM_H */

