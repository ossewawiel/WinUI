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
		, UINT bmp_id = 0):
		_parent{parent},
		_menu_command{ mnu_cmd },
		_tooltip{ tooltip },
		_text{ text.empty() ? mnu_cmd->text() : L"" },
		_bmp_id{ bmp_id == 0 ? mnu_cmd->bmp_id() : 0 }
	{
		_menu_command->set_on_command_checked(std::bind(&win_toolbar_command::on_command_checked, this, std::placeholders::_1));
		_menu_command->set_on_command_enabled(std::bind(&win_toolbar_command::on_command_enabled, this, std::placeholders::_1));
	}

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
