#include "win_window.h"
#include "win_toolbar.h"
#include "win_toolbar_button.h"

win_toolbar::win_toolbar(NN(win_window*) parent) :
	win_item{ parent }
{

	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, nullptr,
		WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_WRAPABLE | TBSTYLE_TOOLTIPS, 0, 0, 0, 0,
		parent->item_handle(), NULL, app_handle(), NULL);

	if (hWndToolbar == nullptr)
		THROW_LAST_ERROR();

	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	::ShowWindow(hWndToolbar, TRUE);
	item_handle(hWndToolbar);
	item_map().emplace(item_handle(), this);
}

void win_toolbar::add_action(std::wstring const& text, UINT id, UINT icon_id, std::wstring const& tooltip, bool enabled)
{
	window()->tlb_cmds().emplace(id, win_toolbar_command(this, _btn_index, id, tooltip, text, win::enum_tlb_cmd_type::ACTION, icon_id, enabled));
	++_btn_index;
	parent()->tb_tooltips().emplace(id, tooltip);
}

void win_toolbar::add_sub_menu(std::wstring const& text, UINT id, NN(win_menu_sub*) sub_menu, UINT icon_id, std::wstring const& tooltip, bool enabled)
{
	window()->tlb_cmds().emplace(id, win_toolbar_command(this, _btn_index, id, tooltip, text, win::enum_tlb_cmd_type::DROPDOWN, icon_id, enabled, sub_menu));
	++_btn_index;
	parent()->tb_tooltips().emplace(id, tooltip);
}

void win_toolbar::add_button(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool enabled)
{

	TBADDBITMAP tb{};

	tb.hInst = nullptr;
	tb.nID = (UINT_PTR)win::generate_transparent_bitmap(
		win_app::hinstance()
		, bitmap_id
		, RGB(0, 128, 128)
		, ::GetSysColor(COLOR_BTNFACE));

	int index = SendMessage(item_handle(), TB_ADDBITMAP, 1, (LPARAM)&tb);

	BYTE state{};
	if (enabled) state += TBSTATE_ENABLED;
	TBBUTTON btn
	{
		index
		, cmd_id
		, state
		, BTNS_AUTOSIZE
		,{ 0 }
		, 0L
		, reinterpret_cast<INT_PTR>(title.c_str())
	};

	insert_button(btn);
	parent()->tb_tooltips().insert(std::make_pair(cmd_id, tooltip));
}

void win_toolbar::add_seperator()
{
	TBBUTTON btn
	{
		8
		, 0
		, TBSTATE_ENABLED
		, BTNS_SEP
		,{ 0 }
		, 0L
		, -1
	};

	insert_button(btn, false);
}

void win_toolbar::insert_button(TBBUTTON const& btn, bool auto_size)
{
	::SendMessage(item_handle(), TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	::SendMessage(item_handle(), TB_INSERTBUTTON, _btn_index, reinterpret_cast<INT_PTR>(&btn));
	if(auto_size) ::SendMessage(item_handle(), TB_AUTOSIZE, 0, 0);
	::ShowWindow(item_handle(), TRUE);
	++_btn_index;
}

void win_toolbar::add_checkable(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool checked, bool enabled)
{
	TBADDBITMAP tb
	{
		nullptr,
		(UINT_PTR)win::generate_transparent_bitmap(win_app::hinstance(), bitmap_id, RGB(0, 128, 128), ::GetSysColor(COLOR_BTNFACE))
	};
	int index = SendMessage(item_handle(), TB_ADDBITMAP, 1, (LPARAM)&tb);

	BYTE state{};
	if (enabled) state += TBSTATE_ENABLED;
	if (checked) state += TBSTATE_CHECKED;
	TBBUTTON btn
	{
		index
		, cmd_id
		, state
		, BTNS_AUTOSIZE | BTNS_CHECK
		,{ 0 }
		, 0L
		, reinterpret_cast<INT_PTR>(title.c_str())
	};

	insert_button(btn);
	parent()->tb_tooltips().insert(std::make_pair(cmd_id, tooltip));
}

LRESULT win_toolbar::event_handler(UINT msg, WPARAM, LPARAM)
{
	return 0;
}

//METHODS//

inline win_window* win_toolbar::window() { return static_cast<win_window*>(parent()); }
