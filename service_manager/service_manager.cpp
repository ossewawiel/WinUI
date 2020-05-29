// service_manager.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "main_dialog.h"
#include "service_manager.h"




void service_manager::init()
{
	 
	_main_dlg = std::make_unique<main_dialog>(this, L"WIN Service Manager");
	_main_dlg->show();
}

#include <win_main.h>
int win_main()
{
	service_manager app{ L"Windows Service Manager" };
	return app.run();
}