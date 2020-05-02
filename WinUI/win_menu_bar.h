#pragma once
#include "win_menu.h"
#include "win_sub_menu.h"

class win_menu_bar :
	public win_menu_item
{
public:
	win_menu_bar(NN(win_window*) window);

	[[nodiscard]] win_sub_menu& create_file_menu();
	[[nodiscard]] win_sub_menu& create_edit_menu();

	[[nodiscard]] win_sub_menu& create_sub_menu(std::wstring const& name);

private:

	std::vector<win_sub_menu> _sub_menus{};
};