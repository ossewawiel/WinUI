#pragma once

namespace win
{
	using left = int;
	using width = int;
	using top = int;
	using height = int;
	//using position = std::pair<left, top>;
	using dimensions = std::pair<width, height>;

	struct position { long left; long top; };
	
#ifndef CATCH_RUNTIME_WITH_MSG
#define CATCH_RUNTIME_WITH_MSG catch(std::exception const& ex)		\
	{																\
		exception_msg("Run-time exception...", ex);					\
	}																\
	catch (...)														\
	{																\
		error_msg(L"Run-time exception...", L"Unknown exception");	\
	}																
#endif // !CATCH_RUNTIME_WITH_MSG

	enum class enum_ex_style : DWORD
	{
		NONE = 0x00000000L,
		ACCEPTFILES = 0x00000010L,
		APPWINDOW = 0x00040000L,
		CLIENTEDGE = 0x00000200L,
		COMPOSITED = 0x02000000L,
		CONTEXTHELP = 0x00000400L,
		CONTROLPARENT = 0x00010000L,
		LAYERED = 0x00080000,
		LAYOUTRTL = 0x00400000L,
		LEFT = 0x00000000L,
		LEFTSCROLLBAR = 0x00004000L,
		LTRREADING = 0x00000000L,
		MDICHILD = 0x00000040L,
		NOACTIVATE = 0x08000000L,
		NOINHERITLAYOUT = 0x00100000L,
		NOPARENTNOTIFY = 0x00000004L,
		NOREDIRECTIONBITMAP = 0x00200000L,
		RIGHT = 0x00001000L,
		RIGHTSCROLLBAR = 0x00000000L,
		RTLREADING = 0x00002000L,
		STATICEDGE = 0x00020000L,
		TOOLWINDOW = 0x00000080L,
		TOPMOST = 0x00000008L,
		WS_TRANSPARENT = 0x00000020L,
		WINDOWEDGE = 0x00000100L,
		OVERLAPPEDWINDOW = (WINDOWEDGE | CLIENTEDGE),
		PALETTEWINDOW = (WINDOWEDGE | TOOLWINDOW | TOPMOST)
	};

	enum class enum_style : DWORD
	{
		BORDER = 0x00800000LU,
		CAPTION = 0x00C00000LU,
		CHILD = 0x40000000LU,
		CHILDWINDOW = 0x40000000LU,
		CLIPCHILDREN = 0x02000000LU,
		CLIPSIBLINGS = 0x04000000LU,
		DISABLED = 0x08000000LU,
		DLGFRAME = 0x00400000LU,
		GROUP = 0x00020000LU,
		HSCROLL = 0x00100000LU,
		ICONIC = 0x20000000LU,
		MAXIMIZE = 0x01000000LU,
		MAXIMIZEBOX = 0x00010000LU,
		MINIMIZE = 0x20000000LU,
		MINIMIZEBOX = 0x00020000LU,
		OVERLAPPED = 0x00000000LU,
		POPUP = 0x80000000LU,
		SIZEBOX = 0x00040000LU,
		SYSMENU = 0x00080000LU,
		TABSTOP = 0x00010000LU,
		THICKFRAME = 0x00040000LU,
		TILED = 0x00000000LU,
		TILEDWINDOW = (OVERLAPPED | CAPTION | SYSMENU | THICKFRAME | MINIMIZEBOX | MAXIMIZEBOX),
		VISIBLE = 0x10000000LU,
		VSCROLL = 0x00200000LU,
		POPUPWINDOW = (POPUP | BORDER | SYSMENU),
		OVERLAPPEDWINDOW = (OVERLAPPED | CAPTION | SYSMENU | THICKFRAME | MINIMIZEBOX | MAXIMIZEBOX)
	};

	enum class enum_button_style
	{
		TRISTATE = BS_3STATE,
		AUTOTRISTATE = BS_AUTO3STATE,
		AUTOCHECKBOX = BS_AUTOCHECKBOX,
		AUTORADIOBUTTON = BS_AUTORADIOBUTTON,
		BITMAP = BS_BITMAP,
		BOTTOM = BS_BOTTOM,
		CENTER = BS_CENTER,
		CHECKBOX = BS_CHECKBOX,
		COMMANDLINK = BS_COMMANDLINK,
		DEFCOMMANDLINK = BS_DEFCOMMANDLINK,
		DEFPUSHBUTTON = BS_DEFPUSHBUTTON,
		DEFSPLITBUTTON = BS_DEFSPLITBUTTON,
		GROUPBOX = BS_GROUPBOX,
		ICON = BS_ICON,
		FLAT = BS_FLAT,
		LEFT = BS_LEFT,
		LEFTTEXT = BS_LEFTTEXT,
		MULTILINE = BS_MULTILINE,
		NOTIFY = BS_NOTIFY,
		OWNERDRAW = BS_OWNERDRAW,
		PUSHBUTTON = BS_PUSHBUTTON,
		PUSHLIKE = BS_PUSHLIKE,
		RADIOBUTTON = BS_RADIOBUTTON,
		RIGHT = BS_RIGHT,
		RIGHTBUTTON = BS_RIGHTBUTTON,
		SPLITBUTTON = BS_SPLITBUTTON,
		TEXT = BS_TEXT,
		TOP = BS_TOP,
		TYPEMASK = BS_TYPEMASK,
		USERBUTTON = BS_USERBUTTON,
		VCENTER = BS_VCENTER
	};

	enum class enum_virtual_button
	{
		NONE = 0x0000,
		CTRL = 0x0008,
		LEFT_MOUSE = 0x0001,
		CENTER_MOUSE = 0x0010,
		RIGHT_MOUSE = 0x0002,
		SHIFT = 0x0004,
		MOUSE_BTN1 = 0x0020,
		MOUSE_BTN2 = 0x0040
	};

	enum class enum_menu_cmd_type
	{
		ACTION,
		CHECKABLE,
		SELECTABLE
	};

	

	static wil::unique_hwnd create_item(
		HINSTANCE app
		, HWND parent
		, HMENU menu
		, std::wstring const& class_name
		, std::wstring const& window_name
		, win::enum_ex_style ex_style
		, win::enum_style style
		, win::position pos
		, win::dimensions dim)
	{
		try
		{
			HWND hWnd = ::CreateWindowEx(
				static_cast<DWORD>(ex_style)
				, class_name.c_str()
				, window_name.c_str()
				, static_cast<DWORD>(style)
				, pos.left
				, pos.top
				, dim.first
				, dim.second
				, parent
				, menu
				, app
				, nullptr);

			THROW_LAST_ERROR_IF_NULL(hWnd);

			return wil::unique_hwnd(hWnd);
		}
		CATCH_RUNTIME_WITH_MSG;

		return nullptr;
	}

	static void init_common_controls()
	{
		try
		{
			// Initialize common controls.
			INITCOMMONCONTROLSEX icex;
			icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
			icex.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
			THROW_IF_WIN32_BOOL_FALSE(::InitCommonControlsEx(&icex));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static int get_window_text_length(HWND handle)
	{
		try
		{
			auto val = ::GetWindowTextLength(handle);
			if (val == 0)
				THROW_LAST_ERROR();
			
			return val;
		}
		CATCH_RUNTIME_WITH_MSG
	}

	static void set_window_text(HWND handle, std::wstring const& text)
	{
		try 
		{
			THROW_IF_WIN32_BOOL_FALSE(::SetWindowText(handle, text.c_str()));
		}
		CATCH_RUNTIME_WITH_MSG
	}

	[[nodiscard]] static std::wstring get_window_text(HWND handle)
	{
		try
		{
			int len = get_window_text_length(handle) + 1;
			std::vector<wchar_t> buf(len);
			auto val = ::GetWindowText(handle, buf.data(), len);
			if (val == 0)
				THROW_LAST_ERROR();

			return std::wstring{ &buf[0] };
		}
		CATCH_RUNTIME_WITH_MSG
	}

	[[nodiscard]] static HMENU create_menu()
	{
		try
		{
			auto val = ::CreateMenu();
			if (val == nullptr)
				THROW_LAST_ERROR();

			return val;
		}
		CATCH_RUNTIME_WITH_MSG;

		return nullptr;
	}

	[[nodiscard]] static HMENU create_popup_menu()
	{
		try
		{
			auto val = ::CreatePopupMenu();
			if (val == nullptr)
				THROW_LAST_ERROR();

			return val;
		}
		CATCH_RUNTIME_WITH_MSG;

		return nullptr;
	}

	static void append_menu(HMENU parent_handle, HMENU menu_handle, UINT options, std::wstring const& name)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::AppendMenu(parent_handle, options, (UINT)menu_handle, name.c_str()));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	static void set_menu(HWND window_handle, HMENU menu_handle)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::SetMenu(window_handle, menu_handle));
		}
		CATCH_RUNTIME_WITH_MSG
	}

	static void draw_menu_bar(HWND window_handle)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::DrawMenuBar(window_handle));
		}
		CATCH_RUNTIME_WITH_MSG
	}

	static void insert_menu_item(HMENU parent_handle, UINT id, bool by_position, MENUITEMINFO const& mii)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::InsertMenuItem(parent_handle, id, by_position ? TRUE : FALSE, &mii));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static int get_menu_item_count(HMENU mnu)
	{
		try
		{
			auto count = ::GetMenuItemCount(mnu);
			if (count == -1) THROW_LAST_ERROR();
			return count;
		}
		CATCH_RUNTIME_WITH_MSG;

		return 0;
	}
	
	static void destroy_window(HWND window)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::DestroyWindow(window));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static bool menu_item_checked(HMENU parent, UINT id)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STATE;
			THROW_IF_WIN32_BOOL_FALSE(::GetMenuItemInfo(parent, id, FALSE, &mii));
			return mii.fState == MFS_CHECKED ? true : false;
		}
		CATCH_RUNTIME_WITH_MSG;

		return false;
	}

	static void menu_item_checked(HMENU parent, UINT id, bool checked)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STATE;
			mii.fState = checked ? MFS_CHECKED : MFS_UNCHECKED;
			THROW_IF_WIN32_BOOL_FALSE(::SetMenuItemInfo(parent, id, FALSE, &mii));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static bool do_menu_item_checked(HMENU parent, UINT id)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STATE;
			THROW_IF_WIN32_BOOL_FALSE(::GetMenuItemInfo(parent, id, FALSE, &mii));
			mii.fState ^= MFS_CHECKED;
			THROW_IF_WIN32_BOOL_FALSE(::SetMenuItemInfo(parent, id, FALSE, &mii));
			return mii.fState == MFS_CHECKED ? true : false;
		}
		CATCH_RUNTIME_WITH_MSG;

		return false;
	}

	static void menu_item_enable(HMENU parent, UINT id, bool enable = true)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STATE;
			mii.fState = enable ? MFS_ENABLED : MFS_DISABLED;
			THROW_IF_WIN32_BOOL_FALSE(::SetMenuItemInfo(parent, id, FALSE, &mii));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static bool menu_item_enabled(HMENU parent, UINT id)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STATE;
			THROW_IF_WIN32_BOOL_FALSE(::SetMenuItemInfo(parent, id, FALSE, &mii));
			return mii.fState == MFS_ENABLED ? true : false;
		}
		CATCH_RUNTIME_WITH_MSG;

		return false;
	}

	[[nodiscard]] static std::wstring menu_item_text(HMENU parent, UINT id)
	{
		try
		{
			MENUITEMINFO mii{};
			mii.cbSize = sizeof(MENUITEMINFO);
			mii.fMask = MIIM_STRING;
			mii.dwTypeData = nullptr;
			THROW_IF_WIN32_BOOL_FALSE(::GetMenuItemInfo(parent, id, FALSE, &mii));
			std::vector<wchar_t> buf(mii.cch + 1);
			mii.dwTypeData = buf.data();
			mii.cch += 1;
			THROW_IF_WIN32_BOOL_FALSE(::GetMenuItemInfo(parent, id, FALSE, &mii));
			return std::wstring{ &buf[0] };
		}
		CATCH_RUNTIME_WITH_MSG;

		return std::wstring{};
	}

	static void do_menu_item_selected(HMENU parent, UINT id, UINT first_id, UINT last_id)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::CheckMenuRadioItem(parent, first_id, last_id, id, MF_BYCOMMAND));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	static void default_item(HMENU parent, UINT id)
	{
		try
		{
			THROW_IF_WIN32_BOOL_FALSE(::SetMenuDefaultItem(parent, id, FALSE));
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static ::RECT get_client_rectangle(HWND handle)
	{
		try
		{
			RECT rc{};
			THROW_IF_WIN32_BOOL_FALSE(::GetClientRect(handle, &rc));
			return rc;
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static bool point_in_rectangle(RECT const& rc, POINT const& pt)
	{
			return ::PtInRect(&rc, pt) != 0;
	}

	[[nodiscard]] static bool clicked_in_current_rectangle(HWND handle, LPARAM lp)
	{
		try
		{
			auto rc = get_client_rectangle(handle);
			POINT pnt{ GET_X_LPARAM(lp), GET_Y_LPARAM(lp) };
			return point_in_rectangle(rc,pnt);
		}
		CATCH_RUNTIME_WITH_MSG;
	}

	[[nodiscard]] static ::POINT get_point(LPARAM lp)
	{
		return ::POINT { GET_X_LPARAM(lp), GET_Y_LPARAM(lp) };
	}

	[[nodiscard]] static position get_position(LPARAM lp)
	{
		return position{ GET_X_LPARAM(lp), GET_Y_LPARAM(lp) };
	}

	[[nodiscard]] static position get_position(::POINT const& pt)
	{
		return position{ pt.x, pt.y };
	}

	[[nodiscard]] static HBITMAP generate_transparent_bitmap(HINSTANCE app_handle, UINT bitmap_id, COLORREF transp_color, COLORREF bg_color)
	{
		try
		{
			COLORMAP colorMap{};
			colorMap.from = transp_color;
			colorMap.to = bg_color;
			HBITMAP hbm = ::CreateMappedBitmap(app_handle, static_cast<INT_PTR>(bitmap_id), 0, &colorMap, 1);
			if (hbm == nullptr)
				THROW_LAST_ERROR();
		}
		CATCH_RUNTIME_WITH_MSG;
	}
}
