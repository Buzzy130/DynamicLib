#pragma once

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

	// ������� ��� �������� �������� ����������� � �������� ����������
	__declspec(dllexport) void CheckConnection(HWND hwnd);

#ifdef __cplusplus
}
#endif
