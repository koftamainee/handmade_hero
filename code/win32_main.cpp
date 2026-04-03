#include <windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    MessageBoxA(0, "This is Handmade Hero", "Handmade Hero", MB_OK | MB_ICONINFORMATION);
    return 0;
}