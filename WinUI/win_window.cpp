#include "framework.h"
#include "win_msg.h"
#include "win_window.h"
#include "win_menu_sub.h"

win_window::win_window(gsl::not_null<win_app*> app, std::wstring title, theme the_theme) :
	win_item{app},
	_app{ app },
	_theme{ the_theme }
{
	try
	{
		_app->register_class(_app->win_class(_win_class));

		win_item::create_main_window(
			nullptr
			, _win_class
			, title.empty() ? _app->app_title() : title
			, win::enum_ex_style::NONE
			, win::enum_style::OVERLAPPEDWINDOW
			, win::position{ CW_USEDEFAULT, 0 }
			, win::dimensions{ CW_USEDEFAULT, 0 });
	}
	CATCH_RUNTIME_WITH_MSG;
}

win_menu_command& win_window::menu_cmd(UINT cmd)
{
	try
	{
		if (_cmd_type.count(cmd) == 0)
			throw std::exception("Menu command requested does not exist");
		return _cmd_type.at(cmd);
	}
	CATCH_RUNTIME_WITH_MSG;
}

void win_window::set_on_close_window(on_close_window_type func)
{
	_on_close_window = func;
}

void win_window::set_on_menu_item_clicked(on_menu_item_clicked func)
{
	_on_menu_item_clicked = func;
}

void win_window::set_on_menu_item_checked(on_menu_item_checked func)
{
	_on_menu_item_checked = func;
}

void win_window::set_on_menu_item_selected(on_menu_item_selected func)
{
	_on_menu_item_selected = func;
}

void win_window::set_on_right_mouse_down(on_right_mouse_down func)
{
	_on_right_mouse_down = func;
}

//METHODS//

void win_window::close() 
{ 
	auto do_close = true;
	if (_on_close_window)
		do_close = _on_close_window();

	if (do_close)
	{
		win::destroy_window(item_handle());
	}
}

LRESULT win_window::event_handler(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_RBUTTONDOWN:
	{
		if (_on_right_mouse_down)
		{
			if (win::clicked_in_current_rectangle(item_handle(), lp))
			{
				_on_right_mouse_down(
					static_cast<win::enum_virtual_button>(wp)
					, win::get_position(lp)
				);
			}
		}
	}
	break;
	/*case WM_ERASEBKGND:
	{
		auto hdc = (HDC)wp;
		RECT rc{};
		
		GetClientRect(item_handle(), &rc);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 100, 100, NULL);
		SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
		FillRect(hdc, &rc, bg);
	}
		return 1L;*/
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(item_handle(), &ps);
		FillRect(hdc, &ps.rcPaint, _theme.clr_window_bkg);
		::EndPaint(item_handle(), &ps);
	}
	break;
	case WM_INITMENUPOPUP:
	{}
	break;
	case WM_COMMAND:
	{
		auto const cmd_id = LOWORD(wp);
		auto& cmd = menu_cmd(cmd_id);
		switch (cmd.type())
		{
		case win::enum_menu_cmd_type::CHECKABLE:
		{
			auto const checked = win::do_menu_item_checked(cmd.parent(), cmd_id);
			if (_on_menu_item_checked)
			{
				_on_menu_item_checked(cmd_id, checked);
			}
		}
		break;
		case win::enum_menu_cmd_type::ACTION:
			if (_on_menu_item_clicked)
				_on_menu_item_clicked(cmd_id);
			break;
		case win::enum_menu_cmd_type::SELECTABLE:
			win::do_menu_item_selected(cmd.parent(), cmd_id, cmd.first_selectable(), cmd.last_selectable());
			if (_on_menu_item_selected)
			{
				_on_menu_item_selected(cmd_id);
			}
			break;
		default:
			break;
		}
	}
	break;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lp)->code)
		{
		case TTN_GETDISPINFO:
		{
			LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lp;

			// Set the instance of the module that contains the resource.
			lpttt->hinst = win_app::hinstance();
			auto entity_id = lpttt->hdr.idFrom;
			if (tb_tooltips().count(entity_id) != 0)
				lpttt->lpszText = const_cast<LPWSTR>(tb_tooltips().at(entity_id).c_str());

			UINT_PTR idButton = lpttt->hdr.idFrom;
		}
		break;
		case TBN_DROPDOWN:
		{
			LPNMTOOLBAR lpnmtb = (LPNMTOOLBAR)lp;
			RECT rc{};
			SendMessage(lpnmtb->hdr.hwndFrom, TB_GETRECT, (WPARAM)lpnmtb->iItem, (LPARAM)&rc);
			MapWindowPoints(lpnmtb->hdr.hwndFrom, HWND_DESKTOP, (LPPOINT)&rc, 2);
			auto entity_id = lpnmtb->iItem;
			if (tlb_cmds().count(entity_id) != 0)
			{
			
				TPMPARAMS tpm;

				tpm.cbSize = sizeof(TPMPARAMS);
				tpm.rcExclude = rc;

				TrackPopupMenuEx(tlb_cmds().at(entity_id).sub_menu()->handle(),
					TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
					rc.left, rc.bottom, item_handle() , &tpm);

			}

		}
		break;
		}
	}
	break;
	case WM_CLOSE:
		close();
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(item_handle(), msg, wp, lp);
	}

	return 0;
}




