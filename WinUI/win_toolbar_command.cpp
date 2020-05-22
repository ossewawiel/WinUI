#include "win_menu_command.h"
#include "win_toolbar_command.h"

win_toolbar_command::win_toolbar_command(
	NN(win_toolbar*) parent
	, NN(win_menu_command*) mnu_cmd
	, std::wstring const& tooltip
	, std::wstring const& text
	, UINT bmp_id) :
	_parent{ parent },
	_menu_command{ mnu_cmd },
	_tooltip{ tooltip },
	_text{ text.empty() ? mnu_cmd->text() : text },
	_bmp_id{ bmp_id == 0 ? mnu_cmd->bmp_id() : bmp_id }
{
	_menu_command->set_on_command_checked(std::bind(&win_toolbar_command::on_command_checked, this, std::placeholders::_1));
	_menu_command->set_on_command_enabled(std::bind(&win_toolbar_command::on_command_enabled, this, std::placeholders::_1));
}
