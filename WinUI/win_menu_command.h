#pragma once
#include "win_menu_item.h"

class win_menu_sub;



class win_menu_command
{
public:
	//EVENT CALLBACK TYPEDEFS//
	using on_command_checked = std::function<void(BOOL)>;
	using on_command_enabled = std::function<void(BOOL)>;

	//CTOR/DTOR//
	win_menu_command(win_menu_command&&);
	virtual ~win_menu_command() = default;

	//OPERATORS//
	win_menu_command& operator=(win_menu_command&&);

	//PROPERTIES//
	[[nodiscard]] UINT id() const noexcept { return _id; }
	[[nodiscard]] win::enum_menu_cmd_type	type() const noexcept { return _type; }
	[[nodiscard]] HMENU parent() const noexcept { return _parent; }
	[[nodiscard]] UINT bmp_id() const noexcept { return _bmp_id; }
	[[nodiscard]] bool	enabled();
	void	enabled(bool val);
	[[nodiscard]] bool	checked();
	void	checked(bool val);
	[[nodiscard]] std::wstring	text();
	void	text(std::wstring val);
	[[nodiscard]] UINT first_selectable();
	[[nodiscard]] UINT last_selectable();

	//EVENT SETTERS//
	void set_on_command_checked(on_command_checked func);
	void set_on_command_enabled(on_command_enabled func);


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
		, bool checked = false
		, UINT bitmap_id = 0
		, bool enabled = true
		, bool v_seperator = false);

	[[nodiscard]] static win_menu_command construct_selectable(
		NN(win_menu_item*)
		, UINT id
		, std::wstring const& text
		, UINT first_id
		, UINT last_id
		, bool selected = false
		, UINT bitmap_id = 0
		, bool enabled = true
		, bool v_seperator = false);

protected:
	

private:
	//CTOR/DTOR//
	win_menu_command(
		NN(HMENU) parent
		, UINT id
		, UINT bmp_id
		, MENUITEMINFO const& mii
		, UINT first_id = 0
		, UINT last_id = 0
		, win::enum_menu_cmd_type type = win::enum_menu_cmd_type::ACTION);

	//MEMBERS//
	HMENU	_parent{ nullptr };
	UINT	_id{ 0 };
	win::enum_menu_cmd_type _type{ win::enum_menu_cmd_type::ACTION };
	UINT	_bmp_id{ 0 };
	UINT	_first_selectable{ 0 };
	UINT	_last_selectable{ 0 };

	on_command_checked	_on_command_checked{};
	on_command_enabled	_on_command_enabled{};
};



