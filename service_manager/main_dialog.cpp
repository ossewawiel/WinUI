#include "framework.h"
#include "resource.h"
#include "service_manager.h"
#include "main_dialog.h"

main_dialog::main_dialog(NN(service_manager*) app, std::wstring title):
    win_window{ app, title, win_window::theme{ IDI_APP } }
{
    _mnu_bar = std::make_unique<win_menu_bar>(this);
    auto& file = _mnu_bar->add_file_menu();
    file.add_action(L"&Options...", M_F_OPTIONS, IDB_OPTIONS16, true);
    file.add_seperator();
    file.add_action(L"Exit\tAlt+F4", M_F_EXIT);

    auto& action = _mnu_bar->add_action_menu();
    action.add_action(L"&Start", M_A_PLAY, IDB_PLAY16, true);
    action.add_action(L"&Stop", M_A_STOP, IDB_STOP16, true);
    action.add_action(L"&Pause/Resume", M_A_PAUSE, IDB_PAUSE16, true);
    action.add_action(L"&Restart", M_A_RESTART, IDB_RESTART16, true);
    action.add_action(L"&Connect to another computer...", M_A_CONNECT, IDB_CONNECTPC16, true);
    action.add_seperator();
    auto& tasks = action.add_sub_menu(L"All Tasks");
    tasks.add_action(L"Connect to another computer...", M_A_CONNECT, IDB_CONNECTPC16, true);
    action.add_seperator();
    action.add_action(L"&Refresh", M_A_REFRESH, IDB_REFRESH16, true);
    action.add_action(L"&Export list", M_A_EXPORT_LST, IDB_EXPORT16, true);
    action.add_action(L"&Properties", M_A_PROPS, IDB_CONFIG16, true);
    action.add_seperator();
    action.add_action(L"&Help", M_A_HELP);

    auto& view = _mnu_bar->add_view_menu();
    view.add_action(L"Add/Remove Columns...", M_V_ADD_REM_COLS);
    view.add_seperator();
    view.add_selectable_group(M_V_SMALL, {
        { L"Large Icons", M_V_LARGE },
        { L"Small Icons", M_V_SMALL },
        { L"List", M_V_LIST },
        { L"Detail", M_V_DETAIL }
        }, IDB_CHECK16);
    view.add_seperator();
    view.add_action(L"Customize...", M_V_CUSTOM, IDB_TOOLBOX16, true);

    auto& help = _mnu_bar->add_help_menu();
    help.add_action(L"About...", M_H_ABOUT);

    _toolbar = std::make_unique<win_toolbar>(this);
    _toolbar->add_action(L"", T_BACK, IDB_BACK16, L"Previous Tab");
    _toolbar->add_action(L"", T_FORWARD, IDB_FORWARD16, L"Next Tab");
    _toolbar->add_seperator();
    _toolbar->add_action(L"", T_TGGL_NAV, IDB_TGGLLEFT16, L"Show/Hide Connections");
    _toolbar->add_seperator();
    _toolbar->add_action(L"", M_A_PROPS, IDB_CONFIG16, L"Properties");
    _toolbar->add_action(L"", M_A_REFRESH, IDB_REFRESH16, L"Refresh");
    _toolbar->add_action(L"", M_A_EXPORT_LST, IDB_EXPORT16, L"Export List");
    _toolbar->add_seperator();
    _toolbar->add_action(L"", M_A_HELP, IDB_HELP16, L"Help");
    _toolbar->add_action(L"", T_TGGL_ACT, IDB_TGGLRIGHT16, L"Show/Hide Actions");
    _toolbar->add_seperator();
    _toolbar->add_action(L"", M_A_PLAY, IDB_PLAY16, L"Start selected service");
    _toolbar->add_action(L"", M_A_STOP, IDB_STOP16, L"Stop selected service");
    _toolbar->add_action(L"", M_A_PAUSE, IDB_PAUSE16, L"Pause selected service");
    _toolbar->add_action(L"", M_A_RESTART, IDB_RESTART16, L"Restart selected service");

    _main_panel = std::make_unique<win_panel>(this, PNL_MAIN);
}
