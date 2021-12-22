#include <thread>
#include "WorkWithComPort.h"
#include "FilterSignal.h"

int main()
{   
    WorkWithComPort workWithComPort;                                   //объект настроек
    FilterSignal filterSignal(2);                                      //объект обработки сигнала
    
    workWithComPort.com_init();                                     
   
    std::thread t1(&WorkWithComPort::com_read, &workWithComPort);   
    std::thread t2(&FilterSignal::filter_dis, &filterSignal);       
         
    t1.join();   
    t2.join();
    
    return 0;
}
