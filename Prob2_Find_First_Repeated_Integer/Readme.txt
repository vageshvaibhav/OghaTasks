ompilation and Application Usage:
For simplicity, I have kept most of the things in header file so we will have to just compile main source file containing main function
$ g++ --version
g++ (GCC) 4.9.1 20140922 (Red Hat 4.9.1-10)

2.Linux version and release:
$ cat /etc/centos-release
CentOS release 6.9 (Final)

3.Application Compilation:
$ g++ first_repeated_integer_large_file.cpp -std=c++14 -o RepeatedInteger


4.Algorithm and Time/Space complexity:
/* Read the data from the file. */
/* The logic is to :
 1) Read the input integer file line by line
 2) As contents of single file can not be loaded in to memory, hash every integer read to one of the intermediate files on the basic of modulo by 100(100 taken as default number)
 3) Now, get first repeating integer from each file independently along with the index. By doing this, we are reducing 
 number of elements loaded in to memory. This can be further reduced by increasing number of intermediate files to more than 100
 4) Finally merge all the results from small intermediate file to arrive to the final result i.e. first repeating integer

Note : 
 * Did not use parallel processing for getting first repeating from different intermediate files as that could have lead to loading
 * more data at once for gettting first repeating number from all intermediate files and finally merging the results to get best candidate using original index
 * This step can be run across independent distributed machines in parallel but since we are running on current machine only, so this is done sequentially to minimise memory load
 */

Time Complexity : O(n) for reading through large file once and breaking down to smaller files. O(n) for getting individual best candidate from temp files
and finally merging the results to get first repeating integer. So O(n)
Space complexity : O(n/number of files) for storing hashed data in temp files


5.Assumption:
I have taken the assumption that duplicate numbers in a huge 6 digit integers file will be  rare



6.Output and few sample test run:
input.txt is the input file read
$ ./RepeatedInteger input.txt
112346,0 written to temp file=output_46.txt
112233,1 written to temp file=output_33.txt
132435,2 written to temp file=output_35.txt
112346,3 written to temp file=output_46.txt
223344,4 written to temp file=output_44.txt
334455,5 written to temp file=output_55.txt
223344,6 written to temp file=output_44.txt
First repeating number is=112346
