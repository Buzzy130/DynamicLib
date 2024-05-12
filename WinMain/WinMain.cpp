#include <windows.h>

// Прототип функции для проверки сетевого подключения
typedef void (*CheckConnectionFunc)(HWND);

// Прототип функции для отображения текста на окне
void DrawTextOnWindow(HWND hwnd, const wchar_t* text, const wchar_t* status);

// Оконная процедура
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
        // При каждой перерисовке окна, вызываем функцию проверки подключения и обновления текста
        DrawTextOnWindow(hwnd, TEXT("Проверка сетевого подключения"), TEXT("Статус: Проверка отобразится в отдельно окне"));
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
    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("MyWindowClass");

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("Не удалось зарегистрировать класс окна"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // Создание окна
    HWND hwnd = CreateWindowEx(0, TEXT("MyWindowClass"), TEXT("Проверка сетевого подключения"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("Не удалось создать окно"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // Загрузка динамической библиотеки
    HINSTANCE hLib = LoadLibrary(TEXT("DynamicLib.dll"));
    if (hLib == NULL) {
        MessageBox(NULL, TEXT("Не удалось загрузить библиотеку"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // Получение указателя на функцию из библиотеки
    CheckConnectionFunc checkConnection = (CheckConnectionFunc)GetProcAddress(hLib, "CheckConnection");
    if (checkConnection == NULL) {
        MessageBox(NULL, TEXT("Не удалось получить адрес функции"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        FreeLibrary(hLib);
        return 0;
    }

    // Отображение окна
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Вызов функции для проверки подключения
    checkConnection(hwnd);

    // Цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Освобождение библиотеки после использования
    FreeLibrary(hLib);

    return msg.wParam;
}

// Функция для отображения текста на окне
void DrawTextOnWindow(HWND hwnd, const wchar_t* text, const wchar_t* status) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);

    // Отображение текста в центре окна
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // Отображение статуса сетевого подключения под текстом
    rect.top += 50;
    DrawText(hdc, status, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    EndPaint(hwnd, &ps);
}