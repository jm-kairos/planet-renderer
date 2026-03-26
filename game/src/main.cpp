// game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "config.h"
#include "defines.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const uint SCR_WIDTH{ 1024 };
const uint SCR_HEIGHT{ 720 };

struct MouseState
{
	MATH_VEC2_r32 pos = { 0.f, 0.f };
	bool pressedLeft = false;
} mouseState;

CameraPositioner_FirstPerson positioner(v3(0, 0, 29000), v3(0.0f, 0.0f, -100.f), v3(0.0f, 1.0f, 0.0f));
Camera camera(positioner);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void error_callback(int error, const char* description){
	fprintf(stderr, "Error: %s\n", description);
} 

int main()
{

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window{ glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "Sunder of Nexus - game", NULL, NULL) };
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // or gladLoadGL();

	GLProgram progPlanet(
		"C:/dev/game/game/src/resources/shaders/planet/vert.glsl",
		"C:/dev/game/game/src/resources/shaders/planet/frag.glsl",
		nullptr,
		"C:/dev/game/game/src/resources/shaders/planet/tc.glsl",
		"C:/dev/game/game/src/resources/shaders/planet/te.glsl"
	);

	GLProgram progSphereCube(
		"C:/dev/game/game/src/resources/shaders/terrain/vertTerrain.glsl",
		"C:/dev/game/game/src/resources/shaders/terrain/fragTerrain.glsl",
		nullptr,
		"C:/dev/game/game/src/resources/shaders/terrain/tessControlTerrain.glsl",
		"C:/dev/game/game/src/resources/shaders/terrain/tessEvalTerrain.glsl"
	);

	GLProgram progTerrain(
		"C:/dev/game/game/src/resources/shaders/terrain/vertTerrain.glsl",
		"C:/dev/game/game/src/resources/shaders/terrain/fragTerrain.glsl",
		nullptr,
		"C:/dev/game/game/src/resources/shaders/terrain/tessControlTerrain.glsl",
		"C:/dev/game/game/src/resources/shaders/terrain/tessEvalTerrain.glsl"
	);

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(
		window,
		[](auto* window, double x, double y)
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			mouseState.pos.x = static_cast<float>(x / width);
			mouseState.pos.y = static_cast<float>(y / height);
		}
	);

	glfwSetMouseButtonCallback(
		window,
		[](auto* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				mouseState.pressedLeft = action == GLFW_PRESS;
		}
	);

	glfwSetKeyCallback(
		window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			const bool pressed = action != GLFW_RELEASE;
			if (key == GLFW_KEY_ESCAPE && pressed)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			if (key == GLFW_KEY_W)
				positioner.movement_.forward_ = pressed;
			if (key == GLFW_KEY_S)
				positioner.movement_.backward_ = pressed;
			if (key == GLFW_KEY_A)
				positioner.movement_.left_ = pressed;
			if (key == GLFW_KEY_D)
				positioner.movement_.right_ = pressed;
			if (mods & GLFW_MOD_SHIFT)
				positioner.movement_.fastSpeed_ = pressed;
			if (key == GLFW_KEY_SPACE) 
				positioner.setUpVector(v3(0.0f, 1.0f, 0.0f));
			if (key == GLFW_KEY_1)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if (key == GLFW_KEY_0)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	);

	//uint textureContainer;
	//glGenTextures(1, &textureContainer);
	//glBindTexture(GL_TEXTURE_2D, textureContainer);
	//// set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load and generate the texture
	//int widthContainer, heightContainer, nrChannelsContainer;
	//unsigned char* data = stbi_load("C:/dev/game/game/src/resources/textures/container.jpg", &widthContainer, &heightContainer, &nrChannelsContainer, 0);
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthContainer, heightContainer, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//stbi_image_free(data);

	//std::vector<BS::Texture> texturesCube;
	//texturesCube.reserve(1);
	//texturesCube.push_back({ textureContainer, "texture1" });

	 
	// TERRAIN TEXTURE

	uint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int widthTerrain, heightTerrain, nrChannelsTerrain;
	unsigned char* dataTerrain = stbi_load("C:/dev/game/game/src/resources/textures/iceland_heightmap.png", &widthTerrain, &heightTerrain, &nrChannelsTerrain, 0);
	if (dataTerrain)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthTerrain, heightTerrain, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataTerrain);
		glGenerateMipmap(GL_TEXTURE_2D);

		progTerrain.set_int("RandomHeightMap", 0);
		std::cout << "Loaded heightmap of size " << heightTerrain << " x " << widthTerrain << '\n';
	}
	else
	{ 
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(dataTerrain);

	const Geometry::SphericalCube* planet = new Geometry::SphericalCube(4, 2, {}, 4);
	//progPlanet.use();
	//progPlanet.set_float("u_radius", planet->radius);
	//progPlanet.unuse();

	const Geometry::SphericalCube* sphereCubeObj = new Geometry::SphericalCube(10000.f, 50, {}, 4);
	progSphereCube.use(); 
	progSphereCube.set_float("u_radius", sphereCubeObj->radius);
	progSphereCube.set_float("u_amplitude", 2500.f);
	progSphereCube.unuse();

	std::vector<Texture> texturesTerrain;
	texturesTerrain.reserve(1);
	texturesTerrain.push_back({ texture, "heightMap" });

	TerrainConfig  terrainConfig = { 4, 50, widthTerrain, widthTerrain };
	
	const Terrain* terrainObj = new Terrain(terrainConfig, texturesTerrain);
	 
	// Specify the number of vertices that make up each of our primitives; 
	// Our new primitive type is a patch;
	// A patch is an abstract primitive that is comprised of a set of n vertices that will be interpolated between;
	// The number of vertices per patch is specified CPU side;

	double timeStamp = 0.f;
	float dt = 0.0f;
	{
		timeStamp = glfwGetTime();
	}

	while (!glfwWindowShouldClose(window))
	{

		positioner.update(dt, mouseState.pos, mouseState.pressedLeft);

		const double newTimeStamp = glfwGetTime();
		dt = static_cast<float>(newTimeStamp - timeStamp);
		timeStamp = newTimeStamp;

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 worldMatrix = glm::mat4(1.0f);


		glm::mat4 viewMatrix = camera.getViewMatrix();
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 100000.0f);

		// NEW CUBE RENDERNING
		//progPlanet.use();
		//
		//progPlanet.set_mat4("projection", projectionMatrix);
		//progPlanet.set_mat4("model", worldMatrix);
		//progPlanet.set_mat4("view", viewMatrix);
		//
		//glBindVertexArray(planet->mesh->VAO);
		//glDrawArrays(GL_PATCHES, 0,
		//4 *
		//planet->numGLPatchesPerPlane * planet->numGLPatchesPerPlane * 6 );
		//glBindVertexArray(0);

		// CUBE RENDERING
		progSphereCube.use();
		
		progSphereCube.set_mat4("projection", projectionMatrix);
		progSphereCube.set_mat4("model", worldMatrix);
		progSphereCube.set_mat4("view", viewMatrix);
		progSphereCube.set_vec3("viewPos", positioner.getPosition());
		// progSphereCube.set_float("t", abs((float)sin(timeStamp)));
		progSphereCube.set_vec3("lightPos", v3( 
			(sphereCubeObj->radius * 50) * (float)cos(timeStamp/4),
			0, 
			(sphereCubeObj->radius * 100) * (float)sin(timeStamp/4)
		));
		//progSphereCube.set_float("radius", sphereCubeObj->radius *  abs((float)sin(newTimeStamp)));

		//progCube.set_vec3("ourColor", v3(1.0f, 1.0f, 1.0f));
		//BS::Geometry::draw_geometry(cubeObj, progCube);
		

		// Render terrain
		glBindVertexArray(sphereCubeObj->mesh->VAO);
		glDrawArrays(GL_PATCHES, 0,
			4 *
			sphereCubeObj->numGLPatchesPerPlane * sphereCubeObj->numGLPatchesPerPlane * 6
		);
		glBindVertexArray(0);

		progSphereCube.unuse();

		// TERRAIN RENDENING

		//progTerrain.use();
		//
		//// set uniforms
		//
		//progTerrain.set_mat4("projection", projectionMatrix);
		//progTerrain.set_mat4("model", worldMatrix);
		//progTerrain.set_mat4("view", viewMatrix);
		//
		//progTerrain.set_float("randomHeight", abs((float)sin(newTimeStamp)));
		//
		//progTerrain.set_vec3("ourColor", v3(1.0f, 1.0f, 1.0f));
		//
		//terrainObj->draw();
		//
		//progTerrain.unuse();

		const v3 camPos = camera.getPosition();

		std::cout << "Camera in World coordinates: (" << camPos.x << ", " << camPos.y << ", " << camPos.z << ")" << "\n";

	}

	delete terrainObj;
	terrainObj = nullptr;

	delete sphereCubeObj;
	sphereCubeObj = nullptr;

	delete planet;
	planet = nullptr;

	progPlanet.~GLProgram();
	progTerrain.~GLProgram();
	progSphereCube.~GLProgram();

	glfwDestroyWindow(window);

}
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
