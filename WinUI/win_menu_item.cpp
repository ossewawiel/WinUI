#include "framework.h"
#include "win_menu_item.h"
#include "win_window.h"


win_menu_item::win_menu_item(NN(win_window*) window, HMENU menu_handle) :
	_my_window{ window },
	_handle{ menu_handle }
{}

win_menu_item::win_menu_item(win_menu_item&& rhs) noexcept :
	_my_window{ std::move(rhs._my_window) },
	_handle{ std::move(rhs._handle) }
{
	rhs._my_window = nullptr;
	rhs._handle = nullptr;
}

win_menu_item& win_menu_item::operator=(win_menu_item&& rhs) noexcept
{
	if (this != &rhs)
	{
		_my_window = std::move(rhs._my_window);
		_handle = std::move(rhs._handle);
		rhs._my_window = nullptr;
		rhs._handle = nullptr;
	}
	return *this;
}

void win_menu_item::set_menu()
{
	win::set_menu(_my_window->item_handle(), _handle.get());
}
