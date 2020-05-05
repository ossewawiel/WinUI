#include "framework.h"
#include "win_menu_item.h"
#include "win_window.h"

void win_menu_item::set_menu()
{
	win::set_menu(_my_window->item_handle(), _handle.get());
}
