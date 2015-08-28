
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

#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")

// Library Includes
#include <Windows.h>
#include <iostream>
#include <vector>
#include "lua.hpp"
#include <iostream>
#include <stdlib.h>                       
#include <stdio.h>  
#include <string>

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

	void InitialiseLua();

	void ConvertTo2D(int* _sudoku1D, int** _sudoku2D);
	void ConvertTo1D(int** _sudoku2D, int* _sudoku1D);

	void SolveSudoku();
	void RetrieveSudokuGUI(int** _sudoku);
	void PlaceSudokuGUI(int** _sudoku);
	void ResetSudokuGrid();
	void GenerateSudoku();
	void StackDump(lua_State* _pLuaEnv);
	void PremadeProblem();

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
	std::string m_strSolveStatus;
	lua_State* m_pLuaState;

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


