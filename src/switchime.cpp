#include <iostream>

#include <windows.h>
#include <winuser.h>

int GetWindowsKeyboardLayout(const HWND hwnd) {
    HKL hkl;
    DWORD tid = GetWindowThreadProcessId(hwnd, NULL);
    hkl = GetKeyboardLayout(tid);
    return reinterpret_cast<intptr_t>(hkl) & 0xFFFF;
}

int main(int argc, char **argv) {
    const int US_HKL = 0x0409;
    const int ZH_HKL = 0x0804;
    HWND hwnd = GetForegroundWindow();

    if (argc > 1) {
        if ((strcmp(argv[1], "en") == 0) || (strcmp(argv[1], "eng") == 0) ||
            (strcmp(argv[1], "off") == 0)) {
            std::cout << "Switch to English IME\n";
            return SendMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, US_HKL);
        } else if ((strcmp(argv[1], "cn") == 0) ||
                   (strcmp(argv[1], "chn") == 0) ||
                   (strcmp(argv[1], "on") == 0)) {
            std::cout << "Switch to Chinese IME\n";
            return SendMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, ZH_HKL);
        } else if (strcmp(argv[1], "query") == 0) {
            int hkl = GetWindowsKeyboardLayout(hwnd);
            if (hkl == ZH_HKL) {
                std::cout << "Current window's input layout is 0x" << std::hex
                          << hkl << " (Chinese)" << std::endl;
                return 2;
            } else if (hkl == 0) {
                std::cout << "Cannot get input layout of current window"
                          << std::endl;
                return 0;
            } else {
                std::cout << "Current window's input layout is 0x" << std::hex
                          << hkl << " (English)" << std::endl;
                return 1;
            }
        }
    }
    std::cout << "Toggle IME\n";
    return SendMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, INPUTLANGCHANGE_FORWARD,
                       0);
}
