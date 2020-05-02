#pragma once

class test_ui_app :
	public win_app
{
public:
	test_ui_app(std::wstring const& appname) : win_app{ appname } {}

private:

	void init() override;
};

