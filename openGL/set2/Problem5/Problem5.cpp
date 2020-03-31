/* Rony Sheik
   301258738
   rsheik@sfu.ca */
   
   // References 
// https://www.youtube.com/watch?v=n4k7ANAFsIQ&t=578s
// https://learnopengl.com/Getting-started/Textures
// https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/4.1.textures/textures.cpp

#include<stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#define GLEW_STATIC
#include <GLEW/glew.h> // Include the GLEW header file
#include <GLFW/glfw3.h>
#include <cstdint>
#include "D:\ENSC482\OpenGL\OpenGLRoot\OpenGLVS\OpenGLVS\stb_image.h""


using namespace std;

unsigned int textureID; //the array for our texture

// defining dimension for window
const unsigned int win_WIDTH = 1000;
const unsigned int win_HEIGHT = 600;


// Code for our vertext and fragment Shaders
const char* VS = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec3 aTexCoord;\n"

"out vec3 ourColor;"
"out vec2 TexCoord;"

"void main()\n"
"{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = aColor;"
	"TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
"}\0";

const char* FS = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"in vec2 TexCoord;"

"uniform sampler2D texture1;"

"void main()\n"
"{\n"
	"FragColor = texture(texture1, TexCoord);\n"
"}\n\0";


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main (int argc, char **argv) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// can not resize the window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(win_WIDTH, win_HEIGHT, "Problem 5 - Neighbourhood's Map", NULL, NULL);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);


	// Build and compile our shader program
	// Vertex shader
	unsigned int vertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_Shader, 1, &VS, NULL);
	glCompileShader(vertex_Shader);

	// Fragment shader
	unsigned int fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_Shader, 1, &FS, NULL);
	glCompileShader(fragment_Shader);

	// Link the shaders
	unsigned int shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertex_Shader);
	glAttachShader(shaderProgramID, fragment_Shader);
	glLinkProgram(shaderProgramID);

	// delete the shadders after it has been linked
	glDeleteShader(vertex_Shader);
	glDeleteShader(fragment_Shader);
	
	// after this
	float Image_vertices[] = {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Image_vertices), Image_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

    //Load our texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//even better quality, but this will do for now.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//to the edge of our shape. 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Generate the texture
	int width, height, Channels;
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char *buffer = stbi_load("Neighbourhood_Map.png", &width, &height, &Channels, 0);

	if (buffer)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(buffer);

	//Draw on window
	

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		// activate the shadder
		glUseProgram(shaderProgramID);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;

}
