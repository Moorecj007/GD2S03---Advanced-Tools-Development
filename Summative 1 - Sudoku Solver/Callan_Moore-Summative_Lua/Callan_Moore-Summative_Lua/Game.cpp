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

	if (m_pLuaState != 0)
	{
		lua_close(m_pLuaState);
	}
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
	m_strSolveStatus = "Unsolved";

	// Create the Game board
	m_pVecGameTiles = new vector < vector< CGameTile*>* > ;

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
		vector< CGameTile*>* vecTemp = new vector < CGameTile* > ;
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

	InitialiseLua();
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

	if (m_strSolveStatus == "SOLVED")
	{
		SetTextColor(m_pBackBuffer->GetBFDC(), RGB(0, 255, 0));
	}
	else
	{
		SetTextColor(m_pBackBuffer->GetBFDC(), RGB(255, 0, 0));
	}
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 675, m_strSolveStatus.c_str(), m_strSolveStatus.size());


	SetTextColor(m_pBackBuffer->GetBFDC(), RGB(255, 255, 255));

	std::string strInstructionsTitle = "INSTRUCTIONS";
	std::string strInstructions = "Use number keys to select a number";
	std::string strLeftClick = "[Left Click] -> Places Selected Tile";
	std::string strRightClick = "[Right Click] -> Clears Any Tile to Blank";
	std::string strReset = "[R] -> Reset";
	std::string strGenerate = "[G] -> Generate a new puzzle";
	std::string strSelected = "Selected -> ";
	std::string strSolve = "[Enter] -> Solve the Sudoku";

	if (m_PlaceMode == IMAGE_BLANK)
	{
		strSelected.append("Blank");
	}
	else if (m_PlaceMode == IMAGE_1)
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

	TextOutA(m_pBackBuffer->GetBFDC(), 10, 710, strSelected.c_str(), strSelected.size());

	TextOutA(m_pBackBuffer->GetBFDC(), 10, 750, strInstructionsTitle.c_str(), strInstructionsTitle.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 765, strInstructions.c_str(), strInstructions.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 780, strLeftClick.c_str(), strLeftClick.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 795, strRightClick.c_str(), strRightClick.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 810, strGenerate.c_str(), strGenerate.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 825, strReset.c_str(), strReset.size());
	TextOutA(m_pBackBuffer->GetBFDC(), 10, 855, strSolve.c_str(), strSolve.size());
}

// TO DO
void CGame::tempPlace()
{
	int* sudoku_2D[9];

	int row1[9] = { 2, 4, 0, 3, 0, 0, 0, 0, 0 };
	int row2[9] = { 0, 0, 0, 5, 2, 0, 4, 0, 7 };
	int row3[9] = { 0, 0, 0, 0, 4, 6, 0, 0, 8 };
	
	int row4[9] = { 6, 1, 0, 7, 0, 0, 0, 8, 4 };
	int row5[9] = { 0, 0, 9, 0, 6, 0, 5, 0, 0 };
	int row6[9] = { 7, 3, 0, 0, 0, 5, 0, 6, 1 };
	
	int row7[9] = { 1, 0, 0, 4, 7, 0, 0, 0, 0 };
	int row8[9] = { 3, 0, 2, 0, 5, 1, 0, 0, 0 };
	int row9[9] = { 0, 0, 0, 0, 0, 2, 0, 1, 9 };
	
	sudoku_2D[0] = row1;
	sudoku_2D[1] = row2;
	sudoku_2D[2] = row3;
	
	sudoku_2D[3] = row4;
	sudoku_2D[4] = row5;
	sudoku_2D[5] = row6;
	
	sudoku_2D[6] = row7;
	sudoku_2D[7] = row8;
	sudoku_2D[8] = row9;

	PlaceSudokuGUI(sudoku_2D);
}

// TO DO
void CGame::InitialiseLua()
{
	m_pLuaState = luaL_newstate();

	// Load the Lua libraries
	luaL_openlibs(m_pLuaState);

	// Load the lua script (but do NOT run it)
	luaL_loadfile(m_pLuaState, "Sudoku Algorithm.lua");
}

// TO DO
void CGame::ConvertTo2D(int* _sudoku1D, int** _sudoku2D)
{
	// Convert back to a 2D array
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			_sudoku2D[i][j] = _sudoku1D[index++];
		}
	}
}

// TO DO
void CGame::ConvertTo1D(int** _sudoku2D, int* _sudoku1D)
{
	// Convert to 1D array
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			_sudoku1D[index++] = _sudoku2D[i][j];
		}
	}
}

/***********************
* SolveSudoku: Solve the Sudoku
* @author: Callan Moore
* @return: void
********************/
void CGame::SolveSudoku()
{
	int sudoku_1D[81];
	int* sudoku_2D[9];

	// Create a 2D array for the sudoku grid
	for (int i = 0; i < 9; i++)
	{
		int* row = new int[9];
		sudoku_2D[i] = row;
	}

	RetrieveSudokuGUI(sudoku_2D);

	ConvertTo1D(sudoku_2D, sudoku_1D);

	// Prime the lua environment
	lua_pcall(m_pLuaState, 0, 0, 0);

	lua_getglobal(m_pLuaState, "BeginSolving");
	lua_newtable(m_pLuaState);

	// Add the Sudoku 1D table to the stack for use in Lua
	for (int i = 1; i < sizeof(sudoku_1D) / sizeof(*sudoku_1D) + 1; i++)
	{
		lua_pushinteger(m_pLuaState, i);
		lua_pushinteger(m_pLuaState, sudoku_1D[i - 1]);
		lua_settable(m_pLuaState, -3);
	}

	// Call the Lua function
	lua_pcall(m_pLuaState, 1, 2, 0);

	// Retrieve the boolean for if the puzzle was solvable
	int solved = lua_toboolean(m_pLuaState, 1);
	
	// Create a string for the Solve status
	if (solved == 0)
	{
		m_strSolveStatus = "UNSOLVABLE";
	}
	else
	{
		m_strSolveStatus = "SOLVED";
	}

	int value = 0;
	int index = 0;
	lua_pushnil(m_pLuaState);
	// Retrieve all table elements in a 1D array
	while (lua_next(m_pLuaState, -2)) {
		value = (int)lua_tonumber(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
		index = (int)lua_tonumber(m_pLuaState, -1);

		sudoku_1D[index - 1] = value;
	}

	ConvertTo2D(sudoku_1D, sudoku_2D);

	PlaceSudokuGUI(sudoku_2D);

	// Delete the allocated memory
	for (int i = 0; i < 9; i++)
	{
		delete[] sudoku_2D[i];
	}

	// Reset the stack pointer
	lua_settop(m_pLuaState, 0);
}

/***********************
* RetrieveSudokuGUI: Retrieve the Sudoku puzzle from the GUI
* @author: Callan Moore
* @parameter: _sudoku: Storage variable for the sudoku in the GUI
* @return: void
********************/
void CGame::RetrieveSudokuGUI(int** _sudoku)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			_sudoku[i][j] = (int)(*(*m_pVecGameTiles)[j])[i]->GetImage();
		}
	}
}

/***********************
* PlaceSudokuGUI: Place the sudoku puzzle in the GUI
* @author: Callan Moore
* @parameter: _sudoku: The Sudoku to place in the GUI
* @return: void
********************/
void CGame::PlaceSudokuGUI(int** _sudoku)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			(*(*m_pVecGameTiles)[j])[i]->SetImage((eImage)_sudoku[i][j]);
		}
	}
}

/***********************
* PlaceSudokuGUI: Reset the Sudoku grid to be empty
* @author: Callan Moore
* @return: void
********************/
void CGame::ResetSudokuGrid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			(*(*m_pVecGameTiles)[j])[i]->SetImage(IMAGE_BLANK);
		}
	}

	m_strSolveStatus = "UNSOLVED";
}

/***********************
* GenerateSudoku: all upon Lua to generate a solvable sudoku puzzle
* @author: Callan Moore
* @return: void
********************/
void CGame::GenerateSudoku()
{
	int sudoku_1D[81];
	int* sudoku_2D[9];

	// Create a 2D array for the sudoku grid
	for (int i = 0; i < 9; i++)
	{
		int* row = new int[9];
		sudoku_2D[i] = row;
	}

	// Prime the lua environment
	lua_pcall(m_pLuaState, 0, 0, 0);

	lua_getglobal(m_pLuaState, "GenerateSudoku");
	lua_newtable(m_pLuaState);

	// Add the Sudoku 1D table to the stack for use in Lua
	for (int i = 1; i < sizeof(sudoku_1D) / sizeof(*sudoku_1D) + 1; i++)
	{
		lua_pushinteger(m_pLuaState, i);
		lua_pushinteger(m_pLuaState, sudoku_1D[i - 1]);
		lua_settable(m_pLuaState, -3);
	}

	// Call the Lua function
	lua_pcall(m_pLuaState, 1, 1, 0);
	
	StackDump(m_pLuaState);

	int value = 0;
	int index = 0;
	lua_pushnil(m_pLuaState);
	// Retrieve all table elements in a 1D array
	while (lua_next(m_pLuaState, -2)) {
		value = (int)lua_tonumber(m_pLuaState, -1);
		lua_pop(m_pLuaState, 1);
		index = (int)lua_tonumber(m_pLuaState, -1);

		sudoku_1D[index - 1] = value;
	}

	ConvertTo2D(sudoku_1D, sudoku_2D);

	PlaceSudokuGUI(sudoku_2D);

	// Delete the allocated memory
	for (int i = 0; i < 9; i++)
	{
		delete[] sudoku_2D[i];
	}

	// Reset the stack pointer
	lua_settop(m_pLuaState, 0);
}

/***********************
* StackDump: Creates a Stack dump in the console window of the lua stack
* @author: Callan Moore
* @parameter: _pLuaState: The current Lua State
* @return: void
********************/
void CGame::StackDump(lua_State* _pLuaState)
{
	int iTopIndex = lua_gettop(_pLuaState);

	for (int i = 1; i <= iTopIndex; i++)
	{
		int iType = lua_type(_pLuaState, i);

		switch (iType)
		{
			case LUA_TSTRING:  // strings 
			{
				printf("`%s'", lua_tostring(_pLuaState, i));
			}
			break;
			case LUA_TBOOLEAN:  // booleans
			{
				printf(lua_toboolean(_pLuaState, i) ? "true" : "false");
			}
			break;
			case LUA_TNUMBER:  // numbers
			{
				printf("%g", lua_tonumber(_pLuaState, i));
			}
			break;
			default:  // other values
			{
				printf("%s", lua_typename(_pLuaState, iType));
			}
			break;
		}
		printf("  ");  // put a separator
	}
	printf("\n");  // end the listing
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


