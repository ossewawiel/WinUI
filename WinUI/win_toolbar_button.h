#pragma once
#include "framework.h"

class win_toolbar;

class win_toolbar_button
{
public:
	win_toolbar_button(
			NN(win_toolbar*) parent
			, UINT cmd_id
			, int pos_index
			, std::wstring const& text
			, UINT bmp_id
			, std::wstring const& tooltip) :
		_parent{ parent },
		_cmd_id{ cmd_id },
		_text{ text },
		_bmp_id{bmp_id},
		_tooltip{ tooltip },
		_pos_index{ pos_index }
	{}

	win_toolbar_button(win_toolbar_button&& rhs);

	virtual ~win_toolbar_button() = default;

	win_toolbar_button& operator=(win_toolbar_button&&);

	[[nodiscard]] UINT bmp_id() const noexcept { return _bmp_id; }
	[[nodiscard]] UINT cmd_id() const noexcept { return _cmd_id; }
	[[nodiscard]] std::wstring const& text() const noexcept { return _text; }
	void enabled(bool val) {}
	void checked(bool val) {}

private:
	win_toolbar*		_parent{ nullptr };
	UINT				_cmd_id{ 0 };
	std::wstring		_tooltip{};
	std::wstring		_text{};
	UINT				_bmp_id{ 0 };
	int					_pos_index{ 0 };
};

