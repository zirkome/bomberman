newLObjectif = function(x, y, thisptr)
      z = math.random(1, 7)
      if z == 1 then
      	 iaAction(5, thisptr)
      end
      xMap, yMap = iaGetSizeMap(thisptr)
      rayon = 5
      i = 0
      while i < rayon do
      	  z = iaGetMap(x - i, y - i, thisptr)
      	  if z == 2 then
	     return x + rayon, y + rayon
	  end
	  if z == 6 then
	     return x - i, y - i
	  end
      	  z = iaGetMap(x - i, y, thisptr)
      	  if z == 2 then
	     return x + rayon, y + rayon
	  end
	  if z == 6 then
	     return x - i, y
	  end
      	  z = iaGetMap(x - i, y + i, thisptr)
      	  if z == 2 then
	     return x + rayon, y - rayon
	  end
	  if z == 6 then
	     return x - i, y + i
	  end
      	  z = iaGetMap(x, y - i, thisptr)
      	  if z == 2 then
	     return x + rayon, y + rayon
	  end
	  if z == 6 then
	     return x, y - i
	  end
      	  z = iaGetMap(x, y, thisptr)
      	  if z == 2 then
	     return x + rayon, y + rayon
	  end
	  if z == 6 then
	     return x, y
	  end
      	  z = iaGetMap(x, y + i, thisptr)
      	  if z == 2 then
	     return x + rayon, y - rayon
	  end
	  if z == 6 then
	     return x, y + i
	  end
      	  z = iaGetMap(x + i, y - i, thisptr)
      	  if z == 2 then
	     return x - rayon, y + rayon
	  end
	  if z == 6 then
	     return x + i, y - i
	  end
      	  z = iaGetMap(x + i, y, thisptr)
      	  if z == 2 then
	     return x - rayon, y + rayon
	  end
	  if z == 6 then
	     return x + i, y
	  end
      	  z = iaGetMap(x + i, y + i, thisptr)
      	  if z == 2 then
	     return x - rayon, y - rayon
	  end
	  if z == 6 then
	     return x + i, y + i
	  end
      	  i = i + 1
      end
      return x+rayon, y+rayon
end

newObjectif = function(x, y, goX, goY, thisptr)
      a = iaGetMap(x-1, y, thisptr)
      b = iaGetMap(x+1, y, thisptr)
      c = iaGetMap(x, y+1, thisptr)
      d = iaGetMap(x, y-1, thisptr)
      if x > goX and y > goY then
      	 if d > 2 then
             return x, y-1
      	 end
      	 if a > 2 then
             return x-1, y
      	 end
      	 if c > 2 then
             return x, y+1
      	 end
      	 if b > 2 then
             return x+1, y
      	 end
      end
      if x < goX and y < goY then
      	 if b > 2 then
             return x+1, y
      	 end
      	 if c > 2 then
             return x, y+1
      	 end
      	 if a > 2 then
             return x-1, y
      	 end
      	 if d > 2 then
             return x, y-1
      	 end
      end
      if x < goX or y > goY then
      	 if b > 2 then
             return x+1, y
      	 end
      	 if d > 2 then
             return x, y-1
      	 end
      	 if a > 2 then
             return x-1, y
      	 end
      	 if c > 2 then
             return x, y+1
      	 end
      end
      if x > goX or y < goY then
      	 if a > 2 then
             return x-1, y
      	 end
      	 if c > 2 then
             return x, y+1
      	 end
      	 if b > 2 then
             return x+1, y
      	 end
      	 if d > 2 then
             return x, y-1
      	 end
      end

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
      return x, y
end

goToObjectif = function(objectifX, objectifY, x, y)
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
lObjectifX = math.floor(x)
lObjectifY = math.floor(y)
mov = 0
while 1 do
      x,y = iaGetPos(thisptr)
      io.write('[Lua] IA action at <' .. x .. ', ' .. y .. '> dir <' .. objectifX .. ', ' .. objectifY .. '> lDir <' .. lObjectifX .. ', ' .. lObjectifY .. '>\n')
      if math.floor(x) == lObjectifX and math.floor(y) == lObjectifY then
	   lObjectifX, lObjectifY = newLObjectif(math.floor(x), math.floor(y), thisptr)
      end
      if math.floor(x) == objectifX and math.floor(y) == objectifY then
	   objectifX, objectifY = newObjectif(math.floor(x), math.floor(y), lObjectifX, lObjectifY, thisptr)
      end
      mov = goToObjectif(objectifX, objectifY, x, y)
      iaAction(mov, thisptr)
end
