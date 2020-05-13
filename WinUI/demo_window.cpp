#include "resource.h"
#include "demo_window.h"

demo_window::demo_window(gsl::not_null<demo_app*> app, std::wstring title) : win_window{ app, title }
{

	_menu_bar = std::make_unique<win_menu_bar>(this);
	auto& file = _menu_bar->add_file_menu();
	file.add_action(L"&New", M_F_NEW);
	file.add_action(L"&Open", M_F_OPEN);
	file.add_seperator();
	file.add_action(L"&Save\tCtrl+S", IDM_SAVE, IDB_SAVE16, true);
	file.add_action(L"S&ave as...", M_F_SAVE_AS);
	file.add_seperator();
	auto& recent = file.add_sub_menu(L"&Recent");
	file.add_seperator();
	file.add_action(L"Exit\tAlt+F4", M_F_EXIT);
	file.default_item(M_F_OPEN);

	recent.add_action(L"First", M_F_R_FIRST);
	recent.add_action(L"Second", M_F_R_SECOND);

	auto& edit = _menu_bar->add_edit_menu();
	edit.add_action(L"Cut\tCtrl+X", M_E_CUT, IDB_CUT16, true);
	edit.add_action(L"Copy\tCtrl+C", M_E_COPY, IDB_COPY16, true);
	edit.add_action(L"Paste\tCtrl+V", M_E_PASTE);
	edit.add_seperator();
	edit.add_action(L"Undo", M_E_UNDO);
	edit.add_action(L"Redo", M_E_REDO);
	edit.add_seperator();
	edit.add_action(L"&Find", M_E_FIND);
	edit.add_action(L"Re&place", M_E_REPLACE);
	edit.add_seperator();
	edit.add_action(L"C&lone", M_E_CLONE);
	edit.add_action(L"&Delete", M_E_DELETE);

	auto& view = _menu_bar->add_view_menu();
	auto& toolbars = view.add_sub_menu(L"Toolbars");
	toolbars.add_checkable(L"First Checkable", M_V_T_FIRST, IDB_CHECK16);
	toolbars.add_checkable(L"Second Checkable", M_V_T_SECOND, IDB_CHECK16);
	toolbars.add_checkable(L"Third Checkable", M_V_T_THIRD, IDB_CHECK16);
	toolbars.add_checkable(L"Fourth Checkable", M_V_T_FOURTH, IDB_CHECK16);
	view.add_seperator();
	view.add_action(L"&Enable", M_V_ENABLE, false);
	view.add_action(L"&Disable", M_V_DISABLE);

	auto& window = _menu_bar->add_window_menu();
	window.add_selectable_group(M_W_SECOND, {
		{ L"First Selectable", M_W_FIRST },
		{ L"Second Selectable", M_W_SECOND },
		{ L"Third Selectable", M_W_THIRD },
		{ L"Fourth Selectable", M_W_FOURTH }
	}, IDB_BULLET16);

	_popup_mnu = std::make_unique<win_menu_sub>(this);
	_popup_mnu->add_action(L"Pop1", M_P_POP1);
	_popup_mnu->add_action(L"Pop2", M_P_POP2);
	_popup_mnu->add_seperator();
	_popup_mnu->add_action(L"Pop3", M_P_POP3);
	_popup_mnu->add_action(L"Pop4", M_P_POP4);

	set_on_close_window(std::bind(&demo_window::on_close, this));
	set_on_menu_item_clicked(std::bind(&demo_window::on_menu_item_clicked, this, std::placeholders::_1));
	set_on_menu_item_checked(std::bind(&demo_window::on_menu_item_checked, this, std::placeholders::_1, std::placeholders::_2));
	set_on_menu_item_selected(std::bind(&demo_window::on_menu_item_selected, this, std::placeholders::_1));
	set_on_right_mouse_down(std::bind(&demo_window::on_right_mouse_down, this, std::placeholders::_1, std::placeholders::_2));

	_toolbar = std::make_unique<win_toolbar>(this);
	_toolbar->add_button(L"New", M_F_NEW, IDB_SAVE16, L"Some Tooltip here");
}

bool demo_window::on_close()
{
	return yesno_msg(L"Message", L"The window is about to close, do you want to proceeed");
}

void demo_window::on_menu_item_clicked(UINT item_id)
{
	switch (item_id)
	{
	case IDM_SAVE:
	case M_F_NEW:
	case M_F_OPEN:
	case M_F_SAVE:
	case M_F_SAVE_AS:
	case M_F_R_FIRST:
	case M_F_R_SECOND:
		info_msg(L"Menu Item clicked", menu_cmd(item_id).text());
		break;
	case M_V_DISABLE:
		menu_cmd(M_V_DISABLE).enabled(false);
		menu_cmd(M_V_ENABLE).enabled(true);
		break;
	case M_V_ENABLE:
		menu_cmd(M_V_DISABLE).enabled(true);
		menu_cmd(M_V_ENABLE).enabled(false);
		break;
	case M_F_EXIT:
		close();
		break;
	default: return;
	}
	
}

void demo_window::on_menu_item_checked(UINT item_id, bool checked)
{
	switch (item_id)
	{
	case M_V_T_FIRST:
	case M_V_T_SECOND:
	case M_V_T_THIRD:
	case M_V_T_FOURTH:
		if(checked)
			info_msg(L"Menu Item checked", std::to_wstring(item_id));
		else
			info_msg(L"Menu Item unchecked", std::to_wstring(item_id));
		break;
	default: return;
	}
}

void demo_window::on_menu_item_selected(UINT item_id)
{
	info_msg(L"Menu Item selected", menu_cmd(item_id).text());
}

void demo_window::on_right_mouse_down(win::enum_virtual_button v_btn, win::position pos)
{
	_popup_mnu->show(pos);
};


