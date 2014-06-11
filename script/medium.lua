iaLaunch(thisptr)
iaX,iaY = iaGetPos(thisptr)
print('[Lua] Hello i\'m  in (' .. iaX .. ', ' .. iaY .. ')')
forward = function () iaAction(1, thisptr) end
backward = function () iaAction(2, thisptr) end
right = function () iaAction(3, thisptr) end
left = function () iaAction(4, thisptr) end

moves = {forward, backward, right, left}
math.randomseed(os.time())

xMap, yMap = iaGetSizeMap(thisptr)
map = { }

print(xMap .. "/" .. yMap);

function updateMap()
  print("=======================\n")
  local i = 1
  while i <= yMap do
  	map[i] = { }
  	local j = 1
  	io.write('|')
  	while j <= xMap do
  		map[i][j] = iaGetMap(j - 1, i - 1, thisptr)
  		if map[i][j] < 10 then
  			io.write(map[i][j] .. " |")
  		else
  			io.write(map[i][j] .. "|")
  		end
  		j = j + 1;
  	end
  	i = i + 1;
  	io.write('\n')
  end
  print("\n=======================")
end

iaAction(5, thisptr)
updateMap()
