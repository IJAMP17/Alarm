#include <iostream>
#include <termios.h>    
#include <unistd.h>
#include <stdlib.h>     
#include <fcntl.h>
#include <sys/poll.h>
#include <iomanip>      
#include "WorkWithComPort.h"
#include "g_buffer.h"
#include <mutex>

using namespace std;

char readBuffer[] = {'0','0','0','0'};
std::mutex m;

void WorkWithComPort::com_init()
{
    m_filePort = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);  // файл порта
    if (m_filePort < 0)
    {
        std::cout << "Error in opening COM" << std::endl;
    }
     
    struct termios options;                                // структура настроек
    tcgetattr(m_filePort, &options);                       // получение настроек порта    
    cfsetispeed(&options,B9600);                           // скорость приема
    cfsetospeed(&options,B9600);                           // скорость передачи
    options.c_cflag &= ~PARENB; 			     // откл.бит четности			
    options.c_cflag &= ~CSTOPB; 			     // стоп-бит 1			
    options.c_cflag &= ~CSIZE;                             // очистка маски размера данных
    options.c_cflag |=  CS8;				     // 8-бит размер данных		
    options.c_cflag &= ~CRTSCTS;			     // откл.управл. данными			
    options.c_oflag &= ~OPOST;                             // откл.режим ввода
    options.c_cflag |= CREAD | CLOCAL;                     // откл.линии модема
    options.c_iflag &= ~(IXON | IXOFF | IXANY);            // откл.управл.потоком данных 
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);    // неканонический режим
    options.c_cc[VMIN]  = 40;                              
    options.c_cc[VTIME] = 10;                                
       
    if ((tcsetattr(m_filePort,TCSANOW,&options))!=0)
    { 
        std::cout << "Error setting" << std::endl;
    }
}

void WorkWithComPort::com_read()                   
{       
    int countCycleRead; 
    for (countCycleRead = 0; countCycleRead < 10; countCycleRead++)      
    {
        tcflush(m_filePort, TCIFLUSH);
        {
        std::lock_guard<std::mutex>lockGuard(m);
        read(m_filePort,&readBuffer,4);
        }
        std::cout << readBuffer[1] << std::endl;
    }
   
}                         


