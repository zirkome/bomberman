iaLaunch(thisptr)
iaX,iaY = iaGetPos(thisptr)
xMap, yMap = iaGetSizeMap(thisptr)
map = { }
bombRange = 2

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
    if square == 2 or square == 0 then break end
    if square ~= 3 then map[i + it][j] = 11 end
    it = it + 1
  end
  -- Up
  it = 1
  while it <= range do
    line = map[i - it]
    if line == nil then break end
    square = line[j]
    if square == nil then break end
    if square == 2 or square == 0 then break end
    if square ~= 3 then map[i - it][j] = 11 end
    it = it + 1
  end
  -- Left
  it = 1
  while it <= range do
    line = map[i]
    if line == nil then break end
    square = line[j + it]
    if square == nil then break end
    if square == 2 or square == 0 then break end
    if square ~= 3 then map[i][j + it] = 11 end
    it = it + 1
  end
  -- Right
  it = 1
  while it <= range do
    line = map[i]
    if line == nil then break end
    square = line[j - it]
    if square == nil then break end
    if square == 2 or square == 0 then break end
    if square ~= 3 then map[i][j - it] = 11 end
    it = it + 1
  end
  -- map[i][j] = 11
end

-- Add the danger zones according to bomb's range

markDanger = function (range)
  local i, j

  i = 1
  while i <= yMap do
    j = 1
    while j <= xMap do
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
      if map[i][j] == 2 then
        io.write("\27[0;32m" .. map[i][j] .. "\27[0;0m  |");
      elseif map[i][j] == 0 then
        io.write("\27[0;31m" .. map[i][j] .. "\27[0;0m  |");
      elseif map[i][j] == 7 then
        io.write("\27[0;33m" .. map[i][j] .. "\27[0;0m  |");
      elseif map[i][j] == 1 then
        io.write("\27[0;34m" .. map[i][j] .. "\27[0;0m  |");
      elseif map[i][j] == 10 then
        io.write("\27[0;35m" .. map[i][j] .. "\27[0;0m |");
      elseif map[i][j] == 11 then
        io.write("\27[0;36m" .. map[i][j] .. "\27[0;0m |");
      elseif map[i][j] < 0 and map[i][j] > -10 then
        io.write(map[i][j] .. " |")
      elseif map[i][j] < 0 and map[i][j] <= -10 then
        io.write(map[i][j] .. "|")
      else
        io.write(map[i][j] .. "  |")  
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
  local x, y = roundCoord(iaGetPos(thisptr))

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
  local x, y = iaGetPos(thisptr)
  
  if getLeft(xBeg, yBeg) ~= 0 and getLeft(xBeg, yBeg) ~= 2 and getLeft(xBeg, yBeg) ~= 3 then
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
  local x, y = iaGetPos(thisptr)

  if getRight(xBeg, yBeg) ~= 0 and getRight(xBeg, yBeg) ~= 2 and getRight(xBeg, yBeg) ~= 3 then
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
  local x, y = iaGetPos(thisptr)

  if getUp(xBeg, yBeg) ~= 0 and getUp(xBeg, yBeg) ~= 2 and getUp(xBeg, yBeg) ~= 3 then
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
  local x, y = iaGetPos(thisptr)

  if getDown(xBeg, yBeg) ~= 0 and getDown(xBeg, yBeg) ~= 2 and getDown(xBeg, yBeg) ~= 3 then
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


-- PathFinding
-- add the ponderation to every points in the map

addPonderation = function (x, y, toFind, pond)
  local square = getSquare(x, y)

  if square == -1 or square == 2 or square == 0 or square == 3 or (square == toFind and pond ~= -1) then return end

  if square < pond or square > 0 then
    map[y + 1][x + 1] = pond
    addPonderation(x, y + 1, toFind, pond - 1)
    addPonderation(x, y - 1, toFind, pond - 1)
    addPonderation(x + 1, y, toFind, pond - 1)
    addPonderation(x - 1, y, toFind, pond - 1)
  else
    return 
  end 
end

-- return the minimum ponderation arround a point


findMinAdj = function (adj)
  local i = 1
  local min = 0

  while i <= #adj do
    if adj[i] < 0 then
      if adj[i] > min or min == 0 then
        min = adj[i]
      end 
    end
    i = i + 1
  end
  return min
end

-- return the x and y of the little ponderation to toFind (-1/-1) if notFound

findLittlePonderation = function (toFind)
  local i, j = 0, 0
  local min, x, y, pond = 0, -1, -1, -9

  while i < yMap do
    j = 0
    while j < xMap do
      if getSquare(j, i) == toFind then
        local minAdj
        adj = { }

        adj[1] = getSquare(j + 1, i)
        adj[2] = getSquare(j - 1, i)
        adj[3] = getSquare(j, i + 1)
        adj[4] = getSquare(j, i - 1)

        minAdj = findMinAdj(adj)
        if minAdj < 0 and (minAdj > min or min == 0) then
          min, x, y, pond = minAdj, j, i, minAdj
        end
      end
      j = j + 1
    end
    i = i + 1
  end
  return x, y, pond
end

-- forme the instruction list

formInstrList = function (x, y, pond)
  local list, i, square = { }, 1, -1
  
  while pond <= -1 do
    if getSquare(x - 1, y) == pond then
      x = x - 1
      list[i] = 4
    elseif getSquare(x + 1, y) == pond then
      x = x + 1
      list[i] = 3 
    elseif getSquare(x, y - 1) == pond then
      y = y - 1
      list[i] = 1
    elseif getSquare(x, y + 1) == pond then
      y = y + 1
      list[i] = 2
    end
    i = i + 1
    pond = pond + 1
  end
  updateMap() -- reset the map
  return list
end

-- Function for reaching a place, return true if the point can be reach false otherwise

goToFirst = function (toFind, xBeg, yBeg)
  map[yBeg + 1][xBeg + 1] = 5
  addPonderation(xBeg, yBeg, toFind, -1)

  xFind, yFind, pond = findLittlePonderation(toFind)
  if pond <= 0 and xFind ~= -1 and yFind ~= -1 then
    list = formInstrList(xFind, yFind, pond)

    it = #list
    while it >= 1 do
      iaX, iaY = roundCoord(iaGetPos(thisptr))
      updateMap()
      if (squares[list[it]](iaX, iaY) == 11 and isInDanger(xBeg, yBeg) == 0) or squares[list[it]](iaX, iaY) == 3 then
        return false
      end

      moves[list[it]]()
      it = it - 1
    end

    updateMap()
    return true
  end
  updateMap()
  return -1
end

-- Avoiding bombs

isInDanger = function (x, y)
  return getSquare(x, y) == 11 or getSquare(x, y) == 3
end

-- Init the IA

updateMap()
dropBomb()
it = 1
while true do
  iaX, iaY = roundCoord(iaGetPos(thisptr))

  if it % 15 == 0 then dropBomb() end

  if isInDanger(iaX, iaY) then
    goToFirst(10, iaX, iaY)
  end
  moves[math.random(1, 4)]()
  it = it + 1;
end
