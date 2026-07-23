function Dump(o)
  if type(o) == 'table' then
    local s = '{ '
    for k, v in pairs(o) do
      if type(k) ~= 'number' then k = '"' .. k .. '"' end
      s = s .. '[' .. k .. '] = ' .. Dump(v) .. ','
    end
    return s .. '} '
  else
    return tostring(o)
  end
end

function Debug(o)
  print(Dump(o))
end

local file = io.open("input.txt", "r")
if not file then
  os.exit(1)
end
local content = file:read("*a")
file:close()

local seeds = {}
local map_blocks = {}
local curr_block_idx = 0

for line in string.gmatch(content, "(.-)\n") do
  if string.sub(line, 0, 5) == "seeds" then
    for seed_num in string.gmatch(line, "%d+") do
      table.insert(seeds, tonumber(seed_num))
    end
  elseif string.match(line, "^[a-z]") then
    curr_block_idx = curr_block_idx + 1
    map_blocks[curr_block_idx] = {}
  elseif string.match(line, "^%d") then
    local dst, src, range = string.match(line, "(%d+) (%d+) (%d+)")

    local from = tonumber(src)
    local to = from + tonumber(range)
    local offset = tonumber(dst) - from

    table.insert(map_blocks[curr_block_idx], {
      b = from,
      e = to,
      offset = offset
    })
  end
end

local function solve1()
  local lowest = nil

  for _, seed in ipairs(seeds) do
    for _, block in ipairs(map_blocks) do
      for _, mapping in ipairs(block) do
        if mapping.b <= seed and seed < mapping.e then
          seed = seed + mapping.offset
          break
        end
      end
    end
    if lowest == nil or seed < lowest then
      lowest = seed
    end
  end

  print(lowest)
end

local function overlap(range, mapping)
  local overlapped = {}
  local rest = {}

  local olap = {
    b = math.max(range.b, mapping.b),
    e = math.min(range.e, mapping.e)
  }

  if (olap.b < olap.e) then
    table.insert(overlapped, {
      b = olap.b + mapping.offset,
      e = olap.e + mapping.offset
    })

    if olap.b > range.b then
      table.insert(rest, { b = range.b, e = olap.b })
    end
    if olap.e < range.e then
      table.insert(rest, { b = olap.e, e = range.e })
    end
  else
    rest = range
  end

  return overlapped, rest
end

local function solve2()
  local r_seeds = {}
  for i = 1, #seeds, 2 do
    table.insert(r_seeds, {
      b = seeds[i],
      e = seeds[i] + seeds[i + 1]
    })
  end

  for _, block in ipairs(map_blocks) do
    local next = {}

    while #r_seeds > 0 do
      local seed_range = table.remove(r_seeds)
      local found = false

      for _, mapping in ipairs(block) do
        local overlapped, rest = overlap(seed_range, mapping)
        if #overlapped > 0 then
          found = true
          for _, v in ipairs(overlapped) do
            table.insert(next, v)
          end
          for _, v in ipairs(rest) do
            table.insert(r_seeds, v)
          end
        end
      end
      if not found then
        table.insert(next, seed_range)
      end
    end

    r_seeds = next
  end

  local lowest = nil
  for _, seed_range in ipairs(r_seeds) do
    if lowest == nil or seed_range.b < lowest then
      lowest = seed_range.b
    end
  end

  print(lowest)
end

solve1()
solve2()
