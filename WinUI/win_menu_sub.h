#pragma once

#include "win_menu_item.h"

class win_menu_bar;

class win_menu_sub :
	public win_menu_item
{
public:
	win_menu_sub(NN(win_menu_bar*) parent, UINT pos, std::wstring const& name);
	win_menu_sub(win_menu_sub&&) noexcept;

	win_menu_sub& operator=(win_menu_sub&&) noexcept;

	win_menu_sub& add_menu_command(std::wstring const& text, UINT id);

private:
	win_menu_bar*	_parent{ nullptr };
	UINT			_position{ 0 };
	std::wstring	_name{};


};


class win_action_menu :
	win_menu_item
{
public:

};
