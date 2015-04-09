/*
	AUTHOR: W. Max Lees
	FILE: Shaders.h
	DATE: March 11th, 2014

	Contains the declarations of the shader programs
	to be used in the OpenGL engine. #defines are used
	so memory is not used to store them if they aren't
	being used
*/

// Passthrough Vertex Shader
#define VERT_SHADER		"#version 430 core\n \
						layout(location = 0) in vec4 vPosition; \
						void main() \
						{ \
							gl_Position = vPosition; \
						}\0"

// Passthrough Fragment Shader
#define FRAG_SHADER		"#version 430 core\n \
						out vec4 fColor; \
						void main() \
						{ \
							fColor = vec4( 0.0, 0.0, 1.0, 1.0 ); \
						}\0"