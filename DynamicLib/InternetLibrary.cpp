#include "InternetLibrary.h"
#include <wininet.h>

void CheckConnection(HWND hwnd) {
    if (InternetCheckConnection(TEXT("http://www.example.com"), FLAG_ICC_FORCE_CONNECTION, 0)) {
        MessageBox(hwnd, TEXT("��������-����������� ��������"), TEXT("���������"), MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(hwnd, TEXT("��������-����������� ����������"), TEXT("���������"), MB_OK | MB_ICONERROR);
    }
}
