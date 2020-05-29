#pragma once
#include "framework.h"
#include "win_app.h"

class win_item
{
public:
	win_item(NN(win_app*) app): _app{ app }
	{}

	win_item(NN(win_item*) parent) : 
		_app{ parent->_app },
		_parent{ parent }
	{}

	~win_item()
	{
		_item_map.erase(_item_handle.get());
	}

	HWND item_handle() { return _item_handle.get(); }
	std::map<UINT, std::wstring>& tb_tooltips() { return _tb_tooltips; }

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
		win::init_common_controls();

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

	void item_handle(HWND handle) { _item_handle.reset(handle); }
	HINSTANCE app_handle() { return _app->hinstance(); }
	
	win_item* parent() { return _parent; }
	wil::unique_hwnd	_item_handle{ nullptr };
	static std::map<HWND, win_item*> _item_map;
	win_app* _app{ nullptr };
private:
	
	
	win_item*			_parent{ nullptr };
	std::map<UINT, std::wstring> _tb_tooltips;
	//

	
	

	//

};

using win_item_map = std::map<HWND, win_item*>;

