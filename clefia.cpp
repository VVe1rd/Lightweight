#include <cstdio>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iostream>

#define ROUNDS_NUMBER 100

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

int (*algorithm)(char*);
int main_LW(char* filename);
int main_clefia(char* filename);

void getOutput()
{
    int algorithm_id, i;
    char message[32];

    cout << "Filename: ";
    scanf("%s", message);

    cout << "Choose an algorithm" << endl;
    cout << "1 - Lesamnta-LW\n" << endl;
    cout << "2 - Clefia\n" << endl;
    cin >> algorithm_id;

    auto t_begin = Clock::now();
    auto t_end = Clock::now();

    switch (algorithm_id)
    {
    case 1:
        algorithm = main_LW;
        break;
    case 2:
        algorithm = main_clefia;
        break;
    }

    t_begin = Clock::now();
    for (i = 0; i < ROUNDS_NUMBER; ++i)
    {
        algorithm(message);
    }
    t_end = Clock::now();

    std::cout << "Execution time: "
    << std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_begin).count() / ROUNDS_NUMBER
    << " nanoseconds" << std::endl;
}

void getRandomMsg()
{
    unsigned int len;
    int i;
    FILE *f;
    string msg;
    string filename = "random.txt";
    cout << "Message length (in bytes): ";
    cin >> len;
    f = fopen(filename.c_str(), "wt");
    if (f != NULL)
    {
        for (i = 0; i < len; ++i)
        {
            msg = msg + (char)(rand() % 256);
        }
        fputs(msg.c_str(), f);
        fclose(f);
    }
    else
    {
        cout << "Error while opening file to create!" << endl;
    }
}

int main()
{
    int mode;
    srand(time(0));
    cout << "Choose mode:" << endl;
    cout << "1 - to get a hash/cipher" << endl;
    cout << "2 - to generate a random message" << endl;
    cin >> mode;
    if (mode == 1)
    {
        getOutput();
    }
    else if (mode == 2)
    {
        getRandomMsg();
    }
    return 0;
}
