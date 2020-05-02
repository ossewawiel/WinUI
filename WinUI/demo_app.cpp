#include "demo_window.h"
#include "demo_app.h"

#include "win_main.h"

int win_main()
{
	demo_app app{ L"Demonstration Application" };
	return app.run();
}

void demo_app::init()
{
	_demo_window = std::make_unique<demo_window>(this, L"Demo App Title");
	_demo_window->show();
}
