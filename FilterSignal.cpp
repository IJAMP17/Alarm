#include <iostream>
#include <unistd.h>     
#include <stdlib.h>      
#include <fcntl.h>
#include <iomanip>      
#include "FilterSignal.h"
#include "g_buffer.h"

using namespace std;

FilterSignal::FilterSignal(int timeButton)
{
    m_timeButton = timeButton;
}

void FilterSignal::filter_dis()
{
    int i;
    for (i = 10; i < 20; i++)
    {
        if (readBuffer[1] < 54)
        {
        m_countFilter = 0;
        std::cout << setw(30) << "Норма" << std::endl;
        }
        else m_countFilter++;    
        
        if (m_countFilter >= m_timeButton)
        {
        m_countFilter = 0;
        std::cout << setw(30) << "Тревога" << std::endl;
        }    
     std::cout << setw(30) << readBuffer[1] + 1 << std::endl;       
     sleep(1);
    }
}
           
