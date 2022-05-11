#include "mbed.h"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
BufferedSerial pc(USBTX, USBRX, 115200);
BufferedSerial esp(PA_9,PA_10, 9600);
#define MAXIMUM_BUFFER_SIZE   32                                              
char var[]= {'1','2','3'};
// main() runs in its own thread in the OS
const char head[] = {'A'};
const char foot[] = {'B'};
int Is_digit(int speed);
int main()
{       esp.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    printf("main\n");
    while (true) {
        int speed =24456;
        int num = Is_digit(speed);
        int int_ptr[num];
        for(int i = num-1; i >= 0; i--){
            int_ptr[i] = speed % 10;
            speed /=10;
        }
        std::string str;
        for (int i: int_ptr) {
        str += std::to_string(i);
            }
        char buf[str.length()+1];
        strcpy(buf, str.c_str());

        //std::cout << str;

        //std::printf("num_char: %c \n", str[1]);
        
            
        esp.write(head, sizeof(head));
        //esp.write(int_ptr, sizeof(int_ptr));
        esp.write(buf, sizeof(buf));
        esp.write(foot, sizeof(foot));
       
            ThisThread::sleep_for(2ms);
    }
}


int Is_digit(int speed){
        int digit = 1;
        while(speed > 10){
        speed = speed/10;
        digit++;
        }
        return digit;
}


