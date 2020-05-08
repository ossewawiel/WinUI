#pragma once

class win_window;

class win_menu_item
{
public:
	win_menu_item(NN(win_window*) window, HMENU menu_handle) :
		_my_window{ window },
		_handle{ menu_handle }
	{}

	win_menu_item(win_menu_item&& rhs) noexcept :
		_my_window{ std::move(rhs._my_window) },
		_handle{ std::move(rhs._handle) }
	{
		rhs._my_window = nullptr;
		rhs._handle = nullptr;
	}

	win_menu_item& operator=(win_menu_item&& rhs) noexcept
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

	virtual ~win_menu_item()
	{

	}

	[[nodiscard]] win_window* window() { return _my_window; }
	[[nodiscard]] HMENU handle() { return _handle.get(); }

protected:
	void set_menu();

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






