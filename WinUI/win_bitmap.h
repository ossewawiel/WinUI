#pragma once
#include "framework.h"
#include "win_app.h"

class win_bitmap
{
public:

	static HBITMAP create_bitmap(UINT resource_id)
	{
		return ::LoadBitmap(win_app::_instance.get(), MAKEINTRESOURCE(resource_id));
	}
private:

};

