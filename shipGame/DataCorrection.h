#ifndef DATACORRECTION_H
#define DATACORRECTION_H
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

class DataCorrection{
    private:
        ShipPlacement shipPlacement;
        CoverData coverData;
        AttackData attackData;
        AttackedData attackedData;
    public:
        void set(ShipPlacement shipPlacement,CoverData coverData,AttackData attackData,AttackedData attackedData){
            this->shipPlacement=shipPlacement;
            this->coverData=coverData;
            this->attackData=attackData;
            this->attackedData=attackedData;
        }
        ShipPlacement getShipPlacement(){
            return this->shipPlacement;
        }
        CoverData getCoverData(){
            return this->coverData;
        }
};

#endif