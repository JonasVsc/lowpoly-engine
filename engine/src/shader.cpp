#include"shader.h"



lowpoly::shader::shader(const char* vertex_path, const char* fragment_path)
	: program{ glCreateProgram() }
	, vertex_shader{ glCreateShader(GL_VERTEX_SHADER) }
	, fragment_shader{ glCreateShader(GL_FRAGMENT_SHADER) }
{
}

const char* lowpoly::shader::read_file(const char* p_shader_file_path)
{
	// open file
	// ---------
	std::fstream file{};
	file.open(p_shader_file_path, std::fstream::in);

	// check error
	// -----------
	if (!file.is_open())
	{
		std::cerr << "ERROR file not found or can't open file\n";
	}

	// read file
	// ---------
	std::stringstream file_stream;
	file_stream << file.rdbuf();

	// convert to str
	// ----------------
	std::string file_str = file_stream.str();

	file.close();

	// convert to c_str
	// ---------------- 
	const char* file_code = file_str.c_str();
	return file_code;
}

void lowpoly::shader::catch_shader_compile_errors(GLuint shader)
{
	int shader_compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(shader, 1024, &log_length, message);
		std::cerr << message << '\n';
	}
}

void lowpoly::shader::catch_program_compile_errors(GLuint program)
{
	GLint program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cerr << message << '\n';
	}
}
