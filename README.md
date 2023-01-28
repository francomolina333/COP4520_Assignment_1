# COP4520_Assignment_1
Assignment 1 for Parallel

To run findPrimes.cpp on cmd prompt, make sure you are in the same directory as the .cpp file. Run the command "g++ findPrimes.cpp" and then run the command "a".
The output will be printed to a file named primes.txt that will appear in the same directory as findPrimes.cpp. The format for the output will be:
<runtime in seconds><number of primes><sum of all primes><ten biggest primes in ascending order>

The program works by dividing the range (10^8) and dividing it into 8 threads. This allows the system to search for primes in parallel. 
