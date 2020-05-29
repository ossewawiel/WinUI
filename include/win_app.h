#pragma once
#include "framework.h"
#include <wil\resource.h>
#include <wil\result.h>


class win_app
{
	static wil::unique_hmodule _instance;
	static wil::unique_hmodule _prev_instance;
	static std::wstring _cmd_line;
	static int _cmd_show;

public:
	win_app(std::wstring const& app_title) : _app_title{ app_title } {}

	virtual ~win_app() = default;

	//

	std::wstring const& app_title() const noexcept { return _app_title; }

	//

	int run();

	//


	static void hinstance(HINSTANCE val) { _instance = wil::unique_hmodule(val); }
	static HINSTANCE hinstance() { return _instance.get(); }

	static void prev_hinstance(HINSTANCE val) { _prev_instance = wil::unique_hmodule(val); }
	static HINSTANCE prev_hinstance() { return _prev_instance.get(); }

	static void cmd_line(PWSTR val) { _cmd_line = std::wstring{ val }; }
	static std::wstring const& cmd_line() { return _cmd_line; }

	static void cmd_show(int val) { _cmd_show = val; }
	static int const& cmd_show() { return _cmd_show; }

protected:
	virtual void init() = 0;

	

private:
	std::wstring _app_title{};
	ATOM		_class_atom{};

	//

	WNDCLASSEX win_class(std::wstring const& name, UINT icon_id = 0) noexcept;
	ATOM register_class(WNDCLASSEX const& the_class);

	//

	static LRESULT CALLBACK callback_msg_handler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//

	friend class win_window;
	friend class win_bitmap;
	friend class win_panel;
};

