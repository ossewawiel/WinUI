#include "framework.h"
#include "win_menu_bar.h"

win_menu_bar::win_menu_bar(NN(win_window*) window) :
	win_menu_item{ window, win::create_menu() }
{
	set_menu();
}

win_sub_menu& win_menu_bar::create_file_menu()
{
	return create_sub_menu(L"&File");
}

win_sub_menu& win_menu_bar::create_edit_menu()
{
	return create_sub_menu(L"&Edit");
}

win_sub_menu& win_menu_bar::create_sub_menu(std::wstring const& name)
{
	_sub_menus.emplace_back(win_sub_menu{ this, _sub_menus.size(), name });
	return _sub_menus.back();
	win::draw_menu_bar(window()->item_handle());
}
