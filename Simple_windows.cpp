#include <windows.h>
#include <stdio.h>
#include <conio.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Janela";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, L"Erro ao registrar janela", L"Erro", MB_OK);
        return -1;
    }

    hWnd = CreateWindowW(L"Janela", L"Janela", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL)
    {
        MessageBox(NULL, L"Erro ao criar janela", L"Erro", MB_OK);
        return -1;
    }

    // Criação das caixas de texto para usuário e senha
    HWND hUserEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 20, 50, 200, 25, hWnd, NULL, hInstance, NULL);
    HWND hPassEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD, 20, 100, 200, 25, hWnd, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg){
        case WM_CREATE:
            // Configura o foco inicial para a caixa de texto do usuário
            SetFocus(GetDlgItem(hWnd, 1));
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1 && HIWORD(wParam) == EN_CHANGE){
            // Evento de alteração na caixa de texto do usuário
            wchar_t buffer[256];
            GetDlgItemText(hWnd, 1, buffer, 256);
            wprintf(L"Usuário: %s\n", buffer);
        }
        else if (LOWORD(wParam) == 2 && HIWORD(wParam) == EN_CHANGE){
            // Evento de alteração na caixa de texto da senha
            wchar_t buffer[256];
            GetDlgItemText(hWnd, 2, buffer, 256);
            wprintf(L"Senha: %s\n", buffer);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
               
