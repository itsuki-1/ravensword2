#pragma once

#include <iostream>
#include <windows.h>

int readMemory(HANDLE processHandle, LPCVOID address)
{
    int value{};
    SIZE_T bytesRead;
    ReadProcessMemory(processHandle, address, &value, sizeof(value), &bytesRead);
    return value;
}

void writeMemory(HANDLE processHandle, LPVOID address, int value)
{
    SIZE_T bytesWritten;
    WriteProcessMemory(processHandle, address, &value, sizeof(value), &bytesWritten);
}