#include "demo_window.h"

demo_window::demo_window(gsl::not_null<demo_app*> app, std::wstring title) : win_window{ app, title }
{

	_menu_bar = std::make_unique<win_menu_bar>(this);
	auto& file = _menu_bar->create_file_menu();
	file.add_action(L"&New", M_F_NEW);
	file.add_action(L"&Open", M_F_OPEN);
	file.add_seperator();
	file.add_action(L"&Save", M_F_SAVE);
	file.add_action(L"&Save as...", M_F_SAVE_AS);
	file.add_seperator();
	auto& recent = file.add_sub_menu(L"&Recent");
	file.add_seperator();
	file.add_action(L"&Exit", M_F_EXIT);

	recent.add_action(L"First", M_F_R_FIRST);
	recent.add_action(L"Second", M_F_R_SECOND);

	auto& edit = _menu_bar->create_edit_menu();
	edit.add_action(L"C&ut", M_E_CUT);
	edit.add_action(L"&Copy", M_E_COPY);
	edit.add_action(L"&Paste", M_E_PASTE);
	edit.add_vertical_seperator();
	edit.add_action(L"&Undo", M_E_UNDO);
	edit.add_action(L"&Redo", M_E_REDO);
	edit.add_vertical_seperator();
	edit.add_action(L"&Find", M_E_FIND);
	edit.add_action(L"&Replace", M_E_REPLACE);
	edit.add_vertical_seperator();
	edit.add_action(L"&Clone", M_E_CLONE);
	edit.add_action(L"&Delete", M_E_DELETE);

	auto& view = _menu_bar->create_view_menu();
	auto& toolbars = view.add_sub_menu(L"Toolbars");
	toolbars.add_checkable(L"First Checkable", M_V_T_FIRST);
	toolbars.add_checkable(L"Second Checkable", M_V_T_SECOND);
	toolbars.add_checkable(L"Third Checkable", M_V_T_THIRD);
	toolbars.add_checkable(L"Fourth Checkable", M_V_T_FOURTH);
	view.add_seperator();
	view.add_action(L"&Enable", M_V_ENABLE, false);
	view.add_action(L"&Disable", M_V_DISABLE);

	auto& window = _menu_bar->create_window_menu();
	window.add_selectable_group({
		{ L"First Selectable", M_W_FIRST },
		{ L"Second Selectable", M_W_SECOND },
		{ L"Third Selectable", M_W_THIRD },
		{ L"Fourth Selectable", M_W_FOURTH }
		});


	set_on_close_window(std::bind(&demo_window::on_close, this));
	set_on_menu_item_clicked(std::bind(&demo_window::on_menu_item_clicked, this, std::placeholders::_1));
	set_on_menu_item_checked(std::bind(&demo_window::on_menu_item_checked, this, std::placeholders::_1, std::placeholders::_2));
}

bool demo_window::on_close()
{
	return yesno_msg(L"Message", L"The window is about to close, do you want to proceeed");
}

void demo_window::on_menu_item_clicked(UINT item_id)
{
	switch (item_id)
	{
	case M_F_NEW:
	case M_F_OPEN:
	case M_F_SAVE:
	case M_F_SAVE_AS:
	case M_F_R_FIRST:
	case M_F_R_SECOND:
		info_msg(L"Menu Item clicked", std::to_wstring(item_id));
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
