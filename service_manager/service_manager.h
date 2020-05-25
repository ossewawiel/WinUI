#pragma once

#include "resource.h"

class main_dialog;

class service_manager :
	public win_app
{
public:
	service_manager(std::wstring const& name) : win_app{ name }
	{}

private:
	std::unique_ptr<main_dialog> _main_dlg{ nullptr };


	void init() final;
};
