-- Local Includes
dofile("lib1.lua")

--[[ 	Demonstation of a block comment
		Also the programming ritual ]]
print("Programming Ritual");
a = "Hello";
b = "World";
c = a .. " " .. b;
print(c);
print("");

-- Demonstrating the use of a included file
print("Printing using a included file");
n = norm(3.4, 1.0);
print("n = ", twice(n));
print("");

-- Showing global variables do not need declaration
print("Showing global variable declaration");
print("x = ",x);
x = 10;
print("x = ",x);
print("");

--[[ 	Assigning nil to a variable to make lua behave
		like the variable has never been used ]]
print("nil assigned variable");
x = nil;
print("x = ",x);
print("");

-- Printing out the types of the values
print("Printing using Type function")
print("Hello World = ", type("Hello World"));
print("10.4*3 = ", type(10.4*3));
print("print = ", type(print));
print("type = ", type(type));
print("true = ", type(true));
print("nil = ", type(nil));
print("");

-- Strings in lua
print("Strings in lua");
a = "One String";
b = string.gsub(a, "One", "Another");
print("a = ", a);
print("b = ", b);
