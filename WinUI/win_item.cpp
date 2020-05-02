#include "win_item.h"

std::map<HWND, win_item*> win_item::_item_map{};

void win_item::show()
{
	try
	{
		::ShowWindow(_item_handle.get(), SW_SHOWNORMAL);
		THROW_IF_WIN32_BOOL_FALSE(::UpdateWindow(_item_handle.get()));
	}
	catch (std::exception const& ex)
	{
		exception_msg("Run-time exception...", ex);
	}
}