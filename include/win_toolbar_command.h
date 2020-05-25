#pragma once
#include "framework.h"
#include "win_toolbar_button.h"


class win_menu_command;
class win_toolbar;

class win_toolbar_command
{
public:
	win_toolbar_command(
		NN(win_toolbar*) parent
		, int pos_index
		, UINT cmd_id
		, std::wstring const& tooltip
		, std::wstring const& text
		, win::enum_tlb_cmd_type type = win::enum_tlb_cmd_type::ACTION
		, UINT bmp_id = 0
		, bool enabled = true
		, win_menu_sub* sub_menu = nullptr);

	win_menu_sub* sub_menu() { return _sub_menu; }
private:
	

	win_toolbar*		_parent{ nullptr };
	UINT				_cmd_id{ 0 };
	win::enum_tlb_cmd_type _type{ win::enum_tlb_cmd_type::ACTION };
	std::wstring		_tooltip{};
	std::wstring		_text{};
	UINT				_bmp_id{ 0 };
	int					_pos_index{ 0 };
	win_menu_sub*		_sub_menu{ nullptr };

};

