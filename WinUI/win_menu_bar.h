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
	[[nodiscard]] win_menu_sub& create_view_menu();
	[[nodiscard]] win_menu_sub& create_window_menu();
	[[nodiscard]] win_menu_sub& create_help_menu();
	[[nodiscard]] win_menu_sub& create_sub_menu(std::wstring const& name, UINT id);

	

private:
	UINT	_other_sub_menu_count{ 0 };
	std::vector<win_menu_sub> _sub_menus{};

	enum menu_ids
	{
		M_FILE = 1000,
		M_EDIT,
		M_VIEW,
		M_WINDOW,
		M_HELP,
		M_OTHER
	};
};