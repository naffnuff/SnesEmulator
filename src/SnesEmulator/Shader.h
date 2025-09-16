#pragma once

namespace Video {

class Renderer;

class Shader
{
public:
	virtual ~Shader() {}

	virtual void apply(const Renderer& renderer);

	void destroy();

protected:
	void createProgram(const char* vertexSource, const char* fragmentSource);

private:
	unsigned int compileShader(const char* source, unsigned int type);

protected:
	unsigned int program = 0;

private:
	int gameTextureUniform = -1;
};

class SimpleShader : public Shader
{
public:
	void initialize();
};

class ScanlineShader : public Shader
{
public:
	void initialize();

private:
	void apply(const Renderer& renderer) override;

public:
	float scanlineIntensity = 0.2f;
	float brightness = 1.1f;
	float contrast = 1.f;

private:
	int timeUniform = -1;
	int resolutionUniform = -1;
	int aspectRatioUniform = -1;
	int scanlineIntensityUniform = -1;
	int brightnessUniform = -1;
	int contrastUniform = -1;
};

}
