#pragma once
#include "framework.h"
#include "win_toolbar_button.h"


class win_menu_command;
class win_toolbar;

class win_toolbar_command:
	public win_toolbar_button
{
public:
	//CTOR/DTOR//
	win_toolbar_command(
		NN(win_toolbar*) parent
		, win_menu_command & mnu_cmd
		, int pos_index
		, std::wstring const& tooltip
		, std::wstring const& text = L""
		, UINT bmp_id = 0);

	win_toolbar_command(win_toolbar_command&& rhs):
		win_toolbar_button{ std::move(rhs) },
		_menu_command{std::move(rhs._menu_command)}
	{
		rhs._menu_command = nullptr;
	}

	win_toolbar_command& operator=(win_toolbar_command&& rhs)
	{
		if (this != &rhs)
		{
			*this = std::move(rhs);
			rhs._menu_command = nullptr;
		}
		return *this;
	}

	//PROPERTIES//


	

private:
	win_menu_command*	_menu_command{ nullptr };

	//EVENT METHODS//
	void on_command_enabled(bool);
	void on_command_checked(bool);
};

