#include "framework.h"
#include "win_menu_command.h"
#include "win_menu_sub.h"

win_menu_command::win_menu_command(NN(win_menu_sub*) parent, std::wstring const& text, UINT id, win::enum_menu_cmd_type type):
	_parent{ parent },
	_id{ id },
	_type{ type }
{

}

bool win_menu_command::enabled() 
{ 
	return win::menu_item_enabled(_parent->handle(), _id); 
}

void win_menu_command::enabled(bool val) 
{ 
	win::menu_item_enable(_parent->handle(), _id, val); 
}

win_menu_cmd_action::win_menu_cmd_action(NN(win_menu_sub*) parent, std::wstring const& text, UINT id, bool enabled, bool break_menu):
	win_menu_command{ parent, text, id }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_DATA | MIIM_ID | MIIM_STATE | MIIM_FTYPE;
	mii.fType = MFT_STRING;
	if (break_menu) mii.fType += MFT_MENUBARBREAK;
	mii.wID = id;
	mii.fState = enabled ? MFS_ENABLED : MFS_GRAYED;
	mii.dwTypeData = const_cast<LPWSTR>(text.c_str());
	win::insert_menu_item(parent->handle(), id, FALSE, mii);
}

win_menu_cmd_checkable::win_menu_cmd_checkable(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, bool checked, bool break_menu):
	win_menu_command{ parent, name, id, win::enum_menu_cmd_type::CHECKABLE }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_DATA | MIIM_ID | MIIM_STATE; //| MIIM_FTYPE;
	//mii.fType = MFT_STRING;
	mii.hbmpChecked = nullptr;
	mii.hbmpUnchecked = nullptr;
	if (break_menu) mii.fType += MFT_MENUBARBREAK;
	mii.wID = id;
	mii.fState = checked ? MFS_CHECKED : MFS_UNCHECKED;
	mii.dwTypeData = const_cast<LPWSTR>(name.c_str());
	win::insert_menu_item(parent->handle(), id, FALSE, mii);
}

win_menu_cmd_selectable::win_menu_cmd_selectable(NN(win_menu_sub*) parent, std::wstring const& name, UINT id, UINT first, UINT last, bool selected, bool break_menu):
	win_menu_command{ parent, name, id, win::enum_menu_cmd_type::SELECTABLE }
{
}
