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
	[[nodiscard]] win_menu_item* parent() noexcept { return _parent; }
	[[nodiscard]] bool	enabled();
	void	enabled(bool val);
	[[nodiscard]] bool	checked();
	void	checked(bool val);
	[[nodiscard]] bool	selected();
	void	selected(bool val);

	//STATICS//
	[[nodiscard]] static win_menu_command construct_action(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
		, bool enabled = true
		, bool v_seperator = false);

	[[nodiscard]] static win_menu_command construct_checkable(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
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
		NN(win_menu_item*) parent
		, UINT id
		, MENUITEMINFO const& mii
		, UINT first_id = 0
		, UINT last_id = 0
		, win::enum_menu_cmd_type type = win::enum_menu_cmd_type::ACTION);

	win_menu_item*	_parent{ nullptr };
	UINT			_id{ 0 };
	win::enum_menu_cmd_type _type{ win::enum_menu_cmd_type::ACTION };
	UINT _first_selectable{ 0 };
	UINT _last_selectable{ 0 };
};



