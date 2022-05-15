#pragma once
#include <memory>
#include <spdlog/spdlog.h>


namespace Sage {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> getClientLogger();
		static std::shared_ptr<spdlog::logger> getEngineLogger();

	private:
		static std::shared_ptr<spdlog::logger> clientLogger;
		static std::shared_ptr<spdlog::logger> engineLogger;
	};
}

#define SAGE_CORE_TRACE(...) ::Sage::Log::getEngineLogger()->trace(__VA_ARGS__)
#define SAGE_CORE_INFO(...) ::Sage::Log::getEngineLogger()->info(__VA_ARGS__)
#define SAGE_CORE_WARN(...) ::Sage::Log::getEngineLogger()->warn(__VA_ARGS__)
#define SAGE_CORE_ERROR(...) ::Sage::Log::getEngineLogger()->error(__VA_ARGS__)
#define SAGE_CORE_CRIT(...) ::Sage::Log::getEngineLogger()->critical(__VA_ARGS__)

#define SAGE_TRACE(...) ::Sage::Log::getClientLogger()->trace(__VA_ARGS__)
#define SAGE_INFO(...) ::Sage::Log::getClientLogger()->info(__VA_ARGS__)
#define SAGE_WARN(...) ::Sage::Log::getClientLogger()->warn(__VA_ARGS__)
#define SAGE_ERROR(...) ::Sage::Log::getClientLogger()->error(__VA_ARGS__)
#define SAGE_CRIT(...) ::Sage::Log::getClientLogger()->critical(__VA_ARGS__)

