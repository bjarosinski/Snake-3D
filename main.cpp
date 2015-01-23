#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "fileio.h"
//#include "data.h"
#include <string>
#include"openGl.h"
#include<ShellAPI.h>

#define button1 501
#define button2 502
#define button3 503
#define button4 504
#define button5 505
#define button6 506

LPSTR NazwaKlasy = "Klasa Okienka"; //nazwa klasy okna 1
LPSTR NazwaKlasy2 = "Klasa Okienka 2"; // nazwa klasy okna 2

WNDCLASSEX wc,wc2; //klasy okien (wc-okno g³ówne, wc2-okno 2)
MSG Komunikat;	//komunikat zwracany przez system (zdarzenie na oknie)
BITMAP bmInfo,bmInfo2, bmInfo3, bmInfo4, bmInfo5; //bitmapy wyœwietlane w oknach(informacje) 
HBITMAP hbmObraz,hbmObraz2, hbmObraz3, hbmObraz4, hbmObraz5; //bitmapy wyœwietlane w oknach
int which_option; //wybrana opcja
options sett;
player best_scorers[20];

int windowWidth=900;
int windowHeight=600;
float cameraAngle=45.0f;
int argcc;
LPWSTR *szArgList;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK WndProc2( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
//**************************************************************
//						FUNKCJA MAIN
//						  program
//**************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    //MessageBox(NULL, "Goodbye, cruel world!", "Note", MB_OK);
    //szArgList = CommandLineToArgvW(GetCommandLine(), &argcc);

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
	
	if( !RegisterClassEx( & wc ) )
	{
		MessageBox( NULL, "Okna nie uda³o siê zarejestrowaæ", "Dalej",
		MB_ICONEXCLAMATION | MB_OK );
		return 1;
	}

	wc2.cbSize = sizeof( WNDCLASSEX );
	wc2.style = 0;
	wc2.lpfnWndProc = WndProc2;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = hInstance;
	wc2.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc2.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc2.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = NazwaKlasy2;
	wc2.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
	
	if( !RegisterClassEx( & wc2 ) )
	{
		MessageBox( NULL, "Okna nie uda³o siê zarejestrowaæ", "Dalej",
		MB_ICONEXCLAMATION | MB_OK );
		return 1;
	}

	HWND hwnd,button_play,button_settings,button_authors,button_help,button_exit,button_bestscores;

	hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Snake 3D beta", WS_OVERLAPPEDWINDOW,
	100, 100, 900, 600, NULL, NULL, hInstance, NULL );

	if( hwnd == NULL )
	{
		MessageBox( NULL, "B³¹d w czasie tworzenia okna", "Dalej", MB_ICONEXCLAMATION );
		return 1;
	}	

	button_play=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Graj w Snake'a",WS_CHILD | WS_VISIBLE,375,300,150,30,hwnd,(HMENU) button1,hInstance,NULL);
	button_settings=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Opcje",WS_CHILD | WS_VISIBLE,375,340,150,30,hwnd,(HMENU) button2,hInstance,NULL);
	button_authors=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","O autorach",WS_CHILD | WS_VISIBLE,375,380,150,30,hwnd,(HMENU) button3,hInstance,NULL);
	button_help=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Pomoc",WS_CHILD | WS_VISIBLE,375,420,150,30,hwnd,(HMENU) button4,hInstance,NULL);
	button_bestscores=CreateWindowEx(WS_EX_CLIENTEDGE,"BUTTON","Najlepsze wyniki",WS_CHILD | WS_VISIBLE,375,460,150,30,hwnd,(HMENU) button5,hInstance,NULL);
	button_exit=CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Wyjœcie", WS_CHILD | WS_VISIBLE,375,500,150,30,hwnd,(HMENU) button6,hInstance,NULL);

	HFONT hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
	SendMessage( button_play, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	SendMessage( button_settings, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	SendMessage( button_exit, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	SendMessage( button_authors, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	SendMessage( button_help, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	SendMessage( button_bestscores, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
	
	hbmObraz =( HBITMAP ) LoadImage( NULL, "BMAP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	if(hbmObraz==0)
	{
		MessageBox(0,"Nie mo¿na otworzyæ pliku bitmap.bmp z folderu z aplikacj¹","Brak pliku",MB_ICONERROR);
		return 0; //zamkniecie programu w razie braku pliku bitmapy
	}

	hbmObraz2 = ( HBITMAP) LoadImage( NULL, "BMAP2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	if( hbmObraz2==0 )
	{
		MessageBox( 0, "Nie mo¿na utworzyæ pliku bitmap.bmp z folderu z aplikacj¹", "Brak pliku", MB_ICONERROR);
		return 0;
	}
	
	hbmObraz3 = ( HBITMAP) LoadImage( NULL, "authors.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	if( hbmObraz3==0 )
	{
		MessageBox( 0, "Nie mo¿na utworzyæ pliku bitmap.bmp z folderu z aplikacj¹", "Brak pliku", MB_ICONERROR);
		return 0;
	}

	hbmObraz4 = ( HBITMAP) LoadImage( NULL, "help.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	if( hbmObraz4==0 )
	{
		MessageBox( 0, "Nie mo¿na utworzyæ pliku bitmap.bmp z folderu z aplikacj¹", "Brak pliku", MB_ICONERROR);
		return 0;
	}
	
	hbmObraz5 = ( HBITMAP) LoadImage( NULL, "best.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	
	if( hbmObraz5==0 )
	{
		MessageBox( 0, "Nie mo¿na utworzyæ pliku bitmap.bmp z folderu z aplikacj¹", "Brak pliku", MB_ICONERROR);
		return 0;
	}

	GetObject( hbmObraz, sizeof( bmInfo ), & bmInfo );
	GetObject( hbmObraz2, sizeof( bmInfo2), & bmInfo2) ;
	GetObject( hbmObraz3, sizeof( bmInfo3), & bmInfo3);
	GetObject( hbmObraz4, sizeof( bmInfo4), & bmInfo4);
	GetObject( hbmObraz5, sizeof( bmInfo5), & bmInfo5);

	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );

	while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    
	return Komunikat.wParam;
	
}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )

{	
	HDC hdco, hdcbitmapy;
	PAINTSTRUCT ps;
	HWND hwnd2;
	HFONT hNormalFont;
	HWND static_name, edit_name, static_res, static_dif, combo_dif, combo_res, button_ok, button_cancel;
	char** ab =new char*[1];
	//ab[0]=new char*;
	ab[0]="Snake 3D";
	int ar=1;
	std::string temp;
    switch( msg )
    {

	case WM_COMMAND:

		
		switch(wParam)
		{

		case button1:
			
			which_option=1;
			
			initGLUT(&ar,ab);
			initGLEW();
			initOpenGL(cameraAngle,windowWidth,windowHeight);
	
			glutMainLoop();
	
			freeVAO();
			freeVBO();
			cleanShaders();
	return 0;
			
			break;

		case button2:

			which_option=2;
			hwnd2=CreateWindow(NazwaKlasy2,"Opcje",WS_OVERLAPPEDWINDOW|WS_VISIBLE,50,50,900,600,hwnd,NULL,NULL,NULL);
			if( hwnd2 == NULL )
			{
				MessageBox( NULL, "B³¹d w czasie tworzenia okna", "Dalej", MB_ICONEXCLAMATION );
				
			}

			
			//g_hBrush = CreateSolidBrush( RGB( 0, 100, 0 ) );
			static_name=CreateWindowEx( WS_EX_CLIENTEDGE, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT,
				70, 50, 150, 20, hwnd2, NULL, NULL, NULL);
			static_dif=CreateWindowEx( WS_EX_CLIENTEDGE, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 
				70, 110, 150, 20, hwnd2, NULL, NULL, NULL);
			static_res=CreateWindowEx( WS_EX_CLIENTEDGE, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 
				70, 170, 150, 20, hwnd2, NULL, NULL, NULL);
			edit_name=CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE,
				70, 80, 150, 20, hwnd2, NULL, NULL, NULL );
			combo_dif=CreateWindowEx( WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
				70, 140, 150, 200, hwnd2, NULL, NULL, NULL);
			combo_res=CreateWindowEx( WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
				70, 200, 150, 200, hwnd2, NULL, NULL, NULL);
			button_ok=CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Zapisz", WS_CHILD | WS_VISIBLE,
				100,260,150,30,hwnd2,(HMENU) 509,NULL,NULL);
			button_cancel=CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Anuluj", WS_CHILD | WS_VISIBLE,
				270,260,150,30,hwnd2,(HMENU) 510,NULL,NULL);

			SetWindowText( static_name, "Nazwa gracza:" );
			SetWindowText( static_res, "Rozdzielczoœæ:" );
			SetWindowText( static_dif, "Poziom trudnoœci:" );
			
			hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
			SendMessage( button_ok, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( button_cancel, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( static_dif, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( static_res, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( static_name, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( combo_dif, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( combo_res, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( edit_name, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			SendMessage( combo_res, CB_ADDSTRING, 0,( LPARAM ) "640x480" );
			SendMessage( combo_res, CB_ADDSTRING, 0,( LPARAM ) "900x600" );
			SendMessage( combo_dif, CB_ADDSTRING, 0,( LPARAM ) "£atwy" );
			SendMessage( combo_dif, CB_ADDSTRING, 0,( LPARAM ) "Œredni" );
			SendMessage( combo_dif, CB_ADDSTRING, 0,( LPARAM ) "Trudny" );
			loadOptions(sett);
			
			SetWindowText( edit_name, "Bartek" );
			SendMessage( combo_dif,CB_SETCURSEL,(WPARAM)sett.difficulty,1);
			SendMessage( combo_res,CB_SETCURSEL,(WPARAM)sett.res,1);
			break;

		case button3:

			hwnd2=CreateWindow(NazwaKlasy2,"O autorach",WS_OVERLAPPEDWINDOW|WS_VISIBLE,50,50,900,600,hwnd,NULL,NULL,NULL);
			if( hwnd2 == NULL )
			{
				MessageBox( NULL, "B³¹d w czasie tworzenia okna", "Dalej", MB_ICONEXCLAMATION );
				
			}
			button_cancel=CreateWindowEx( WS_EX_CLIENTEDGE,"BUTTON","Wstecz",WS_CHILD|WS_VISIBLE,200,450,150,30,hwnd2,(HMENU) 510,NULL,NULL);
			hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
			SendMessage( button_cancel, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

			which_option=3;
			break;

		case button4:
			
			which_option=4;
			hwnd2=CreateWindow(NazwaKlasy2,"Pomoc",WS_OVERLAPPEDWINDOW|WS_VISIBLE,50,50,900,600,hwnd,NULL,NULL,NULL);
			if( hwnd2 == NULL )
			{
				MessageBox( NULL, "B³¹d w czasie tworzenia okna", "Dalej", MB_ICONEXCLAMATION );
				
			}
			button_cancel=CreateWindowEx( WS_EX_CLIENTEDGE,"BUTTON","Wstecz",WS_CHILD|WS_VISIBLE,200,450,150,30,hwnd2,(HMENU) 510,NULL,NULL);
			hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
			SendMessage( button_cancel, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

			break;

		case button5:
			
			which_option=5;
			hwnd2=CreateWindow(NazwaKlasy2,"Najlepsze wyniki",WS_OVERLAPPEDWINDOW|WS_VISIBLE,50,50,900,600,hwnd,NULL,NULL,NULL);
			if( hwnd2 == NULL )
			{
				MessageBox( NULL, "B³¹d w czasie tworzenia okna", "Dalej", MB_ICONEXCLAMATION );
				
			}

			button_cancel=CreateWindowEx( WS_EX_CLIENTEDGE,"BUTTON","Wstecz",WS_CHILD|WS_VISIBLE,200,450,150,30,hwnd2,(HMENU) 510,NULL,NULL);
			hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
			SendMessage( button_cancel, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

			combo_dif=CreateWindowEx(WS_EX_CLIENTEDGE,"LISTBOX",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,70,70,300,350,hwnd2,NULL,NULL,NULL);
			loadBest(best_scorers);

			
			for(int i=0;i<20;i++){
			
			//temp=best_scorers[i].name +itoa(best_scorers[i].points,0,1);
			SendMessage( combo_dif, LB_ADDSTRING, 0,( LPARAM ) (best_scorers[i].name+"       "+"50").c_str());
			}
			SendMessage( combo_dif, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
			break;

		case button6:

			DestroyWindow( hwnd );
			break;


		}
		break;

	case WM_PAINT:
		hdco=BeginPaint(hwnd,&ps); //kontekst okna uzyskujemy w momencie odrysowywania
		hdcbitmapy=CreateCompatibleDC(hdco); //teraz musimy utworzyæ kontekst pamiêciowy dla bitmapy
		hbmObraz=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz); //zamieniamy konteksty wi¹¿¹c bitmapê z kontekstem
		//tutaj mo¿emy przeprowadzaæ jakieœ operacje graficzne z naszym kontekstem bitmapy
		//uwaga te operacje bêd¹ przeprowadzane co ka¿de odœwie¿enie okna
		//wyœwietlenie bitmapy na oknie, operacja przekopiowania
		BitBlt(hdco,0,0,bmInfo.bmWidth,bmInfo.bmHeight,hdcbitmapy,0,0,SRCCOPY);
		hbmObraz=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz); //z powrotem zamieniamy bitmapy w kontekœcie
		DeleteDC(hdcbitmapy); //usuwamy kontekst pamiêciowy bitmapy
		EndPaint(hwnd,&ps);
		break;
    
	case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
        
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
        
        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    
    return 0;
}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc2( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )

{	
	HDC hdco, hdcbitmapy;
	PAINTSTRUCT ps;

    switch( msg )
    {

	case WM_COMMAND:

		switch(wParam)
		{

		case 509:

			break;

		case 510:

			DestroyWindow( hwnd );
			break;

		}
		
		break;

	case WM_PAINT:
		hdco=BeginPaint(hwnd,&ps); //kontekst okna uzyskujemy w momencie odrysowywania
		hdcbitmapy=CreateCompatibleDC(hdco); //teraz musimy utworzyæ kontekst pamiêciowy dla bitmapy
		hbmObraz2=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz2); //zamieniamy konteksty wi¹¿¹c bitmapê z kontekstem
		//tutaj mo¿emy przeprowadzaæ jakieœ operacje graficzne z naszym kontekstem bitmapy
		//uwaga te operacje bêd¹ przeprowadzane co ka¿de odœwie¿enie okna
		//wyœwietlenie bitmapy na oknie, operacja przekopiowania
		BitBlt(hdco,0,0,bmInfo2.bmWidth,bmInfo2.bmHeight,hdcbitmapy,0,0,SRCCOPY);
		hbmObraz2=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz2); //z powrotem zamieniamy bitmapy w kontekœcie
		if(which_option==3)
		{		
		hbmObraz3=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz3);
		BitBlt(hdco,0,0,bmInfo3.bmWidth,bmInfo3.bmHeight,hdcbitmapy,0,0,SRCCOPY);
		hbmObraz3=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz3);
		}

		if(which_option==4)
		{
			hbmObraz4=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz4);
			BitBlt(hdco,0,0,bmInfo4.bmWidth,bmInfo4.bmHeight,hdcbitmapy,0,0,SRCCOPY);
			hbmObraz4=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz4);
		}

		if(which_option==5)
		{
			hbmObraz5=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz5);
			BitBlt(hdco,0,0,bmInfo5.bmWidth,bmInfo5.bmHeight,hdcbitmapy,0,0,SRCCOPY);
			hbmObraz5=(HBITMAP)SelectObject(hdcbitmapy,hbmObraz5);
		}

		DeleteDC(hdcbitmapy); //usuwamy kontekst pamiêciowy bitmapy
		
		EndPaint(hwnd,&ps);
		
		break;
    
	case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
        
    case WM_DESTROY:
       
        break;
    
	case WM_CTLCOLORSTATIC:
	{
		HWND hCtl =( HWND ) lParam;
		HDC hDC =( HDC ) wParam;
	 
	
		SetBkMode( hDC, TRANSPARENT );
		SetTextColor( hDC, RGB( 255, 255, 255 ) );
		SendMessage( hCtl, WM_ERASEBKGND, wParam, 0 );
		return( LRESULT ) CreateSolidBrush( RGB( 0, 100, 0 ) );
		
	}
		break;
        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    
    return 0;
}