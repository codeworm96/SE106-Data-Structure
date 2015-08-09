(Given the various environment of coding (Windows/Linux/Mac OS), to avoid the confusing caused by encoding ,I choosed to use
ASCII charater only.
This is a file with markdown format.
It is better to use monospace font to read it , because it contains ASCII art.) :wq!
# Input Format 
Line 1: a integer n (0 <= n < 2000000), # of elements to sort
Line 2: n integers (which long can store) , the array to sort
# Output Format
n lines , one integer per line, the sorted array
# Simple Input
5
5 2 3 4 1
# Simple Output
1
2
3
4
5
# Note
using stdin & stdout (i.e. cin & cout)

# Note of implementation
## General
Mergesort: 
if a array's length is 0 or 1, it is sorted.
otherwise, we split it at middle , sorted the two parts and merge them into a sorted one.
## classic
To merge two arrays arr1 and arr2, we should put one element to the auxiliary array at a time.
Given both arr1 and arr2 is non-empty, if the head of arr1 is not greater than arr2, the head of arr1 is choosed.
otherwise, the head of arr2 is choosed to put into the auxiliary array.
if one of the two arrays is empty, we just append the other to the end of the auxiliary array.
At last, we move the merged array from the auxiliary array to the array to sort.
## inplace
In the inplace implementation , there is no auxiliary array. Instead, we use the part in the front of the array as a auxiliary array.
+----------+----------------+---------------------+
| merged   |   arr1         |     arr2            |
+----------+----------------+---------------------+
and we just preform what we did in the classic merge.it's easy to append the head of arr1.
But its not easy to append the head of arr2.so we just leave them at their orign places, until we have to append the head of arr1
Now, we get:
+----------+----------+---------+-----------------+
| merged   |   arr1   |  *      | arr2            |
+----------+----------+---------+-----------------+
Next we need to swap the arr1 and the (*).
it easy to reverse a array in place. so we just reverse arr1 , reverse * , reverse (arr1 + *). After 3 reverse operations:
+---------+-------+--------------+------------------------+
| merged  |  *    |  arr1        |             arr2       |
+---------+-------+--------------+------------------------+
which is just what we need.(you can check it!)
So, merge can be done in place.
But this implementation of merge is O(n^2), because there are O(n) calls of reserve, which is O(n).
With the master method, we can prove that the sort is O(n^2).
We cut down the space complexity, but the time complexity rises. We cannot get the two things at the same time.