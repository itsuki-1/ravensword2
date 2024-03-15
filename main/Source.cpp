#include <iostream>
#include <chrono>
#include <windows.h>
#include <string>
#include "getProcess.h"
#include "changeMemory.h"
#define DEBUG_ENABLED

char mainMenu()
{
    std::cout << "==========Ravensword Shadowland Trainer v1 by 1tsuki==========" << '\n';
    std::cout << "[1]: Health Modify" << '\n';
    std::cout << "[2] Mana Modify" << '\n';
    std::cout << "[3] Attribute Point Modify" << '\n';
    std::cout << "[4] Talent Point Modify" << '\n';
    std::cout << "[5] Weight Modify" << '\n';
    std::cout << "[6] Armor Modify" << '\n';
    std::cout << "[q] Quit" << '\n';
    std::cout << "Please Enter Your Choice: ";
    char menuSelection{ 0 };
    std::cin >> menuSelection;
    return menuSelection;
}

void processStats()
{
    bool wasRunning{ false };
    std::cout << "Please Open The Game" << '\n';

    while (true)
    {
        bool isRunning{ isProcessRunning(L"Ravensword2.exe") };

        if (isRunning && !wasRunning)
        {
            system("cls");
            std::wcout << L"Ravensword2.exe is now running." << '\n';
            wasRunning = true;
            return;
        }
        else if (!isRunning && wasRunning)
        {
            system("cls");
            std::wcout << L"Ravensword2.exe is not running. Please open the game!" << '\n';
            wasRunning = false;
        }

        Sleep(1000);
    }
}

void changeAttributePoint(int value)
{
    LPCVOID address = (LPCVOID)0x160E347C;
    if (isProcessRunning(L"Ravensword2.exe"))
    {
        DWORD processID = getProcessID(L"Ravensword2.exe");
        HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        if (processHandle != NULL)
        {
            writeMemory(processHandle, (LPVOID)address, value);
            #ifdef DEBUG_ENABLED
            std::cout << "Updated value is " << readMemory(processHandle, address) << std::endl;
            #endif
            CloseHandle(processHandle);
        }
        else
        {
            std::cout << "Failed to open process!" << '\n';
        }
        Sleep(5000);
        system("cls");
    }
    else
    {
        std::cout << "Error Occurred!" << '\n';
        Sleep(5000);
        system("cls");
    }
}

int main()
{
    bool gameRunning = false;
    while (!gameRunning)
    {
        processStats();
        gameRunning = isProcessRunning(L"Ravensword2.exe");
    }

    while (gameRunning)
    {
        char userChoice{ mainMenu() };
        #ifdef DEBUG_ENABLED
        std::cout << "User Choice is: " << userChoice << '\n';
        #endif
        if (userChoice == '3')
        {
            #ifdef DEBUG_ENABLED
            std::cout << "Function is called" << '\n';
            #endif
            LPCVOID address = (LPCVOID)0x160E347C; // Note that if the address changed then this would never work
            DWORD processID = getProcessID(L"Ravensword2.exe");
            HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
            if (processHandle != NULL)
            {
                int32_t currentValue{ readMemory(processHandle, address) };
                std::cout << "Current Value is: " << currentValue << std::endl;
                std::cout << "Enter a new value: ";
                int newValue{ 0 };
                std::cin >> newValue;
                changeAttributePoint(newValue);
                CloseHandle(processHandle);
            }
            else
            {
                std::cout << "Failed to open process!" << '\n';
            }
        }
        else if (userChoice == 'q')
        {
            break;
        }
        gameRunning = isProcessRunning(L"Ravensword2.exe");
    }

    std::cout << "Application Closed, Program Terminated!";
    Sleep(5000);
    return 0;
}

