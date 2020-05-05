#include "framework.h"
#include "win_menu_sub.h"
#include "win_menu_bar.h"
#include "win_window.h"

win_menu_sub::win_menu_sub(NN(win_menu_item*) parent, UINT id, std::wstring const& name) :
	win_menu_item{ parent->window(), win::create_popup_menu() },
	_parent{ parent },
	_window{ parent->window() },
	_name{ name }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_ID | MIIM_STRING | MIIM_DATA | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.wID = id;
	mii.dwTypeData = const_cast<LPWSTR>(name.c_str());
	mii.hSubMenu = handle();
	win::insert_menu_item(parent->handle(), id, FALSE, mii);
}

win_menu_sub::win_menu_sub(win_menu_sub&& rhs) noexcept:
	win_menu_item{ std::move(rhs) },
	_parent{ nullptr },
	_name{}
{
	std::swap(_parent, rhs._parent);
	_name = std::move(rhs._name);
}

win_menu_sub& win_menu_sub::operator=(win_menu_sub&& rhs) noexcept
{
	if (this != &rhs)
	{
		_parent = nullptr;
		_name.clear();
		std::swap(_parent, rhs._parent);
		_name = std::move(rhs._name);
	}
	return *this;
}

void win_menu_sub::add_action(std::wstring const& text, UINT id, bool enabled)
{
	_parent->window()->menu_cmds().emplace(id, std::make_unique<win_menu_command>(win_menu_cmd_action{ this, text, id, enabled, _has_menu_break }));
	win::draw_menu_bar(window()->item_handle());
	if (_has_menu_break) _has_menu_break = false;

}

void win_menu_sub::add_checkable(std::wstring const& text, UINT id, bool checked)
{
	_parent->window()->menu_cmds().emplace(id, std::make_unique<win_menu_command>(win_menu_cmd_checkable{ this, text, id, checked, _has_menu_break }));
	win::draw_menu_bar(window()->item_handle());
	if (_has_menu_break) _has_menu_break = false;
}

void win_menu_sub::add_seperator()
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_FTYPE;
	mii.fType = MFT_SEPARATOR;
	win::insert_menu_item(handle(), static_cast<UINT>(win::get_menu_item_count(handle())), true, mii);
}

void win_menu_sub::add_vertical_seperator()
{
	_has_menu_break = true;
}

win_menu_sub& win_menu_sub::add_sub_menu(std::wstring const& text, bool enabled)
{
	_sub_menus.emplace_back(win_menu_sub{ this, static_cast<UINT>(win::get_menu_item_count(handle())), text });
	win::draw_menu_bar(window()->item_handle());
	
	return _sub_menus.back();
}

void win_menu_sub::add_selectable_group(std::initializer_list<std::pair<std::wstring, UINT>> items)
{
}
