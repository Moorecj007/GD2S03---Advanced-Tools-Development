_end = 6
End = 3
NULL = 0

-- defines a factorial function
function fact(n)
	if n < 0 then
		return nil
	elseif n == 0 then
		return 1
	else
		return n * fact(n-1)
	end
end

print("enter a number:")
--a = io.read("*n") -- reads a number
--print(fact(a))
a = 2

-- Local Includes
dofile("lib1.lua")

print(twice(a))
print(type(nil))
print(nil == nil)
print(type(nil) == type(nil))
print(type(nil) == "nil")

print(arg[0])


print(.0e12)
print("FAIL")
print("FAIL")
print(0x12)
print("FAIL")
print(0xFFFFFFF)

print(FFFF)
print(0xA)
print("FAIL")
print("FAIL")
print(0.1e1)
print("FAIL")

a = {}; a.a = a;
a.a.a.a = 3
print(a)
print(a.a)

for i = -11, 10 do
	print(i, i % 3)
end

print(2^3^4)
print(2^-3^4)

function CalcPolynomial(poly, xValue)
	result = 0
	for i = 1, #poly do
		result = result + poly[i] * (xValue^(i-1))
	end
	print(result)
end

function CalcPolynomial2(poly, xValue)
	result = 0
	for i = 1, #poly do
		xCalc = 1
		for j = 1, (i - 1) do
			xCalc = xCalc * xValue
		end
		result = result + poly[i] * xCalc
	end
	print(result)
end

poly = {5, 3, 2}
xValue = 2

CalcPolynomial(poly, xValue)
CalcPolynomial2(poly, xValue)



bCheck = 10

if( (bCheck == true) or (bCheck == false)) then
	print("True")
else
	print("False")
end


Sunday = "Monday"; Monday = "SundayMon"
t = {Sunday = "Monday", [Sunday] = Monday}
print(t.Sunday, t[Sunday], t[t.Sunday])


function AddToTable(Table, sequence, meaning)
	Table[#Table + 1] = sequence
	Table[sequence] = meaning
end

function PrintTable(Table)
	for i = 1, #Table do
		print(Table[i], Table[Table[i]])
	end
end

TableD = {apples = 10}
AddToTable(TableD, "/b", "Backspace");
AddToTable(TableD, "/r", "Return");
AddToTable(TableD, "/n", "New Line");

PrintTable(TableD)




























