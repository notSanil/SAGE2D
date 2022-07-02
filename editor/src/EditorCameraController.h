#pragma once
#include "Sage/Core/Camera.h"
#include "Sage/Events/Event.h"
#include "Sage/Events/MouseEvent.h"

namespace Sage {
	class EditorCameraController
	{
	public:
		EditorCameraController() = default;
		EditorCameraController(float width, float height);
		void OnStep(float deltaTime);
		void OnWindowResize(float width, float height);
		void OnEvent(Event& e);

		Camera& GetCamera() { return camera; }
		const Camera& GetCamera() const { return camera; }
	private:
		void OnMouseScroll(MouseScrollEvent& e);

	private:
		Camera camera;
		const float moveSpeed = 5.0f;
		const float rotateSpeed = 45.0f;
	};
}