#include "win_menu_command.h"
#include "win_toolbar_command.h"
#include "win_app.h"
#include "win_toolbar.h"
#include "win_menu_command.h"

win_toolbar_command::win_toolbar_command(
		NN(win_toolbar*) parent
		, int pos_index
		, UINT cmd_id
		, std::wstring const& tooltip
		, std::wstring const& text
		, win::enum_tlb_cmd_type type
		, UINT bmp_id
		, bool enabled) :
	_parent{parent},
	_cmd_id{cmd_id},
	_type{ type },
	_tooltip{tooltip},
	_bmp_id{bmp_id},
	_pos_index{pos_index}
{

	TBADDBITMAP tb{};

	tb.hInst = nullptr;
	tb.nID = (UINT_PTR)win::generate_transparent_bitmap(
		win_app::hinstance()
		, bmp_id
		, RGB(0, 128, 128)
		, ::GetSysColor(COLOR_BTNFACE));

	int index = SendMessage(parent->item_handle(), TB_ADDBITMAP, 1, (LPARAM)&tb);

	BYTE state{};
	if (enabled) state += TBSTATE_ENABLED;
	BYTE style = BTNS_AUTOSIZE;
	if (type == win::enum_tlb_cmd_type::DROPDOWN) style += BTNS_DROPDOWN;
	TBBUTTON btn
	{
		index
		, cmd_id
		, state
		, style
		, { 0 }
		, 0L
		, reinterpret_cast<INT_PTR>(text.c_str())
	};

	win::insert_button(parent->item_handle(), pos_index, btn);
	//parent->tb_tooltips().insert(std::make_pair(cmd_id(), tooltip));
}




