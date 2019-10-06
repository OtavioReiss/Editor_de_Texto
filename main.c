/*
LEMBRETE, PARA COMPILAR O PROGRAMA, DEVE-SE LINKAR O ARQUIVO 
 "libcomdlg32.a"  COM O COMPILADOR, 
 SE NÃO IRA OCORRER UM ERRO NA COMPILAÇÃO

   - "gcc -o main .\main.c  .\libcomdlg32.a"
*/

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ARQ_MENU_SALV 2
#define ARQ_MENU_CARR 3
#define ARQ_MENU_SAIR 4

/* DECLARAÇÃO DAS FUNÇÕES */
LRESULT CALLBACK WProcedure(HWND, UINT, WPARAM, LPARAM);
void addMenus(HWND);
HMENU hMenu;//();
void AddControls(HWND);
HWND TextRecive;
void open_file(HWND hWnd);
void display_file(char* path);
void save_file(HWND hWnd);
/* Função pricipal da Biblioteca Windows.h, Equivalente a função Main() */
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

void display_file(char* path)
{
    FILE *arq;
    arq = fopen(path, "rb");
    fseek(arq, 0, SEEK_END);
    int _size = ftell(arq);
    rewind(arq);
    char *data = (char *)malloc(_size+1);
    fread(data, _size, 1, arq);
    data[_size] = '\0';

    SetWindowText(TextRecive, data);

    fclose(arq);
}

/*FUNÇÃO QUE ABRE UM NOVO ARQUIVO*/
void open_file(HWND hWnd)
{
    OPENFILENAME ofn;
    char file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    /* CRIA A JANELA QUE PROCURA ARQUIVOS */
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Arquivos de Texto\0*.TXT\0";
    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    /* CARREGA O ARQUIVO SELECIONADO */
    display_file(ofn.lpstrFile);

}


/*ESCREVE O ARQUIVO EM UM .TXT*/

void write_file(char* path)
{
    FILE *arq;
    arq = fopen(path, "w");

    int _size = GetWindowTextLength(TextRecive);
    char *data = (char *)malloc(_size+1);
    GetWindowText(TextRecive, data, _size+1);

    fwrite(data, _size+1, 1, arq);

    fclose(arq);
}

/* FUNÇÃO QUE SALVA O ARQUIVE */
void save_file(HWND hWnd)
{
    OPENFILENAME ofn;
    char file_name[100];
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    /* CRIA A JANELA QUE PROCURA ARQUIVOS */
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = file_name;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 100;
    ofn.lpstrFilter = "All files\0*.*\0Arquivos de Texto\0*.TXT\0";
    ofn.nFilterIndex = 1;

    GetSaveFileName(&ofn);

    /* CARREGA O ARQUIVO SELECIONADO */
    write_file(ofn.lpstrFile);

}

/* FUNÇÃO DE CALLBACK PARA CONTROLE DA JANELA*/

LRESULT CALLBACK WProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_COMMAND: // CASO QUE CONTROLAR AS AÇÕES DO MENU
            switch (wp)
            {
                case ARQ_MENU_SAIR:
                    DestroyWindow(hWnd);
                    break;
                case ARQ_MENU_CARR:
                    open_file(hWnd);
                    break;
                case ARQ_MENU_SALV:
                    save_file(hWnd);
                    break;
            }
            break;

        case WM_CREATE://QUANDO A JANELA É CRIADA AS FUNÇÕES ABAIXOS SÃO CHAMADAS PELA PRIMEIRA VEZ
            addMenus(hWnd);
            AddControls(hWnd);
            break;

         case WM_DESTROY: //QUANDO A JANELA É FINALIZADA AS FUNÇÕES ABAIXOS SÃO CHAMADAS
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
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    /* SUB MENU --ARQUIVO-- */
    AppendMenu(hFileMenu, MF_STRING, ARQ_MENU_SALV, "Salvar");
    AppendMenu(hFileMenu, MF_STRING, ARQ_MENU_CARR, "Carregar");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, ARQ_MENU_SAIR, "Sair");

    /* BARRA PRINCIPAL */
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu,"Arquivo");
    AppendMenu(hMenu, MF_STRING, 2,"Sobre");

    SetMenu(hWnd, hMenu);
}

//FUNÇÃO QUE CONTROLA AS APLICAÇÕES
void AddControls(HWND hWnd)
{
    //CreateWindowW(L"static", L"Enter the text here: ", WS_VISIBLE | WS_CHILD , 0, 0, 1920, 1080, hWnd, NULL, NULL, NULL);
    /*CRIA O CAMPO DE ESCRITA*/
    TextRecive = CreateWindowW(L"edit", L"",  WS_VISIBLE | WS_CHILD  | ES_MULTILINE | ES_LEFT 
                | EM_GETSEL  | ES_AUTOHSCROLL | ES_AUTOVSCROLL | EM_UNDO | EM_SCROLL | WS_VSCROLL | WS_HSCROLL , 0, 0, 480, 440, hWnd, NULL, NULL, NULL);
}