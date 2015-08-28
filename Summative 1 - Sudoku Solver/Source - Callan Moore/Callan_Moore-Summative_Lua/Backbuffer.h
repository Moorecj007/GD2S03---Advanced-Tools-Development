/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand

* (c) 2005 - 2015 Media Design School

* File Name : Backbuffer.h
* Description : Header file for the Backbuffer class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz
*/

#pragma once

#if !defined(__BACKBUFFER_H__)
#define __BACKBUFFER_H__

// Library Includes
#include <Windows.h>

// Prototypes
class CBackBuffer
{
public:
	// Constructors / Destructors
	CBackBuffer();
	~CBackBuffer();
	bool Initialise(HWND _hWnd, int _iWidth, int _iHeight);

	// Prototypes
	void Clear();
	void Present();

	// Getters
	HDC GetBFDC() const;
	int GetHeight() const;
	int GetWidth() const;

private:
	// Disallowing copies
	CBackBuffer(const CBackBuffer& _kr);
	CBackBuffer& operator= (const CBackBuffer& _kr);

	// Member Variables
protected:
	HWND m_hWnd;
	HDC m_hDC;
	HBITMAP m_hSurface;
	HBITMAP m_hOldObject;

	int m_iWidth;
	int m_iHeight;
};

#endif // __BACKBUFFER_H__