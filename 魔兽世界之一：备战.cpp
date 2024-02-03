#include <iostream>
#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;
#define WARRIOR_NUM 5
unordered_map <int,int> warriors;
//五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。
/*
红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
*/
unordered_map <int,string> warriorName{
    {0,"dragon"},
    {1,"ninja"},
    {2,"iceman"},
    {3,"lion"},
    {4,"wolf"}
};

class Base{
    private:
        int totalLifeValue;
        bool stop;
        int cur;
        unordered_map <int,int> warriornums;
        int order[2][WARRIOR_NUM]{
            {2,3,4,1,0},
            {3,0,1,2,4}
        };
        int type;
        int totalWarriorNum;

    public:
        Base(int n){
            type = n;
            stop = true;
            cur = 0;
            totalWarriorNum = 0;
        }
        void init(int m){
            totalLifeValue = m;
            stop = true;
            cur = 0;
            warriornums.clear();
            totalWarriorNum = 0;
        }
        bool produce(int t){
            if (!stop){
                return false;
            }
            int search = 0;
            while(warriors[order[type][cur]] > totalLifeValue && search < WARRIOR_NUM){
                cur = (cur+1)%WARRIOR_NUM;
                search++;
            }
            if(search == WARRIOR_NUM){
                if(type == 0)
                    printf("%03d red headquarter stops making warriors\n",t);
                else
                    printf("%03d blue headquarter stops making warriors\n",t);
                stop = false;
                return stop;
            }else{
                totalLifeValue -= warriors[order[type][cur]];
                totalWarriorNum++;
                warriornums[order[type][cur]]++;
                if(type == 0)
                    printf("%03d red %s %d born with strength %d,%d %s in red headquarter\n",t,warriorName[order[type][cur]].c_str(),totalWarriorNum,warriors[order[type][cur]],warriornums[order[type][cur]],warriorName[order[type][cur]].c_str());
                else
                    printf("%03d blue %s %d born with strength %d,%d %s in blue headquarter\n",t,warriorName[order[type][cur]].c_str(),totalWarriorNum,warriors[order[type][cur]],warriornums[order[type][cur]],warriorName[order[type][cur]].c_str());
                cur = (cur+1)%WARRIOR_NUM;
                return stop;
            }
        }

};

int main()
{
    int t; cin>>t;
    Base red(0),blue(1);
    int ncase {1};
    while(t--){
        cout<<"Case:"<<ncase++<<endl;
        int M; cin>>M;
        red.init(M);blue.init(M);
        for(int i{0};i<WARRIOR_NUM;i++){
            cin>>warriors[i];
        }
        int time {0};
        while(true){
            bool tmp1 = red.produce(time);
            bool tmp2 = blue.produce(time); 
            if(!(tmp1 || tmp2)){
                break;
            }
            time++;
        }
    }
    return 0;
}