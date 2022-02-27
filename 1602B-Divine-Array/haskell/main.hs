import Prelude hiding (lookup)
import Data.Char
import Data.List hiding (lookup)
import Data.Map (fromList, insertWith, lookup)
import System.IO
 
fromJust :: Maybe a -> a
fromJust (Just a) = a
fromJust _ = undefined
 
getWord' :: String -> IO (String)
getWord' "" = do ch <- getChar ; eof <- isEOF
                 if eof then return "" else if isSpace ch then getWord' "" else getWord' [ch]
getWord' chs = do ch <- getChar ; eof <- isEOF
                  if eof then return chs else if isSpace ch then return chs else getWord' (chs ++ [ch])
 
getWord = getWord' ""
 
getInt :: IO (Int)
getInt = fmap read getWord
 
getInts' 0 acc = return acc
getInts' n acc = do x <- getInt ; getInts' (n-1) (acc ++ [x])
 
getInts :: Int -> IO ([Int])
getInts n = getInts' n []
 
-- SOLUTION
 
count xs = foldl f (fromList []) xs
           where f acc x = insertWith (+) x 1 acc
 
iter xs = map f xs
          where f x = fromJust (lookup x (count xs))
 
data Query = Query {
      posQuery :: Int
    , kQuery :: Int
    , idxQuery :: Int
    } deriving (Show)
 
type QResult = (Query, Int)
 
getQuery i n xs | i == n = return xs
getQuery i n xs = do
    idx <- getInt
    k <- getInt
    getQuery (i+1) n (xs ++ [Query i k (idx-1)])
 
 
getQueries = do
    q <- getInt
    getQuery 0 q []
 
 
 
sortQueries qs f = sortBy compareQueries qs
                 where compareQueries a b = compare (f a) (f b)
sortByK qs = sortQueries qs kQuery
 
sortResults qs = sortBy f qs
                 where f (a, _) (b, _) = compare (posQuery a) (posQuery b) 
 
calcQueries :: [Query] -> [Int] -> Int -> Int -> [QResult] -> [QResult]
calcQueries [] _ _ _ res = res
calcQueries (q:qs) xs k n res 
    | (k == (kQuery q)) || (k >= n) = calcQueries qs xs k n (res ++ [(q, xs !! (idxQuery q))])
calcQueries qs xs k n res = calcQueries qs (iter xs) (k+1) n res
 
 
putRes :: QResult -> IO ()
putRes res = do putStrLn (show (snd res))
 
forEach :: [a] -> (a -> IO ()) -> IO ()
forEach [] _ = return ()
forEach (x:xs) a = do a x; forEach xs a
 
--2
isqrt :: Int -> Int
isqrt = floor . sqrt . fromIntegral
 
maxK n = 2 * (isqrt (2*n))
 
iterNums :: [[Int]] -> Int -> [[Int]]
iterNums rs target | ((length rs)-1) < target = iterNums (rs ++ [iter (last rs)]) target
iterNums rs target = rs
 
getRes :: [[Int]] -> Int -> Int -> Int
getRes rs idx k = (rs !! k) !! (idx-1)
 
doQuery :: [[Int]] -> Int -> Int -> IO ()
doQuery _ _ 0 = return ()
doQuery rs mK i = do
    idx <- getInt
    k <- getInt
    let nk = min k mK
    let nrs = iterNums rs nk
    putStrLn (show (getRes nrs idx nk))
    doQuery nrs mK (i-1)
 
loop :: IO () -> Int -> IO ()
loop a 0 = return ()
loop a n = do a; loop a (n-1)
 
doTests 0 = return ()
doTests t = do
    n <- getInt
    nums <- getInts n
    q <- getInt
    doQuery [nums] (maxK n) q
    doTests (t-1)
 
 
main = do t <- getInt ; doTests t
