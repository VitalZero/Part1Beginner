#include "wndproc.h"

const int SHAPE_COUNT = 3;
RECT shapes[SHAPE_COUNT] = 
{
  {10, 10, 200, 100},
  {50, 50, 200, 300},
  {70, 80, 400, 200}
};
static POINT ptStart;
static POINT ptCur;
bool isDrawing = false;

LRESULT CALLBACK WindowProc(
  HWND   hwnd,
  UINT   msg,
  WPARAM wparam,
  LPARAM lparam)
{
  TRACKMOUSEEVENT tme;
  RECT crc;

  switch(msg)
  {
  case WM_SIZE:
    GetClientRect(hwnd, &crc);
    return 0;

  case WM_LBUTTONDOWN:
    ptStart.x = (LONG)LOWORD(lparam);
    ptStart.y = (LONG)HIWORD(lparam);
    ptCur.x = LOWORD(lparam);
    ptCur.y = HIWORD(lparam);
    
    isDrawing = true;

    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = hwnd;
    tme.dwHoverTime = 400;
    TrackMouseEvent(&tme);
    return 0;
    break;

  case WM_KILLFOCUS:
  case WM_MOUSELEAVE: // FALL THROUGHT
  case WM_LBUTTONUP:
  if(isDrawing)
    {
      HDC hdc = GetDC(hwnd);
      SelectObject(hdc, GetStockObject(NULL_BRUSH));
      Rectangle(hdc, ptStart.x, ptStart.y, ptCur.x, ptCur.y);
      ReleaseDC(hwnd, hdc);
    }
    isDrawing = false;
    return 0;
    break;

  case WM_MOUSEMOVE:
  {
    if(wparam && MK_LBUTTON && isDrawing)  
    {
      DrawRubberBand(hwnd);
      ptCur.x = LOWORD(lparam);
      ptCur.y = HIWORD(lparam);
      DrawRubberBand(hwnd);
    }
    return 0;
  }
    break;

  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // for(int i = 0; i < SHAPE_COUNT; ++i)
    // {
    //   Rectangle(hdc, shapes[i].left, shapes[i].top,
    //     shapes[i].right, shapes[i].bottom);
    // }

    // Rectangle(hdc, 100, 100, 200, 300);
    // Ellipse(hdc, 100, 100, 200, 300);

    // wchar_t msg[] = L"Paint Beginner";
    // int len = wcsnlen(msg, MAX_PATH);
    // TextOut(hdc, 100, 25, msg, len);

    EndPaint(hwnd, &ps);
    return 0;
  }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
    break;

  default:
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }

  return 0;
}

void DrawRubberBand(HWND hwnd)
{
  HDC hdc;
  hdc = GetDC(hwnd);
  SetROP2(hdc, R2_NOTXORPEN);

  HPEN pen = CreatePen(PS_DOT, 1, RGB(0,0,0));
  HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)pen);

  SelectObject(hdc, GetStockObject(NULL_BRUSH));

  Rectangle(hdc, ptStart.x, ptStart.y, ptCur.x, ptCur.y);
  
  SelectObject(hdc, (HGDIOBJ)oldPen);
  DeleteObject((HGDIOBJ)pen);
  ReleaseDC(hwnd, hdc);
}