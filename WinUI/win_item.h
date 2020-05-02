#pragma once
#include "framework.h"
#include "win_app.h"

class win_item
{
public:
	win_item(gsl::not_null<win_app*> app): _app{ app }
	{}

	HWND item_handle() { return _item_handle.get(); }

	void show();
	LRESULT virtual event_handler(UINT, WPARAM, LPARAM) = 0;

	static std::map<HWND, win_item*> item_map() { return _item_map; }

protected:
	void create_main_window(
		HMENU menu
		, std::wstring const& class_name
		, std::wstring const& window_name
		, win::enum_ex_style ex_style
		, win::enum_style style, win::position pos
		, win::dimensions dim)
	{
		_item_handle = create_item(
			_app->hinstance()
			, nullptr
			, menu
			, class_name
			, window_name
			, ex_style
			, style
			, pos
			, dim);
		_item_map.emplace(_item_handle.get(), this);
	}

	
	

private:
	win_app* _app{ nullptr };
	wil::unique_hwnd _item_handle{ nullptr };

	//

	

	//

	static std::map<HWND, win_item*> _item_map;
};

using win_item_map = std::map<HWND, win_item*>;

