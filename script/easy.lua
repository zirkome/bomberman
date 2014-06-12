iaLaunch(thisptr)
iaX,iaY = iaGetPos(thisptr)
xMap, yMap = iaGetSizeMap(thisptr)
map = { }
bombRange = 1

print(xMap .. "/" .. yMap);

round = function (num, dec)
  local mult = 10^(dec or 0)
  return math.floor(num * mult + 0.5) / mult
end

roundCoord = function (x, y)
  return round(x), round(y)
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
  map[i][j] = "D"
end

-- Add the danger zones according to bomb's range

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

-- Print the map

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

-- Update the current map, add the dangerous zones

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
  markDanger(bombRange)
end

math.randomseed(os.time())

dropBomb = function ()
  local x, y = iaGetPos(thisptr)

  x = round(x)
  y = round(y)
  iaAction(5, thisptr)
  map[y + 1][x + 1] = 3
  markDanger(bombRange)
end

-- Functions for moving step by step

getSquare = function (x, y)
  local line = map[y + 1]
  local square

  if line == nil then return -1 end
  square = line[x + 1]
  if square == nil then return -1 end
  return map[y + 1][x + 1]
end

getUp = function (x, y) return getSquare(x, y + 1) end
getDown = function (x, y) return getSquare(x, y - 1) end
getLeft = function (x, y) return getSquare(x + 1, y) end
getRight = function (x, y) return getSquare(x - 1, y) end
stop = function () iaAction(0, thisptr) end

left = function ()
  local xBeg, yBeg = roundCoord(iaGetPos(thisptr))

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
  local xBeg, yBeg = roundCoord(iaGetPos(thisptr))


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
  local xBeg, yBeg = roundCoord(iaGetPos(thisptr))

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
  local xBeg, yBeg = roundCoord(iaGetPos(thisptr))
  
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
squares = {getUp, getDown, getRight, getLeft}

-- Avoiding bombs

isInDanger = function (x, y)
  return getSquare(x, y) == "D"
end

escapeDanger = function (x, y)
  local square

  while isInDanger(x, y) do
    square = getUp(x, y)
    if square == 10 or square == 7 then return up() end
    square = getDown(x, y)
    if square == 10 or square == 7 then return down() end
    square = getLeft(x, y)
    if square == 10 or square == 7 then return left() end
    square = getRight(x, y)
    if square == 10 or square == 7 then return right() end

    -- Si on peux pas sortir imédiatement du danger, deplacement random
    moves[math.random(1, 4)]()

    x, y = roundCoord(iaGetPos(thisptr))
  end
end

-- Init the IA

print('[Lua] Hello i\'m  in (' .. iaX .. ', ' .. iaY .. ')')
print('Map size is : ' .. xMap .. "/" .. yMap)
print('Map is : ')

updateMap()
printMap()

it = 0
while 1 do
  local x, y = roundCoord(iaGetPos(thisptr))
  local dir

  if it % 10 == 0 then
    dropBomb()
  end

  updateMap()
  if isInDanger(x, y) then
    escapeDanger(x, y)
  end

  dir = math.random(1, 4)
  moves[dir]()
  while squares[dir](x, y) == "D" do
    dir = math.random(1, 4)
  end
  moves[dir]()
  it = it + 1
end
