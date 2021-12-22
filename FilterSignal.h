#ifndef FilterSignal_H
#define FilterSignal_H

class FilterSignal
{
    private:
        int m_timeButton;
        int m_countFilter;
    public:
        FilterSignal(int timeButton);
        void filter_dis();             // дискретный датчик
        void filter_an();              // аналоговый датчик
    
};  
#endif   
