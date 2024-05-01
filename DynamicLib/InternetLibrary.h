#pragma once

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Функция для проверки сетевого подключения и передачи результата
	__declspec(dllexport) void CheckConnection(HWND hwnd);

#ifdef __cplusplus
}
#endif
