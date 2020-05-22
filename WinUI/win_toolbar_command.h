#pragma once
#include "framework.h"

class win_menu_command;
class win_toolbar;

class win_toolbar_command
{
public:
	//CTOR/DTOR//
	win_toolbar_command(
		NN(win_toolbar*) parent
		, NN(win_menu_command*) mnu_cmd
		, std::wstring const& tooltip
		, std::wstring const& text = L""
		, UINT bmp_id = 0);

	//PROPERTIES//


	

private:
	win_toolbar*		_parent{ nullptr };
	win_menu_command*	_menu_command{ nullptr };
	std::wstring		_tooltip{};
	std::wstring		_text{};
	UINT				_bmp_id{ 0 };

	//EVENT METHODS//
	void on_command_enabled(bool);
	void on_command_checked(bool);
};

