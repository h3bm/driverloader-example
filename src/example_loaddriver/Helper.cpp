/**********************************************************
*  Educational Use Only | https://github.com/triggerbotten*
**********************************************************/

#include <Windows.h>
#include <string>
#include <iostream>

// (IF NEEDED) Sets up a Reg for your Driver
bool SetupDriverRegistry(const std::wstring& driverPath) {
    HKEY hKey;
    LONG res = RegCreateKeyEx(
        HKEY_LOCAL_MACHINE,
        L"System\\CurrentControlSet\\Services\\YourDriver",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hKey,
        NULL
    );

    if (res != ERROR_SUCCESS) {
        std::cerr << "Failed to create registry key for the driver\n";
        return false;
    }


    res = RegSetValueEx(hKey, L"ImagePath", 0, REG_SZ, (const BYTE*)driverPath.c_str(), (DWORD)(driverPath.length() * sizeof(wchar_t)));
    RegCloseKey(hKey);

    if (res != ERROR_SUCCESS) {
        std::cerr << "Failed to set driver path in the registry\n";
        return false;
    }

    return true;
}

// Cleans up any traces of the Driver in Registry
void CleanupDriverRegistry() {
    LONG res = RegDeleteTree(HKEY_LOCAL_MACHINE, L"System\\CurrentControlSet\\Services\\YourDriver");

    if (res == ERROR_SUCCESS) {
        std::cout << "Registry cleaned up successfully!\n";
    }
    else {
        std::cerr << "Failed to clean up registry\n";
    }
}