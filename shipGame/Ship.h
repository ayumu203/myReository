#ifndef SHIP_H
#define SHIP_H
#include <bits/stdc++.h>
using namespace std;
//船の情報を管理するためのクラス
class Ship{
    private:
        int x;
        int y;
        int hp;
        int number;
    public:
        void set(int x,int y,int hp,int number){
            this->x=x;
            this->y=y;
            this->hp=hp;
            this->number=number;
        }
        void setPosition(int x,int y){
            this->x=x;
            this->y=y;
        }
        pair<int,int> getPosition(){
            pair<int,int> p = {this->x,this->y};
            return p;
        }
        int getNumber(){
            return this->number;
        }
};

#endif