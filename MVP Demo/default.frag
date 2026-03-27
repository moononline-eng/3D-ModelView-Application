#version 330 core 
out vec4 FragColor;

// The fragment shader takes in a vec3 color as an input. It gets this input from the Vertex shader.
in vec3 color;
// Inputs the texture coordinates from the Vertex shader
in vec2 texCoord;
// Gets the texture Unit from the main function
uniform sampler2D tex0;


void main()
{
	FragColor = texture(tex0, texCoord);
}