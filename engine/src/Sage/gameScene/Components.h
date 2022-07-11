#pragma once
#include <memory>
#include "Sage/texture/Texture.hpp"
#include <glm/glm.hpp>
#include "Sage/gameScene/NativeScript.h"

namespace Sage {
	struct SpriteRendererComponent
	{
		enum Primitives
		{
			None,
			Rectangle,
			COUNT
		};
		std::shared_ptr<Texture> texture = nullptr;
		int hash = NULL;
		glm::vec4 Color{ 1, 1, 1, 1 };
		Primitives primitive = None;
	};

	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(int x, int y)
			: Position{ x, y }
		{}

		glm::vec2 Position{ 0, 0 };
		glm::vec2 Scale{ 1, 1 };
		float Rotation = 0.0f;
	};

	struct NameComponent
	{
		NameComponent(const std::string& name = "NewEntity")
			: Name(name)
		{}
		std::string Name;
	};

	struct AnimatorComponent
	{
		glm::ivec2 SheetGrid{ 1, 1 };
		int Speed = 1;
		int CurrentFrame = 0;
	};

	struct NativeScriptComponent
	{
		NativeScript* script = nullptr;

		NativeScript* (*CreateScript)();
		void (*DestroyScript)(NativeScriptComponent*);


		template <typename T>
		void Bind()
		{
			CreateScript = []() {return (NativeScript*)new T; };
			DestroyScript = [](NativeScriptComponent* component) {
				delete component->script;
				component->script = nullptr;
			};
		}
	};
}