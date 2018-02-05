(1) the general problem you are trying to solve:
The main.c program will read infor.txt file, which stored the records. Then,
main.c program will generate data.bin and index.bin file. If there is a
permission issue, you need to use chmod 777 to change files' permission.
binarySearch.c program will use index.bin and data.bin to perform binary search
and output data to std out.

(2) what are the assumptions and limitations of your solution:
1. When run main.c program again, you have to delete data.bin and index.bin
first.
2. When run binarySearch.c program, there must be data.bin and index.bin there.
3. The records cannot be more than 20. Since I defined array as 20 elements.
4. You need to edit infor.txt file in the Windows OS, because the infor file
has to end with \r\n. Or you can add one more character at end of each line
under Linux OS.

(3) how can a user build and test your program (also called the user guide):
1. open terminal in the folder and type gcc -Wall -std=c99 main.c
2. type ./a.out to generate data.bin and index.bin.
3. then type gcc -Wall -std=c99 binarySearch.c
4. type ./a.out to run the program.
5. type the name you want to search, or Q for quit.

(4) how is the program tested for correctness:
1. Use Virgrand to make sure there is no memory leak.
2. Test couple times with option Q, option not found, and option name in the
file.

(5) what possible improvements could be done if you were to do it again or have
extra time available.
1. dynamically allocated memory for the int array so it can store as many
records as user wants.
2. add if statements to check \r\n or \n in order to make the program run in
different environment.
3. dynamically allocated memory for string, so user can add as long string as
he wants.
