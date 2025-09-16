#include "Shader.h"

#include "VideoRenderer.h"

#include <glad/glad.h>

namespace Video {

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
)";

const char* simpleFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D gameTexture;

void main()
{
	FragColor = texture(gameTexture, TexCoord);
}
)";

const char* scanlineFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D gameTexture;
uniform float time;
uniform vec2 resolution;
uniform float aspectRatio;

// CRT effect parameters
uniform float scanlineIntensity;
uniform float brightness;
uniform float contrast;

void main()
{
	vec2 coord = TexCoord;

	// Sample the game texture
	vec4 color = texture(gameTexture, coord);

	// Apply scanlines
	float scanline = sin(coord.y * resolution.y * 3.14159);
	scanline = 1.0 - scanlineIntensity + scanlineIntensity * scanline * scanline;
	
	// Apply brightness and contrast
	color.rgb *= brightness;
	color.rgb = (color.rgb - 0.5) * contrast + 0.5;

	// Apply scanline effect
	color.rgb *= scanline;

	// Slight vignette effect
	//vec2 center = coord - 0.5;
	//float vignette = 1.0 - length(center) * 0.3;
	//color.rgb *= vignette;

	FragColor = color;
}
)";

void Shader::apply(const Renderer& renderer)
{
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer.getTexture());
	if (gameTextureUniform >= 0)
	{
		glUniform1i(gameTextureUniform, 0);
	}
}

void Shader::destroy()
{
	if (program)
	{
		glDeleteProgram(program);
	}
}

void Shader::createProgram(const char* vertexSource, const char* fragmentSource)
{
	unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		throw std::runtime_error("Shader linking failed: " + std::string(infoLog));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	gameTextureUniform = glGetUniformLocation(program, "gameTexture");
}

unsigned int Shader::compileShader(const char* source, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
	}

	return shader;
}

void SimpleShader::initialize()
{
	createProgram(vertexShaderSource, simpleFragmentShaderSource);
}

void ScanlineShader::initialize()
{
	createProgram(vertexShaderSource, scanlineFragmentShaderSource);

	timeUniform = glGetUniformLocation(program, "time");
	resolutionUniform = glGetUniformLocation(program, "resolution");
	aspectRatioUniform = glGetUniformLocation(program, "aspectRatio");
	scanlineIntensityUniform = glGetUniformLocation(program, "scanlineIntensity");
	brightnessUniform = glGetUniformLocation(program, "brightness");
	contrastUniform = glGetUniformLocation(program, "contrast");
}

void ScanlineShader::apply(const Renderer& renderer)
{
	Shader::apply(renderer);

	glUniform1f(timeUniform, (float)renderer.getTime());
	glUniform2f(resolutionUniform, (float)renderer.width, (float)renderer.height);
	glUniform1f(aspectRatioUniform, (float)renderer.width / (float)renderer.height);
	glUniform1f(scanlineIntensityUniform, scanlineIntensity);
	glUniform1f(brightnessUniform, brightness);
	glUniform1f(contrastUniform, contrast);
}

}
