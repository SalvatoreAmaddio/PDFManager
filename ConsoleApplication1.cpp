#include <iostream>
#include <Windows.h>
#include <Winspool.h>
#include<string.h>
#include <string>

DWORD CreatePort(LPWSTR portName);
DWORD DeletePort(LPWSTR portName);

int main(int argc, char** argv) {
//        LPWSTR a = const_cast<LPTSTR>(TEXT("C:\\Users\\Salvatore\\OneDrive\\Desktop\\MyFile.pdf"));
    
    std::cout << "You Have " << argc << " arguments:" << std::endl;
    int index = 1;

    for (int i = 0; i < argc;i++) {
        printf(argv[i]);
        printf("\n");
    }
    
    int number = atoi(argv[2]);

    size_t size = strlen(argv[index]) + 1;
    wchar_t* portName = new wchar_t[size];

    size_t outSize;
    mbstowcs_s(&outSize, portName, size, argv[index], size - 1);
    LPWSTR a = portName;

    printf("%d",number);

    if (number == 0) {
        printf("\nYou Add A Port\n");
        CreatePort(a);
   }
    else {
        printf("\nYou Remove A Port\n");
        DeletePort(a);
    }
      printf("Done");

#ifdef _UNICODE
       std::wostream& COUT = std::wcout;
#else
       std::ostream& COUT = std::cout;
#endif
       int x;
       std::cin >> x;
}

DWORD CreatePort(LPWSTR portName)
{
    HANDLE hPrinter;
    PRINTER_DEFAULTS PrinterDefaults;
    memset(&PrinterDefaults, 0, sizeof(PrinterDefaults));

   
    PrinterDefaults.pDatatype = NULL;
    PrinterDefaults.pDevMode = NULL;
    PrinterDefaults.DesiredAccess = SERVER_ACCESS_ADMINISTER;
   
    DWORD needed;
    DWORD result;

    LPWSTR printer = const_cast<LPTSTR>(TEXT(",XcvMonitor Local Port"));

    OpenPrinter(printer, &hPrinter, &PrinterDefaults);
         
    
    DWORD xcvresult = 0;
    XcvData(hPrinter,
        L"AddPort",
        (BYTE*)portName,
        (lstrlenW(portName) + 1) * 2,
        NULL, 0, &needed, &xcvresult);
    
    DWORD xcvresult1 = 0;
    LPDWORD needed2=0;


 
    ClosePrinter(hPrinter);

    return 0;
}

DWORD DeletePort(LPWSTR portName)
{
    HANDLE hPrinter;
    PRINTER_DEFAULTS PrinterDefaults;
    memset(&PrinterDefaults, 0, sizeof(PrinterDefaults));

    PrinterDefaults.pDatatype = NULL;
    PrinterDefaults.pDevMode = NULL;
    PrinterDefaults.DesiredAccess = SERVER_ACCESS_ADMINISTER;

    DWORD needed;
    DWORD rslt;
    //Microsoft Print to PDF
    LPWSTR printer = const_cast<LPTSTR>(TEXT(",XcvMonitor Local Port"));

    if (!OpenPrinter(printer, &hPrinter, &PrinterDefaults)) return -1;

    DWORD xcvresult = 0;
    if (!XcvData(hPrinter, L"DeletePort", (BYTE*)portName, (lstrlenW(portName) + 1) * 2, NULL, 0, &needed, &xcvresult))
        rslt = GetLastError();


    if (!ClosePrinter(hPrinter))
        rslt = GetLastError();

    return 0;
}

