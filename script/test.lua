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
	   mov = math.random(1, 4)

      iaAction(mov, thisptr)
      a = x
      b = y
end
