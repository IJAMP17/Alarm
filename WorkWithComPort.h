#ifndef WorkWithComPort_H
#define WorkWithComPort_H

class WorkWithComPort
{
    int m_filePort;                // файл-дескриптор порта
     
    public:
        void com_init();           // открытие и настройка порта
        void com_read();           // чтение с порта
        void com_write();          // отправка в порт
};  
#endif      
