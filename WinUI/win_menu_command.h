#pragma once
#include "win_menu_item.h"

class win_menu_sub;

class win_menu_command
{
public:
	win_menu_command(NN(win_menu_sub*) parent, std::wstring const& name, UINT id);

private:
	win_menu_sub* _parent{ nullptr };
	UINT _id;
};

