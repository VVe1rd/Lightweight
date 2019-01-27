#include <cstdio>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iostream>

#define ROUNDS_NUMBER 100

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

int (*algorithm)(char*, char*);
int main_LW(char* msg_filename, char*);
int main_clefia(char* msg_filename, char*);
int main_Spongent(char* msg_filename, char*);
int main_present(char* msg_filename, char* key_filename);

void getOutput()
{
    int algorithm_id, i;
    char message[32];
    char key[32];

    cout << "Message filename: ";
    scanf("%s", message);
    cout << "Key filename (print No if does not exist): ";
    scanf("%s", key);

    cout << "Choose an algorithm" << endl;
    cout << "1 - Lesamnta-LW" << endl;
    cout << "2 - Clefia" << endl;
    cout << "3 - Spongent" << endl;
    cout << "4 - PRESENT" << endl;
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
    case 3:
        algorithm = main_Spongent;
        break;
    case 4:
        algorithm = main_present;
        break;
    }

    t_begin = Clock::now();
    for (i = 0; i < ROUNDS_NUMBER; ++i)
    {
        algorithm(message, key);
    }
    t_end = Clock::now();

    std::cout << "Execution time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_begin).count() / ROUNDS_NUMBER
    << " milliseconds" << std::endl;
}

void getRandomMsg()
{
    unsigned int len;
    int i;
    FILE *f;
    char c;
    string filename = "random_msg.txt";
    cout << "Message length (in bytes): ";
    cin >> len;
    f = fopen(filename.c_str(), "wt");
    if (f != NULL)
    {
        for (i = 0; i < len; ++i)
        {
            c = (char)(rand() % 256);
            fwrite(&c, sizeof(char), 1, f);
        }
        fclose(f);
    }
    else
    {
        cout << "Error while opening file to create!" << endl;
    }
}

void getRandomKey()
{
    unsigned int len;
    int i;
    FILE *f;
    char c;
    string filename = "random_key.txt";
    cout << "Message length (in bytes): ";
    cin >> len;
    f = fopen(filename.c_str(), "wt");
    if (f != NULL)
    {
        for (i = 0; i < len; ++i)
        {
            c = (char)(rand() % 256);
            fwrite(&c, sizeof(char), 1, f);
        }
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
    cout << "3 - to generate a random key" << endl;
    cin >> mode;
    if (mode == 1)
    {
        getOutput();
    }
    else if (mode == 2)
    {
        getRandomMsg();
    }
    else if (mode == 3)
    {
        getRandomKey();
    }
    return 0;
}
