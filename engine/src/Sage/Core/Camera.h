#pragma once
#include <glm/glm.hpp>


namespace Sage {
	class Camera
	{
	public:
		Camera() = default;
		Camera(float left, float right, float top, float bottom);

		glm::mat4& GetProjection() { return projection; }
		glm::mat4 GetViewProjection() const { return projection * view; }
		glm::mat4& GetView() { return view; }
		void Resize(float left, float right, float bottom, float top);

		void SetRotation(float newRotation) { rotation = newRotation; RecalculateView(); }
		float GetRotation() const { return rotation; }
		void SetTranslate(glm::vec2 newTranslate) { translation = newTranslate; RecalculateView(); }
		glm::vec2 GetTranslate() const { return translation; }

	private:
		void RecalculateView();
	private:
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		glm::vec2 translation = glm::vec2();
		float rotation = 0.0f;
	};
}