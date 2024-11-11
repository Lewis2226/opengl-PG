//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{    //Los vertices base
	//     COORDINATES Vec3    /        COLORS Vec3     /   TexCoord Vec2 //
	 0.0,  1.0f, 0.0f,     0.0f,  1.0f,  0.0f,         0.1954141, 0.8570613,     //0

	 1.0,  0.5f, 0.0f,     0.0f,  1.0f,  0.0f,         0.1224047, 0.7327173, //1
	 0.8, -0.5f, 0.6f,     0.0f,  1.0f,  0.0f,         0.1942733, 0.6038102,     //2

	 0.3,  0.5f, 1.0f,     0.0f,  1.0f,  0.0f,         0.2638603, 0.7327173, //3
	-0.3f,-0.5,  1.0f,     0.0f,  1.0f,  0.0f,	       0.348199, 0.5995785,  //4

	-0.8f, 0.5,  0.6f,     0.0f,  1.0f,  0.0f,         0.4203972, 0.7304358,  //5
	-1.0f,-0.5,  0.0f,     0.0f,  1.0f,  0.0f,         0.5023591, 0.6073365, //6

	-0.8f, 0.5, -0.6f,     0.0f,  1.0f,  0.0f,         0.5695919, 0.7347252, //7
	-0.3, -0.5, -1.0f,     0.0f,  1.0f,  0.0f,         0.6568768, 0.6120547,     //8

	 0.3,  0.5, -1.0f,     0.0f,  1.0f,  0.0f,         0.7276481, 0.7311865,     //9
	 0.8, -0.5, -0.6f,     0.0f,  1.0f,  0.0f,         0.8090354, 0.601439,     //10

	0.0f, -1.0f, 0.0f,     0.0f,  0.0f,  1.0f,	       0.1142961, 0.4657937,      //11

	//Los vertices extra
	//Parte de arriba
	 0.0,  1.0f, 0.0f,     0.0f,  1.0f,  0.0f,        0.3481832, 0.8570613,     //0 //12
	 0.0,  1.0f, 0.0f,     0.0f,  1.0f,  0.0f,        0.5011795, 0.8570613,     //0 //13
	 0.0,  1.0f, 0.0f,     0.0f,  1.0f,  0.0f,        0.6545177, 0.8570613,     //0 //14
	 0.0,  1.0f, 0.0f,     0.0f,  1.0f,  0.0f,        0.8102149, 0.8570613,     //0 //15
	 1.0,  0.5f, 0.0f,     0.0f,  1.0f,  0.0f,        0.8809863, 0.7327173,     //1 //16
	 0.8, -0.5, -0.6f,     0.0f,  1.0f,  0.0f,       0.04234518, 0.6026184,     //10 //17

	 //Parte de abajo
	0.0f, -1.0f, 0.0f,     0.0f,  0.0f,  1.0f,	       0.2676342, 0.4657937,      //11 //18
	0.0f, -1.0f, 0.0f,     0.0f,  0.0f,  1.0f,	       0.4245109, 0.4657937,      //11 //19
	0.0f, -1.0f, 0.0f,     0.0f,  0.0f,  1.0f,	       0.5766695, 0.4657937,      //11 //20
	0.0f, -1.0f, 0.0f,     0.0f,  0.0f,  1.0f,	       0.7323666, 0.4657937,      //11 //21



};

// Indices for vertices order
GLuint indices[] =
{
   0,1,3,
   
   1,3,2,
   
   12,5,3,
   
   3,5,4,
   
   13,7,5,
   
   5,6,7,
   
   14,9,7,
   
   7,9,8,
   
   15,16,9,
   
   9,16,10,
   
   11,17,2,

   17,1,2,

   18,2,4,

   2,3,4,

   19,4,6,

   4,5,6,

   20,6,8,

   6,7,8,
   
   21,8,10,

   8,9,10
   
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Dado 20", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);
	



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/YoutubeOpenGL 7 - Going 3D/";

	// Texture
	Texture brickTex((parentDir + texPath + "D20_tower.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	/*Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);*/

	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.01f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.0f, -6.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}