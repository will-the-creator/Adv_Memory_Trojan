#ifndef UAC_BYPASS_H
#define UAC_BYPASS_H

#ifdef __cplusplus
extern "C" {
#endif

void UAC_bypass(const char *path);

#ifdef __cplusplus
}
#endif

#endif 
/* 
#include "uac_bypass.h"

int main() {
    UAC_bypass("C:\\Users\\user\\AppData\\Roaming\\payload.exe");
    return 0;
}

*/
