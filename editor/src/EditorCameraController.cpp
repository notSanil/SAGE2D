#include "EditorCameraController.h"
#include "Sage/Core/Input.h"
#include "Sage/Core/Log.h"

namespace Sage {
	EditorCameraController::EditorCameraController(float width, float height)
		:viewportHeight(height), viewportWidth(width)
	{
		aspectRatio = width / height;
		camera = Camera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
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
		viewportHeight = height;
		viewportWidth = width;
		aspectRatio = width / height;
		camera.Resize(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
	}

	void EditorCameraController::OnEvent(Event& e)
	{
		Dispatcher dispatcher(e);
		dispatcher.Dispatch<Sage::MouseScrollEvent>(std::bind(&EditorCameraController::OnMouseScroll, this, std::placeholders::_1));
		dispatcher.Dispatch<Sage::MouseMovedEvent>(std::bind(&EditorCameraController::OnMouseMove, this, std::placeholders::_1));
	}

	void EditorCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		zoom -= e.GetYOffset() * 0.25f;
		zoom = zoom < 0.25f ? 0.25f : zoom;
		moveSpeed = zoom * baseMoveSpeed;
		camera.Resize(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
	}

	void EditorCameraController::OnMouseMove(MouseMovedEvent& e)
	{
		if (Input::IsMouseButtonPressed(MouseCode::ButtonRight) && !Input::IsKeyPressed(KeyCode::LeftShift))
		{
			auto translate = camera.GetTranslate();
			float xDelta = std::min(e.GetMouseXDelta(), 50.0f);
			float yDelta = std::min(e.GetMouseYDelta(), 50.0f);
			translate.x -= xDelta * 2.0f * aspectRatio * zoom / viewportWidth;
			translate.y -= yDelta *  2.0f * zoom / viewportHeight;
			camera.SetTranslate(translate);
		}
		else if (Input::IsKeyPressed(KeyCode::LeftShift) && Input::IsMouseButtonPressed(MouseCode::ButtonRight))
		{
			float slowDownFactor = 0.5f;
			if (Input::IsKeyPressed(KeyCode::LeftAlt))
				slowDownFactor *= 0.25f;
			float rotation = glm::degrees(camera.GetRotation());
			float xDelta = std::min(e.GetMouseXDelta(), 50.0f);
			rotation += xDelta * slowDownFactor;
			camera.SetRotation(glm::radians(rotation));
		}
	}
}