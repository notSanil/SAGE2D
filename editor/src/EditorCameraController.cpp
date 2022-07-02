#include "EditorCameraController.h"
#include "Sage/Core/Input.h"
#include "Sage/Core/Log.h"

namespace Sage {
	EditorCameraController::EditorCameraController(float width, float height)
		: camera(Camera(width, height))
	{
	}


	void EditorCameraController::OnStep(float deltaTime)
	{
		glm::vec2 translate = camera.GetTranslate();
		if (Input::IsKeyPressed(KeyCode::a))
			translate.x -= moveSpeed * deltaTime;
		
		if (Input::IsKeyPressed(KeyCode::d))
			translate.x += moveSpeed * deltaTime;

		if (Input::IsKeyPressed(KeyCode::w))
			translate.y -= moveSpeed * deltaTime;
		if (Input::IsKeyPressed(KeyCode::s))
			translate.y += moveSpeed * deltaTime;

		float rotation = glm::degrees(camera.GetRotation());
		if (Input::IsKeyPressed(KeyCode::q))
			rotation += rotateSpeed * deltaTime;
		if (Input::IsKeyPressed(KeyCode::e))
			rotation -= rotateSpeed * deltaTime;

		camera.SetTranslate(translate);
		camera.SetRotation(glm::radians(rotation));
	}

	void EditorCameraController::OnWindowResize(float width, float height)
	{
		camera.Resize(width, height);
	}

	void EditorCameraController::OnEvent(Event& e)
	{
		Dispatcher dispatcher(e);
		dispatcher.Dispatch<Sage::MouseScrollEvent>(std::bind(&EditorCameraController::OnMouseScroll, this, std::placeholders::_1));
	}

	void EditorCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		//TODO: Refactor this to ensure that the zoom stays outside the camera class
		float zoom = camera.GetZoom();
		zoom -= e.GetYOffset() * 0.25f;
		zoom = zoom < 0.25f ? 0.25f : zoom;
		camera.SetZoom(zoom);
	}
}