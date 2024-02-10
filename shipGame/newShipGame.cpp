#include <bits/stdc++.h>
#include "constant.h"
#include "DataAnalyzer.h"
#include "Ship.h"
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


int main(){
    //船を格納しておく配列
    ShipCorrection shipCorrection;
    shipCorrection.set();
    //-------------------------------------------
    //船の設定
    Ship s0;
    s0.set(0,0,HP,0);
    shipCorrection.registerShip(s0);
    Ship s1;
    s1.set(1,0,HP,1);
    shipCorrection.registerShip(s1);
    Ship s2;
    s2.set(0,1,HP,2);
    shipCorrection.registerShip(s2);
    Ship s3;
    s3.set(1,1,HP,3);
    shipCorrection.registerShip(s3);
    ShipPlacement shipPlacement;
    shipPlacement.set(shipCorrection);
    shipPlacement.showArrangement();
    //-------------------------------------------
    //-------------------------------------------
    //データを格納
    DataCorrection dataCorrection;
    Coverage coverage;
    dataCorrection.set(shipPlacement);
    coverage.set();
    coverage.setCoverage(shipPlacement);
    coverage.showCoverage();
    //-------------------------------------------
    //-------------------------------------------
    //コレクションに船を設定
    shipCorrection.registerShip(s0);
    shipCorrection.registerShip(s1);
    shipCorrection.registerShip(s2);
    shipCorrection.registerShip(s3);
    //-------------------------------------------
    //-------------------------------------------
    //対戦相手のインスタンス
    Partner partner;
    //-------------------------------------------
    //-------------------------------------------
    //ゲーム開始
    int turn=-1;
    cout << "先行ならば0,後攻ならば1を入力" << endl;
    dataCorrection.getShipPlacement().showArrangement();
    while(!(turn==0||turn==1))cin >> turn;
     while(true){
        if(turn%2==0){
            cout << "turn:" << turn << "\n" << endl;
            cout << "続行[c],終了[e],戻る[b]" << endl;
            turn++;
        }
        if(turn%2==1){
            char action='*';
            while(!(action=='a'||action=='m'||action=='e'||action=='b')){
                cout << "攻撃[a],移動[m],終了[e],戻る[b]" << endl;
                cin >> action;
            }
            if(action=='a'){
                char result = partner.attack(dataCorrection);
                cout << result << endl;
            }
            else if(action=='m'){
                partner.move();
            }
            else if(action=='e'){
            }
            else if(action=='b'){
            }
            cout << "turn:" << turn << "\n" << endl;
            turn++;
        }
    //-------------------------------------------
    }
}