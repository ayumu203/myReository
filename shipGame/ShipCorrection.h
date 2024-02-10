#ifndef SHIPCORRECTION_H
#define SHIPCORRECTION_H
#include <bits/stdc++.h>
#include "Ship.h"
#include "constant.h"
using namespace std;
//船を格納しておくクラス
class ShipCorrection{
    private:
        vector<Ship> correction;
        int size;
    public:
        void set(){
            setSize();
            this->correction.resize(this->size);
        }
        void setSize(){
            this->size=SHIPNUM;
        }
        int getSize(){
            return this->size;
        }
        void registerShip(Ship s){
            this->correction[s.getNumber()]=s;
        }
        vector<Ship> &getShipCorrection(){
            return this->correction;
        }
        Ship getShip(int number){
            return this->correction[number];
        }
};
#endif