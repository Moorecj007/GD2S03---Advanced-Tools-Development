/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Source.cpp
* Description : Integrates Lua and runs a sudoku solver using a Lua algorithm
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")

// Library Includes
#include "lua.hpp"
#include <iostream>
#include <stdlib.h>                       
#include <stdio.h>  
#include <string>
#include <conio.h>

// Function Prototypes
void retError(lua_State* _env, std::string _msg);

int main()
{
	int sudoku_1D[81];
	int* sudoku_2D[9];

	// Generate Sudoku Table

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

	// Convert to 1D array
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku_1D[index++] = sudoku_2D[i][j];
		}
	}
	

	lua_State* luaEnv;
	luaEnv = luaL_newstate();
	
	// Load the Lua libraries
	luaL_openlibs(luaEnv);
	
	// Load the lua script (but do NOT run it)
	if (luaL_loadfile(luaEnv, "Sudoku Algorithm.lua"))
	{
		retError(luaEnv, "luaL_loadfile() failed");
	}
	
	// Prime the lua environment
	if (lua_pcall(luaEnv, 0, 0, 0))
	{
		retError(luaEnv, "luaL_pcall() failed");
	}
	
	lua_getglobal(luaEnv, "BeginSolving");
	lua_newtable(luaEnv);
	
	// Add the Sudoku 1D table to the stack for use in Lua
	for (int i = 1; i < sizeof(sudoku_1D) / sizeof(*sudoku_1D) + 1; i++)
	{
		lua_pushinteger(luaEnv, i);
		lua_pushinteger(luaEnv, sudoku_1D[i - 1]);
		lua_settable(luaEnv, -3);
	}

	// Call the Lua function
	if (lua_pcall(luaEnv, 1, 2, 0))
	{
		retError(luaEnv, "luaL_pcall() failed");
	}

	// Retrieve the 1D table from Lua
	lua_pushnil(luaEnv);

	// Retrieve the boolean for if the puzzle was solvable
	lua_next(luaEnv, -2);
	int solved = lua_toboolean(luaEnv, -1);
	lua_pop(luaEnv, 1);

	int value = 0;
	index = 0;
	// Retrieve all table elements in a 1D array
	while (lua_next(luaEnv, -2)) {
		value = (int)lua_tonumber(luaEnv, -1);
		lua_pop(luaEnv, 1);
		index = (int)lua_tonumber(luaEnv, -1);

		sudoku_1D[index - 1] = value;
	}

	// Convert back to a 2D array
	index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku_2D[i][j] = sudoku_1D[index++];
		}
	}

	// Print the solution
	std::cout << "Solution Solvable: ";
	solved ? std::cout << "true" : std::cout << "false";
	std::cout << std::endl;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout <<sudoku_2D[i][j] << " ";
		}
		std::cout << std::endl;
	}

	lua_close(luaEnv);

	system("pause");
	return 0;
}

void retError(lua_State* _env, std::string _msg)
{
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n", _msg, lua_tostring(_env, -1));
	exit(1);
}