#include "framework.h"
#include "win_menu_command.h"
#include "win_menu_sub.h"
#include "win_bitmap.h"
#include "win_window.h"


win_menu_command::win_menu_command(
		NN(HMENU) parent
		, UINT id
		, UINT bmp_id
		, MENUITEMINFO const& mii
		, UINT first_id
		, UINT last_id
		, win::enum_menu_cmd_type type) :
	_parent{ parent },
	_id{ id },
	_bmp_id{ bmp_id },
	_type{ type },
	_first_selectable{ first_id },
	_last_selectable{ last_id }
{
	win::insert_menu_item(parent, id, FALSE, mii);
}


win_menu_command::win_menu_command(win_menu_command&& rhs):
	_parent{ std::move(rhs._parent) },
	_id{ std::move(rhs._id) },
	_type{ std::move(rhs._type) },
	_bmp_id{ std::move(rhs._bmp_id) },
	_first_selectable{ std::move(rhs._first_selectable) },
	_last_selectable{ std::move(rhs._last_selectable) }
{
	rhs._parent = nullptr;
}


win_menu_command& win_menu_command::operator=(win_menu_command&& rhs)
{
	if (this != &rhs)
	{
		std::swap(_parent, rhs._parent);
		_id = rhs._id;
		_type = rhs._type;
		_bmp_id = rhs._bmp_id;
		_first_selectable = rhs._first_selectable;
		_last_selectable = rhs._last_selectable;

		rhs._parent = nullptr;
	}
	return *this;
}


bool win_menu_command::enabled() 
{ 
	return win::menu_item_enabled(_parent, _id); 
}


void win_menu_command::enabled(bool val) 
{ 
	win::menu_item_enable(_parent, _id, val); 
	if(_on_command_enabled)
		_on_command_enabled(val);
}

bool win_menu_command::checked()
{
	return win::menu_item_checked(parent(), id());
}

void win_menu_command::checked(bool val)
{
	win::menu_item_checked(parent(), id(), val);
	if (_on_command_checked)
		_on_command_checked(val);
}


win_menu_command win_menu_command::construct_action(
	NN(win_menu_item*) parent
	, UINT id
	, std::wstring const& text
	, UINT icon_id
	, bool enabled
	, bool v_seperator)
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE | MIIM_FTYPE;
	mii.fType = MFT_STRING;
	if (v_seperator) mii.fType += MFT_MENUBARBREAK;
	mii.wID = id;
	mii.fState = enabled ? MFS_ENABLED : MFS_GRAYED;
	mii.dwTypeData = const_cast<LPWSTR>(text.c_str());
	//add bitmap
	if (icon_id != 0) 
	{
		mii.fMask += MIIM_CHECKMARKS;
		mii.fState += MFS_CHECKED;
		mii.hbmpChecked = win::generate_transparent_bitmap(
			win_app::hinstance()
			, icon_id, RGB(0, 128, 128)
			, ::GetSysColor(COLOR_BTNFACE));
		mii.hbmpUnchecked = nullptr;
	}


	return win_menu_command{parent->handle(), id, icon_id, mii};
}


win_menu_command win_menu_command::construct_checkable(
	NN(win_menu_item*) parent
	, UINT id
	, std::wstring const& text
	, bool checked
	, UINT bitmap_id
	, bool enabled
	, bool v_seperator)
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE | MIIM_FTYPE;
	mii.fType = MFT_STRING;
	if (v_seperator) mii.fType += MFT_MENUBARBREAK;
	mii.wID = id;
	mii.fState = checked ? MFS_CHECKED : MFS_UNCHECKED;
	mii.dwTypeData = const_cast<LPWSTR>(text.c_str());
	//add bitmap
	if (bitmap_id != 0)
	{
		mii.fMask += MIIM_CHECKMARKS;
		mii.hbmpChecked = win::generate_transparent_bitmap(
			win_app::hinstance()
			, bitmap_id, RGB(0, 128, 128)
			, ::GetSysColor(COLOR_BTNFACE));
		mii.hbmpUnchecked = nullptr;
	}
	
	return win_menu_command{ parent->handle(), id, bitmap_id, mii, 0, 0, win::enum_menu_cmd_type::CHECKABLE };
}


win_menu_command win_menu_command::construct_selectable(
	NN(win_menu_item*) parent
	, UINT id
	, std::wstring const& text
	, UINT first_id
	, UINT last_id
	, bool selected
	, UINT bitmap_id
	, bool enabled
	, bool v_seperator)
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE | MIIM_FTYPE;
	mii.fType = MFT_STRING;
	if(bitmap_id == 0) mii.fType += MFT_RADIOCHECK;
	if (v_seperator) mii.fType += MFT_MENUBARBREAK;
	mii.wID = id;
	mii.fState = selected ? MFS_CHECKED : MFS_UNCHECKED;
	mii.dwTypeData = const_cast<LPWSTR>(text.c_str());
	//add bitmap
	if (bitmap_id != 0)
	{
		mii.fMask += MIIM_CHECKMARKS;
		mii.hbmpChecked = win::generate_transparent_bitmap(
			win_app::hinstance()
			, bitmap_id, RGB(0, 128, 128)
			, ::GetSysColor(COLOR_BTNFACE));
		mii.hbmpUnchecked = nullptr;
	}

	return win_menu_command{ parent->handle(), id, bitmap_id, mii, first_id, last_id, win::enum_menu_cmd_type::SELECTABLE };
}

std::wstring win_menu_command::text()
{
	return win::menu_item_text(_parent, _id);
}

void win_menu_command::text(std::wstring val)
{
}

UINT win_menu_command::first_selectable()
{
	return _first_selectable;
}

UINT win_menu_command::last_selectable()
{
	return _last_selectable;
}

void win_menu_command::set_on_command_checked(on_command_checked func)
{
	_on_command_checked = func;
}

void win_menu_command::set_on_command_enabled(on_command_enabled func)
{
	_on_command_enabled = func;
}
