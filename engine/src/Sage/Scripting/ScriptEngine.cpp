#include "ScriptEngine.h"
#include "Sage/Core/Log.h"
#include <sol/sol.hpp>
#include "Sage/renderer/renderer.hpp"
#include <glm/glm.hpp>

namespace Sage {
	static struct ScriptEngineData
	{
		sol::state* LuaState = nullptr;
		sol::function* renderFunc = nullptr;
	};

	static bool loaded = false;

	static int panicFunc(lua_State* L) 
	{
		size_t messagesize;
		const char* message = lua_tolstring(L, -1, &messagesize);
		if (message) {
			std::string err(message, messagesize);
			lua_settop(L, 0);

			SAGE_CORE_CRIT("Lua panic. {0}", err);
		}
		lua_settop(L, 0);
		return 0;
	}
	
	static ScriptEngineData scriptEngineData;
	void ScriptEngine::Init()
	{
		scriptEngineData.LuaState = new sol::state();
		scriptEngineData.LuaState->open_libraries(sol::lib::base);
		scriptEngineData.LuaState->set_panic(panicFunc);

		RegisterSystems();
		ExecuteScript("assets/scripts/test.lua");
	}

	void ScriptEngine::Destroy()
	{
		delete scriptEngineData.LuaState;
	}

	void ScriptEngine::RegisterSystems()
	{
		RegisterVectors();
		RegisterTexture();
		RegisterRenderer();
	}

	void ScriptEngine::RegisterVectors()
	{
		auto vec2 = scriptEngineData.LuaState->new_usertype<glm::vec2>("Vector2", 
			sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>());

		vec2["x"] = &glm::vec2::x;
		vec2["y"] = &glm::vec2::y;

		auto vec4 = scriptEngineData.LuaState->new_usertype<glm::vec4>("Vector4",
			sol::constructors<glm::vec4(), glm::vec4(float), glm::vec4(float, float, float, float)>());
		vec4["r"] = &glm::vec4::r;
		vec4["g"] = &glm::vec4::g;
		vec4["b"] = &glm::vec4::b;
		vec4["a"] = &glm::vec4::a;
	}

	void ScriptEngine::RegisterTexture()
	{
		auto texture = scriptEngineData.LuaState->new_usertype<Texture>("Texture", sol::no_constructor);
		texture["GetWidth"] = &Texture::getWidth;
		texture["GetHeight"] = &Texture::getHeight;

		auto textureManager = scriptEngineData.LuaState->new_usertype<TextureManager>("TextureManager", sol::no_constructor);

	}

	void ScriptEngine::RegisterRenderer()
	{
		auto renderer = scriptEngineData.LuaState->new_usertype<Renderer>("Renderer", sol::no_constructor);

		renderer["RenderRect"] = &Renderer::RenderRect;
	}

	void ScriptEngine::ExecuteScript(const std::string& path)
	{
		if (!loaded)
		{
			scriptEngineData.LuaState->script_file(path);
			loaded = true;
		}
		sol::function render = scriptEngineData.LuaState->operator[]("OnRender");

		render();
	}

	void ScriptEngine::OnRender()
	{
		scriptEngineData.renderFunc->operator()();
	}
}