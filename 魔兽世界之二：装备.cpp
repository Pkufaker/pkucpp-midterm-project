#include <iostream>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;
#define WARRIOR_NUM 5

unordered_map <int,int> warriors; 

//record warrior's life value
//五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。
/*
红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。
蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。
*/

/*
dragon 可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。
ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。
iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。
lion 有“忠诚度”这个属性，其值等于它降生后其司令部剩余生命元的数目。
wolf没特点。
*/

unordered_map <int,string> warriorName{
    {0,"dragon"},
    {1,"ninja"},
    {2,"iceman"},
    {3,"lion"},
    {4,"wolf"}
};

unordered_map <int,string> weaponName{
    {0,"sword"},
    {1,"bomb"},
    {2,"arrow"}
};

struct Warrior{
    int type;
    int num;
    int life;
    float morale = -1.0;
    int loyalty = -1;
    vector<int> weapon = {-1,-1};
    string warrior_name;
    
    Warrior(int t, int n ,int l,int res){
        type = t;
        num = n;
        life = l;
        warrior_name = warriorName[type];
        switch (type)
        {
        case 0:/* constant-expression */
            morale = 1.0 * res / life;
            weapon[0] = num%3;
            break;
        case 1:
            weapon[0] = num%3;
            weapon[1] = (num+1)%3;
            break;
        case 2:
            weapon[0] = num%3;
            break;
        case 3:
            loyalty = res;
            break;
        case 4:
            break;
        }
    }
    void show(){
        switch (type)
        {
        case 0:
            printf("It has a %s,and it's morale is %.2f\n",weaponName[weapon[0]].c_str(),morale);
            break;
        case 1:
            printf("It has a %s and a %s\n",weaponName[weapon[0]].c_str(),weaponName[weapon[1]].c_str());
            break;
        case 2:
            printf("It has a %s\n",weaponName[weapon[0]].c_str());
            break;
        case 3: 
            printf("It's loyalty is %d\n",loyalty);
            break;
        default:
            break;
        }
        return ;
    }
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
                if(type == 0){
                    printf("%03d red %s %d born with strength %d,%d %s in red headquarter\n",t,warriorName[order[type][cur]].c_str(),totalWarriorNum,warriors[order[type][cur]],warriornums[order[type][cur]],warriorName[order[type][cur]].c_str());
                    Warrior tmp(order[type][cur],totalWarriorNum,warriors[order[type][cur]],totalLifeValue);
                    tmp.show();
                }else{
                    printf("%03d blue %s %d born with strength %d,%d %s in blue headquarter\n",t,warriorName[order[type][cur]].c_str(),totalWarriorNum,warriors[order[type][cur]],warriornums[order[type][cur]],warriorName[order[type][cur]].c_str());
                    Warrior tmp(order[type][cur],totalWarriorNum,warriors[order[type][cur]],totalLifeValue);
                    tmp.show();
                }
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