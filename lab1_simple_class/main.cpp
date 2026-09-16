#include <iostream>
#include <type_traits>

using namespace std;

class TimePoint{
    private:
        int hours;
        int minuts;
        int seconds;

        void proverka(int h, int m, int s){
            if (h<0 || h>23){
                cout<<"invalid hours";
                exit(1);
            }
            if (m<0 || h>59){
                cout<<"invalid minuts";
                exit(1);
            }
            if (s<0 || s>59){
                cout<<"invalid seconds";
                exit(1);
            }
        }
    public:

    TimePoint(int h, int m, int s){
        proverka(h, m, s);
        hours=h;
        minuts=m;
        seconds=s;
    }
    void input(){
        int h, m, s;
        cout<<"print hours, minuts, seconds:";
        cin>>h>>m>>s;
        //proverka(h, m, s);
        hours=h; minuts=m; seconds=s;
    }
    void output(){
        if (hours<10)
            cout<<'0'<<hours<<':';
        if (minuts<10)
            cout<<'0'<<minuts<<':';
        if (seconds<10)
            cout<<'0'<<seconds<<endl;
    }

};
int main(){


}