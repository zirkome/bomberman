newObjectif = function(x, y, thisptr)
      z = math.random(1, 7)
      if z == 1 then
      	 iaAction(5, thisptr)
      end
      a = iaGetMap(x-1, y, thisptr)
      b = iaGetMap(x+1, y, thisptr)
      c = iaGetMap(x, y+1, thisptr)
      d = iaGetMap(x, y-1, thisptr)
      if a > 2 then
          return x-1, y
      end
      if b > 2 then
          return x+1, y
      end
      if c > 2 then
          return x, y+1
      end
      if d > 2 then
          return x, y-1
      end
      io.write('ret' .. a .. b .. c .. d .. '\n')
      return x, y
end

goToObjectif = function(objectifX, objectifY, x, y)
      io.write('[Lua] IA at <' .. x .. ', ' .. y .. '> obj <' .. objectifX .. ', ' .. objectifY .. '>\n')
      if objectifX < x then
      	 return 4
      end
      if objectifX > x then
      	 return 3
      end
      if objectifY < y then
      	 return 2
      end
      if objectifY > y then
      	 return 1
      end
      return 0
end

iaLaunch(thisptr)
io.write('[Lua] Hello,\n')
x,y = iaGetPos(thisptr)
io.write('[Lua] IA create at <' .. x .. ', ' .. y .. '>\n')
objectifX = math.floor(x)
objectifY = math.floor(y)
mov = 0
while 1 do
      x,y = iaGetPos(thisptr)
      if math.floor(x) == objectifX and math.floor(y) == objectifY then
	   objectifX, objectifY = newObjectif(math.floor(x), math.floor(y), thisptr)
      end
      mov = goToObjectif(objectifX, objectifY, x, y)
      iaAction(mov, thisptr)
end
