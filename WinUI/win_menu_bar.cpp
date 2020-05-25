#include "framework.h"
#include "win_menu_bar.h"
#include "win_window.h"

win_menu_bar::win_menu_bar(NN(win_window*) window) :
	win_menu_item{ window, win::create_menu() }
{
	MENUINFO mi{};
	mi.cbSize = sizeof(MENUINFO);
	mi.fMask = MIM_BACKGROUND;
	mi.hbrBack = window->_theme.clr_menubar_bkg;
	mi.dwStyle = MNS_AUTODISMISS;
	THROW_IF_WIN32_BOOL_FALSE(::SetMenuInfo(handle(), &mi));
	set_menu();
	win::draw_menu_bar(window->item_handle());
}

win_menu_sub& win_menu_bar::add_file_menu()
{
	return add_sub_menu(L"&File", win_window::M_FILE);
}

win_menu_sub& win_menu_bar::add_edit_menu()
{
	return add_sub_menu(L"&Edit", win_window::M_EDIT);
}

win_menu_sub& win_menu_bar::add_action_menu()
{
	return add_sub_menu(L"&Action", win_window::M_ACTION);
}

win_menu_sub& win_menu_bar::add_view_menu()
{
	return add_sub_menu(L"&View", win_window::M_VIEW);
}

win_menu_sub& win_menu_bar::add_window_menu()
{
	return add_sub_menu(L"&Window", win_window::M_WINDOW);
}

win_menu_sub& win_menu_bar::add_help_menu()
{
	return add_sub_menu(L"&Help", win_window::M_HELP);
}

win_menu_sub& win_menu_bar::add_sub_menu(std::wstring const& name, UINT id)
{
	_sub_menus.emplace_back(win_menu_sub{ window(), handle(), static_cast<UINT>(win::get_menu_item_count(handle())), id, name });
	return _sub_menus.back();
}
