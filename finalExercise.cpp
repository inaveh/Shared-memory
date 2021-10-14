#include <iostream>
#include <Windows.h>

#define FILE_NAME "D:\\cyber\\bootcamp\\os\\sharedMemory\\finalExercise\\gibrish.bin"

using namespace std;

int main()
{
    LPSTR pBuf;
    LPCSTR file_name = FILE_NAME;
    HANDLE hFile;
    HANDLE hMapFile;
    DWORD error = NULL;

    hMapFile = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE, 
        "myFile");

    // check if has handle to file is exist (this file already mapped)
    if (hMapFile == NULL)
    {
       hFile = CreateFileA(
            file_name,			   // name of the read
            GENERIC_READ | GENERIC_WRITE,// open for all
            0,				       // share for reading
            NULL,                   // default security
            OPEN_EXISTING,          // create new file only
            FILE_ATTRIBUTE_NORMAL,  // normal file
            NULL
        );
        
       // file mapping
        hMapFile = CreateFileMappingA(
           hFile,				     // use paging file
           NULL,                    // default security
           PAGE_READWRITE,           // read/write access
           0,                       // maximum object size (high-order DWORD)
           0,						 // maximum object size (low-order DWORD)
           "myFile");               // name of mapping object

		pBuf = (LPSTR)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 1);
        
        while (true)
        {
            if (pBuf[0] == '*') {
                CloseHandle(hMapFile);
                CloseHandle(hFile);
				UnmapViewOfFile(pBuf);
                break;
            }
        }
        cout << pBuf[0] << "\n process 1 finish";

    }
    else
    {
        pBuf = (LPSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 1);        
        pBuf[0] = '*';
        cout << pBuf[0] << "\n process 2 finish";
    }
 
    //Sleep(2000);
    //CloseHandle(hFile);
    return 0;
}
