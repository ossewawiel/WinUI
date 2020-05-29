#include "framework.h"
#include "win_panel.h"
#include "win_app.h"

win_panel::win_panel(NN(win_item*) parent, UINT panel_id):
	win_item{ parent }
{

	_app->register_class(_app->win_class(_panel_class));

	win_item::_item_handle = win::create_item(
		win_app::hinstance()
		, parent->item_handle()
		, nullptr
		, _panel_class
		, L""
		, win::enum_ex_style::NONE
		, win::enum_style::PANEL
		, win::position{ CW_USEDEFAULT, 0 }
		, win::dimensions{ CW_USEDEFAULT, 0 });


	_item_map.emplace(_item_handle.get(), this);

    
}

LRESULT win_panel::event_handler(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		RECT rcClient;
		GetClientRect(parent()->item_handle(), &rcClient);
	}
	}
	return 0;
}
