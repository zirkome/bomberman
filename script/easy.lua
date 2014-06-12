iaLaunch(thisptr)
iaX,iaY = iaGetPos(thisptr)
xMap, yMap = iaGetSizeMap(thisptr)
map = { }

print(xMap .. "/" .. yMap);

round = function (num, dec)
  local mult = 10^(dec or 0)
  return math.floor(num * mult + 0.5) / mult
end

markSquare = function (i, j, range)
  local it, line, square

  -- Down
  it = 1
  while it <= range do
    line = map[i + it]
    if line == nil then break end
    square = line[j]
    if square == nil then break end
    if square == 2 then break end
    if square ~= 3 then map[i + it][j] = "D" end
    it = it + 1
  end
  -- Up
  it = 1
  while it <= range do
    line = map[i - it]
    if line == nil then break end
    square = line[j]
    if square == nil then break end
    if square == 2 then break end
    if square ~= 3 then map[i - it][j] = "D" end
    it = it + 1
  end
  -- Left
  it = 1
  while it <= range do
    line = map[i]
    if line == nil then break end
    square = line[j + it]
    if square == nil then break end
    if square == 2 then break end
    if square ~= 3 then map[i][j + it] = "D" end
    it = it + 1
  end
  -- Right
  it = 1
  while it <= range do
    line = map[i]
    if line == nil then break end
    square = line[j - it]
    if square == nil then break end
    if square == 2 then break end
    if square ~= 3 then map[i][j - it] = "D" end
    it = it + 1
  end
end

markDanger = function (range)
  local i, j

  i = 1
  while i < xMap + 1 do
    j = 1
    while j < yMap do
      if map[i][j] == 3 then
        markSquare(i, j, range)
      end
      j = j + 1
    end
    i = i + 1
  end
end


printMap = function () 
  local i, j

  i = 1
  while i < yMap + 1 do
    j = 1
    while j < xMap do
      if map[i][j] == "D" then
        io.write("\27[0;32m" .. map[i][j] .. "\27[0;0m |");
      elseif map[i][j] < 10 then
        io.write(map[i][j] .. " |");
      else
        io.write(map[i][j] .. "|")
      end
      j = j + 1
    end
    print("")
    i = i + 1
  end
  print("====================================================\n")
end

-- Update the current map, add the dangerous zones and print it

updateMap = function ()
  local i, j = 1, 1

  while i <= yMap do
    map[i] = { }
    j = 1
    while j <= xMap do
      map[i][j] = iaGetMap(j - 1, i - 1, thisptr)
      j = j + 1;
    end
    i = i + 1;
  end 
end

math.randomseed(os.time())

dropBomb = function ()
  local x, y = iaGetPos(thisptr)

  x = round(x)
  y = round(y)
  print("x = " .. x .. " y = " .. y)
  iaAction(5, thisptr)
  map[y + 1][x + 1] = 3
end

-- Functions for moving step by step

getUp = function (x, y) return map[y + 2][x + 1] end
getDown = function (x, y) return map[y][x + 1] end
getLeft = function (x, y) return map[y + 1][x + 2] end
getRight = function (x, y) return map[y + 1][x] end
stop = function () iaAction(0, thisptr) end

left = function ()
  local xBeg, yBeg = iaGetPos(thisptr)
  xBeg = round(xBeg)
  yBeg = round(yBeg)
  if getLeft(xBeg, yBeg) == 10 or getLeft(xBeg, yBeg) == 7 then
    local x, y = iaGetPos(thisptr)
    x = math.floor(x)  
    while x < xBeg + 1 do
      iaAction(4, thisptr)
      x, y = iaGetPos(thisptr)
      x = math.floor(x)
    end
  end
  stop()
end


right = function ()
  local xBeg, yBeg = iaGetPos(thisptr)
  xBeg = round(xBeg)
  yBeg = round(yBeg)
  if getRight(xBeg, yBeg) == 10 or getRight(xBeg, yBeg) == 7 then
    local x, y = iaGetPos(thisptr)
    x = math.ceil(x)
    while x > xBeg - 1 do
      iaAction(3, thisptr)
      x, y = iaGetPos(thisptr)
      x = math.ceil(x)
    end
  end
  stop()
end

up = function ()
  local xBeg, yBeg = iaGetPos(thisptr)
  xBeg = round(xBeg)
  yBeg = round(yBeg)
  print("xBeg = " ..xBeg .. " yBeg = " .. yBeg)
  print(getUp(xBeg, yBeg))
  if getUp(xBeg, yBeg) == 10 or getUp(xBeg, yBeg) == 7 then
    local x, y = iaGetPos(thisptr)
    y = math.floor(y)    
    while y < yBeg + 1 do
      iaAction(1, thisptr)
      x, y = iaGetPos(thisptr)
      y = math.floor(y)
    end
  end
  stop()
end

down = function ()
  local xBeg, yBeg = iaGetPos(thisptr)
  xBeg = round(xBeg)
  yBeg = round(yBeg)
  if getDown(xBeg, yBeg) == 10 or getDown(xBeg, yBeg) == 7 then
    local x, y = iaGetPos(thisptr)
    y = math.ceil(y)    
    while y > yBeg - 1 do
      iaAction(2, thisptr)
      x, y = iaGetPos(thisptr)
      y = math.ceil(y)
    end
  end
  stop()
end

moves = {up, down, right, left}
bombRange = 1

print('[Lua] Hello i\'m  in (' .. iaX .. ', ' .. iaY .. ')')
print('Map size is : ' .. xMap .. "/" .. yMap)
print('Map is : ')

updateMap()
printMap()

dropBomb()
markDanger(bombRange)
printMap()

-- Si on est en zone de danger, en sortir (diagonales)
-- Sinon on cherche des cases autour à casser
-- on pose une bombe on se recule et on va choper le bonus
-- si on voit un autre joueur on essaie d'aller vers lui, dropBomb et de s'en aller


-- while 1 do
--   dir = math.random(1, 4);
--   print("Dir = " .. dir)
--   moves[dir]();
--   iaX, iaY = iaGetPos(thisptr)
--   print('[Lua] Hello i\'m  in (' .. iaX .. ', ' .. iaY .. ')')
-- end
