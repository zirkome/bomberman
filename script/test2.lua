iaLaunch(thisptr)
io.write('[Lua] Hello,\n')
x,y = iaGetPos(thisptr)
z = iaGetMap(2, 2, thisptr)
io.write('[Lua] IA create at <' .. x .. ', ' .. y .. '> : ' .. z .. '\n')
a = x
b = y
mov = 1
while 1 do
      x,y = iaGetPos(thisptr)
      if x == a and y == b then
      	 if mov == 1 then
	   mov = 2
	 elseif mov == 2 then
	   mov = 4
	 elseif mov == 3 then
	   mov = 1
	 elseif mov == 4 then
	   mov = 3
	 end
      end
      iaAction(mov, thisptr)
      a = x
      b = y
end
