#pragma once
#include "framework.h"
#include "win_item.h"

class win_toolbar :
	public win_item
{
public:
	win_toolbar(gsl::not_null<win_item*> parent) :
		win_item{ parent }
	{
		HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
			parent->item_handle(), NULL, app_handle(), NULL);

		if (hWndToolbar == nullptr)
			THROW_LAST_ERROR();

		SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
		::ShowWindow(hWndToolbar, TRUE);

		item_handle(hWndToolbar);

		item_map().emplace(item_handle(), this);
	}

	void add_button(std::wstring const& title, UINT cmd_id, UINT bitmap_id, std::wstring const& tooltip)
	{
		SendMessage(item_handle(), TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
		DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);
		COLORMAP colorMap;
		colorMap.from = RGB(0, 128, 128);
		colorMap.to = backgroundColor;
		HBITMAP hbm = CreateMappedBitmap(app_handle(), bitmap_id, 0, &colorMap, 1);
		TBADDBITMAP tb;
		tb.hInst = NULL;
		tb.nID = (UINT_PTR)hbm;

		// hWndToolbar is the window handle of the toolbar.
		// Do not forget to send TB_BUTTONSTRUCTSIZE if the toolbar was 
		// created by using CreateWindowEx.
		int index = SendMessage(item_handle(), TB_ADDBITMAP, 0, (LPARAM)&tb);
		TBBUTTON btn{ STD_FILENEW, cmd_id, TBSTATE_ENABLED, BTNS_AUTOSIZE, { 0 }, 0L, reinterpret_cast<INT_PTR>(title.c_str()) };
		SendMessage(item_handle(), TB_INSERTBUTTON, 0, reinterpret_cast<INT_PTR>(&btn));
		SendMessage(item_handle(), TB_AUTOSIZE, 0, 0);
		::ShowWindow(item_handle(), TRUE);
	}

protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;

private:

};

