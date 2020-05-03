#include "framework.h"
#include "win_menu_sub.h"
#include "win_menu_bar.h"


win_menu_sub::win_menu_sub(NN(win_menu_bar*) parent, UINT pos, std::wstring const& name) :
	win_menu_item{ parent->window(), win::create_popup_menu() },
	_parent{ parent },
	_name{ name }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_ID | MIIM_STRING | MIIM_DATA | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.wID = pos;
	mii.dwTypeData = const_cast<LPWSTR>(name.c_str());
	mii.hSubMenu = handle();
	win::insert_menu_item(parent->handle(), pos, true, mii);
}

win_menu_sub::win_menu_sub(win_menu_sub&& rhs) noexcept:
	win_menu_item{ std::move(rhs) },
	_parent{ nullptr },
	_position{ 0 },
	_name{}
{
	std::swap(_parent, rhs._parent);
	_position = rhs._position;
	_name = std::move(rhs._name);
}

win_menu_sub& win_menu_sub::operator=(win_menu_sub&& rhs) noexcept
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

void win_menu_sub::add_action(std::wstring const& text, UINT id, bool enabled)
{
	_menu_commands.emplace(id, std::make_unique<win_menu_cmd_action>( this, text, id, enabled ));
	win::draw_menu_bar(window()->item_handle());
	++_position;
}

void win_menu_sub::add_seperator()
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE;
	mii.fType = MFT_SEPARATOR;
	win::insert_menu_item(handle(), _position, true, mii);
	++_position;
}
