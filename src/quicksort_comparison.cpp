#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#define numberOfSamples 10
#define tests 5
using namespace std;

/*
 * Test System Specifications
 * RYZEN 9 5900HX @ 4.2 GHz 8 Core 16 Threads
 * RAM 16 GB DUAL CHANNEL @ 3200 MT/s
 */

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(0, 100000);
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition_right(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort_right(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_right(arr, low, high);
        quicksort_right(arr, low, pi - 1);
        quicksort_right(arr, pi + 1, high);
    }
}

int partition_middle(vector<int> &arr, int low, int high)
{
    int pivot = arr[(low + high) / 2];
    while (low <= high) {
        while (arr[low] < pivot)
            low++;
        while (arr[high] > pivot)
            high--;
        if (low <= high) {
            swap(&arr[low], &arr[high]);
            low++;
            high--;
        }
    }
    return low;
}

void quicksort_middle(vector<int> &arr, int low, int high)
{

    if (low < high)
    {
        int pi = partition_middle(arr, low, high);
        quicksort_middle(arr, low, pi - 1);
        quicksort_middle(arr, pi, high);
    }
}

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int randomized_partition(vector<int> &arr, int low, int high)
{
    // srand(time(NULL));
    int random = low +  dist(gen) % (high - low);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void randomized_quicksort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = randomized_partition(arr, low, high);
        randomized_quicksort(arr, low, pi - 1);
        randomized_quicksort(arr, pi + 1, high);
    }
}

string testSort(vector<int> &numberSampleQSR, vector<int> &numberSampleQSM, vector<int> &numberSampleQSRand, int size)
{
    vector<string> starter{"Right : ", ", Middle :", ", Random : "};
    string res = "";
    double elapsed;

    auto start1 = std::chrono::high_resolution_clock::now();
    quicksort_right(numberSampleQSR, 0, size - 1);
    auto end1 = std::chrono::high_resolution_clock::now();
    elapsed = double (std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count());
    res += starter[0] + to_string(elapsed/1e6);

    auto start2 = std::chrono::high_resolution_clock::now();
    quicksort_middle(numberSampleQSM, 0, size - 1);
    auto end2 = std::chrono::high_resolution_clock::now();
    elapsed = double (std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count());
    res += starter[1] + to_string(elapsed/1e6);

    
    auto start3 = std::chrono::high_resolution_clock::now();
    randomized_quicksort(numberSampleQSRand, 0, size - 1);
    auto end3 = std::chrono::high_resolution_clock::now();
    elapsed = double (std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count());
    res += starter[2] + to_string(elapsed/1e6);

    return res;
}

int main()
{
    
    vector<vector<vector<int>>> numberList(numberOfSamples, vector<vector<int>>(3, vector<int>()));
    string line;
    string file_name = "..\\data\\random_numbers_";
    string end_name = "0k.csv";
    ofstream outFile("..\\result\\result.txt");
    string result = "";
    if (outFile.is_open())
    {
        for (int i = 1; i <= 10; i++)
        {
            string num = to_string(i);
            string file = file_name + num + end_name;
            ifstream inputFile(file);

            if (inputFile.is_open())
            {
                while (getline(inputFile, line))
                {
                    stringstream ss(line);
                    string value;
                    while (std::getline(ss, value, ','))
                    {
                        numberList[i - 1][0].push_back(std::stoi(value));
                        numberList[i - 1][1].push_back(std::stoi(value));
                        numberList[i - 1][2].push_back(std::stoi(value));
                    }
                }
                inputFile.close();
            }
            else
            {
                std::cerr << "Unable to open file!" << std::endl;
                return 1;
            }
            int samplesize = i * 10000;
            result = to_string(samplesize) + " : ";
            result += testSort(numberList[i - 1][0], numberList[i - 1][1], numberList[i - 1][2], numberList[i - 1][1].size());
            outFile << result << endl;
        }
    }
    else
    {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }
    cout << "File written successfully." << endl;
    outFile.close();
    return 0;
}