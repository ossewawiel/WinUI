#pragma once
#include <gsl\gsl>
#include "win_window.h"

#include "win_menu_bar.h"
#include "win_rebar.h"
#include "demo_app.h"


class demo_window :
	public win_window
{
public:
	demo_window(gsl::not_null<demo_app*> app, std::wstring title);

private:
	std::unique_ptr<win_menu_bar> _menu_bar{ nullptr };
	std::unique_ptr<win_menu_sub> _popup_mnu{ nullptr };
	std::unique_ptr<win_rebar> _rebar{ nullptr };

	bool on_close();
	void on_menu_item_clicked(UINT item_id);
	void on_menu_item_checked(UINT item_id, bool checked);
	void on_menu_item_selected(UINT item_id);
	void on_right_mouse_down(win::enum_virtual_button, win::position);

	enum menu_id
	{
		M_F_NEW = 1,
		M_F_OPEN,
		M_F_SAVE,
		M_F_SAVE_AS,
		M_F_RECENT,
		M_F_EXIT,
		M_F_R_FIRST,
		M_F_R_SECOND,
		M_E_CUT,
		M_E_COPY,
		M_E_PASTE,
		M_E_UNDO,
		M_E_REDO,
		M_E_FIND,
		M_E_REPLACE,
		M_E_CLONE,
		M_E_DELETE,
		M_V_T_FIRST,
		M_V_T_SECOND,
		M_V_T_THIRD,
		M_V_T_FOURTH,
		M_V_ENABLE,
		M_V_DISABLE,
		M_W_FIRST,
		M_W_SECOND,
		M_W_THIRD,
		M_W_FOURTH,
		M_P_POP1,
		M_P_POP2,
		M_P_POP3,
		M_P_POP4
	};
};

