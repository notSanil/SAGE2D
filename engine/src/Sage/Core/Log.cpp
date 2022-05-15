#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>



namespace Sage {
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	std::shared_ptr<spdlog::logger> Log::engineLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T]%n: %v%$");
		clientLogger = spdlog::stdout_color_mt("APP");
		clientLogger->set_level(spdlog::level::trace);

		engineLogger = spdlog::stdout_color_mt("SAGE");
		engineLogger->set_level(spdlog::level::trace);
	}
	std::shared_ptr<spdlog::logger> Log::getClientLogger()
	{
		return clientLogger;
	}
	std::shared_ptr<spdlog::logger> Log::getEngineLogger()
	{
		return engineLogger;
	}
}