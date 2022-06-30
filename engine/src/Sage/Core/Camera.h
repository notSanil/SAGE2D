#pragma once
#include <glm/glm.hpp>


namespace Sage {
	class Camera
	{
	public:
		Camera() = default;
		Camera(float width, float height);

		glm::mat4& GetProjection() { return projection; }
		glm::mat4 GetViewProjection() { return projection * view; }
		glm::mat4& GetView() { return view; }
		void Resize(float width, float height);

		void SetRotation(float newRotation) { rotation = newRotation; RecalculateView(); }
		float GetRotation() { return rotation; }
		void SetTranslate(glm::vec2 newTranslate) { translation = newTranslate; RecalculateView(); }
		glm::vec2 GetTranslate() { return translation; }


	private:
		void RecalculateView();
	private:
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec2 translation = glm::vec2();
		float rotation = 0.0f;
	};
}