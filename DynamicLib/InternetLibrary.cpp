#include "InternetLibrary.h"
#include <wininet.h>

void CheckConnection(HWND hwnd) {
    if (InternetCheckConnection(TEXT("http://www.example.com"), FLAG_ICC_FORCE_CONNECTION, 0)) {
        MessageBox(hwnd, TEXT("Интернет-подключение доступно"), TEXT("Результат"), MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(hwnd, TEXT("Интернет-подключение недоступно"), TEXT("Результат"), MB_OK | MB_ICONERROR);
    }
}
