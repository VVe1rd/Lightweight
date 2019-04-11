#include <cstdio>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;
typedef std::chrono::high_resolution_clock Clock;

int (*algorithm)(unsigned char*, int, unsigned char*, int, unsigned char*, int);
int main_LW(unsigned char* random_message, int msg_length, unsigned char*, int, unsigned char*, int);
int main_clefia(unsigned char* random_message, int msg_length, unsigned char*, int, unsigned char*, int);
int main_Spongent(unsigned char* random_message, int msg_length, unsigned char*, int, unsigned char*, int);
int main_present(unsigned char* random_message, int msg_length, unsigned char* random_key, int key_length, unsigned char* random_iv, int iv_length);
int main_grain(unsigned char* random_message, int msg_length, unsigned char* random_key, int key_length, unsigned char* random_iv, int iv_length);

int main(int argc, char* argv[])
{
    //arg1 == key_length (int)
    int algorithm_id, i, j;
    int block_size = 100; //in bytes
    int msg_length = 128; //in bytes
    int key_length = 64; //in bytes
    int iv_length = 8; //in bytes
    unsigned char **random_messages = new unsigned char*[block_size];
    unsigned char **random_keys = new unsigned char*[block_size];
    unsigned char **random_ivs = new unsigned char*[block_size];
    for (i = 0; i < block_size; ++i)
    {
        random_messages[i] = new unsigned char[msg_length];
        random_keys[i] = new unsigned char[key_length];
        random_ivs[i] = new unsigned char[iv_length];
    }
    srand(time(0));
    for (i = 0; i < block_size; ++i)
    {
        for (j = 0; j < msg_length; ++j)
        {
            random_messages[i][j] = (unsigned char)(rand() % 256);
        }
        for (j = 0; j < key_length; ++j)
        {
            random_keys[i][j] = (unsigned char)(rand() % 256);
        }
        for (j = 0; j < iv_length; ++j)
        {
            random_ivs[i][j] = (unsigned char)(rand() % 256);
        }
    }


    //////////////////////////////////////////////////////////////
    cout << "Choose an algorithm" << endl;
    cout << "1 - Lesamnta-LW" << endl;
    cout << "2 - Clefia" << endl;
    cout << "3 - Spongent" << endl;
    cout << "4 - PRESENT" << endl;
    cout << "5 - Grain" << endl;
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
        case 5:
            algorithm = main_grain;
            break;
    }

    t_begin = Clock::now();
    for (i = 0; i < block_size; ++i)
    {
        algorithm(random_messages[i], msg_length, random_keys[i], key_length, random_ivs[i], iv_length);
    }
    t_end = Clock::now();

    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_begin).count() / block_size
              << " nanoseconds" << std::endl;


    ////////////////////////
    delete[] random_messages;
    delete[] random_keys;
    delete[] random_ivs;
    return 0;
}
