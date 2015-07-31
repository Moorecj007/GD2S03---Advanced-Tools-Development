
-- Print funtions
print("10 " + 1)	-- Converts string to numbber	-> 11
print("10 + 1")		-- Prints normal string			-> 10 + 1

-- .. is Concatenation
print(10 .. 20)		-- Expects strings and converts -> 1020



-- Conversion Functions
tonumber("10")		-- Converts string to number	-> 10
--tonumber("ten")		-- Invalid					-> nil


tableA = {}
for i = 0, 1000
	do tableA[i] = i*2
end

print(tableA[9])
--tableA["x"] = 10
--print(tableA.x)		-- Same as tableA["x"]
print(tableA["y"])


tableX = {}; tableX.x = 1; tableX.y = 0
tableY = {}; tableY.x = 1; tableY.y = 0
tableZ = tableX
print(tableZ == tableX)
print(tableX == tableY)


print(#tableA)
tableA[5] = nil
print(#tableA)

tableCheck = {}
tableCheck[1] = 2
tableCheck[2] = 2
tableCheck[5] = 3

print(#tableCheck)

