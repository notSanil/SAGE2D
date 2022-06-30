#include "Serialiser.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <entt.hpp>
#include "Entity.h"
#include "Components.h"
#include <glm/glm.hpp>

namespace YAML {
	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::ivec2>
	{
		static Node encode(const glm::ivec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, glm::ivec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<int>();
			rhs.y = node[1].as<int>();
			return true;
		}
	};
	
	template<>
	struct convert<glm::ivec4>
	{
		static Node encode(const glm::ivec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::ivec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<int>();
			rhs.y = node[1].as<int>();
			rhs.z = node[2].as<int>();
			rhs.w = node[3].as<int>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}



namespace Sage {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::ivec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	void SerialiseEntity(Entity entity, YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity";
		out << YAML::Flow;
		out << YAML::BeginSeq << (uint32_t)entity << YAML::EndSeq;
		if (entity.HasComponent<NameComponent>())
		{
			out << YAML::Key << "NameComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "Name";
			out << YAML::Value << entity.GetComponent<NameComponent>().Name;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;

			auto& transform = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Position";
			out << YAML::Value << transform.Position;
			out << YAML::Key << "Scale";
			out << YAML::Value << transform.Scale;
			out << YAML::Key << "Rotation";
			out << YAML::Value << transform.Rotation;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap;

			auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Texture";
			out << YAML::Value << spriteRenderer.hash;

			out << YAML::Key << "Color";
			out << YAML::Value << spriteRenderer.Color;		

			out << YAML::EndMap;
		}

		if (entity.HasComponent<AnimatorComponent>())
		{
			out << YAML::Key << "AnimatorComponent";
			out << YAML::BeginMap;

			auto& animatorComponent = entity.GetComponent<AnimatorComponent>();
			out << YAML::Key << "SheetGrid";
			out << YAML::Value << animatorComponent.SheetGrid;

			out << YAML::Key << "Speed";
			out << YAML::Value << animatorComponent.Speed;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void Serialiser::SerialiseScene(GameScene* scene, const std::string& path)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << scene->GetName();
		out << YAML::Key << "Entities" << YAML::BeginSeq;
		scene->registry.each([&](const entt::entity entity) {
			Entity e{ entity, scene };
			SerialiseEntity(e, out);
		});

		out << YAML::EndSeq;

		out << YAML::Key << "Assets";
		
		out << YAML::BeginMap;
		std::hash <std::string> hasher;
		for (auto& [path, texture] : TextureManager::loadedTextures)
		{
			int id = hasher(path);
			out << YAML::Key << id << YAML::Value << path;
		}
		out << YAML::EndMap;

		out << YAML::EndMap;

		std::ofstream file(path);
		file << out.c_str();
	}

	void DeserialiseEntity(Entity entity, YAML::Node& data, YAML::Node& assets)
	{
		if (data["NameComponent"])
		{
			auto& name = entity.GetComponent<NameComponent>();
			name.Name = data["NameComponent"]["Name"].as<std::string>();
		}

		if (data["TransformComponent"])
		{
			YAML::Node transformComponentData = data["TransformComponent"];
			auto& transform = entity.GetComponent<TransformComponent>();
			transform.Position = transformComponentData["Position"].as<glm::vec2>();
			transform.Scale = transformComponentData["Scale"].as<glm::vec2>();
			transform.Rotation = transformComponentData["Rotation"].as<float>();
		}

		if (data["SpriteRendererComponent"])
		{
			YAML::Node spriteRendererData = data["SpriteRendererComponent"];
			auto& spriteRenderer = entity.AddComponent<SpriteRendererComponent>();
			spriteRenderer.Color = spriteRendererData["Color"].as<glm::vec4>();
			spriteRenderer.hash = spriteRendererData["Texture"].as<int>();
			std::string texturePath = assets[spriteRenderer.hash].as<std::string>();
			spriteRenderer.texture = TextureManager::load(texturePath);
		}

		if (data["AnimatorComponent"])
		{
			YAML::Node animatorComponentData = data["AnimatorComponent"];

			auto& animatorComponent = entity.AddComponent<AnimatorComponent>();
			animatorComponent.SheetGrid = animatorComponentData["SheetGrid"].as<glm::ivec2>();
			animatorComponent.Speed = animatorComponentData["Speed"].as<int>();
		}
	}

	void Serialiser::DeserialiseScene(const std::string& path, GameScene* outScene)
	{
		YAML::Node sceneData = YAML::LoadFile(path);
		YAML::Node entities = sceneData["Entities"];
		YAML::Node assets = sceneData["Assets"];

		std::string sceneName = sceneData["Scene"].as<std::string>();
		outScene->SetName(sceneName);
		
		//The entities are saved in reverse order so we iterate backwards
		for (int i = entities.size() - 1; i >= 0; --i)
		{
			uint32_t id = entities[i]["Entity"][0].as<uint32_t>();
			Entity created = outScene->CreateEntity();
			DeserialiseEntity(created, entities[i], assets);
		}
	}
}