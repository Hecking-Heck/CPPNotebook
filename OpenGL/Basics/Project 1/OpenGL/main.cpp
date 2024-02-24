// Includes
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


// Main Loop
int main()
{
	// Initialise GLFW
	glfwInit();
	
	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile of OpenGL
	// This means we get only modern functions, the COMPAT profile would include
	// both modern and Deprecated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Triangle Vertices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};

	// Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window Name", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Tell GLFW we want to use the window we just created, aka add it to the current context
	glfwMakeContextCurrent(window);

	// Load open GL with Glad
	gladLoadGL();

	// Tell OpenGL where it is allowed to render
	glViewport(0, 0, 800, 800);

	// Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// Clean Up the Shaders as they are already in the program now
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex Data
	GLuint VAO, VBO;

	// Generate Vertex Arrays
	// Remember to always generate the VAO before VBO!
	glGenVertexArrays(1, &VAO);

	// Generate Vertex Buffers
	// Always do this after Generating the VAO!
	glGenBuffers(1, &VBO);

	// Binding (making a certain object the current object)

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Data Uses: GL_STREAM vertices will be modified once and used a few times, GL_STATIC modified once but used many many times, GL_DYNAMIC modified multiple times and used many many times
	// DRAW draw image on screen, READ image on screen, COPY image on screen
	// Specify the correct uses to improve performance
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO and VBO by binding the Array Buffer to 0
	// Remember this ordering!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back and front buffers around
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the back and front buffers around
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroy the window before we exit
	glfwDestroyWindow(window);

	// Terminate GLFW before we exit
	glfwTerminate();

	// Exit
	return 0;
}