#pragma once
#include <gsl\gsl>
#include "win_window.h"

#include "win_menu_bar.h"
#include "demo_app.h"


class demo_window :
	public win_window
{
public:
	demo_window(gsl::not_null<demo_app*> app, std::wstring title);

private:
	std::unique_ptr<win_menu_bar> _menu_bar{ nullptr };
	bool on_close();
};

