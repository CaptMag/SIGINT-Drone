# SIGINT-Drone
## Creation of a homemade Signals Intelligence (SIGINT) Drone designed to capture unencrypted data

This will be a Glider styled drone which will carry a Raspberry Pi 4 alongside a HackRF to capture unencrypted data in the air.  
The glider will be built using OpenVSP alongside XFOIL and use a symmetrical airfoil, specifically the MH60-il.  

## Dependencies

Must have [SoapySDR Installed](https://github.com/pothosware/SoapySDR) either through CMake or directly downloading it [here](https://downloads.myriadrf.org/builds/PothosSDR/)  
When compiling in Visual Studio, it must be ran on a x64 architechture on release mode, debugging mode will not work.  
Must have needed DLLs installed including HackRF.dll and SoapySDR.dll.

Include Directories: C:\Program Files\PothosSDR\include to C/C++ Additional Include Directories  
Library Directories: C:\Program Files\PothosSDR\lib to Linker Additional Library Directories  
Additional Dependecies: SoapySDR.lib to Linker Additional Dependencies

## Planning

Ongoing documentation is currently being created to explain the workings of this project.  
There will be multiple programs designed to capture signals, 802.11 frames and more features such as bluetooth monotoring, Encryption Protcol Detection, etc.

## Ongoing Work

As of right now, the 802.11 packet sniffer has been completed, alongside the intial SDR creation.  
The packet sniffer will print all available networks alongside their BSSID, MAC address and beacon, probe response and request packets.  
The SDR creation is designed to print all available devices, and create a fully formatted SDR that is ready for data capturing.

Currently the project is working towards setting up the proper frequency rates, signal strength and directions.  
More functions will be implemented to allow the user to customize their SDR preferences, before ensuring the SDR is ready for capturing.  
This will be the last step for enumeration, and after will allow for the ability to capture and parse data.  
Pothosware SDR GUI tools will be used for proper data capturing.  
