#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Sloth {
	class SLOTH_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define SLTH_CORE_TRACE(...) ::Sloth::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SLTH_CORE_INFO(...)  ::Sloth::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SLTH_CORE_WARN(...)  ::Sloth::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SLTH_CORE_ERROR(...) ::Sloth::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SLTH_CORE_CRITICAL(...) ::Sloth::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SLTH_TRACE(...)      ::Sloth::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SLTH_INFO(...)       ::Sloth::Log::GetClientLogger()->info(__VA_ARGS__)
#define SLTH_WARN(...)       ::Sloth::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SLTH_ERROR(...)      ::Sloth::Log::GetClientLogger()->error(__VA_ARGS__)
#define SLTH_CRITICAL(...)   ::Sloth::Log::GetClientLogger()->critical(__VA_ARGS__)
#define SLTH_CRITICAL(...)   ::Sloth::Log::GetClientLogger()->critical(__VA_ARGS__) 