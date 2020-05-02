#pragma once
#include "win_menu_item.h"
#include "win_menu_sub.h"

class win_menu_bar :
	public win_menu_item
{
public:
	win_menu_bar(NN(win_window*) window);

	[[nodiscard]] win_menu_sub& create_file_menu();
	[[nodiscard]] win_menu_sub& create_edit_menu();

	[[nodiscard]] win_menu_sub& create_sub_menu(std::wstring const& name);

private:

	std::vector<win_menu_sub> _sub_menus{};
};