#pragma once
#include "framework.h"
#include "win_item.h"

class win_rebar :
	public win_item
{
public:
	win_rebar(gsl::not_null<win_item*> parent) :
		win_item{parent}
	{
        HWND hwndRebar = CreateWindowEx(WS_EX_TOOLWINDOW,
            REBARCLASSNAME,
            NULL,
            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
            WS_CLIPCHILDREN | RBS_VARHEIGHT |
            CCS_NODIVIDER | RBS_BANDBORDERS,
            0, 0, 0, 0,
            parent->item_handle(),
            NULL,
            app_handle(), // global instance handle
            NULL);
        if (hwndRebar == nullptr)
            THROW_LAST_ERROR();

        item_handle(hwndRebar);

       item_map().emplace(item_handle(), this);
	}

protected:
    LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;

private:
};

