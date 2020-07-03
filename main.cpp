// ===========================================================
// File: main.cpp
// Date: 01/July/2020
// Description: Part 1 paint guide, win32 code project
//  as in https://www.codeproject.com/Articles/1988/Guide-to-WIN32-Paint-for-Beginners
// Copyright: VZ
// ===========================================================
#include "includes.h"

ATOM RegisterWC(const wchar_t* className);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


int WINAPI WinMain(
  HINSTANCE instance,
  HINSTANCE,
  LPSTR cmd,
  int show)
{
  const wchar_t* CLASS_NAME = L"VZ Window";
  const wchar_t* WINDOW_NAME = L"Gdi32 beginner";

  if(!RegisterWC(CLASS_NAME))
  {
    MessageBox(nullptr, L"Error", L"No se pudo registrar la ventana",
	       MB_ICONINFORMATION);
    return FALSE;
  }
  
  HWND mainWindow = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    CLASS_NAME,
    WINDOW_NAME,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    nullptr,
    nullptr,
    instance,
    nullptr);

  if(!mainWindow)
  {
    MessageBox(0, L"Error", L"No se pudo crear la ventana principal",
	       MB_ICONINFORMATION);
    return FALSE;
  }

  ShowWindow(mainWindow, show);
  UpdateWindow(mainWindow);

  MSG msg = {0};
  BOOL retMsg;
  while((retMsg = GetMessage(&msg, 0, 0, 0)) != 0)
  {
    if(retMsg == -1)
    {
    }
    else
    {
      if(!IsDialogMessage(mainWindow, &msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }
  
  return msg.wParam;
}


ATOM RegisterWC(const wchar_t* className)
{
  WNDCLASS wc = {0};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.hIcon = LoadIcon(GetModuleHandle(nullptr), IDI_APPLICATION);
  wc.hCursor = LoadCursor(GetModuleHandle(nullptr), IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszClassName = className;

  return RegisterClass(&wc);
}