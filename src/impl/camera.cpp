#include "camera.h"


Camera::Camera(glm::vec3 pos, float speed, float sensitivity, float slowFactor)
{
	this->speed = speed;
	this->sensitivity = sensitivity;
	this->slowFactor = slowFactor;

	this->firstMouse = true;
	this->rightPressed = false;
	this->lastX = 0.0f;
	this->lastY = 0.0f;

	this->yaw = -90.0f;
	this->pitch = 0.0f;

	this->pos = pos;
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (!this->rightPressed) return;

	if (firstMouse)
	{
		this->lastX = xPos;
		this->lastY = yPos;
		this->firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	this->lastX = xPos;
	this->lastY = yPos;

	xOffset *= this->sensitivity;
	yOffset *= this->sensitivity;

	this->yaw   += xOffset;
	this->pitch += yOffset;

	if (this->pitch >  89.0f) this->pitch =  89.0f;
	if (this->pitch < -89.0f) this->pitch = -89.0f;
}

void Camera::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->rightPressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			this->rightPressed = false;
			this->firstMouse = true;
		}
	}
}

void Camera::ProcessInput(GLFWwindow* window, float dt)
{
	float slow = 1.0f;

	// W
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->pos += this->speed * dt * this->front;
	}

	// S
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		slow = this->slowFactor;
		this->pos -= this->speed * dt * this->front * slow;
	}

	// A
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (this->rightPressed)
		{
			this->pos -= this->speed * dt * glm::normalize(glm::cross(this->front, this->up)) * slow;
		}
		else
		{
			this->yaw -= this->speed * dt * 30.0f;
		}
	}

	// D
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (this->rightPressed)
		{
			this->pos += this->speed * dt * glm::normalize(glm::cross(this->front, this->up)) * slow;
		}
		else
		{
			this->yaw += this->speed * dt * 30.0f;
		}
	}

	// direction vector
	glm::vec3 direction(
		cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
		sin(glm::radians(this->pitch)),
		sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
	);
	this->front = glm::normalize(direction);
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(this->pos, this->pos + this->front, this->up);
}
