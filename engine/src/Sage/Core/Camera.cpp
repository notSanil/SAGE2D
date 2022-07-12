#include "Camera.h"
#include <glm/ext.hpp>

namespace Sage {
	Camera::Camera(float left, float right, float bottom, float top)
		:Left(left), Right(right), Bottom(bottom), Top(top)
	{
		projection = glm::ortho(left, right, bottom, top);
		view = glm::mat4(1.0f);
	}

	void Camera::Resize(float left, float right, float bottom, float top)
	{
		Left = left;
		Right = right;
		Bottom = bottom;
		Top = top;
		projection = glm::ortho(left, right, bottom, top);
	}

	void Camera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { translation.x, translation.y, 0.0f }) * 
			glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });

		view = glm::inverse(transform);
	}
}