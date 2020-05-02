#pragma once
#include "framework.h"

static void error_msg(std::wstring const& title, std::wstring const& msg) noexcept
{
	::MessageBoxW(0, msg.c_str(), title.c_str(), MB_OK | MB_ICONSTOP | MB_TASKMODAL);
}

static void exception_msg(std::string const& title, std::exception const& ex)
{
	::MessageBoxA(0, ex.what(), title.c_str(), MB_OK | MB_ICONSTOP | MB_TASKMODAL);
}

static bool yesno_msg(std::wstring const& title, std::wstring const& msg)
{
	auto result = ::MessageBoxW(0, msg.c_str(), title.c_str(), MB_YESNO | MB_ICONQUESTION | MB_TASKMODAL);

	return result == 7 ? false : true;
}

static void info_msg(std::wstring const& title, std::wstring const& msg)
{
	auto result = ::MessageBoxW(0, msg.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}
