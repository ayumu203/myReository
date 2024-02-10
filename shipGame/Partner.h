#ifndef PLAYER_H
#define PLAYER_H
#include <bits/stdc++.h>
#include "constant.h"
#include "DataAnalyzer.h"
#include "Ship.h"
#include "constant.h"
#include "ShipCorrection.h"
#include "ShipPlacement.h"
#include "MapData.h"
#include "CoverData.h"
#include "AttackData.h"
#include "AttackedData.h"
#include "DataCorrection.h"
using namespace std;
class Partner{
    public:
        char attack(DataCorrection dataCorrection);
        void move();
};

char Partner::attack(DataCorrection dataCorrection){
    ShipPlacement shipPlacement = dataCorrection.getShipPlacement();
    vector<vector<int>> arrangement=shipPlacement.getArrangement();
    int x,y;
    x=-1;
    y=-1;

    while(!DataAnalyzer::checkValidPosition(x,y)){
        std::cout << "攻撃する座標を入力" << endl;
        // cout << "y: ";
        std::cout << "y(a~e): ";
        char c;
        cin >> c;
        y=c;
        y-=97;
        std::cout << "x(1~5): ";
        cin >> x;
        x--;
        if(DataAnalyzer::checkValidPosition(x,y)){
            break;
        }
    }
    cout << x << " " << y << endl;
    if(arrangement[y][x]!=-1){
        std::cout << "命中" << endl;
        return 'H';
    }
    for(int i=0; i<DYA.size(); i++){
        int targetX=x+DXA[i];
        int targetY=y+DYA[i];
        if(DataAnalyzer::checkValidPosition(targetX,targetY)&&arrangement[targetY][targetX]!=-1){
            std::cout << "波高し" << endl;
            return 'W';
        }
    }
    //miss
    return 'M';
}

void Partner::move(){
    char direction;
    int count;
    while(!(direction=='n'||direction=='s'||direction=='e'||direction=='w')){
        cout << "動く方向を入力(n,s,e,w):" << endl;
        cin >> direction;
    }
    while(!(count==1||count==2)){
        cout << "動くマスの数を入力" << endl;
        cin >> count;
        cout << "マス" << endl;
    }
    cout << direction << "方向に" << count << "マス移動" << endl;
}
#endif