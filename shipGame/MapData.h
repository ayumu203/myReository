#ifndef MAPDATA_H
#define MAPDATA_H
#include <bits/stdc++.h>
#include "constant.h"
#include "DataAnalyzer.h"
#include "Ship.h"
#include "constant.h"
#include "ShipCorrection.h"
#include "ShipPlacement.h"

class MapData{
    private:
        int width;
        int height;
        vector<vector<int>> array;
    public:
        void set(int w,int h){
            this->width=w;
            this->height=h;
            this->array.assign(this->height,vector<int>(this->width,-1));
        }
        int getHeight(){
            return this->height;
        }
        int getWidth(){
            return this->width;
        }
        vector<vector<int>>& getArray(){
            return this->array;
        }
        void showArray(){
            for(int h=0; h<this->height; h++){
                for(int w=0; w<width; w++){
                    cout << this->array[h][w] << " ";
                }
                cout << endl;
            }
        }
};

#endif