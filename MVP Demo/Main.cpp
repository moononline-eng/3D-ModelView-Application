#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

const unsigned int width = 1200;
const unsigned int height = 1200;


// Vertices coordinates
GLfloat vertices[] =
{//		 Coordinates	 /     RGB values        /Texture coordinates
	-0.5f,   0.0f,  0.5f,   0.80f, 0.70f, 0.45f,   0.0f, 0.0f,
	-0.5f,   0.0f, -0.5f,   0.80f, 0.70f, 0.45f,   5.0f, 0.0f,
	 0.5f,   0.0f, -0.5f,   0.80f, 0.70f, 0.45f,   0.0f, 0.0f,	
	 0.5f,   0.0f,  0.5f,   0.80f, 0.70f, 0.45f,   5.0f, 0.0f,	
	 0.0f,   0.8f,  0.0f,   0.90f, 0.86f, 0.75f,   2.5f, 5.0f
};

GLuint indices[] =
{
	0,1,2,
	0,2,3,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4
};

int main() 
{
	// Initialize GLFW
	glfwInit();

	// The major and minor OpenGL version we want to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tells GLFW we are using the CORE profile. This means we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a GLFWwindow object with the pixels 800 x 800 and naming it "Window"
	GLFWwindow* window = glfwCreateWindow(width, height, "Window", NULL, NULL);

	//Error handling to see if we have a window or not
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// We tell OpenGL that we want to use the window we created
	glfwMakeContextCurrent(window);
	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Tell OpenGL which part of the screen we want to render. Here we want to render from the bottom left (0,0) to the top right (800,800)
	glViewport(0, 0, width, height);

	// Create a Shader Program with Vertex shader from default.vert and Fragment shader from default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate a Vertex Array Object for us to use
	VAO VAO1;
	// Make it the currently used VAO
	VAO1.Bind();

	// Create a Vertex Buffer Object for us to bind to the VAO 
	VBO VBO1(vertices, sizeof(vertices));
	// Create an EBO that is automatically binded on instantiation (check class)
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attritubes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent them from accidentally being modified.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// A reference for the uniform value "scale" in the rendering pipeline
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture choice. Textures can bug if the wrong color format is used. Try GL_RGBA and GL_RGB
	Texture testTexture("stone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	testTexture.texUnit(shaderProgram, "tex0", 0);

	// Variables that help with the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop 
	while (!glfwWindowShouldClose(window))
	{
		// Background color
		glClearColor(0.10f, 0.10f, 0.20f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = currentTime;
		}

		// Initialize the Identity matrices (Enhetsmatrisen) so they are not null matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f); 
		glm::mat4 proj = glm::mat4(1.0f); 

		// Assign different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.5f));	// Move the camera down 0.5 and forward 2.0. Z axis is positive towards us and negative away from us
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		// Inputs the matrices into the Vertex Shader
		int modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		int projLocation = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform variable. We can only do this after the Shader program is activated.
		glUniform1f(uniID, 0.5f);
		// Binds texture so that it appears in rendering
		testTexture.Bind();

		// Bind the VAO for OpenGL
		VAO1.Bind();
		// This function draws the primitives based on number of indices, datatype of indices and index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Handles all GLFW events
		glfwPollEvents();
	}

	// Destroying and uninitializing objects we created.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	testTexture.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}