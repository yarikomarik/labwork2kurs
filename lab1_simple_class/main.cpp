#include <iostream>
#include <cmath>

using namespace std;

class TimePoint
{
    private:
        int hours;
        int minuts;
        int seconds;

        void proverka(int h, int m, int s)
        {
            if (h<0 || h>23)
            {
                cout<<"invalid hours";
                exit(1);
            }
            if (m<0 || m>59)
            {
                cout<<"invalid minuts";
                exit(1);
            }
            if (s<0 || s>59)
            {
                cout<<"invalid seconds";
                exit(1);
            }
        }
    public:
        //конструктор по умолчанию
        TimePoint()
        {
            hours=0;
            minuts=0;
            seconds=0;
        }

        //конструктор  с аргументами
        TimePoint(const int h, const int m, const int s)
        {
            proverka(h, m, s);
            hours=h;
            minuts=m;
            seconds=s;
        }

        //геттеры
        int getHours() const
        {
            return hours; 
        }
        int getMinutes() const
        {
            return minuts; 
        }
        int getSeconds() const 
        {
            return seconds; 
        }
        
        //сеттеры
        void setHours(const int h) 
        {
            proverka(h, minuts, seconds);
            hours = h;
        }

        void setMinutes(int m) 
        {
            proverka(hours, m, seconds);
            minuts = m;
        }

        void setSeconds(int s) 
        {
            proverka(hours, minuts, s);
            seconds = s;
        }
        //ввод
        void input()
        {
            int h, m, s;
            cout<<"print hours, minuts, seconds:";
            cin>>h>>m>>s;
            proverka(h, m, s);
            hours=h; minuts=m; seconds=s;
        }
        //вывод
        void output()
        {
            if (hours<10)
                cout<<'0'<<hours<<':';
            else
                cout<<hours<<':';
            if (minuts<10)
                cout<<'0'<<minuts<<':';
            else
                cout<<minuts<<':';
            if (seconds<10)
                cout<<'0'<<seconds<<endl;
            else
                cout<<seconds<<':';
        }

        TimePoint operator+ (TimePoint other)
        {
            int h = hours + other.hours;
            int m = minuts + other.minuts;
            int s = seconds + other.seconds;

            m=m*s/60;
            s=s%60;
            h=h+m/60;
            m=m%60;

            return TimePoint(h, m, s);
        }

        TimePoint operator- (TimePoint other)
        {
            int h = hours - other.hours;
            int m = minuts - other.minuts;
            int s = seconds - other.seconds;

            if (s<0)
            {
                --m;
                s+=60;
            }
            if (m<0)
            {
                --h;
                m+=60;
            }
            return TimePoint(h, m, s);
        }

        bool operator> (TimePoint other)
        {
            if (hours>other.hours)
                return (1);
            else if (hours==other.hours)
            {
                if (minuts>other.minuts)
            }

        }

        TimePoint operator< (TimePoint other)
        {


        }

        TimePoint operator== (TimePoint other)
        {


        }

        TimePoint operator!= (TimePoint other)
        {


        }

};
int main()
{
    TimePoint time1, time2, timesum;

    time1.input();
    time2.input();
    timesum=time1-time2;
    timesum.output();
}