#ifndef PARTNER_H
#define PARTNER_H
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

class Player{
    public:
        void decideAction(DataCorrection dataCorrection){
            this->attack(dataCorrection);
        }
        void attack(DataCorrection dataCorrection){
            int x=0;
            int y=0;
            CoverData coverData=dataCorrection.getCoverData();
            for(int i=0; i<MAPHEIGHT; i++){
                for(int j=0; j<MAPWIDTH; j++){
                    vector<vector<int>> array=coverData.getArray();
                    if(array[y][x]==1){}
                }
            }
        }
        void setAttackResult(DataCorrection dataCorrection){
            cout << "攻撃結果を入力" << endl;
        }
};

#endif