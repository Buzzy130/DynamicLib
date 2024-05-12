#include <windows.h>

// �������� ������� ��� �������� �������� �����������
typedef void (*CheckConnectionFunc)(HWND);

// �������� ������� ��� ����������� ������ �� ����
void DrawTextOnWindow(HWND hwnd, const wchar_t* text, const wchar_t* status);

// ������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
        // ��� ������ ����������� ����, �������� ������� �������� ����������� � ���������� ������
        DrawTextOnWindow(hwnd, TEXT("�������� �������� �����������"), TEXT("������: �������� ����������� � �������� ����"));
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ����������� ������ ����
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("MyWindowClass");

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("�� ������� ���������������� ����� ����"), TEXT("������"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // �������� ����
    HWND hwnd = CreateWindowEx(0, TEXT("MyWindowClass"), TEXT("�������� �������� �����������"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("�� ������� ������� ����"), TEXT("������"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // �������� ������������ ����������
    HINSTANCE hLib = LoadLibrary(TEXT("DynamicLib.dll"));
    if (hLib == NULL) {
        MessageBox(NULL, TEXT("�� ������� ��������� ����������"), TEXT("������"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // ��������� ��������� �� ������� �� ����������
    CheckConnectionFunc checkConnection = (CheckConnectionFunc)GetProcAddress(hLib, "CheckConnection");
    if (checkConnection == NULL) {
        MessageBox(NULL, TEXT("�� ������� �������� ����� �������"), TEXT("������"), MB_OK | MB_ICONERROR);
        FreeLibrary(hLib);
        return 0;
    }

    // ����������� ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ����� ������� ��� �������� �����������
    checkConnection(hwnd);

    // ���� ��������� ���������
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ������������ ���������� ����� �������������
    FreeLibrary(hLib);

    return msg.wParam;
}

// ������� ��� ����������� ������ �� ����
void DrawTextOnWindow(HWND hwnd, const wchar_t* text, const wchar_t* status) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);

    // ����������� ������ � ������ ����
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // ����������� ������� �������� ����������� ��� �������
    rect.top += 50;
    DrawText(hdc, status, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    EndPaint(hwnd, &ps);
}