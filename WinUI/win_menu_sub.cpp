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
	MENUINFO mi{ 0 };
	mi.cbSize = sizeof(MENUINFO);
	mi.fMask = MIM_APPLYTOSUBMENUS | MIM_BACKGROUND | MIM_STYLE;
	mi.dwStyle = MNS_AUTODISMISS | MNS_CHECKORBMP| MNS_NOTIFYBYPOS;
	mi.hbrBack = window->_theme.clr_menubar_bkg;
	THROW_IF_WIN32_BOOL_FALSE(::SetMenuInfo(handle(), &mi));
}

win_menu_sub::win_menu_sub(win_menu_sub&& rhs) noexcept:
	win_menu_item{ std::move(rhs) },
	_has_menu_break{std::move(rhs._has_menu_break)},
	_sub_menus{ std::move(rhs._sub_menus) }
{}

win_menu_sub& win_menu_sub::operator=(win_menu_sub&& rhs) noexcept
{
	if (this != &rhs)
	{
		*this = std::move(rhs);
	}
	return *this;
}

void win_menu_sub::default_item(UINT id)
{
	win::default_item(handle(), id);
}

void win_menu_sub::show(win::position pos)
{
	::ClientToScreen(window()->item_handle(), (LPPOINT)&pos);
	::TrackPopupMenu(handle(),
		TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RIGHTBUTTON,
		pos.left, pos.top, 0, window()->item_handle(), NULL);
}

void win_menu_sub::add_action(std::wstring const& text, UINT id, bool enabled)
{
	add_action(text, id, 0, enabled);
}

void win_menu_sub::add_action(std::wstring const& text, UINT id, UINT icon_id, bool enabled)
{
	window()->menu_cmds().emplace(id, win_menu_command::construct_action(this, id, text, icon_id, enabled, _has_menu_break));
	win::draw_menu_bar(window()->item_handle());
	if (_has_menu_break) _has_menu_break = false;
}

void win_menu_sub::add_checkable(std::wstring const& text, UINT id, UINT bitmap_id, bool checked)
{
	window()->menu_cmds().emplace(id, win_menu_command::construct_checkable(this, id, text, checked, bitmap_id, true, _has_menu_break));
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

void win_menu_sub::add_selectable_group(UINT selected, std::initializer_list<std::pair<std::wstring, UINT>> items, UINT bitmap_id)
{
	if (items.size() == 0)
		return;

	auto f_iter = items.begin();
	UINT first_id = f_iter->second;
	auto l_iter = std::next(f_iter, items.size() - 1);
	UINT last_id = l_iter->second;

	for (auto const& param : items)
	{
		window()->menu_cmds().emplace(std::get<1>(param), win_menu_command::construct_selectable(
			this
			, param.second
			, param.first
			, first_id
			, last_id
			, selected == param.second
			, bitmap_id
			, true
			, _has_menu_break)
		);
		if (_has_menu_break) _has_menu_break = false;
	}
	win::draw_menu_bar(window()->item_handle());
}
