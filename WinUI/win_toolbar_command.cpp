#include "win_menu_command.h"
#include "win_toolbar_command.h"
#include "win_app.h"
#include "win_toolbar.h"
#include "win_menu_command.h"

win_toolbar_command::win_toolbar_command(
	NN(win_toolbar*) parent
	, win_menu_command & mnu_cmd
	, int pos_index
	, std::wstring const& tooltip
	, std::wstring const& text
	, UINT bmp_id) :
	win_toolbar_button{
		parent
		, mnu_cmd.id()
		, pos_index
		, text.empty() ? mnu_cmd.text() : text
		, bmp_id == 0 ? mnu_cmd.bmp_id() : bmp_id
		, tooltip }
{
	mnu_cmd.set_on_command_checked(std::bind(&win_toolbar_command::on_command_checked, this, std::placeholders::_1));
	mnu_cmd.set_on_command_enabled(std::bind(&win_toolbar_command::on_command_enabled, this, std::placeholders::_1));

	TBADDBITMAP tb{};

	tb.hInst = nullptr;
	tb.nID = (UINT_PTR)win::generate_transparent_bitmap(
		win_app::hinstance()
		, win_toolbar_button::bmp_id()
		, RGB(0, 128, 128)
		, ::GetSysColor(COLOR_BTNFACE));

	int index = SendMessage(parent->item_handle(), TB_ADDBITMAP, 1, (LPARAM)&tb);

	BYTE state{};
	if (mnu_cmd.enabled()) state += TBSTATE_ENABLED;
	TBBUTTON btn
	{
		index
		, cmd_id()
		, state
		, BTNS_AUTOSIZE
		, { 0 }
		, 0L
		, reinterpret_cast<INT_PTR>(win_toolbar_button::text().c_str())
	};

	win::insert_button(parent->item_handle(), pos_index, btn);
	parent->tb_tooltips().insert(std::make_pair(cmd_id(), tooltip));
}

void win_toolbar_command::on_command_enabled(bool val)
{
	enabled(val);
}

void win_toolbar_command::on_command_checked(bool val)
{
	checked(val);
}
