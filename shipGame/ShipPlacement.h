#ifndef SHIPPLACEMENT_H
#define SHIPPLACEMENT_H
#include <bits/stdc++.h>
#include "constant.h"
#include "DataAnalyzer.h"
#include "Ship.h"
#include "constant.h"
#include "ShipCorrection.h"
using namespace std;
class ShipPlacement{
    private:
        int width;
        int height;
        vector<vector<int>> arrangement;
    public:
        void set(ShipCorrection shipCorrection){
            this->width=MAPWIDTH;
            this->height=MAPHEIGHT;
            this->arrangement.assign(this->height,vector<int>(this->width,-1));
            this->initArrangement(shipCorrection);
        } 
        vector<vector<int>> &getArrangement(){
            return this->arrangement;
        }
        //shipCorrectionの船を配置する
        void initArrangement(ShipCorrection shipCorrection){
            this->arrangement.assign(this->height,vector<int>(this->width,-1));
            int size=shipCorrection.getSize();
            for(int i=0; i<size; i++){
                Ship s = shipCorrection.getShip(i);
                pair<int,int> p = s.getPosition();
                int x = p.first;
                int y = p.second;
                this->arrangement[y][x]=s.getNumber();
            }
        }
        //配置を表示
        void showArrangement(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    std::cout << this->arrangement[i][j] << " ";
                }
                std::cout << endl;
            }
            cout << endl;
        }
};
#endif