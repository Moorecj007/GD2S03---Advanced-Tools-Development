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
a = io.read("*n") -- reads a number
print(fact(a))

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

