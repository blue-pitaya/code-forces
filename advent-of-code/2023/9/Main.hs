{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Avoid lambda" #-}

import Data.Char (digitToInt, isDigit)
import Data.List (isPrefixOf)

getDiffs :: [Int] -> [Int]
getDiffs nums = f nums []
  where
    f (a : b : rest) diffs = f (b : rest) ((b - a) : diffs)
    f _ diffs = reverse diffs

getNextNum :: [Int] -> Int
getNextNum nums = f [] nums
  where
    f lastNums nums = if all (== 0) nums then sum lastNums else f lastNums' diffs
      where
        lastNums' = last nums : lastNums
        diffs = getDiffs nums

getNextNum2 :: [Int] -> Int
getNextNum2 nums = f [] nums
  where
    f firstNums nums = if all (== 0) nums then foldl (\acc x -> x - acc) 0 firstNums else f firstNums' diffs
      where
        firstNums' = head nums : firstNums
        diffs = getDiffs nums

solve1 :: String -> Int
solve1 line = getNextNum (map read (words line))

solve2 :: String -> Int
solve2 line = getNextNum2 (map read (words line))

main :: IO ()
main = do
  fileContent <- readFile "input.txt"
  let lines' = lines fileContent
  let result = sum (map solve1 lines')
  let result2 = sum (map solve2 lines')
  print result
  print result2
