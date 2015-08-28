/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand

* (c) 2005 - 2015 Media Design School

* File Name : Backbuffer.cpp
* Description : Implementation file for the Backbuffer class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz
*/

// This include
#include "BackBuffer.h"

/***********************
* CBackBuffer: Contructor for the BackBuffer class
* @author: Callan Moore
********************/
CBackBuffer::CBackBuffer()
{
	m_hWnd = 0;
	m_hDC = 0;
	m_hSurface = 0;
	m_hOldObject = 0;
	m_iWidth = 0;
	m_iHeight = 0;
}

/***********************
* ~CBackBuffer: Destructor for the BackBuffer class
* @author: Callan Moore
********************/
CBackBuffer::~CBackBuffer()
{
	SelectObject(m_hDC, m_hOldObject);
	DeleteObject(m_hSurface);
	DeleteObject(m_hDC);
}

/***********************
* Initialise: Initialises all the Backbuffer member variables
* @author: Callan Moore
* @parameter: _hWnd: Handle to the main window.
* @parameter: _iWidth: Width of the main window to determine the backbuffer height.
* @parameter: _iHeight: Height of the main window to determine the backbuffer height.
* @return: bool: Always return true.
********************/
bool CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hWnd = _hWnd;
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	HDC hWindowDC = ::GetDC(m_hWnd);
	m_hDC = CreateCompatibleDC(hWindowDC);
	m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);
	ReleaseDC(m_hWnd, hWindowDC);

	m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));
	HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

	Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);
	SelectObject(m_hDC, oldBrush);

	return (true);
}

/***********************
* Clear: Clears the backbuffer to an empty state
* @author: Callan Moore
* @return: void
********************/
void CBackBuffer::Clear()
{
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(BLACK_BRUSH)));
	Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());
	SelectObject(GetBFDC(), hOldBrush);
}

/***********************
* GetBFDC: Retrieves the backbuffers Handle to the Device Context (HDC)
* @author: Callan Moore
* @return: HDC: The backbuffers HDC
********************/
HDC CBackBuffer::GetBFDC() const
{
	return (m_hDC);
}

/***********************
* GetWidth: Retrieves the width of the backbuffer
* @author: Callan Moore
* @return: int: The width of the backbuffer
********************/
int CBackBuffer::GetWidth() const
{
	return (m_iWidth);
}

/***********************
* GetHeight: Retrieves the height of the backbuffer
* @author: Callan Moore
* @return: int: The height of the backbuffer
********************/
int CBackBuffer::GetHeight() const
{
	return (m_iHeight);
}

/***********************
* Present: Copies the backbuffer onto the main screen window for display
* @author: Callan Moore
* @return: void
********************/
void CBackBuffer::Present()
{
	HDC hWndDC = ::GetDC(m_hWnd);
	BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hWndDC);
}