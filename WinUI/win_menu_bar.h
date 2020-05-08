#pragma once
#include "win_menu_item.h"
#include "win_menu_sub.h"

class win_menu_bar :
	public win_menu_item
{
public:
	win_menu_bar(NN(win_window*) window);

	[[nodiscard]] win_menu_sub& add_file_menu();
	[[nodiscard]] win_menu_sub& add_edit_menu();
	[[nodiscard]] win_menu_sub& add_view_menu();
	[[nodiscard]] win_menu_sub& add_window_menu();
	[[nodiscard]] win_menu_sub& add_help_menu();
	[[nodiscard]] win_menu_sub& add_sub_menu(std::wstring const& name, UINT id);

	

private:
	
	std::vector<win_menu_sub> _sub_menus{};

	
};