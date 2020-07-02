#pragma once
#include "includes.h"

LRESULT CALLBACK WindowProc(HWND   hwnd, UINT   msg,
                            WPARAM wparam, LPARAM lparam);
void DrawRubberBand(HWND hwnd);