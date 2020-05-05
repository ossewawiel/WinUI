#pragma once

#include "win_menu_item.h"
#include "win_menu_command.h"

class win_menu_bar;
using win_menu_cmd_map = std::map<UINT, std::unique_ptr<win_menu_command>>;

class win_menu_sub :
	public win_menu_item
{
public:
	win_menu_sub(NN(win_menu_item*) parent, UINT pos, std::wstring const& name);
	win_menu_sub(win_menu_sub&&) noexcept;

	win_menu_sub& operator=(win_menu_sub&&) noexcept;

	win_menu_cmd_map& menu_commands() { return _menu_commands; }

	void add_action(std::wstring const& text, UINT id, bool enabled = true);
	void add_checkable(std::wstring const& text, UINT id, bool checked = false);
	void add_seperator();
	void add_vertical_seperator();
	win_menu_sub& add_sub_menu(std::wstring const& text, bool enabled = true);
	void add_selectable_group(std::initializer_list<std::pair<std::wstring, UINT>> items);

private:
	win_menu_item*	_parent{ nullptr };
	win_window* _window{ nullptr };
	std::wstring	_name{};
	std::vector<win_menu_sub> _sub_menus{};
	bool _has_menu_break{ false };

	win_menu_cmd_map _menu_commands{};

};

struct menu_cmd_struct
{
	win::enum_menu_cmd_type type;
	win_menu_sub* parent;
};

using menu_cmd_map = std::unordered_map<UINT, win_menu_command>;


