#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "win_app.h"

extern int win_main();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    win_app::hinstance(hInstance);
    win_app::prev_hinstance(hPrevInstance);
    win_app::cmd_line(lpCmdLine);
    win_app::cmd_show(nCmdShow);

    int result = 1;
    try 
    {
        result = win_main();
    }
    catch (std::exception const& ex) //TODO make exception wrapper
    {
        static const CHAR title[] = "Run-time exception...";
        ::MessageBoxA(0, ex.what(), title, MB_OK | MB_ICONSTOP | MB_TASKMODAL); //TODO make static cpp friendly message box
    }
    catch (...)
    {
        static const WCHAR title[] = L"Run-time exception...";
        static const WCHAR msg[] = L"Unknown exception";
        ::MessageBox(0, msg, title, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
    }

    return result;
}
