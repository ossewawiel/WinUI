#include "framework.h"
#include "win_msg.h"
#include "win_window.h"
#include "win_menu_sub.h"

win_window::win_window(gsl::not_null<win_app*> app, std::wstring title) :
	win_item{app},
	_app{ app }
{
	try
	{
		_app->register_class(_app->win_class(_win_class));

		win_item::create_main_window(
			nullptr
			, _win_class
			, title.empty() ? _app->app_title() : title
			, win::enum_ex_style::NONE
			, win::enum_style::OVERLAPPEDWINDOW
			, win::position{ CW_USEDEFAULT, 0 }
			, win::dimensions{ CW_USEDEFAULT, 0 });
	}
	CATCH_RUNTIME_WITH_MSG;
}

win_menu_command& win_window::menu_cmd(UINT cmd)
{
	try
	{
		if (_cmd_type.count(cmd) == 0)
			throw std::exception("Menu command requested does not exist");
		return _cmd_type.at(cmd);
	}
	CATCH_RUNTIME_WITH_MSG;
}

void win_window::set_on_close_window(on_close_window_type func)
{
	_on_close_window = func;
}

void win_window::set_on_menu_item_clicked(on_menu_item_clicked func)
{
	_on_menu_item_clicked = func;
}

void win_window::set_on_menu_item_checked(on_menu_item_checked func)
{
	_on_menu_item_checked = func;
}

//METHODS//

void win_window::close() 
{ 
	auto do_close = true;
	if (_on_close_window)
		do_close = _on_close_window();

	if (do_close)
		win::destroy_window(item_handle());
}

LRESULT win_window::event_handler(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(item_handle(), &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(item_handle(), &ps);
	}
	break;
	case WM_COMMAND:
	{
		auto cmd_id = LOWORD(wp);
		auto cmd = menu_cmd(cmd_id);
		switch (cmd.type())
		{
		case win::enum_menu_cmd_type::CHECKABLE:
			if (_on_menu_item_checked)
			{
				_on_menu_item_checked(cmd_id, win::do_menu_item_checked(cmd.parent()->handle(), cmd_id));
			}
			break;
		case win::enum_menu_cmd_type::ACTION:
			if (_on_menu_item_clicked)
				_on_menu_item_clicked(cmd_id);
			break;
		default:
			break;
		}
	}
	break;
	case WM_CLOSE:
		close();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(item_handle(), msg, wp, lp);
	}

	return 0;
}

void win_window::add_menu_cmd(UINT id, win_menu_command const& cmd)
{
	if(_cmd_type.count(id) == 0)
		_cmd_type.insert(std::make_pair(id, cmd));
}


