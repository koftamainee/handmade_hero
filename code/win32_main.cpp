#define UNICODE
#define _UNICODE
#include <windows.h>

LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    LRESULT result = 0;
    switch (message) {
    case WM_SIZE: {
        OutputDebugString(L"WM_SIZE\n");
    } break;

    case WM_DESTROY: {
        OutputDebugString(L"WM_DESTROY\n");
        PostQuitMessage(0);
        result = 0;
    } break;

    case WM_CLOSE: {
        OutputDebugString(L"WM_CLOSE\n");
        DestroyWindow(window);
    } break;

    case WM_ACTIVATEAPP: {
        OutputDebugString(L"WM_ACTIVATEAPP\n");
    } break;

    case WM_PAINT: {
        OutputDebugString(L"WM_PAINT\n");
        PAINTSTRUCT paint;
        HDC device_context = BeginPaint(window, &paint);

        int x = paint.rcPaint.left;
        int y = paint.rcPaint.top;
        int w = paint.rcPaint.right - paint.rcPaint.left;
        int h = paint.rcPaint.bottom - paint.rcPaint.top;

        PatBlt(device_context, x, y, w, h, WHITENESS);

        EndPaint(window, &paint);
    } break;

    default: {
        result = DefWindowProc(window, message, w_param, l_param);
    } break;
    }

    return result;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR command_line, int show_code) {
    WNDCLASS window_class = {};
    wchar_t window_class_name[] = L"HandmadeHeroWindowClass";

    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = instance;
    // window_class.hIcon = ;
    window_class.lpszClassName = window_class_name;

    if (!RegisterClass(&window_class)) {
        // TODO: logging
        return 1;
    }

    HWND window = CreateWindowEx(0, window_class_name, L"Handmade Hero", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, instance, NULL);

    if (window == NULL) {
        // TODO: logging
        return 1;
    }

    ShowWindow(window, show_code);
    UpdateWindow(window);

    MSG message;
    for (;;) {
        BOOL message_result = GetMessage(&message, 0, 0, 0);
        if (message_result > 0) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else {
            break;
        }
    }
    return 0;
}
