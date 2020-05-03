#include "demo_window.h"

demo_window::demo_window(gsl::not_null<demo_app*> app, std::wstring title) : win_window{ app, title }
{

	_menu_bar = std::make_unique<win_menu_bar>(this);
	auto& file = _menu_bar->create_file_menu();
	file.add_action(L"&New", menu_id::M_F_NEW);
	file.add_action(L"&Open", menu_id::M_F_OPEN);
	file.add_seperator();
	file.add_action(L"&Save", menu_id::M_F_SAVE);
	file.add_action(L"&Save as..", menu_id::M_F_SAVE_AS);
	file.add_seperator();
	//file.add_sub_menu(L"&Recent");
	file.add_seperator();
	file.add_action(L"&Exit", menu_id::M_F_EXIT);

	auto& edit = _menu_bar->create_edit_menu();

	set_on_close_window(std::bind(&demo_window::on_close, this));
}

bool demo_window::on_close()
{
	return yesno_msg(L"Message", L"The window is about to close, do you want to proceeed");
}
