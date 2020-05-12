#pragma once

class win_window;

class win_menu_item
{
public:
	win_menu_item(NN(win_window*) window, HMENU menu_handle);
	win_menu_item(win_menu_item&& rhs) noexcept;
	
	virtual ~win_menu_item() {}

	win_menu_item& operator=(win_menu_item&& rhs) noexcept;

	[[nodiscard]] win_window* window() noexcept { return _my_window; }
	[[nodiscard]] HMENU handle() noexcept { return _handle.get(); }

protected:
	void set_menu();

private:
	win_window* _my_window{ nullptr };
	wil::unique_hmenu _handle{ nullptr };
};







