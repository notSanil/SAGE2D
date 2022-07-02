#include "Camera.h"
#include <glm/ext.hpp>

namespace Sage {
	Camera::Camera(float width, float height)
		:width(width), height(height)
	{
		float m_AspectRatio = width / height;
		projection = glm::ortho(-m_AspectRatio * zoom, m_AspectRatio * zoom, -zoom, zoom);
		//projection = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1.0f, 1.0f);
		view = glm::mat4(1.0f);
	}

	void Camera::Resize(float width, float height)
	{
		this->width = width;
		this->height = height;
		float m_AspectRatio = width / height;
		RecalculateProjection();
		//projection = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1.0f, 1.0f);
	}

	void Camera::RecalculateView()
	{
		//view = glm::mat4(1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { translation.x, translation.y, 0.0f }) * 
			glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });

		view = glm::inverse(transform);
	}

	void Camera::RecalculateProjection()
	{
		float m_AspectRatio = width / height;
		projection = glm::ortho(-m_AspectRatio * zoom, m_AspectRatio * zoom, -zoom, zoom);
	}
}