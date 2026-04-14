#include <iostream>
#include <windows.h>

using namespace std;

// tekan tombol
void pressKey(WORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;

    SendInput(1, &input, sizeof(INPUT));
}

// lepas tombol
void releaseKey(WORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

// klik (tekan + lepas)
void clickKey(WORD key, int delay = 50) {
    pressKey(key);
    Sleep(delay);
    releaseKey(key);
}

int main() {
    bool aktif = false;
    bool ctrlPressed = false;

    while (true) {

        // Toggle pakai CTRL
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
            if (!ctrlPressed) {
                aktif = !aktif;
                cout << (aktif ? "ON" : "OFF") << endl;
                ctrlPressed = true;
                Sleep(200);
            }
        } else {
            ctrlPressed = false;
        }

        if (aktif) {

            clickKey('B', 60);
            Sleep(80);
            clickKey('J', 60);
            Sleep(80);
            clickKey('K', 60);
            Sleep(80);
            // 1. TAHAN tombol O (2.8 detik)
            pressKey('O');
            Sleep(2800); // HOLD 2.8 detik
            releaseKey('O');

            Sleep(100); // jeda kecil biar natural

            // 2. Klik tombol I
            pressKey('I');
            Sleep(500); // HOLD 0.5 detik
            releaseKey('I');

            // 3. Klik tombol U
            pressKey('U');
            Sleep(500); // HOLD 0.5 detik
            releaseKey('U');

            Sleep(80);
            clickKey('I', 60);
            Sleep(80);
            Sleep(200); // jeda sebelum ulang siklus
        }

        Sleep(1);
    }

    return 0;
}
