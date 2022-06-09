#pragma once
#include "GameScene.h"

namespace Sage {
	class Serialiser
	{
	public:
		static void SerialiseScene(GameScene* scene, const std::string& path);
		static void DeserialiseScene(const std::string& path, GameScene* outScene);
	};
}