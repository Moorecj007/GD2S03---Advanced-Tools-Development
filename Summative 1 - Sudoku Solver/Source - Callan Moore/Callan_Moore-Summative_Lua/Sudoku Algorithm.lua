----------------
-- Bachelor of Software Engineering
-- Media Design School
-- Auckland
-- New Zealand
--
-- (c) 2005 - 2015 Media Design School
--
-- File Name : Sudoku Solver.lua
-- Description : Solves a sudoku puzzle
-- Author :	Callan Moore
-- Mail :	Callan.Moore@mediadesign.school.nz
----------------

---------------------------
-- RowNumExists: Check if a number already exists in a Row
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @parameter: row: Current row index
-- @parameter: num: Number to check (0-9)
-- @return: bool: true if the number already exists
--------------------
local function RowNumExists(sudoku, row, num)

	for col = 1, #sudoku do
		if (sudoku[row][col] == num) then
			return true;
		end
	end

	return false;
end

---------------------------
-- ColNumExists: Check if a number already exists in a Column
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @parameter: col: Current column index
-- @parameter: num: Number to check (0-9)
-- @return: bool: true if the number already exists
--------------------
local function ColNumExists(sudoku, col, num)

	for row = 1,#sudoku do
		if (sudoku[row][col] == num) then
			return true;
		end
	end

	return false;
end

---------------------------
-- RowNumExists: Checks a subsquare to check if a number aleady exists
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @parameter: row: Current row index
-- @parameter: col: Current column index
-- @parameter: num: Number to check (0-9)
-- @return: bool: true if the number already exists
--------------------
local function BoxNumExists(sudoku, row, col, num)

	row = math.floor((row - 1) / 3) * 3 + 1;
	col = math.floor((col - 1) / 3) * 3 + 1;

	for rowSubSquare = 0, 2 do
		for colSubSquare = 0, 2 do
			if sudoku[row + rowSubSquare][col + colSubSquare] == num then
				return true;
			end
		end
	end

	return false;
end

---------------------------
-- CanBeAssigned: Checks if number can be assigned to a slot within sudoku rules
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @parameter: row: Current row index
-- @parameter: col: Current column index
-- @parameter: num: Number to check (0-9)
-- @return: bool: true if the number can be assigned
--------------------
local function CanBeAssigned(sudoku, row, col, num)

	return (	not RowNumExists(sudoku, row, num)
			and not ColNumExists(sudoku, col, num)
			and not BoxNumExists(sudoku, row, col, num))
end

---------------------------
-- IsSolved: Checks if the whole sudoku is solved
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @return: bool: True if the sudoku is solved, false if not plus the first unnassigned slot
-- @return: number: Row number of first unnasigned slot
-- @return: number: Column number of first unnasigned slot
--------------------
local function IsSolved(sudoku)

	for row = 1, #sudoku do
		for col = 1, #sudoku do
			if sudoku[row][col] == 0 then
				return false, row, col;
			end
		end
	end

  return true
end


---------------------------
-- ConvertTo2D: Convert 1D Sudokutable into 2D
-- @author: Callan Moore
-- @parameter: tab_in: Sudoku Table in 1D form
-- @return: Table: Sudoku Table in 2D form
--------------------
local function ConvertTo2D(tab_in)

	tab_out = {}

	index = 1;
	for i = 1, 9 do

		row = {};

		for j = 1, 9 do

			row[j] = tab_in[index];
			index = index + 1;
		end

		tab_out[i] = row;
	end

	return tab_out;
end

---------------------------
-- ConvertTo1D: Convert 2D Sudoku table into 1D
-- @author: Callan Moore
-- @parameter: tab_in: Sudoku Table in 2D form
-- @return: Table: Sudoku Table in 1D form
--------------------
local function ConvertTo1D(tab_in)

	tab_out = {};
	index = 1;

	for i = 1, 9 do

		for j = 1, 9 do

			tab_out[index] = tab_in[i][j];
			index = index + 1;
		end

	end

	return tab_out
end

---------------------------
-- Solve: Solves the given sudoku with recursion and backtracking
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @return: bool: True if the sudoku is solved, false if it cannot be solved
-- @return: Table: The 2D sudoku table
--------------------
local function Solve(sudoku)

	local solved, row, col = IsSolved(sudoku);	-- Can return 3 values

	if solved then
		return true, sudoku;
	end

	for num = 1, #sudoku do

		if (CanBeAssigned(sudoku, row, col, num)) then

			sudoku[row][col] = num

			if Solve(sudoku) then
				return true, sudoku;
			end

			sudoku[row][col] = 0;
		end
	end


	return false, sudoku;
end

---------------------------
-- CheckValidity: Checks that the sudoku is a valid sudoku
-- @author: Callan Moore
-- @parameter: sudoku: 2D table of numbers (Sudoku Puzzle)
-- @return: bool: True if the sudoku is valid
--------------------
local function CheckValidity(sudoku)

	for row = 1, 9 do
		for col = 1, 9 do

			tempStore = sudoku[row][col];
			sudoku[row][col] = 0;

			if( tempStore ~= 0) then
				if (CanBeAssigned(sudoku, row, col, tempStore)) then
					sudoku[row][col] = tempStore;
				else
					sudoku[row][col] = tempStore;
					return false;
				end
			end
		end
	end

	return true;
end

---------------------------
-- BeginSolving: Begins the Solving of the sudoku
-- @author: Callan Moore
-- @parameter: sudoku: 1D table of numbers (Sudoku Puzzle)
-- @return: table: A 1D representation of the sudoku puzzle
--------------------
function BeginSolving(sudoku_1D)

	sudoku_2D = ConvertTo2D(sudoku_1D);

	valid = CheckValidity(sudoku_2D);

	if (valid == true) then
		solved, sudoku_2D = Solve(sudoku_2D);
	else
		solved = false;
	end

	sudoku_1D = ConvertTo1D(sudoku_2D);
	return solved, sudoku_1D;
end

---------------------------
-- GenerateSudoku: Generate a solvable sudoku puzzle
-- @author: Callan Moore
-- @parameter: sudoku: 1D table of numbers (Sudoku Puzzle)
-- @return: table: A 1D representation of the sudoku puzzle
--------------------
function GenerateSudoku(sudoku_1D)

	sudoku_2D = ConvertTo2D(sudoku_1D);

	-- create a table to store numbers 1-9
	tabBox = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	shuffleCount = math.random(10, 30);

	-- Shuffle the table numbers around
	for i = 1, shuffleCount do

		local index1 = math.random(1, #tabBox);
		local index2 = math.random(1, #tabBox);

		tabBox[index1], tabBox[index2] = tabBox[index2], tabBox[index1];
	end

	-- Fill the centre box with the numbers from the table
	index = 1
	for row = 4, 6 do
		for col = 4, 6 do

			sudoku_2D[row][col] = tabBox[index];
			index = index + 1;
		end
	end

	-- Solve the Sudoku
	solved, Sudoku_2D = Solve(sudoku_2D);

	-- Remove numbers in pairs to create a puzzle
	for i = 1, 45 do

		local randomRow = math.random(1, 9);
		local randomCol = math.random(1, 9);

		Sudoku_2D[randomRow][randomCol] = 0;
		Sudoku_2D[randomCol][randomRow] = 0;
	end

	sudoku_1D = ConvertTo1D(sudoku_2D);
	return sudoku_1D;
end

-- Seed to time and remove the first three numbers
math.randomseed(os.time());
math.random(); math.random(); math.random();
print("priming Run");