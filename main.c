#include <Windows.h>
#include <stdio.h>

/* DECLARAÇÃO DAS FUNÇÕES */
LRESULT CALLBACK WProcedure(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
HMENU hMenu;

/* Função pricipal da Biblioteca Windows.h */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    
    WNDCLASSW wc = {0};

    /*INICIALIZA ESTRUTURAS BASICAS*/
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WProcedure;
    
    if(!RegisterClassW(&wc))
        return -1;
    CreateWindowW(L"myWindowClass", L"Editor de Texto", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL );

    MSG msg = {0};

    /* LOOP PRINCIPAL*/
    while( GetMessage(&msg, NULL, NULL, NULL ))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return 0;
}


/* FUNÇÃO DE CALLBACK PARA CONTROLE DA JANELA*/

LRESULT CALLBACK WProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_COMMAND: // CASO QUE CONTROLAR AS AÇÕES DO MENU
            switch (wp)
            {
                case 1:
                    MessageBeep(MB_OK);
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            break;
        case WM_CREATE:
            addMenus(hWnd);
            break;
         case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp ,lp);
    }

}
/* BARRA DE MENU DO PROGRAMA */
void addMenus(HWND hWnd)
{
    hMenu = CreateMenu();

    AppendMenu(hMenu, MF_STRING, 1,"Salvar");
    AppendMenu(hMenu, MF_STRING, 2,"Carregar");
    AppendMenu(hMenu, MF_STRING, 3,"Sobre");

    SetMenu(hWnd, hMenu);

}