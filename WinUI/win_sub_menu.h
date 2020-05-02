#pragma once

#include "win_menu.h"

class win_menu_bar;

class win_sub_menu :
	win_menu_item
{
public:
	win_sub_menu(NN(win_menu_bar*) parent, UINT pos, std::wstring const& name);
	win_sub_menu(win_sub_menu&&) noexcept;

	win_sub_menu& operator=(win_sub_menu&&) noexcept;

private:
	win_menu_bar*	_parent{ nullptr };
	UINT			_position{ 0 };
	std::wstring	_name{};
};
