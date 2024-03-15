#pragma once

#include <string>
#include <windows.h>
#include <tlhelp32.h>

bool isProcessRunning(const std::wstring& processName) {
    bool exists = false;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32FirstW(snapshot, &entry)) {
        while (Process32NextW(snapshot, &entry)) {
            if (wcscmp(entry.szExeFile, processName.c_str()) == 0) {
                exists = true;
                break;
            }
        }
    }

    CloseHandle(snapshot);
    return exists;
}

DWORD getProcessID(const std::wstring& processName) {
    DWORD processID = 0;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32FirstW(snapshot, &entry)) {
        while (Process32NextW(snapshot, &entry)) {
            if (wcscmp(entry.szExeFile, processName.c_str()) == 0) {
                processID = entry.th32ProcessID;
                break;
            }
        }
    }

    CloseHandle(snapshot);
    return processID;
}