#pragma once
#include "win_app.h"
#include "win_item.h"
#include "win_menu_sub.h"

class win_window : public win_item
{
	const std::wstring _win_class{ L"win_window_class" };
public:
	struct theme
	{
		HBRUSH clr_menubar_bkg{ nullptr };// CreateSolidBrush(RGB(203, 214, 232))
		HBRUSH clr_window_bkg{ nullptr };// 
	};


	//EVENT CALLBACK TYPEDEFS//
	using on_close_window_type = std::function<bool()>;
	using on_menu_item_clicked = std::function<void(UINT)>;
	using on_menu_item_checked = std::function<void(UINT, BOOL)>;
	using on_menu_item_selected = std::function<void(UINT)>;
	using on_right_mouse_down = std::function<void(win::enum_virtual_button, win::position)>;

	//C/D-TORS//
	win_window(gsl::not_null<win_app*> app, std::wstring title, theme the_theme = theme{});

	//PROPERTIES//
	//TITLE//
	void title(std::wstring const& val) { win::set_window_text(item_handle(), val); }
	[[nodiscard]] std::wstring title() { return win::get_window_text(item_handle()); }
	[[nodiscard]] win_menu_command& menu_cmd(UINT cmd);
	[[nodiscard]] menu_cmd_map& menu_cmds() { return _cmd_type; }

	//EVENT SETTERS//
	void set_on_close_window(on_close_window_type func);
	void set_on_menu_item_clicked(on_menu_item_clicked func);
	void set_on_menu_item_checked(on_menu_item_checked func);
	void set_on_menu_item_selected(on_menu_item_selected func);
	void set_on_right_mouse_down(on_right_mouse_down func);

	//METHODS//
	void close();
	
protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;
	
	
private:
	win_app* _app{ nullptr };
	menu_cmd_map _cmd_type;
	HMENU _current_menu_item{ nullptr };
	UINT	_sub_menu_count{ 0 };
	theme _theme{};
	
	//
	
	enum menu_ids: UINT
	{
		M_FILE = 1000,
		M_EDIT,
		M_VIEW,
		M_WINDOW,
		M_HELP,
		M_SUB
	};

	UINT sub_menu_id()
	{
		auto current_id = _sub_menu_count;
		++_sub_menu_count;
		return M_SUB + current_id;
	}

	//

	on_close_window_type	_on_close_window{};
	on_menu_item_clicked	_on_menu_item_clicked{};
	on_menu_item_checked	_on_menu_item_checked{};
	on_menu_item_selected	_on_menu_item_selected{};
	on_right_mouse_down		_on_right_mouse_down{};
	//

	friend class win_menu_sub;
	friend class win_menu_bar;
};

