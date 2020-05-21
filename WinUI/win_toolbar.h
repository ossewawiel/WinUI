#pragma once
#include "framework.h"
#include "win_item.h"
#include "win_toolbar_command.h"

class win_toolbar :
	public win_item
{
public:
	win_toolbar(NN(win_item*) parent);

	void add_command(win_menu_command &, std::wstring const& tooltip, std::wstring const& text = L"", UINT bmp_id = 0);
	void add_button(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool enabled = true);
	void add_seperator();
	void insert_button(TBBUTTON const& btn);
	void add_checkable(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip, bool checked = false, bool enabled = true);

protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;

private:
	int	_btn_index{ 0 };
	std::map<UINT, win_toolbar_command> _btn_map{};
};

