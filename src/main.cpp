#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#define WND_CLASS_NAME L"MAIN_WND"
#define WND_TITLE L"Window title"

LRESULT CALLBACK WndProc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    return DefWindowProc(h_wnd, msg, w_param, l_param);
}

int WINAPI wWinMain(_In_ HINSTANCE h_instance, _In_opt_ HINSTANCE h_prev_instance,
    _In_ LPWSTR lp_cmd_line, _In_ int n_show_cmd)
{
    HWND h_wnd{};
    MSG msg{};
    WNDCLASSEX wc{};

    wc.cbSize = sizeof(wc);
    wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = h_instance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WND_CLASS_NAME;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Error", L"RegisterClassEx() fail", MB_ICONERROR);
        return NULL;
    }

    h_wnd = CreateWindowEx(
        0,
        WND_CLASS_NAME,
        WND_TITLE,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0,
        500,
        300,
        NULL,
        NULL,
        h_instance,
        NULL);

    if (!h_wnd) {
        MessageBox(NULL, L"Error", L"CreateWindowEx() fail", MB_ICONERROR);
        return NULL;
    }

    /* Main loop */
    for (;;) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
