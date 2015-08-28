/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : GameTile.cpp
* Description : Implementation File for all GameTile funtions
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Local Includes
#include "GameTile.h"
#include "Game.h"

// Static Variables
HDC CGameTile::s_hSharedSpriteDC = 0;


/***********************
* CGameObject: Default Constructor of the Game Tile
* @author: Callan Moore
********************/
CGameTile::CGameTile()
{

}

/***********************
* ~CGameObject: Default Destructor of the Game Tile
* @author: Callan Moore
********************/
CGameTile::~CGameTile()
{

}

/***********************
* Initialise: Initialise the GameTile for use
* @author: Callan Moore
* @parameter: _iXpos: The X position of the Tiles top left corner
* @parameter: _iYpos: The Y position of the Tiles top left corner
* @parameter: _iImageSize: The size of one side of the square image
* @return: bool: Success of the Initialisation
********************/
bool CGameTile::Initialise(int _iXpos, int _iYpos, int _iImageSize)
{
	m_pPrevTile = 0;

	m_iXpos = _iXpos;
	m_iYpos = _iYpos;

	// All Tiles start blank 
	m_eImage = IMAGE_BLANK;
	m_iImageSize = _iImageSize;

	// Creates a Shared Sprite if one does not exist
	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	HINSTANCE hInstance = CGame::GetInstance().GetExeInstance();

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BLANK));
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);

	return true;
}

/***********************
* GetXpos: Retrieve the X position of the Game Tile
* @author: Callan Moore
* @return: int: The X position in Screen coordinates
********************/
int CGameTile::GetXpos()
{
	return m_iXpos;
}

/***********************
* GetYpos: Retrieve the Y position of the Game Tile
* @author: Callan Moore
* @return: int: The Y position in Screen coordinates
********************/
int CGameTile::GetYpos()
{
	return m_iYpos;
}

/***********************
* GetImage: Retrieve the Image enumerator of the Game Tile
* @author: Callan Moore
* @return: eImage: Enumerator to define what Image the Tile holds
********************/
eImage CGameTile::GetImage()
{
	return m_eImage;
}

/***********************
* SetXpos: Sets the X position of the Game Tile
* @author: Callan Moore
* @parameter: _iNewX: The X position in Screen coordinates
* @return: void
********************/
void CGameTile::SetXpos(int _iNewX)
{
	m_iXpos = _iNewX;
}

/***********************
* SetYpos: Sets the Y position of the Game Object
* @author: Callan Moore
* @parameter: _iNewY: The Y position in Screen coordinates
* @return: void
********************/
void CGameTile::SetYpos(int _iNewY)
{
	m_iYpos = _iNewY;
}

/***********************
* SetImage: Sets the Image Pointer of the Game Object
* @author: Callan Moore
* @parameter: _eImage: Enumerator to define what Image the Tile holds
* @return: void
********************/
void CGameTile::SetImage(eImage _eImage)
{
	m_eImage = _eImage;

	HINSTANCE hInstance = CGame::GetInstance().GetExeInstance();

	switch (m_eImage)
	{
	case IMAGE_1:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_1));
	}
		break;
	case IMAGE_2:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_2));
	}
		break;
	case IMAGE_3:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_3));
	}
		break;
	case IMAGE_4:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_4));
	}
		break;
	case IMAGE_5:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_5));
	}
		break;
	case IMAGE_6:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_6));
	}
		break;
	case IMAGE_7:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_7));
	}
		break;
	case IMAGE_8:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_8));
	}
		break;
	case IMAGE_9:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_9));
	}
		break;
	case IMAGE_BLANK:	// Fall Through
	default:
	{
		m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BLANK));
	}
		break;
	}	// End Switch

	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
}

/***********************
* Process: Process the Game Tile
* @author: Callan Moore
* @return: void
********************/
void CGameTile::Process()
{

}

/***********************
* Draw: Draws the Tile to the screen
* @author: Callan Moore
* @return: void
********************/
void CGameTile::Draw()
{
	// Get the Back buffer
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	// Select Object and StretchBlt onto the backbuffer
	SelectObject(s_hSharedSpriteDC, m_hSprite);
	StretchBlt(pBackBuffer->GetBFDC(), m_iXpos, m_iYpos, m_iImageSize, m_iImageSize, s_hSharedSpriteDC, 0, 0, m_bitmapSprite.bmWidth, m_bitmapSprite.bmHeight, SRCCOPY);
}