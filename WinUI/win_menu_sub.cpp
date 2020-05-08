#include "framework.h"
#include "win_menu_sub.h"
#include "win_menu_bar.h"
#include "win_window.h"

win_menu_sub::win_menu_sub(NN(win_window*) window, NN(HMENU) parent, UINT pos, UINT id, std::wstring const& name) :
	win_menu_item{ window, win::create_popup_menu() }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_SUBMENU | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.wID = id;
	mii.dwTypeData = const_cast<LPWSTR>(name.c_str());
	mii.hSubMenu = handle();
	win::insert_menu_item(parent, pos, TRUE, mii);
}

win_menu_sub::win_menu_sub(NN(win_window*) window):
	win_menu_item{ window, win::create_popup_menu() }
{
	set_menu();
}

win_menu_sub::win_menu_sub(win_menu_sub&& rhs) noexcept:
	win_menu_item{ std::move(rhs) }
{}

win_menu_sub& win_menu_sub::operator=(win_menu_sub&& rhs) noexcept
{
	if (this != &rhs)
	{
		*this = std::move(rhs);
	}
	return *this;
}

void win_menu_sub::add_action(std::wstring const& text, UINT id, bool enabled)
{
	window()->menu_cmds().emplace(id, win_menu_command::construct_action(this, id, text, enabled, _has_menu_break));
	win::draw_menu_bar(window()->item_handle());
	if (_has_menu_break) _has_menu_break = false;

}

void win_menu_sub::add_checkable(std::wstring const& text, UINT id, bool checked)
{
	window()->menu_cmds().emplace(id, win_menu_command::construct_checkable(this, id, text, checked, true, _has_menu_break));
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
	_sub_menus.emplace_back(win_menu_sub{ window(), handle(), static_cast<UINT>(win::get_menu_item_count(handle())), window()->sub_menu_id(), text });
	return _sub_menus.back();
}

void win_menu_sub::add_selectable_group(std::initializer_list<std::tuple<std::wstring, UINT, bool>> items)
{
	auto f_iter = items.begin();
	UINT first_id = std::get<1>(*f_iter);
	auto l_iter = std::next(f_iter, items.size() - 1);
	UINT last_id = std::get<1>(*l_iter);

	for (auto const& param : items)
	{
		window()->menu_cmds().emplace(std::get<1>(param), win_menu_command::construct_selectable(
			this
			, std::get<1>(param)
			, std::get<0>(param)
			, first_id
			, last_id
			, std::get<2>(param)
			, true
			, _has_menu_break)
		);
		if (_has_menu_break) _has_menu_break = false;
	}
	win::draw_menu_bar(window()->item_handle());
}
