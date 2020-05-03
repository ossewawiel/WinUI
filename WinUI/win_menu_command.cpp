#include "framework.h"
#include "win_menu_command.h"
#include "win_menu_sub.h"

win_menu_command::win_menu_command(NN(win_menu_sub*) parent, std::wstring const& text, UINT id):
	_parent{ parent },
	_id{ id }
{

}

win_menu_cmd_action::win_menu_cmd_action(NN(win_menu_sub*) parent, std::wstring const& text, UINT id, bool enabled):
	win_menu_command{ parent, text, id }
{
	MENUITEMINFO mii{};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING | MIIM_DATA | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = enabled ? MFS_ENABLED : MFS_GRAYED;
	mii.wID = id;
	mii.hSubMenu = parent->handle();
	mii.dwTypeData = const_cast<LPWSTR>(text.c_str());
	win::insert_menu_item(parent->handle(), id, false, mii);
}
