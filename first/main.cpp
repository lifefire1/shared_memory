#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
using namespace std;

int main()
{
    // ftok to generate unique key
    key_t key = ftok("shared_memory",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,nullptr,0);

    cout<<"Write Data first memory: ";
    cin >> str;                 //7,8,9,1

    printf("Data written in memory: %s\n",str);
    shmdt(str);


    int contin;
    cout << "Enter a number to continue";
    cin >> contin;

    //---------second write in memory
    key_t second_key = ftok("second_shared",66);
    int shmid_second = shmget(second_key,1024,0666|IPC_CREAT);
    char *str_second = (char*) shmat(shmid_second,nullptr,0);
    cout<<"Write Data second memory: ";
    cin >> str_second;                  // 4,3,9,1
    printf("Data written in second memory: %s\n",str_second);
    shmdt(str_second);

    int contin2;
    cout << "Enter a number to continue";
    cin >> contin2;
    //---------third write in memory
    key_t third_key = ftok("third_shared",67);
    int shmid_third = shmget(third_key,1024,0666|IPC_CREAT);
    char *str_third = (char*) shmat(shmid_third,nullptr,0);
    cout<<"Write Data third memory: ";
    cin >> str_third;                    // 4,3,7,8
    printf("Data written in second memory: %s\n",str_third);
    shmdt(str_third);

    // output memory
    int cont;
    cout << "Begin read number from memory ";
    cin >> cont;
    key_t key_output = ftok("output_second",68);

    // shmget returns an identifier in shmid
    int shmid_output = shmget(key_output,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str_output = (char*) shmat(shmid_output,nullptr,0);

    printf("Data read from memory: %s\n",str_output);
    int first_det = std::stoi(str_output);
    shmdt(str_output);

    // destroy the shared memory
    shmctl(shmid_output,IPC_RMID,nullptr);


    // second det
    int cont2;
    cout << "Begin read number from  second memory " << endl;
    cin >> cont2;
    key_t key_output_second = ftok("output_second",69);

    // shmget returns an identifier in shmid
    int shmid_output_second = shmget(key_output_second,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str_output_second = (char*) shmat(shmid_output_second,nullptr,0);

    printf("Data read from memory: %s\n",str_output_second);
    int first_det_second = std::stoi(str_output_second);
    shmdt(str_output_second);

    // destroy the shared memory
    shmctl(shmid_output_second,IPC_RMID,nullptr);

    // third det
    int cont3;
    cout << "Begin read number from  second memory " << endl;
    cin >> cont3;
    key_t key_output_third = ftok("output_second",70);

    // shmget returns an identifier in shmid
    int shmid_output_third = shmget(key_output_third,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str_output_third = (char*) shmat(shmid_output_third,nullptr,0);

    printf("Data read from memory: %s\n",str_output_third);
    int first_det_third = std::stoi(str_output_third);
    shmdt(str_output_third);

    // destroy the shared memory
    shmctl(shmid_output_third,IPC_RMID,nullptr);

    int result = 2 * first_det - 5 * first_det_second + 6 * first_det_third;
    cout << "Determinante is matrix " << endl;
    cout << "2, 4, 3 " << endl;
    cout << "5, 7, 8 " << endl;
    cout << "6, 9, 1 " << endl;
    cout << " is " << result << endl;
    return 0;
}