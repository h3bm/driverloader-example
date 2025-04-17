/**********************************************************
*  Educational Use Only | https://github.com/h3bm*
**********************************************************/

#include <Windows.h>
#include <iostream>
#include <winternl.h>
#include <string>
#include "Helper.h"

#define DRIVER_PATH L"C:\\Drivers\\YourDriver.sys" // Directory of your Driver goes here

typedef NTSTATUS(WINAPI* NtLoadDriver)(PUNICODE_STRING DriverServiceName);
typedef NTSTATUS(WINAPI* NtUnloadDriver)(PUNICODE_STRING DriverServiceName);

// Define a function to load the driver
bool LoadDriver(const std::wstring& driverPath) {
    HMODULE ntdll = GetModuleHandle(L"ntdll.dll");

    if (ntdll == NULL) {
        std::cerr << "Failed to load ntdll.dll\n";
        return false;
    }

    NtLoadDriver loadDriver = (NtLoadDriver)GetProcAddress(ntdll, "NtLoadDriver");
    if (loadDriver == NULL) {
        std::cerr << "Failed to find NtLoadDriver function\n";
        return false;
    }

    // Initialize a UNICODE_STRING structure
    UNICODE_STRING driverPathStr;
    RtlInitUnicodeString(&driverPathStr, driverPath.c_str());

    // Attempt to load the driver
    NTSTATUS status = loadDriver(&driverPathStr);
    if (status != 0) {
        std::cerr << "Failed to load driver, NTSTATUS: " << status << "\n";
        return false;
    }

    std::cout << "Driver loaded successfully!\n";
    return true;
}

// Name of the Bool says it all *-*
bool UnloadDriver(const std::wstring& driverPath) {
    HMODULE ntdll = GetModuleHandle(L"ntdll.dll");

    if (ntdll == NULL) {
        std::cerr << "Failed to load ntdll.dll\n";
        return false;
    }

    NtUnloadDriver unloadDriver = (NtUnloadDriver)GetProcAddress(ntdll, "NtUnloadDriver");
    if (unloadDriver == NULL) {
        std::cerr << "Failed to find NtUnloadDriver function\n";
        return false;
    }

    UNICODE_STRING driverPathStr;
    RtlInitUnicodeString(&driverPathStr, driverPath.c_str());

    NTSTATUS status = unloadDriver(&driverPathStr);
    if (status != 0) {
        std::cerr << "Failed to unload driver, NTSTATUS: " << status << "\n";
        return false;
    }

    std::cout << "Driver unloaded successfully!\n";
    return true;
}

int main() {
    std::wstring driverPath = DRIVER_PATH;

    // Setup the registry (if needed)
    if (!SetupDriverRegistry(driverPath)) {
        std::cerr << "Failed to set up driver registry\n";
        return -1;
    }

    // Loads the driver
    if (!LoadDriver(driverPath)) {
        return -1;
    }

    std::cout << "Press any key to unload the driver...\n";
    std::cin.get();

    // Unloads the driver
    if (!UnloadDriver(driverPath)) {
        return -1;
    }

    // Cleans up the registry
    CleanupDriverRegistry();
    return 0;
}
