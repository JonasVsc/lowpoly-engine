#include"shader.h"

shader::shader(const char* p_vertex_file_path, const char* p_fragment_file_path)
{
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vs_shader_file;
	std::ifstream fs_shader_file;

	vs_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fs_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vs_shader_file.open(p_vertex_file_path);
		fs_shader_file.open(p_fragment_file_path);
		std::stringstream vs_shader_stream, fs_shader_stream;
		vs_shader_stream << vs_shader_file.rdbuf();
		fs_shader_stream << fs_shader_file.rdbuf();

		vs_shader_file.close();
		fs_shader_file.close();

		vertex_code = vs_shader_stream.str();
		fragment_code = fs_shader_stream.str();
	}
	catch (std::ifstream::failure &e)
	{
		std::cerr << "ERROR::SHADER::FILE::FILE_NOT_SUCCESSFULLY_READ" << e.what() << std::endl;
	}
	const char* vs_shader_code = vertex_code.c_str();
	const char* fs_shader_code = fragment_code.c_str();

	// compile shaders
	// ---------------
	GLuint vertex, fragment;

	// vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vs_shader_code, NULL);
	glCompileShader(vertex);
	check_compile_errors(vertex, "VERTEX");
	// fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fs_shader_code, NULL);
	glCompileShader(fragment);
	check_compile_errors(fragment, "FRAGMENT");
	// program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	check_compile_errors(ID, "PROGRAM");
	// delete
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void shader::use()
{
	glUseProgram(ID);
}


void shader::check_compile_errors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
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


