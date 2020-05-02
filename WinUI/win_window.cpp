#include "framework.h"
#include "win_msg.h"
#include "win_window.h"


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

void win_window::set_on_close_window(on_close_window_type func)
{
	_on_close_window = func;
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
	case WM_CLOSE:
	{
		auto do_close = true;
		if (_on_close_window)
			do_close = _on_close_window();

		if (do_close)
			::DestroyWindow(item_handle());
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(item_handle(), msg, wp, lp);
	}

	return 0;
}


