#include "Shader.h"
#include <cstring>


//****************************************
//
// Shader()
//
//****************************************

Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}



//****************************************
//
// createFromString
//
//****************************************

void Shader::createFromString(const char *vertexCode, const char *fragmentCode) {

	compileShader(vertexCode, fragmentCode);
}



//****************************************
//
// createFromFiles
//
//****************************************

void Shader::createFromFiles(const char *vertexLocation, const char *fragmentLocation) {

	std::string vertexString = readFile(vertexLocation);
	const char *vertexCode = vertexString.c_str();

	std::string fragmentString = readFile(fragmentLocation);
	const char *fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}



//****************************************
//
// readFile
//
//****************************************


std::string Shader::readFile(const char *fileLocation) {

	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if( !fileStream.is_open() ) {
		printf("failed to read %s!: file doesn't exist.", fileLocation);
		return "";
	}


	std::string line = "";
	while( !fileStream.eof() ) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}




//****************************************
//
// setFloat
//
//****************************************

void Shader::setFloat(const std::string &name, float value) {

	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setInteger(const std::string &name, int value) {

	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}


//****************************************
//
// getProjectionLocation
//
//****************************************

GLuint Shader::getProjectionLocation() {

	return uniformProjection;
}



//****************************************
//
// getModelLocation
//
//****************************************

GLuint Shader::getModelLocation() {

	return uniformModel;
}



//****************************************
//
// compileShader
//
//****************************************

void Shader::compileShader(const char *vertexCode, const char *fragmentCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Error creating shader program!\n");
		return;
	}


	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");

}



//****************************************
//
// useShader
//
//****************************************

void Shader::useShader() {

	glUseProgram(shaderID);
}



//****************************************
//
// clearShader
//
//****************************************

void Shader::clearShader() {

	if(shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}



//****************************************
//
// addShader
//
//****************************************

void Shader::addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType) {
	
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}



//****************************************
//
// ~Shader()
//
//****************************************

Shader::~Shader() {

	clearShader();
}


