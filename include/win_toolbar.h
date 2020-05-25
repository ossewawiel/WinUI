#pragma once
#include "framework.h"
#include "win_item.h"
#include "win_toolbar_command.h"

class win_toolbar :
	public win_item
{
public:
	win_toolbar(NN(win_window*) parent);

	void add_action(std::wstring const& text, UINT id, UINT icon_id, std::wstring const& tooltip, bool enabled = true);
	void add_sub_menu(std::wstring const& text, UINT id, NN(win_menu_sub*) sub_menu, UINT icon_id, std::wstring const& tooltip, bool enabled = true);
	void add_button(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool enabled = true);
	void add_seperator();
	void insert_button(TBBUTTON const& btn);
	void add_checkable(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool checked = false, bool enabled = true);

protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;

private:
	int	_btn_index{ 0 };
	std::map<UINT, win_toolbar_command> _btn_map{};

	//METHODS//
	win_window* window();
};

using tlb_cmd_map = std::unordered_map<UINT, win_toolbar_command>;

