#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_BTN_ADD 201
#define ID_BTN_SUB 202
#define ID_BTN_MUL 203
#define ID_BTN_DIV 204

HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 195, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 55, 195, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 20, 95, 45, 45, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 70, 95, 45, 45, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 120, 95, 45, 45, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 170, 95, 45, 45, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) >= ID_BTN_ADD && LOWORD(wParam) <= ID_BTN_DIV) {
                char buf1[100], buf2[100];
                
                GetWindowText(hEdit1, buf1, 100);
                GetWindowText(hEdit2, buf2, 100);

                double num1 = atof(buf1);
                double num2 = atof(buf2);
                double result = 0.0;
                char resultStr[100];

                switch(LOWORD(wParam)) {
                    case ID_BTN_ADD: result = num1 + num2; break;
                    case ID_BTN_SUB: result = num1 - num2; break;
                    case ID_BTN_MUL: result = num1 * num2; break;
                    case ID_BTN_DIV: 
                        if (num2 == 0) {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2; 
                        break;
                }

                sprintf(resultStr, "%f", result);
                
                MessageBox(hwnd, resultStr, "Result", MB_OK);
            }
            break;
        }
        
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));
    wc.lpszClassName = "WindowClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}