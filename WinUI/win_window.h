#pragma once
#include "win_app.h"
#include "win_item.h"
#include "win_menu_sub.h"

class win_window : public win_item
{
	const std::wstring _win_class{ L"win_window_class" };
public:
	//EVENT CALLBACK TYPEDEFS//
	using on_close_window_type = std::function<bool()>;
	using on_menu_item_clicked = std::function<void(UINT)>;
	using on_menu_item_checked = std::function<void(UINT, BOOL)>;

	//C/D-TORS//
	win_window(gsl::not_null<win_app*> app, std::wstring title);

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

	//METHODS//
	void close();
	
protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;
	
	
private:
	win_app* _app{ nullptr };
	menu_cmd_map _cmd_type;
	
	//
	


	//

	on_close_window_type _on_close_window{};
	on_menu_item_clicked _on_menu_item_clicked{};
	on_menu_item_checked _on_menu_item_checked{};

	//

	friend class win_menu_sub;
};

