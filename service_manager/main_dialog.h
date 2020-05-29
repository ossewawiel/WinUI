#pragma once

class service_manager;

class main_dialog :
	public win_window
{
public:
	main_dialog(NN(service_manager*) app, std::wstring title);

private:
	std::unique_ptr<win_menu_bar> _mnu_bar{ nullptr };
	std::unique_ptr<win_toolbar> _toolbar{ nullptr };
	std::unique_ptr<win_panel> _main_panel{ nullptr };

	enum cmd_id
	{
		M_F_OPTIONS,
		M_F_EXIT,
		M_A_PLAY,
		M_A_STOP,
		M_A_PAUSE,
		M_A_RESTART,
		M_A_CONNECT,
		M_A_REFRESH,
		M_A_EXPORT_LST,
		M_A_PROPS,
		M_A_HELP,
		M_V_ADD_REM_COLS,
		M_V_LARGE,
		M_V_SMALL,
		M_V_LIST,
		M_V_DETAIL,
		M_V_CUSTOM,
		M_H_ABOUT,
		T_BACK,
		T_FORWARD,
		T_TGGL_NAV,
		T_TGGL_ACT
		
		
	};

	enum pnl_id
	{
		PNL_MAIN
	};
};

