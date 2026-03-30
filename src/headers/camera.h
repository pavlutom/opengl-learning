#pragma once

#include <utility>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 pos, float speed = 3.5f, float sensitivity = 0.1f, float slowFactor = 0.25f);
	void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void ProcessInput(GLFWwindow* window, float dt);
	glm::mat4 GetView() const;

private:
	float speed;
	float sensitivity;
	float slowFactor;

	bool firstMouse;
	float lastX;
	float lastY;
	bool rightPressed;

	float yaw;
	float pitch;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
};