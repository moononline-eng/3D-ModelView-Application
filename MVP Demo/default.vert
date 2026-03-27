#version 330 core 
// Layout 0 is only for vertex positions
layout (location = 0) in vec3 aPos;
// Layout 1 is only for color of vertices
layout (location = 1) in vec3 aColor;
// Layout 2 is for texture coordinates
layout (location = 2) in vec2 aTex;


//Outputs a vec3 color which will be used by the Fragment shader
out vec3 color;

//Output texture coordinates to the fragment shader
out vec2 texCoord;

//Universally available float variable that can be accessed in the Shader program
uniform float scale;

//Inputs the matrices we need for 3D viewing with perspective
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from Vertex Data to "texCoord"
	texCoord = aTex;
}