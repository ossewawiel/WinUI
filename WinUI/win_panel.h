#pragma once
#include "win_item.h"


class win_panel :
	public win_item
{
	const std::wstring _panel_class{ L"win_panel_class" };
public:
	//C/D-TORS//
	win_panel(NN(win_item*) parent, UINT panel_id);

protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;
};

