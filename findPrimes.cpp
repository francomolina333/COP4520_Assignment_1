#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <numeric>

std::vector<int> primes;
std::mutex mtx;

// Function to check if a number is prime
bool isPrime(int num)
{
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to find primes within a range
void findPrimes(int start, int end)
{
    for (int i = start; i <= end; i += 2)
    {
        if (isPrime(i))
        {
            mtx.lock();
            primes.push_back(i);
            mtx.unlock();
        }
    }
}

int main()
{
    // Get starting time
    auto start = std::chrono::high_resolution_clock::now();

    // Set the range and number of threads
    int range = 100000000;
    int num_threads = 8;

    // Divide the range into equal parts for each thread
    int interval = range / num_threads;

    findPrimes(2, 2);
    // Create threads
    std::vector<std::thread>
        threads;
    for (int i = 0; i < num_threads; i++)
    {
        int start_range = i * interval + 1;
        int end_range = (i + 1) * interval;
        threads.push_back(std::thread(findPrimes, start_range, end_range));
    }

    // Join all threads
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Get ending time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate total execution time, number of primes found and sum of all primes
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    int num_primes = primes.size();
    unsigned long int sum_primes = std::accumulate(primes.begin(), primes.end(), 0ll);
    int maxPrimes[10];
    int j = 9;
    for (int i = primes.size() - 1; i >= (primes.size() - 10); i--)
    {
        maxPrimes[j] = primes[i];
        j--;
    }

    // Print the output to a file
    std::ofstream outfile("primes.txt");
    outfile << duration << " " << num_primes << " " << sum_primes;
    for (int i = 0; i < 10; i++)
    {
        outfile << " " << maxPrimes[i];
    }
    outfile << std::endl;
    outfile.close();

    return 0;
}
