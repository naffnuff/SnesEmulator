#pragma once

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
const float scanlineIntensity = 0.3;
const float brightness = 1.1;
const float contrast = 1.2;

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
	vec2 center = coord - 0.5;
	float vignette = 1.0 - length(center) * 0.3;
	color.rgb *= vignette;

	FragColor = color;
}
)";

}
