#include "win_toolbar_button.h"

win_toolbar_button::win_toolbar_button(win_toolbar_button&& rhs) :
	_parent{ std::move(rhs._parent) },
	_cmd_id{ std::move(rhs._cmd_id) },
	_tooltip{ std::move(rhs._tooltip) },
	_text{ std::move(rhs._text) },
	_bmp_id{ std::move(rhs._bmp_id) },
	_pos_index{ std::move(rhs._pos_index) }
{
	rhs._parent = nullptr;
}

win_toolbar_button& win_toolbar_button::operator=(win_toolbar_button&& rhs)
{
	if (this != &rhs)
	{
		_parent = std::move(rhs._parent);
		_cmd_id = std::move(rhs._cmd_id);
		_tooltip = std::move(rhs._tooltip);
		_text = std::move(rhs._text);
		_bmp_id = std::move(rhs._bmp_id);
		_pos_index = std::move(rhs._pos_index);
		rhs._parent = nullptr;
	}
	return *this;
}
