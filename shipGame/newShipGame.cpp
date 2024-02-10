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
#include "Player.h"
#include "Partner.h"
#include "Order.h"
using namespace std;

int main(){
    //船を格納しておく配列
    ShipCorrection shipCorrection;
    shipCorrection.set();
    //-------------------------------------------
    //船の設定
    //〇ここで船を位置を登録できる
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
    // shipPlacement.showArrangement();
    //-------------------------------------------
    //コレクションに船を設定
    shipCorrection.registerShip(s0);
    shipCorrection.registerShip(s1);
    shipCorrection.registerShip(s2);
    shipCorrection.registerShip(s3);
    //-------------------------------------------
    //-------------------------------------------
    //データを格納
    //-------------------------------------------
    DataCorrection dataCorrection;
    CoverData coverData;
    coverData.set(MAPWIDTH,MAPHEIGHT);
    AttackData attackData;
    attackData.set(MAPWIDTH,MAPHEIGHT);
    AttackedData attackedData;
    attackData.set(MAPWIDTH,MAPHEIGHT);
    dataCorrection.set(shipPlacement,coverData,attackData,attackedData);
    //-------------------------------------------
    //-------------------------------------------
    //対戦相手のインスタンス
    Player player;
    Partner partner;
    vector<Order> playerOrders;
    vector<Order> partnerOrders;
    //-------------------------------------------
    //-------------------------------------------
    //ゲーム開始
    int turn=-1;
    cout << "先行ならば0,後攻ならば1を入力" << endl;
    // dataCorrection.getShipPlacement().showArrangement();
    while(!(turn==0||turn==1))cin >> turn;
     while(true){
        if(turn%2==0){
            cout << "プレイヤーのターン" << "\n" << endl;
            char c='@';
            while(!(c=='c'||c=='e'&&c=='b')){
                cout << "続行[c],終了[e],戻る[b]" << endl;
                cin >> c;
                if(c=='e'){
                    cout << "ゲームを終了します" << endl;
                    return ;
            }
            player.decideAction(dataCorrection,playerOrders,partnerOrders);
        }
        if(turn%2==1){
            cout << "相手のターン" << "\n" << endl;
            char c='@';
            while(!(c=='c'||c=='e'&&c=='b')){
                cout << "続行[c],終了[e],戻る[b]" << endl;
                cin >> c;
                if(c=='e'){
                    cout << "ゲームを終了します" << endl;
                    return ;
                }            
            }
            char action='*';
            while(!(action=='a'||action=='m'||action=='e'||action=='b')){
                cout << "攻撃[a],移動[m],終了[e],戻る[b]" << endl;
                cin >> action;
            }
            if(action=='a'){
                Order result = partner.attack(dataCorrection);
                partnerOrders.push_back(result);
            }
            else if(action=='m'){
                Order result = partner.move();
                partnerOrders.push_back(result);
            }
            else if(action=='e'){
                cout << "ゲームを終了します" << endl;
                return ;
            }
            else if(action=='b'){
            }
            cout << "turn:" << turn << "\n" << endl;
        }
        turn++;
    //-------------------------------------------
        }
    }
}