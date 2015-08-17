/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Game.cpp
* Description : Implementation for the functions of the Game class
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Local Includes
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

/***********************
* Game: Default Contructor for Game class
* @author: Callan Moore
********************/
CGame::CGame()
{
	// Set all Pointers to NULL when constructed
	m_pClock = 0;
	m_pBackBuffer = 0;
	m_pVecGameTiles = 0;

	m_bMouseDrag = false;
}

/***********************
* ~Game: Default Destructor for Game class
* @author: Callan Moore
********************/
CGame::~CGame()
{
	// Delete Clock and Backbuffer
	delete m_pClock;
	m_pClock = 0;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	// Delete all GameTiles
	// Cycle through Columns
	if (m_pVecGameTiles != 0)
	{
		while (m_pVecGameTiles->empty() == false)
		{
			vector<CGameTile*>* pLastRow = m_pVecGameTiles->back();
			// Cycle through Rows
			while (pLastRow->empty() == false)
			{
				// Delete the last GameTile in the Row
				delete pLastRow->back();
				pLastRow->back() = 0;
				pLastRow->pop_back();
			}

			// Delete the Last Column of Game Tiles
			delete m_pVecGameTiles->back();
			m_pVecGameTiles->back() = 0;
			m_pVecGameTiles->pop_back();
		}
	}

	// Delete the GameTile Grid
	delete m_pVecGameTiles;
	m_pVecGameTiles = 0;
}

/***********************
* GetMouseDrag: Retrieve whether the mouse is clicked and dragging
* @author: Callan Moore
* @return: void
********************/
bool CGame::GetMouseDrag()
{
	return m_bMouseDrag;
}

/***********************
* GetPlaceMode: Retrieve The current place mode
* @author: Callan Moore
* @return: eImage: The current Place Mode
********************/
eImage CGame::GetPlaceMode()
{
	return m_PlaceMode;
}

/***********************
* GetOldImage: Retrieve The Old Place mode Image
* @author: Callan Moore
* @return: eImage: The Old Place mode Image
********************/
eImage CGame::GetOldImage()
{
	return m_OldImage;
}

/***********************
* SetMouseDrag: Set the Variable for whether the mouse is clicked and dragging
* @author: Callan Moore
* @parameters: _bDrag: New boolean to determine whether the mouse is clicked and dragging
* @return: void
********************/
void CGame::SetMouseDrag(bool _bDrag)
{
	m_bMouseDrag = _bDrag;
}

/***********************
* SetOldImage: Set the Variable to store the old place mode image
* @author: Callan Moore
* @parameters: _eImage: The Old Image to Store
* @return: void
********************/
void CGame::SetOldImage(eImage _eImage)
{
	m_OldImage = _eImage;
}

/***********************
* Initialize: Create a new object of Game
* @author: Callan Moore
* @parameters: _hInstance: Handle to the Instance of the executable
* @parameters: _hWnd: Handle to The creating window
* @parameters: _iScreenWidth: Screen width for this application
* @parameters: _iScreenHeight: Screen width for this application
* @return: void
********************/
void CGame::Initialize(HINSTANCE _hInstance, HWND _hWnd, int _iScreenWidth, int _iScreenHeight)
{
	// Create a clock and Backbuffer
	m_pClock = new CClock();
	m_pClock->Initialise();
	m_pBackBuffer = new CBackBuffer();
	m_pBackBuffer->Initialise(_hWnd, _iScreenWidth, _iScreenHeight);

	// Initialize member variables
	m_hWnd = _hWnd;
	m_hInstance = _hInstance;
	m_PlaceMode = IMAGE_1;
	m_iScreenWidth = _iScreenWidth;
	m_iScreenHeight = _iScreenHeight;

	// Create the Game board
	m_pVecGameTiles = new vector < vector< CGameTile*>* >;

	// Set StrBlt Mode to Halftone
	SetStretchBltMode(m_pBackBuffer->GetBFDC(), HALFTONE);

	// Define the Grid Values to be used in creating a Game Grid
	m_uiGridRow = 9;
	m_uiGridCol = 9;
	m_iTileSize = 75;
	
	// Initial positions for X and Y
	int iTileX = 0;
	int iTileY = 0;

	// Create the Grid
	for (unsigned int iRow = 0; iRow < m_uiGridRow; iRow++)
	{
		// Reset the X value to the left of the screen
		iTileY = 0;

		// Create and push back a vector to store Game Tile Rows
		vector< CGameTile*>* vecTemp = new vector< CGameTile*>;
		m_pVecGameTiles->push_back(vecTemp);

		for (unsigned int iCol = 0; iCol < m_uiGridCol; iCol++)
		{
			// Create a new Game Tile at the current X and Y positions
			CGameTile* GTtemp = new CGameTile();
			GTtemp->Initialise(iTileX, iTileY, m_iTileSize);
			vecTemp->push_back(GTtemp);

			iTileY += m_iTileSize;
		}
		iTileX += m_iTileSize;
	}
}

/***********************
* ExecuteOneFrame: Executes one frame
* @author: Callan Moore
* @return: void
********************/
void CGame::ExecuteOneFrame()
{
	Process();
	Draw();
}

/***********************
* Process: Processes the Game for the Delta tick
* @author: Callan Moore
* @return: void
********************/
void CGame::Process()
{

}

/***********************
* Draw: Draws all the Tiles of the Game World
* @author: Callan Moore
* @return: void
********************/
void CGame::Draw()
{
	m_pBackBuffer->Clear();

	// Draw all Gametiles to the backbuffer
	for (unsigned int uiRow = 0; uiRow < m_uiGridRow; uiRow++)
	{
		for (unsigned int uiCol = 0; uiCol < m_uiGridCol; uiCol++)
		{
			(*(*m_pVecGameTiles)[uiRow])[uiCol]->Draw();
		}
	}

	TextOutput();

	m_pBackBuffer->Present();
}

/***********************
* PlaceTile: Places a tile in the clicked location dependent on the PlaceMode
* @author: Callan Moore
* @parameter: _iMouseX: The Mouses X position
* @parameter: _iMouseY: The Mouses X position
* @return: void
********************/
void CGame::PlaceTile(int _iMouseX, int _iMouseY)
{
	// Find the GameTile that the mouse is clicking on
	int TileX = _iMouseX / m_iTileSize;
	int TileY = _iMouseY / m_iTileSize;

	if (TileX >= 9 || TileY >= 9)
	{
		return;
	}

	CGameTile* pTileClicked = (*(*m_pVecGameTiles)[TileX])[TileY];

	// Switch case to find what the user is trying to place on that tile
	switch (m_PlaceMode)
	{
		case IMAGE_BLANK:
		{
			pTileClicked->SetImage(IMAGE_BLANK);

		}
		break;
		case IMAGE_1:
		{
			pTileClicked->SetImage(IMAGE_1);

		}
		break;
		case IMAGE_2:
		{
			pTileClicked->SetImage(IMAGE_2);

		}
		break;
		case IMAGE_3:
		{
			pTileClicked->SetImage(IMAGE_3);

		}
		break;
		case IMAGE_4:
		{
			pTileClicked->SetImage(IMAGE_4);

		}
		break;
		case IMAGE_5:
		{
			pTileClicked->SetImage(IMAGE_5);

		}
		break;
		case IMAGE_6:
		{
			pTileClicked->SetImage(IMAGE_6);

		}
		break;
		case IMAGE_7:
		{
			pTileClicked->SetImage(IMAGE_7);

		}
		break;
		case IMAGE_8:
		{
			pTileClicked->SetImage(IMAGE_8);

		}
		break;
		case IMAGE_9:
		{
			pTileClicked->SetImage(IMAGE_9);

		}
		break;
		default: break;
	}	// End Switch
}

/***********************
* ChangePlaceMode: Changes the PlaceMode to the input choice
* @author: Callan Moore
* @parameter: _iNew: The new placement Mode
* @return: void
********************/
void CGame::ChangePlaceMode(int _iNew)
{
	// Changing the Placemode
	switch (_iNew)
	{
	case 0:
	{
		m_PlaceMode = IMAGE_BLANK;
	}
		break;
	case 1:
	{
		m_PlaceMode = IMAGE_1;
	}
		break;
	case 2:
	{
		m_PlaceMode = IMAGE_2;
	}
		break;
	case 3:
	{
		m_PlaceMode = IMAGE_3;
	}
		break;
	case 4:
	{
		m_PlaceMode = IMAGE_4;
	}
		break;
	case 5:
	{
		m_PlaceMode = IMAGE_5;
	}
		break;
	case 6:
	{
		m_PlaceMode = IMAGE_6;
	}
		break;
	case 7:
	{
		m_PlaceMode = IMAGE_7;
	}
		break;
	case 8:
	{
		m_PlaceMode = IMAGE_8;
	}
		break;
	case 9:
	{
		m_PlaceMode = IMAGE_9;
	}
		break;
	default:
	{
		m_PlaceMode = IMAGE_BLANK;
	}
		break;
	}	// End Switch
}

/***********************
* Reset: Reset the values and arrow images of the Game Tiles
* @author: Callan Moore
* @return: void
********************/
void CGame::Reset()
{
	
}

/***********************
* TextOutput: Displays text information on the screen
* @author: Callan Moore
* @return: void
********************/
void CGame::TextOutput()
{
	// Set the Background color for Text and the Text color
	SetBkMode(m_pBackBuffer->GetBFDC(), TRANSPARENT);
	SetTextColor(m_pBackBuffer->GetBFDC(), RGB(255, 255, 255));

	// Write how many cities are present
	std::string strPathfinder = "[1] -> Selects the Pathfinder";
	std::string strDestination = "[2] -> Selects the Destination";
	std::string strWall = "[3] -> Selects the Wall";

	std::string strLeftClick = "[Left Click] -> Places Selected Tile";
	std::string strRightClick = "[Right Click] -> Clears Any Tile to Dirt";
	std::string strSelected = "Selected -> ";

	TextOutA(m_pBackBuffer->GetBFDC(), 10, 15, strPathfinder.c_str(), strPathfinder.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 30, strDestination.c_str(), strDestination.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 45, strWall.c_str(), strWall.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 60, strLeftClick.c_str(), strLeftClick.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 75, strRightClick.c_str(), strRightClick.size());

	if (m_PlaceMode == IMAGE_1)
	{
		strSelected.append("1");
	}
	else if (m_PlaceMode == IMAGE_2)
	{
		strSelected.append("2");
	}
	else if (m_PlaceMode == IMAGE_3)
	{
		strSelected.append("3");
	}
	else if (m_PlaceMode == IMAGE_4)
	{
		strSelected.append("4");
	}
	else if (m_PlaceMode == IMAGE_5)
	{
		strSelected.append("5");
	}
	else if (m_PlaceMode == IMAGE_6)
	{
		strSelected.append("6");
	}
	else if (m_PlaceMode == IMAGE_7)
	{
		strSelected.append("7");
	}
	else if (m_PlaceMode == IMAGE_8)
	{
		strSelected.append("8");
	}
	else if (m_PlaceMode == IMAGE_9)
	{
		strSelected.append("9");
	}

	TextOutA(m_pBackBuffer->GetBFDC(), 10, 105, strSelected.c_str(), strSelected.size());
}

/***********************
* GetExeInstance: Retrieves the instance of the executable
* @author: Callan Moore
* @return: HINSTANCE: Instance of the Executable
********************/
HINSTANCE CGame::GetExeInstance()
{
	return m_hInstance;
}

/***********************
* GetBackBuffer: Retrieves the current backbuffer to be used or updated.
* @author: Callan Moore
* @return: CBackBuffer*: The current backbuffer
********************/
CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

/***********************
* GetInstance: Returns the singleton instance of the game, if it doesnt exist creates it.
* @author: Callan Moore
* @return: CGame&: The current instance of the game
********************/
CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************
* DestroyInstance: Deletes the instance of the game. 
* @author: Callan Moore
* @return: void
********************/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}
