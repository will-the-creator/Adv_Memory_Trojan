### Disclaimer

This project is intended solely for **educational and research purposes**. It is designed to demonstrate common techniques used in malware development and analysis in a **controlled, ethical environment**.

---

### ⚠️ Warning:

- **Do not deploy or distribute** any part of this code in real-world systems or networks without **explicit authorization**.  
- The use of this code against devices, users, or systems without consent is **illegal** and may result in **criminal prosecution**.  
- The author assumes **no liability** for misuse or damage caused by the use or replication of this project.

---

By accessing or using this code, you acknowledge that you understand the risks and agree to use it **responsibly and lawfully**.
/malware_project/
│
├── docs/                      # Documentation
│   ├── architecture.md        # Design and module interactions
│   ├── development_roadmap.md # Step-by-step development plan
│   ├── testing_guides.md      # Safe testing instructions
│
├── droppers/                  # Trojan dropper executables
│   ├── dropper.c              # Dropper main source code
│   ├── dropper.h              # Dropper interface/header
│   ├── Makefile               # Build instructions for droppers
│
├── injector/                  # Injection & loader tools
│   ├── injector.c             # DLL/process injection logic
│   ├── injector.h             # Injector interface/header
│   ├── Makefile               # Build instructions for injector
│
├── payload/                   # Core payload modules
│   ├── keylogger.c            # Keylogging functionality
│   ├── keylogger.h
│   ├── exfiltration.c         # Network exfiltration (HTTP, DNS, SMTP)
│   ├── exfiltration.h
│   ├── persistence.c          # Registry, scheduled tasks persistence
│   ├── persistence.h
│   ├── evasion.c              # Sandbox detection, anti-debugging
│   ├── evasion.h
│   ├── uac_bypass.c           # UAC bypass techniques
│   ├── uac_bypass.h
│   ├── reflective_loader.c    # Reflective DLL loading logic
│   ├── reflective_loader.h
│   ├── payload_main.c         # Main orchestration of payload features
│   ├── payload_main.h
│   ├── Makefile               # Build payload DLL or shellcode
│
├── tools/                     # Build and utility scripts
│   ├── build_all.sh           # Script to build entire project
│                              # Cleanup build artifacts
│
├── Makefile                   # Root Makefile automating all builds
├── README.md                  # Project overview and usage instructions
### How I Learned
- [https://learn.microsoft.com/en-us/windows/win32/](https://learn.microsoft.com/en-us/windows/win32/)
- [learn-c.org](https://www.learn-c.org/)
- [https://learn.microsoft.com/en-us/windows/win32/apiindex](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)
- [lowlevel.academy](https://lowlevel.academy/)
- [https://learn.microsoft.com/en-us/windows/win32/inputdev/keyboard-input](https://learn.microsoft.com/en-us/windows/win32/inputdev/keyboard-input)
- [https://docs.redteamleaders.com] (https://docs.redteamleaders.com/offensive-security/privilege-escalation/windows-uac-bypass-techniques)
