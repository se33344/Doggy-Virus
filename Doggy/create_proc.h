#include <windows.h>

void createprocs() {
    system("echo Your PC has been dumped :D >> README.txt");
    system("echo                   =Doggy Virus= >> README.txt");
    system("echo. >> README.txt");
    system("echo Use your PC while the virus destroys your PC >> README.txt");
    system("start README.txt");
    system("timeout 5 > nul");
    system("del README.txt");
}