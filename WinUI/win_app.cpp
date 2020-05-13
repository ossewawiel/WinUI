#include "win_item.h"
#include "win_app.h"
#include "Resource.h"
wil::unique_hmodule win_app::_instance = nullptr;
wil::unique_hmodule win_app::_prev_instance = nullptr;
std::wstring win_app::_cmd_line = L"";
int win_app::_cmd_show = 0;

LRESULT CALLBACK win_app::callback_msg_handler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (win_item::item_map().empty() || win_item::item_map().count(hWnd) == 0)
        return DefWindowProc(hWnd, message, wParam, lParam);

    NN(win_item*) item = win_item::item_map().at(hWnd);

    return item->event_handler(message, wParam, lParam);


    //return 0;
    //switch (message)
    //{
    //case WM_COMMAND:
    //{
    //    int wmId = LOWORD(wParam);
    //    // Parse the menu selections:
    //    switch (wmId)
    //    {
    //    //case IDM_ABOUT:
    //    //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //    //    break;
    //    //case IDM_EXIT:
    //    //    DestroyWindow(hWnd);
    //    //    break;
    //    default:
    //        return DefWindowProc(hWnd, message, wParam, lParam);
    //    }
    //}
    //break;
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hWnd, &ps);
    //    // TODO: Add any drawing code that uses hdc here...
    //    EndPaint(hWnd, &ps);
    //}
    //break;
    //case WM_DESTROY:
    //    PostQuitMessage(0);
    //    break;
    //default:
    //    return DefWindowProc(hWnd, message, wParam, lParam);
    //}
    //return 0;
}


int win_app::run() 
{ 
    init();  
    
   HACCEL hAccelTable = LoadAccelerators(win_app::hinstance(), MAKEINTRESOURCE(IDC_WINUI));
   
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    return 1; 
}

WNDCLASSEX win_app::win_class(std::wstring const& name) noexcept
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = win_app::callback_msg_handler;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _instance.get();
    wcex.hIcon = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_APP));;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = name.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP));

    return wcex;
}

ATOM win_app::register_class(WNDCLASSEX const& the_class)
{
    try
    {
        if (ATOM a = ::RegisterClassEx(&the_class); a == 0)
        {
            THROW_LAST_ERROR();
        }
        else
        {
            _class_atom = a;
        }
        return _class_atom;
    }
    catch (std::exception const& ex)
    {
        exception_msg("Run-time exception...", ex);
    }
    catch (...)
    {
        error_msg(L"Run-time exception...", L"Unknown exception");
    }

    return 0;
}
