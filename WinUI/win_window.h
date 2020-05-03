#pragma once
#include "win_app.h"
#include "win_item.h"

class win_window : public win_item
{
	const std::wstring _win_class{ L"win_window_class" };
public:
	//EVENT CALLBACK TYPEDEFS//
	using on_close_window_type = std::function<bool()>;

	//C/D-TORS//
	win_window(gsl::not_null<win_app*> app, std::wstring title);

	//PROPERTIES//
	//TITLE//
	void title(std::wstring const& val) { win::set_window_text(item_handle(), val); }
	[[nodiscard]] std::wstring title() { return win::get_window_text(item_handle()); }

	//

	void set_on_close_window(on_close_window_type func);

protected:
	LRESULT event_handler(UINT msg, WPARAM, LPARAM) override;

private:
	win_app* _app{ nullptr };
	
	//

	on_close_window_type _on_close_window{};
	
};

