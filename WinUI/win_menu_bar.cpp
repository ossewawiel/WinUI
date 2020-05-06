#include "framework.h"
#include "win_menu_bar.h"
#include "win_window.h"

win_menu_bar::win_menu_bar(NN(win_window*) window) :
	win_menu_item{ window, win::create_menu() }
{
	set_menu();
}

win_menu_sub& win_menu_bar::create_file_menu()
{
	return create_sub_menu(L"&File", M_FILE);
}

win_menu_sub& win_menu_bar::create_edit_menu()
{
	return create_sub_menu(L"&Edit", M_EDIT);
}

win_menu_sub& win_menu_bar::create_view_menu()
{
	return create_sub_menu(L"&View", M_VIEW);
}

win_menu_sub& win_menu_bar::create_window_menu()
{
	return create_sub_menu(L"&Window", M_WINDOW);
}

win_menu_sub& win_menu_bar::create_help_menu()
{
	return create_sub_menu(L"&View", M_HELP);
}

win_menu_sub& win_menu_bar::create_sub_menu(std::wstring const& name, UINT id)
{
	_sub_menus.emplace_back(win_menu_sub{ this, static_cast<UINT>(win::get_menu_item_count(handle())), name });
	win::draw_menu_bar(window()->item_handle());

	return _sub_menus.back();

}
