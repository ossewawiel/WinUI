#include "demo_window.h"

demo_window::demo_window(gsl::not_null<demo_app*> app, std::wstring title) : win_window{ app, title }
{

	_menu_bar = std::make_unique<win_menu_bar>(this);
	auto& file = _menu_bar->create_file_menu();

	auto& edit = _menu_bar->create_edit_menu();

	set_on_close_window(std::bind(&demo_window::on_close, this));
}

bool demo_window::on_close()
{
	return yesno_msg(L"Message", L"The window is about to close, do you want to proceeed");
}
