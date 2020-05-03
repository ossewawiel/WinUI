#pragma once

#include "win_menu_item.h"
#include "win_menu_command.h"

class win_menu_bar;
using win_menu_cmd_map = std::map<UINT, std::unique_ptr<win_menu_command>>;

class win_menu_sub :
	public win_menu_item
{
public:
	win_menu_sub(NN(win_menu_bar*) parent, UINT pos, std::wstring const& name);
	win_menu_sub(win_menu_sub&&) noexcept;

	win_menu_sub& operator=(win_menu_sub&&) noexcept;

	win_menu_cmd_map& menu_commands() { return _menu_commands; }

	void add_action(std::wstring const& text, UINT pos, bool enabled = true);
	void add_seperator();
	//win_menu_sub& add_sub_menu(std::wstring const& text, bool enabled = true) { }

private:
	win_menu_bar*	_parent{ nullptr };
	UINT			_position{ 0 };
	std::wstring	_name{};

	win_menu_cmd_map _menu_commands{};

};


