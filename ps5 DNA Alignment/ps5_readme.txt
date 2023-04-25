/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name:       Thomas O'Connor
Section:    202
Partner's name: N/A
Hours to complete assignment:   5 Hours

/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/

Used the Needleman-Wunsch method.
After calculating my matrix, I traversed the matrix top-left
to bottom-right: checking bottom, right, and diagonal boundaries
from previous coordinates and pushing back pairs of coordinates
into a list that were the minimum of the three, prioritizing
edge cases, then diagonals, then jumps.
After the complete traversal I had an ordered list of coordinates
for the ideal alignment, which I then parsed through. Using the previous
coordinates pair I was able to detect a jump, a diagonal, or a mismatched
diagonal by refrencing the input strings. The traversal of the strings
were then appended to an output string based on traversal type
(including jumps with dashes and mismatched characters with penalties).

/**********************************************************************
 * You are required to create one additional test case by hand. 
 * It should be constructed in such a way that you know the correct 
 * output before running your program on it, and it should be a 
 * "corner case" that helps check if your program handles all special 
 * situations correctly. Please list:
 * - a copy of the test case input
 * - the expected test case output
 * - whether your program ran correctly on it or not
 * - optionally, any other remarks
 **********************************************************************/
Input:

0123456789abcdz
1234567890zabcd

Expected output:

Edit distance = 8
0 - 2
1 1 0
2 2 0
3 3 0
4 4 0
5 5 0
6 6 0
7 7 0
8 8 0
9 9 0
- 0 2
- z 2
a a 0
b b 0
c c 0
d d 0
z - 2

What happened:

Correct output.
Testing for beginning shift, back to back shifts, ending with a shift,
shifts in both strings, and alphabetical characters with numeric characters.

Additionally I created an example15810.txt file to test out the
1gb memory space calculation. I was close to 1gb but went a little over.

/**********************************************************************
 *  How much main memory does your computer have?
 **********************************************************************/

8gb

/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 1GB (billion bytes) of memory?
 **********************************************************************/
a = 4
b = 2
largest N = 15,811 (without taking into account character allocations)
            15,810 (with character/string allocations)

In my implimentation I create an NxN matrix, simplifying to N^2.
Because this matrix is populated by ints, each item in the matrix
is 4 bytes, with additional small allocations for input strings
of approximately 4N bytes (2 strings of 2N bytes).

/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *  For help on how to do timing, see the checklist (e.g. -Xprof).
 *  If you get an OutOfMemoryError, see the checklist about -Xmx.
 *  If you get "Could not reserve enough space for object heap" or the timing
 *  of these tests takes too long for the last few test cases (N=20000 or higher), 
 *   note this, and skip filling out those rows of the table.
 **********************************************************************/

data file           distance       time (seconds)           storage (MB)
---------------------------------------------------------------------------
ecoli2500.txt       118             0.0777                  25.118MB
ecoli5000.txt       160             0.3060                  100.158MB
ecoli7000.txt       194             0.5927                  196.179MB
ecoli10000.txt      223             1.1215                  400.239MB
ecoli20000.txt      3135            5.1270                  1,600.401MB
ecoli28284.txt      8394            10.0525                 3,200.422MB
ecoli50000.txt      threw 'std::bad_array_new_length'
ecoli100000.txt     Segmentation fault


/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730

/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 1/50,000,000
b = 2
largest N = 2,078,461

Applying the doubling rule: for every doubling of the length N, the time
to completion is roughly 4x because the matrix expands by 4x the area.
Given that there are 86,400 seconds in a day, the algorithm will be
able to compute roughly a 2 million by 2 million matrix.

/**********************************************************************
 *  If you worked with a partner, do you have any remarks on the pair
 *  programming method? E.g., how many times did you switch, what are
 *  the tradeoffs of driving vs. navigating, etc.
 **********************************************************************/

N/A

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs, 
 *  classmates, past Computing IV students, or anyone else.
 **********************************************************************/

N/A

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

String input was variable depending on wether the file ended with
a third new line or terminated with the second string (2 total lines).
I had to impliment a check on input strings to ensure they both ended
with a alphanumeric character rather than an uneccesary terminating
character.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

CPU Speed:  4,000 MHz (4 GHz) while executing program
Added a new section to the chart detailing storage used in MB
Implimented using Needleman-Wunsch in a single c-array.
OS: 64-bit os running WSL Ubuntu subsystem
CPU type: 11th Gen Intel(R) Core(TM) i5-11400H @ 2.70GHz
