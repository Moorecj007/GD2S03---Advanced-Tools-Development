
/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Game.h
* Description : Declarations for the functions of the Game class
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once

#ifndef __GAME_H__
#define __GAME_H__

// Library Includes
#include <Windows.h>
#include <iostream>
#include <vector>

// Local Includes
#include "Clock.h"
#include "GameTile.h"
#include "Backbuffer.h"
#include "Defines.h"

using namespace std;

class CGame
{
public:
	// Constructors / Destructors
	~CGame();

	// Getters
	bool GetMouseDrag();
	eImage GetPlaceMode();
	eImage GetOldImage();

	// Setters
	void SetMouseDrag(bool _bDrag);
	void SetOldImage(eImage _eImage);

	//Protoypes
	void Initialize(HINSTANCE _hInstance, HWND _hWnd, int _iScreenWidth, int _iScreenHeight);
	void ExecuteOneFrame();
	void Process();
	void Draw();
	void PlaceTile(int _iMouseX, int _iMouseY);
	void ChangePlaceMode(int _iNew);
	void Reset();
	void TextOutput();

	HINSTANCE GetExeInstance();
	CBackBuffer* GetBackBuffer();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

private:
	//Disallowing copies and extra constructions
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

	// Singleton Instance
	static CGame* s_pGame;

private:
	// Member Variables
	bool m_bMouseDrag;
	CClock* m_pClock;
	CBackBuffer* m_pBackBuffer;
	eImage m_PlaceMode;
	eImage m_OldImage;

	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_iScreenWidth;
	int m_iScreenHeight;

	vector< vector<CGameTile*>*>* m_pVecGameTiles;
	unsigned int m_uiGridRow;
	unsigned int m_uiGridCol;
	int m_iTileSize;
};

#endif //__GAME_H__


