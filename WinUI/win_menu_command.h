#pragma once
#include "win_menu_item.h"

class win_menu_sub;



class win_menu_command
{
public:
	win_menu_command(NN(win_menu_sub*) parent, std::wstring const& text, UINT id, win::enum_menu_cmd_type type = win::enum_menu_cmd_type::ACTION);

	[[nodiscard]] UINT id() const noexcept { return _id; }

	[[nodiscard]] win::enum_menu_cmd_type	type() { return _type; }

	[[nodiscard]] win_menu_sub* parent() { return _parent; }

	[[nodiscard]] bool	enabled();
	void	enabled(bool val);
	

protected:
	

private:
	win_menu_sub*	_parent{ nullptr };
	UINT			_id;
	win::enum_menu_cmd_type _type;
};



class win_menu_cmd_action :
	public win_menu_command
{
public:
	win_menu_cmd_action(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, bool enabled = true, bool break_menu = false);
};

class win_menu_cmd_checkable :
	public win_menu_command
{
public:
	win_menu_cmd_checkable(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, bool checked = false, bool break_menu = false);
};

class win_menu_cmd_selectable :
	public win_menu_command
{
public:
	win_menu_cmd_selectable(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, UINT first, UINT last, bool selected = false, bool break_menu = false);

private:
	UINT _first_selectable{ 0 };
	UINT _last_selectable{ 0 };
};

