#pragma once
#include "win_window.h"

class win_menu_item
{
public:
	win_menu_item(NN(win_window*) window, HMENU menu_handle) :
		_my_window{ window },
		_handle{ menu_handle }
	{}

	win_menu_item(win_menu_item&& rhs) noexcept :
		_my_window{ nullptr },
		_handle{ nullptr }
	{
		std::swap(_my_window, rhs._my_window);
		std::swap(_handle, rhs._handle);
	}

	win_menu_item& operator=(win_menu_item&& rhs) noexcept
	{
		if (this != &rhs)
		{
			_my_window = nullptr;
			_handle.reset(nullptr);
			std::swap(_my_window, rhs._my_window);
			std::swap(_handle, rhs._handle);
		}
		return *this;
	}

	virtual ~win_menu_item() = default;

	[[nodiscard]] win_window* window() { return _my_window; }
	[[nodiscard]] HMENU handle() { return _handle.get(); }

protected:
	void set_menu()
	{
		win::set_menu(_my_window->item_handle(), _handle.get());
	}

private:
	win_window* _my_window{ nullptr };
	wil::unique_hmenu _handle{ nullptr };
};

/*****************************************/

class win_popup_menu :
	win_menu_item
{
public:

};






