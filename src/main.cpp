#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>

#define WND_CLASS_NAME L"MAIN_WND"
#define WND_TITLE L"Window title"

#define LOG_FILENAME "output.log"

void WriteToLogFile(const char* data_str)
{
    FILE* log_file_ptr = NULL;

    log_file_ptr = fopen(LOG_FILENAME, "a+");
    if (!log_file_ptr) {
        return;
    }

    fprintf(log_file_ptr, data_str);

    fclose(log_file_ptr);
}

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

HWND InitWindow(HINSTANCE h_instance, const wchar_t* wnd_title, int wnd_w, int wnd_h)
{
    int wnd_pos_x = 0;
    int wnd_pos_y = 0;
    HWND h_wnd = NULL;
    WNDCLASSEX wc = {};

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

    // Place the window in cetnter of the screen
    wnd_pos_x = (GetSystemMetrics(SM_CXSCREEN) - wnd_w) / 2;
    wnd_pos_y = (GetSystemMetrics(SM_CYSCREEN) - wnd_h) / 2;

    h_wnd = CreateWindowEx(
        0,
        WND_CLASS_NAME,
        WND_TITLE,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        wnd_pos_x, wnd_pos_y,
        wnd_w, wnd_h,
        NULL,
        NULL,
        h_instance,
        NULL);

    if (!h_wnd) {
        MessageBox(NULL, L"Error", L"CreateWindowEx() fail", MB_ICONERROR);
        return NULL;
    }

    return h_wnd;
}

int WINAPI wWinMain(_In_ HINSTANCE h_instance, _In_opt_ HINSTANCE h_prev_instance,
    _In_ LPWSTR lp_cmd_line, _In_ int n_show_cmd)
{
    int wnd_w = 600;
    int wnd_h = 480;
    HWND h_wnd{};
    MSG msg{};

    h_wnd = InitWindow(h_instance, WND_TITLE, wnd_w, wnd_h);

    if (!h_wnd) {
        MessageBox(NULL, L"Error", L"InitWindow() fail", MB_ICONERROR);
        return 1;
    }

    WriteToLogFile("Test log message\n");

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
