# Driverloader Example

**Driverloader Example** is a usermode tool for loading and unloading unsigned Windows drivers.  
This project is intended **strictly for educational purposes only**. It demonstrates how to interact with Windows low-level APIs to load and unload drivers programmatically.

## Features

- Loads `.sys` drivers using the `NtLoadDriver` function.
- Unloads drivers via the `NtUnloadDriver` function.
- Initializes and handles driver paths using `RtlInitUnicodeString`.
- Works only with **test-signed drivers** (requires **test-signing mode** enabled).
- Provides basic logging to the console to inform you about the driver loading and unloading status.

## Requirements

Before building and using this tool, make sure you have the following:

- **Windows (64-bit recommended)**.
- **Administrator privileges** are required to load and unload drivers.
- **Test-signing mode enabled** on your system (required for loading unsigned drivers)
- Run the Bat i provided to enable it or just c&p the commands into your cmd

## Setup and Building the Project
Step 1: `Clone the Repository`

Step 2: `Open the Project in Visual Studio`

- Open Visual Studio (or your preferred C++ IDE).
- Create a new C++ project or open the DriverLoader.cpp file.
- Ensure you are building the project as a 64-bit application (x64).

Step 3: `Link Necessary Libraries`
To work with the low-level Windows functions, you'll need to link to ntdll.lib:

- Right-click on your project in Solution Explorer and choose Properties.
- In the Properties window, go to Configuration Properties > Linker > Input.
- Under Additional Dependencies, add ntdll.lib.
- Ensure ntdll.lib is available in your Library Directories:
- Typically located in `C:\Program Files (x86)\Windows Kits\10\Lib\<version>\um\x64\ntdll.lib`

Step 4: `Build the Project`
Once everything is set up:
- Click Build > Build Solution in Visual Studio.
- Once built, you should have a .exe file in the Debug or Release folder, depending on your configuration.

Step 5: `Running the Tool`
Enabling Test-Signing Mode
- Restart your system to apply the changes.
- Running the Driver Loader

- Place the driver file (YourDriver.sys) in a directory, such as C:\Drivers\YourDriver.sys.
- Run the tool with administrator privileges:
- Right-click on the compiled .exe and select Run as Administrator.
- The tool will attempt to load the driver from the specified path.

## Unloading the Driver
- To unload the driver, press any key when prompted. The tool will clean up and remove the driver from memory.
  
## Disclaimer
This project is for educational purposes and should not be used in production environments.
The driver must be test-signed. This tool will not work on drivers that are not signed and will not bypass Windows' kernel security features.
This tool does not bypass Windows security features such as Windows Defender or integrity checks.
