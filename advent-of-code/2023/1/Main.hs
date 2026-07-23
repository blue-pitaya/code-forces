import Data.Char (digitToInt, isDigit)
import Data.List (isPrefixOf)

getDigits :: String -> [Int]
getDigits line = map digitToInt (filter isDigit line)

getFunkyDigits :: String -> [Int]
getFunkyDigits line = f line []
  where
    f [] acc = reverse acc
    f line acc
      | "one" `isPrefixOf` line = next (1 : acc)
      | "two" `isPrefixOf` line = next (2 : acc)
      | "three" `isPrefixOf` line = next (3 : acc)
      | "four" `isPrefixOf` line = next (4 : acc)
      | "five" `isPrefixOf` line = next (5 : acc)
      | "six" `isPrefixOf` line = next (6 : acc)
      | "seven" `isPrefixOf` line = next (7 : acc)
      | "eight" `isPrefixOf` line = next (8 : acc)
      | "nine" `isPrefixOf` line = next (9 : acc)
      | isDigit fst = next (digitToInt fst : acc)
      | otherwise = next acc
      where
        fst = head line
        next = f (tail line)

solve :: (String -> [Int]) -> [String] -> Int
solve getDigits = sum . map f
  where
    f line = (head digits * 10) + last digits
      where
        digits = getDigits line

main :: IO ()
main = do
  fileContent <- readFile "input.txt"
  _ <- print (solve getDigits (lines fileContent))
  _ <- print (solve getFunkyDigits (lines fileContent))
  print "One, armani suits and run!"
