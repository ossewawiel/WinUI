#include "framework.h"
#include "win_menu_command.h"
#include "win_menu_sub.h"

win_menu_command::win_menu_command(NN(win_menu_sub*) parent, std::wstring const& name, UINT id):
	_parent{ parent },
	_id{ id }
{
	win::insert_menu_item(_parent->handle(), id, name);
}
