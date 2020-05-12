#pragma once
#include "win_menu_item.h"

class win_menu_sub;



class win_menu_command
{
public:
	
	win_menu_command(win_menu_command&&);
	
	virtual ~win_menu_command() = default;

	win_menu_command& operator=(win_menu_command&&);

	[[nodiscard]] UINT id() const noexcept { return _id; }
	[[nodiscard]] win::enum_menu_cmd_type	type() const noexcept { return _type; }
	[[nodiscard]] HMENU parent() noexcept { return _parent; }
	[[nodiscard]] bool	enabled();
	void	enabled(bool val);
	[[nodiscard]] bool	checked();
	void	checked(bool val);
	[[nodiscard]] bool	selected();
	void	selected(bool val);
	[[nodiscard]] std::wstring	text();
	void	text(std::wstring val);
	[[nodiscard]] UINT first_selectable();
	[[nodiscard]] UINT last_selectable();

	//STATICS//
	[[nodiscard]] static win_menu_command construct_action(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
		, UINT bitmap_id
		, bool enabled = true
		, bool v_seperator = false);

	[[nodiscard]] static win_menu_command construct_checkable(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
		, UINT bitmap_id = 0
		, bool checked = false
		, bool enabled = true
		, bool v_seperator = false);

	[[nodiscard]] static win_menu_command construct_selectable(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
		, UINT first_id
		, UINT last_id
		, bool selected = false
		, bool enabled = true
		, bool v_seperator = false);

protected:
	

private:
	win_menu_command(
		NN(HMENU) parent
		, UINT id
		, MENUITEMINFO const& mii
		, UINT first_id = 0
		, UINT last_id = 0
		, win::enum_menu_cmd_type type = win::enum_menu_cmd_type::ACTION);

	HMENU	_parent{ nullptr };
	UINT			_id{ 0 };
	win::enum_menu_cmd_type _type{ win::enum_menu_cmd_type::ACTION };
	UINT _first_selectable{ 0 };
	UINT _last_selectable{ 0 };
};



