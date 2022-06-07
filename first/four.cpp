#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include "vector"
using namespace std;

int main()
{
    // ftok to generate unique key
    key_t four_key = ftok("third_shared",67);

    // shmget returns an identifier in shmid
    int shmid_four = shmget(four_key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid_four,nullptr,0);

    printf("Data read from memory: %s\n",str);

    std::string s = str;
    std::string delimiter = ",";
    vector<string> mass;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        mass.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    std::cout << s << std::endl;
    mass.push_back(s);;
    int mass1 = std::stoi(mass.at(0));
    int mass2 = std::stoi(mass.at(1));
    int mass3 = std::stoi(mass.at(2));
    int mass4 = std::stoi(mass.at(3));
    int result = mass1 * mass4 - mass2 * mass3;
    cout << result << endl;
    //detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid_four,IPC_RMID,nullptr);

    int cont;
    cout << "Enter a number to continiu";
    cin >> cont;

    // ftok to generate unique key
    key_t key_output = ftok("output_second",70);

    // shmget returns an identifier in shmid
    int shmid_output = shmget(key_output,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str_output = (char*) shmat(shmid_output,nullptr,0);

    cout<<"Write Data third memory: ";
    cin >> str_output;                  //11
    cout << str_output << endl;
    printf("Data written in memory: %s\n",str_output);
    shmdt(str_output);
    return 0;
}

