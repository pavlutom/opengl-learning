#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "shader.h"
#include "texture.h"


#define WINDOW_BASE_WIDTH 800
#define WINDOW_BASE_HEIGHT 600
#define WINDOW_BASE_TITLE "GL test"
#define FPS_UPDATE_INTERVAL_S 0.5
#define FOV_Y 45.0f


float WINDOW_WIDTH = 1.0f, WINDOW_HEIGHT = 1.0f;


float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

// GLOBALS
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouse = true;
float lastX = WINDOW_BASE_WIDTH / 2;
float lastY = WINDOW_BASE_HEIGHT / 2;
bool mouseRightPressed = false;

double t1, t2 = 0.0, dt = 0.0, dtThis;
int frameCtr = 0.0, fps;


bool isKeyPressed(GLFWwindow* window, int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}


// Window resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WINDOW_WIDTH = (float)width;
	WINDOW_HEIGHT = (float)height;
}

// Mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!mouseRightPressed) return;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouseRightPressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseRightPressed = false;
			firstMouse = true;
		}
	}
}


// Input processing
void processInput(GLFWwindow* window)
{
	if (isKeyPressed(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	float slowCoef = 1.0;
	const float cameraSpeed = 3.5f * dtThis;
	if (isKeyPressed(window, GLFW_KEY_W)) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (isKeyPressed(window, GLFW_KEY_S)) {
		slowCoef = 0.25;
		cameraPos -= cameraSpeed * cameraFront * slowCoef;
	}
	if (isKeyPressed(window, GLFW_KEY_A)) {
		if (mouseRightPressed) {
			cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp)) * slowCoef;
		}
		else {
			yaw -= cameraSpeed * 30.0f;
		}
	}
	if (isKeyPressed(window, GLFW_KEY_D)) {
		if (mouseRightPressed) {
			cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp)) * slowCoef;
		}
		else {
			yaw += cameraSpeed * 30.0f;
		}
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}


// Rendering
void render(unsigned int VAO, const Shader& shader, std::vector<Texture> textures)
{
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// clear
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// projection
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(FOV_Y), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

	// Camera
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// shaders
	shader.Use();
	
	// textures
	for (unsigned short i = 0; i < textures.size(); i++)
	{
		textures[i].Bind(i);
		shader.setInt("tex" + std::to_string(i + 1), i);
	}
	glBindVertexArray(VAO);

	// transforms
	shader.setMatF4("view", glm::value_ptr(view));
	shader.setMatF4("projection", glm::value_ptr(projection));
	for (unsigned int i = 0; i < 10; i++)
	{
		// define model transform per cube
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setMatF4("model", glm::value_ptr(model));

		// draw
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// unbind VAO
	glBindVertexArray(0);
}


int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, WINDOW_BASE_TITLE, NULL, NULL);
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return - 1;
	}
	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Viewport
	framebuffer_size_callback(window, WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Disable VSync
	//glfwSwapInterval(0);

	// Cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Buffers
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// bind VAO
	glBindVertexArray(VAO);

	// copy vertices array into vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set the vertex attributes pointers
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind VAO
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	// Textures
	stbi_set_flip_vertically_on_load(true);
	Texture textureContainer("resources/images/container.jpg");
	Texture textureFace("resources/images/awesomeface.png");
	std::vector<Texture> textures = { textureContainer, textureFace };

	// Shaders
	Shader defaultShader("resources/shaders/default");
	if (!defaultShader.IsLoaded())
	{
		std::cerr << "Failed to compile shaders." << std::endl;
		return -1;
	}

	std::string title = WINDOW_BASE_TITLE;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// FPS counter
		t1 = t2;
		t2 = glfwGetTime();
		dtThis = t2 - t1;
		dt += dtThis;
		frameCtr++;
		if (dt >= FPS_UPDATE_INTERVAL_S)
		{
			fps = (int)(frameCtr / dt);
			dt = 0.0;
			frameCtr = 0;

			title = WINDOW_BASE_TITLE + (" (" + std::to_string(fps) + " FPS)");
			glfwSetWindowTitle(window, title.c_str());
		}

		// Input
		processInput(window);

		// Rendering
		render(VAO, defaultShader, textures);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
