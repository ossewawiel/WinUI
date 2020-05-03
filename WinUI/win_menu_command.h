#pragma once
#include "win_menu_item.h"

class win_menu_sub;



class win_menu_command
{
public:
	win_menu_command(NN(win_menu_sub*) parent, std::wstring const& text, UINT id);

	UINT id() const noexcept { return _id; }
	bool	enabled() { return false; }

protected:


private:
	win_menu_sub*	_parent{ nullptr };
	UINT			_id;

};



class win_menu_cmd_action :
	public win_menu_command
{
public:
	win_menu_cmd_action(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, bool enabled = true);
};

