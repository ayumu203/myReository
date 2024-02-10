#ifndef DATAANALYZER_H
#define DATAANALYZER_H
#include <bits/stdc++.h>
#include "constant.h"
using namespace std;
//船の配置の決定や入力された座標の検証を行う
class DataAnalyzer{
    public:
        static bool checkValidPosition(int x,int y);
};

bool DataAnalyzer::checkValidPosition(int x,int y){
    if(x>=0&&x<MAPWIDTH&&y>=0&&y<MAPHEIGHT)return true;
    return false;
}
#endif