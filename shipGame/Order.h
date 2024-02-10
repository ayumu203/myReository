#ifndef ORDER_H
#define ORDER_H
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

class Order{
    private:
        char action;
        pair<int,int> point;
        char result;
        char direction;
        int length;
    public:
        void set(char action,pair<int,int> point,char result,char derection,int len){
            this->action=action;
            if(action=='a'){
                this->point.first=point.first;
                this->point.second=point.second;
                this->result=result;
            }
            else {
                this->direction=direction;
                this->length=len;
            }
        }
};

#endif