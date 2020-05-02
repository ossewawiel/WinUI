#include "framework.h"
#include "win_sub_menu.h"
#include "win_menu_bar.h"

win_sub_menu::win_sub_menu(NN(win_menu_bar*) parent, UINT pos, std::wstring const& name) :
	win_menu_item{ parent->window(), win::create_popup_menu() },
	_parent{ parent },
	_position{ pos },
	_name{ name }
{
	win::append_menu(parent->handle(), handle(), MF_POPUP | MF_STRING, name);
}

win_sub_menu::win_sub_menu(win_sub_menu&& rhs) noexcept:
	win_menu_item{ std::move(rhs) },
	_parent{ nullptr },
	_position{ 0 },
	_name{}
{
	std::swap(_parent, rhs._parent);
	_position = rhs._position;
	_name = std::move(rhs._name);
}

win_sub_menu& win_sub_menu::operator=(win_sub_menu&& rhs) noexcept
{
	if (this != &rhs)
	{
		_parent = nullptr;
		_position = 0;
		_name.clear();
		std::swap(_parent, rhs._parent);
		_position = rhs._position;
		_name = std::move(rhs._name);
	}
	return *this;
}
