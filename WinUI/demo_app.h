#pragma once

#include "win_app.h"

class demo_window;

class demo_app :
	public win_app
{
public:
	demo_app(std::wstring const& name): win_app{name}
	{}

private:
	std::unique_ptr<demo_window> _demo_window{ nullptr };


	void init() final;
};

