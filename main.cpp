#include <string>
#include <iostream>
#include <windows.h>
#include <format>
#include <signal.h>


#define ARR_SIZE 128
int main(){
    signal(SIGINT, [](int signum){
        exit(0);
    });

    char option;

    int varInt = 123456;
    std::string varString = "DefaultString";
    char arrChar[ARR_SIZE] = "Long char array right here ->";

    int *ptr2int = &varInt;
    int **ptr2ptr = &ptr2int;
    int ***ptr2ptr2 = &ptr2ptr;

    while (true) {
        std::cout << "Process ID: " << GetCurrentProcessId() << std::endl;
        std::cout << "varInt\t\t(" << std::uppercase << &varInt << ") = "<< varInt << std::endl;
        std::cout << "varString\t(" << &varString << ") = "<< varString << std::endl;
        std::cout << "varChar\t\t(" << &arrChar << ") = "<< arrChar << std::endl;

        std::cout << "ptr2int\t\t(" << &ptr2int << ") = "<< ptr2int << std::endl;
        std::cout << "ptr2ptr\t\t(" << &ptr2ptr << ") = "<< ptr2ptr << std::endl;
        std::cout << "ptr2ptr2\t(" << &ptr2ptr2 << ") = "<< ptr2ptr2 << std::endl;

        std::cout << "Press ENTER to print again" << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;
        getchar();
    }
    return 0;
}