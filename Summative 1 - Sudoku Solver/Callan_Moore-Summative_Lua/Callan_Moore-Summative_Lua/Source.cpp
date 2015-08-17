/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Source.cpp
* Description : Sets up the Window for the Program and processes all the messages
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
//#include <vld.h>
#endif // _DEBUG

// Library Includes
#pragma comment(lib, "Winmm.lib")
#include <windows.h>		// Include all the windows headers.
#include <windowsx.h>		// Include useful macros.

// Local Includes
#include "Defines.h"
#include "Game.h"

// Defines
#define WINDOW_CLASS_NAME L"Sudoku Solver"

// Prototypes
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

/***********************
* WindowProc: Process the window
* @author: Callan Moore
* @Parameter: _hWnd: Handle to the Window sending the message
* @Parameter: _uiMsg: The message ID being sent
* @Parameter: _wParam: Additional detail about the message being sent
* @Parameter: _lParam: Additional detail about the message being sent
* @return: LRESULT: The resulting value
********************/
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT paintStruct;		// Used in WM_PAINT.
	HDC hDC;						// Handle to a device context.

	// Switch case dependent on the message sent
	switch (_uiMsg)
	{
	case WM_CREATE:
	{

		return (0);
	}
		break;
	case WM_PAINT:
	{
		hDC = BeginPaint(_hWnd, &paintStruct);	// Prepares the window for painting
		EndPaint(_hWnd, &paintStruct);			// Marks the ending of the window being painted

		return (0);
	}
		break;
	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);
		return (0);
	}
		break;
	case WM_LBUTTONDOWN:
	{

		// Get the position of the mouse and place tile on the relevant GameTile
		int iXpos = GET_X_LPARAM(_lParam);
		int iYpos = GET_Y_LPARAM(_lParam);
		CGame::GetInstance().PlaceTile(iXpos, iYpos);
	}
		break;
	case WM_RBUTTONDOWN:
	{
		// Mouse is being held down
		CGame::GetInstance().SetMouseDrag(true);

		// Store the Old Placement Mode and set Place Mode to Dirt
		CGame::GetInstance().SetOldImage(CGame::GetInstance().GetPlaceMode());
		CGame::GetInstance().ChangePlaceMode(IMAGE_BLANK);

		// Get the position of the mouse and place tile on the relevant GameTile
		int iXpos = GET_X_LPARAM(_lParam);
		int iYpos = GET_Y_LPARAM(_lParam);
		CGame::GetInstance().PlaceTile(iXpos, iYpos);
	}
		break;
	case WM_RBUTTONUP:
	{
		// Mouse click is no longer held down
		CGame::GetInstance().SetMouseDrag(false);
		// Reset placemode to the Old Image
		CGame::GetInstance().ChangePlaceMode(CGame::GetInstance().GetOldImage());
	}
	case WM_MOUSEMOVE:
	{
		if (CGame::GetInstance().GetMouseDrag() == true)
		{
			// Get the position of the mouse and place tile on the relevant GameTile
			int iXpos = GET_X_LPARAM(_lParam);
			int iYpos = GET_Y_LPARAM(_lParam);
			CGame::GetInstance().PlaceTile(iXpos, iYpos);
		}
	}
	default:break;
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE:
		{
			// Terminate Application
			PostQuitMessage(0);
		}
			break;
		case '1':	// Fall Through
		case VK_NUMPAD1:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Pathfinder
				CGame::GetInstance().ChangePlaceMode(IMAGE_1);
			}
		}
			break;
		case '2':	// Fall Through
		case VK_NUMPAD2:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Destination
				CGame::GetInstance().ChangePlaceMode(IMAGE_2);
			}
		}
			break;
		case '3':	// Fall Through
		case VK_NUMPAD3:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_3);
			}
		}
			break;
		case '4':	// Fall Through
		case VK_NUMPAD4:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_4);
			}
		}
			break;
		case '5':	// Fall Through
		case VK_NUMPAD5:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_5);
			}
		}
			break;
		case '6':	// Fall Through
		case VK_NUMPAD6:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_6);
			}
		}
			break;
		case '7':	// Fall Through
		case VK_NUMPAD7:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_7);
			}
		}
			break;
		case '8':	// Fall Through
		case VK_NUMPAD8:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_8);
			}
		}
			break;
		case '9':	// Fall Through
		case VK_NUMPAD9:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				// Change Placement Mode to Wall
				CGame::GetInstance().ChangePlaceMode(IMAGE_9);
			}
		}
			break;
		case VK_RETURN:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				CGame::GetInstance().SolveSudoku();
			}
		}
			break;
		// TO DO - delete
		case VK_F1:
		{
			if (((_lParam >> 30) & 1) != 1)
			{
				CGame::GetInstance().tempPlace();
			}
		}
			break;
		} // End Switch
	}
	}	// End Switch
	// Process any messages left to process
	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

/***********************
* WinMain: Initialises the program to start and creates the window
* @author: Callan Moore
* @Parameter: _hInstance: Instance handle that Windows generates for your application
* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments
* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
* @return: int: Program ends here
********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	WNDCLASSEX winClass;	// This will hold the class we create.
	HWND hWnd;				// Generic window handle.
	MSG uiMsg;				// Generic message.

	// Fills in the window class structure.
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = _hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = WINDOW_CLASS_NAME;
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	const int kiScreenWidth = 1000;
	const int kiScreenHeight = 1000;

	// Registers the window class
	if (!RegisterClassEx(&winClass))
	{
		return (0);
	}

	hWnd = CreateWindowEx(NULL,				// Extended style.
		WINDOW_CLASS_NAME,					// Class.
		L"ASTAR - AI",						// Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,								// Initial x,y position for the top left corner of the window
		kiScreenWidth, kiScreenHeight,		// Initial width, height of the window
		NULL,								// Handle to parent.
		NULL,								// Handle to menu.
		_hInstance,							// Instance of this application.
		NULL);								// Extra creation parameters.

	// Check the window was created successfully.
	if (!hWnd)
	{
		return (0);
	}

	CGame& rGameInstance = CGame::GetInstance();
	rGameInstance.Initialize(_hInstance, hWnd, kiScreenWidth, kiScreenHeight);

	// Enter main event loop.
	while (true)
	{
		while (PeekMessage(&uiMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uiMsg);
			DispatchMessage(&uiMsg);
		}

		if (uiMsg.message == WM_QUIT)
		{
			break;
		}

		rGameInstance.ExecuteOneFrame();
	}

	rGameInstance.DestroyInstance();


	// Return to Windows
	return (static_cast<int>(uiMsg.wParam));
}