#pragma once
#include <string>

namespace Sage {
	class ScriptEngine
	{
	public:
		static void Init();
		static void Destroy();
		static void ExecuteScript(const std::string& path);
		static void OnRender();

	private:
		static void RegisterSystems();
		static void RegisterRenderer();
		static void RegisterVectors();
		static void RegisterTexture();
	};
}