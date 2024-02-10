#ifndef CONSTANT_H
#define CONSTANT_H
#include <bits/stdc++.h>
using namespace std;
const int HP=3;
const int MAPWIDTH=5;
const int MAPHEIGHT=5;
const int SHIPNUM=4;

const int MISS=0;
const int WAVE=1;
const int PRIORITY=2;
const int HIT=103;
const int UNKNOWN=-1;

//攻撃範囲
vector<int> DXA={0,0,1,1,1,-1,-1,-1};
vector<int> DYA={1,-1,0,1,-1,0,1,-1};
//移動範囲
vector<int> DXM={1,2,-1,-2,0,0,0,0};
vector<int> DYM={0,0,0,0,1,2,-1,-2};
#endif