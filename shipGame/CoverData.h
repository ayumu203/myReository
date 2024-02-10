#ifndef COVERDATA_H
#define COVERDATA_H
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

class CoverData:MapData{
    public:
    void setCoverage(ShipPlacement shipPlacement){
        int height=this->getHeight();
        int width=this->getWidth();
        vector<vector<int>> array=this->getArray();
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    if(shipPlacement.getArrangement()[i][j]!=-1){
                        array[i][j]=1;
                        for(int k=0; k<DXA.size(); k++){
                            int targetX=j+DXA[k];
                            int targetY=i+DYA[k];
                            if(DataAnalyzer::checkValidPosition(targetX,targetY)){
                                array[targetY][targetX]=1;
                            }
                        }
                    }
                }
            }
        }
};

#endif