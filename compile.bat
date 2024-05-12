@echo off
if exist *.exe del *.exe
if exist *.dll del *.dll

rem Полный путь к компилятору Visual C++
set "VC_COMPILER=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.37.32822\bin\Hostx64\x64\cl.exe"

rem Путь к каталогу включаемых файлов Windows SDK
set "SDK_INCLUDE=C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt"

rem Компиляция основного приложения
"%VC_COMPILER%" /I"%SDK_INCLUDE%" WinMain/WinMain.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib

rem Компиляция динамической библиотеки
"%VC_COMPILER%" /I"%SDK_INCLUDE%" /LD DynamicLib/InternetLibrary.cpp kernel32.lib user32.lib gdi32.lib advapi32.lib

rem Удаление временных файлов
del *.obj *.lib *.exp
