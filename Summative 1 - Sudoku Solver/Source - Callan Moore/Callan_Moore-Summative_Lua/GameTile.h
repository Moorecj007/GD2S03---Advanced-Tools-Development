/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : CGameTile.h
* Description : Declaration File for all CGameTile funtions
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once

// Local Includes
#include "Defines.h"
#include "Backbuffer.h"
#include "resource.h"

class CGameTile
{
public:
	// Constructors / Destructors
	CGameTile();
	~CGameTile();

	bool Initialise(int _iXpos, int _iYpos, int _iImageSize);

	// Getters
	int GetXpos();
	int GetYpos();
	eImage GetImage();

	// Setters
	void SetXpos(int _iNewX);
	void SetYpos(int _iNewY);
	void SetImage(eImage _eImage);

	// Prototypes
	void Process();
	void Draw();

private:
	// Member Variables
	CGameTile* m_pPrevTile;

	// Image Properties
	int m_iXpos;
	int m_iYpos;
	eImage m_eImage;
	int m_iImageSize;
	static HDC s_hSharedSpriteDC;
	HBITMAP m_hSprite;
	BITMAP m_bitmapSprite;
};

