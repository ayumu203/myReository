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

//船の配置の決定や入力された座標の検証を行う
class DataAnalyzer{
    public:
        static bool checkValidPosition(int x,int y);
        static pair<int,int> findBestPos(vector<vector<int>> &checkedPositions);
};

bool DataAnalyzer::checkValidPosition(int x,int y){
    if(x>=0&&x<MAPWIDTH&&y>=0&&y<MAPHEIGHT)return true;
    return false;
}

pair<int,int> DataAnalyzer::findBestPos(vector<vector<int>> &checkedPositions){
    int maxCoverage = 0;
    pair<int,int> bestPos;
    
    for(int i=0; i<MAPHEIGHT; i++){
        for(int j=0; j<MAPWIDTH; j++){
            if(checkedPositions[i][j]!=-1){
                int coverage=0;
                for(int k=0; k<DYA.size(); k++){
                    int targetY=i+DYA[k];
                    int targetX=j+DXA[k];
                    if(DataAnalyzer::checkValidPosition(targetX,targetY)&&checkedPositions[targetY][targetX]!=-1)coverage++;
                }
                if(checkedPositions[i][j]!=-1&&coverage>maxCoverage){
                    maxCoverage=coverage;
                    bestPos=make_pair(i,j);
                }
            }
        }
    }
    return bestPos;
}

//船の情報を管理するためのクラス
class Ship{
    public:
        int x;
        int y;
        int hp;
        int number;
        void set(int x,int y,int hp,int number){
            this->x=x;
            this->y=y;
            this->hp=hp;
            this->number=number;
        }
        void setPosition(int x,int y){
            this->x=x;
            this->y=y;
        }
};
//船を格納しておくクラス
class ShipCorrection{
    public:
        vector<Ship> correction;
        void setCorrection(Ship s){
            this->correction.push_back(s);
        }
};

//船の配置に関するクラス
class ShipArrangeMent
{
    public:
        int width;
        int height;
        vector<vector<int>> arrangement;
        vector<vector<int>> attackablePosition;
        void set(int w,int h){
            this->width=w;
            this->height=h;
            this->arrangement.assign(h,vector<int>(w,-1));
            this->attackablePosition.assign(h,vector<int>(w,-1));
        }
        void setShipPosition(Ship s){
            this->arrangement[s.y][s.x]=s.number;
        }
        void setAttackablePoint(int x,int y){
            this->attackablePosition[y][x]=1;
        }
        void resetAttackablePoint(){
            this->attackablePosition.assign(this->height,vector<int>(this->width,-1));
        }
        bool isAttackable(int x,int y){
            if(this->attackablePosition[y][x]!=-1)return true;
            return false;
        }
        void updateAttackablePosition(){
            this->resetAttackablePoint();
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    if(this->arrangement[i][j]!=-1){
                        for(int k=0; k<DYA.size(); k++){
                            int targetX=i+DXA[k];
                            int targetY=j+DYA[k];
                            if(DataAnalyzer::checkValidPosition(targetX,targetY)){
                                setAttackablePoint(targetX,targetX);
                            }
                        }
                    }
                }
            }
        }
        void showArrangement(){
            for(int i=0; i<MAPHEIGHT; i++){
                for(int j=0; j<MAPWIDTH; j++){
                    if(this->arrangement[i][j]!=-1)cout << "S" << this->arrangement[i][j] << "  ";
                    else cout << "H" << "   ";
                }
                cout << endl;
            }
        }
        void showAttackablePosition(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    cout << this->attackablePosition[i][j] << " ";
                }
                cout << endl;
            }
        }
};

class ExpectData{
    public:
        int width;
        int height;
        //自軍の攻撃により得られるデータ
        //各種パラメータ
        //-1:未探索
        //0:ミス
        //1:波高し
        //10- ex)101,102,103:ヒット
        vector<vector<int>> attackData;
        //相手の攻撃により得られるデータ
        vector<vector<int>> dangerData;
        //探索済みか記録
        vector<vector<int>> coverData;
        void set(int w,int h){
            this->width=w;
            this->height=h;
            this->attackData.assign(h,vector<int>(w,-1));
            this->dangerData.assign(h,vector<int>(w,-1));
            this->coverData.assign(h,vector<int>(w,-1));
        }
        void setCovarage(){
            for(int i=0; i<MAPHEIGHT; i++){
                for(int j=0; j<MAPWIDTH; j++){
                    int tmp = getAttackCoverage(i,j);
                    coverData[i][j]=tmp;
                }
            }
        }
        int getAttackCoverage(int x,int y){
            int coverage=0;
            if(attackData[y][x]==0||coverData[y][x]==0)return coverage;
            for(int i=0; i<DXA.size(); i++){
                int targetX = x+DXA[i];
                int targetY = y+DYA[i];
                if(DataAnalyzer::checkValidPosition(targetX,targetY)&&(this->attackData[targetY][targetX]==-1||this->attackData[targetY][targetX]==1)){
                    coverage++;
                }
            }
            return coverage;
        }
        void showAttackData(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    cout << this->attackData[i][j] << "   ";
                }
                cout << endl;
            }
        }
        void showAttackDataElement(int x,int y){
            cout << "aaa" << this->attackData[y][x] << endl;
        }
        void setAttackResult(int x,int y,int result){
            this->attackData[y][x]=result;
        }
};

class Player{
    public:
        void desideAction(ExpectData &expectData,ShipArrangeMent shipArrangement);
        void attack(ExpectData &expectData,ShipArrangeMent shipArrangement);
        pair<int,int> findBestAttackPosition(ExpectData &expectData);
        char getAttackResult(int x,int y);
        char setAttackResult(int x,int y,char result,ExpectData &ExpectData);
};
//攻撃か移動化を決定
void Player::desideAction(ExpectData &expectData,ShipArrangeMent shipArrangement){
    this->attack(expectData,shipArrangement);
}

pair<int,int> Player::findBestAttackPosition(ExpectData &expectData){
    int coverage = 100;
    pair<int,int> p;
    expectData.setCovarage();
    for(int i=0; i<MAPHEIGHT; i++){
        for(int j=0; j<MAPWIDTH; j++){
            int tmp = expectData.coverData[i][j];
            if(tmp>0&&coverage>tmp)p=make_pair(i,j);
            cout << tmp << " ";
        }
        cout << endl;
    }
    return p;
} 

void Player::attack(ExpectData &expectData,ShipArrangeMent shipArrangement){
    pair<int,int> p = Player::findBestAttackPosition(expectData);
    int targetX = p.first;
    int targetY = p.second;
    char result = this->getAttackResult(targetX,targetY);
    this->setAttackResult(targetX,targetY,result,expectData);
    return ;
    //角の4点を優先的に探索する点とする
    // vector<pair<int,int>> importantPosition={pair(0,0),pair(0,MAPHEIGHT-1),pair(MAPWIDTH-1,0),pair(MAPWIDTH-1,MAPHEIGHT-1)};
    // for(int i=0; i<importantPosition.size(); i++){
    //     int targetX=importantPosition[i].first;
    //     int targetY=importantPosition[i].second;
    //     int target = expectData.attackData[targetY][targetX];
    //     //まずは角を攻撃
    //     if(target==UNKNOWN&&target==PRIORITY&&shipArrangement.isAttackable(targetX,targetY)){
    //         char result = this->getAttackResult(targetX,targetY);
    //         this->setAttackResult(targetX,targetY,result,expectData);
    //         return ;
    //     }
    //     //もし相手が角にいた場合は相手のHPで位置を記録&その地点を攻撃
    //     else if(target==103||target==102||target==101&&shipArrangement.isAttackable(targetX,targetY)){
    //         char result = this->getAttackResult(targetX,targetY);
    //         this->setAttackResult(targetX,targetY,result,expectData);
    //         return ;
    //     }
    // }
}

char Player::getAttackResult(int x,int y){
    cout << x+1 << "," << y+1 << "を攻撃" << endl;
    char result='*';
    while(!(result=='H'||result=='W'||result=='M')){
        cout << "攻撃結果を入力(ヒット=H,波高し=W,外れ=M):" << endl;
        cin >> result;
    }
    return result;
}

char Player::setAttackResult(int x,int y,char result,ExpectData &expectData){
    //攻撃したマス,if文の中などの条件でのみ使用
    auto target = expectData.attackData[y][x];
    //外れた場合はそのマスと周囲の8マスに0を入力
    if(result=='M'){
        expectData.setAttackResult(x,y,MISS);
        for(int i=0; i<DYA.size(); i++){
            int targetX = x+DXA[i];
            int targetY = y+DYA[i];
            if(DataAnalyzer::checkValidPosition(targetX,targetY)){
                expectData.setAttackResult(targetX,targetY,MISS);
            }
        }
    }
    else if(result=='W'){
        expectData.setAttackResult(x,y,MISS);
        for(int i=0; i<DYA.size(); i++){
            int targetX = x+DXA[i];
            int targetY = y+DYA[i];
            //波高しの点と未探索の点を波高しとして1を入力
            if(DataAnalyzer::checkValidPosition(targetX,targetY)&&(target==-1||target==1)&&target!=100){
                expectData.setAttackResult(targetX,targetY,WAVE);
            }
        }
    }
    else if(result=='H'){
        //バグ防止のため冗長な記法ですが、お許しを...
        if(expectData.attackData[y][x]==-1||expectData.attackData[y][x]==1||expectData.attackData[y][x]==0)expectData.setAttackResult(x,y,HIT);
        else if(expectData.attackData[y][x]==HIT)expectData.setAttackResult(x,y,HIT-1);
        else if(expectData.attackData[y][x]==HIT-1)expectData.setAttackResult(x,y,HIT-2);
        else if(expectData.attackData[y][x]==HIT-2)expectData.setAttackResult(x,y,HIT-3);
    }
    cout << result << "を記録" << endl;
    return result;
}


class Partner{
    public:
        char attack(ShipArrangeMent shipArrangement,ShipCorrection shipCorrection);
        void move();
};

char Partner::attack(ShipArrangeMent shipArrangement,ShipCorrection shipCorrection){
    int x,y;
    x=-1;
    y=-1;
    while(!DataAnalyzer::checkValidPosition(x,y)){
        cout << "攻撃する座標を入力(1~5)" << endl;
        cout << "x: ";
        cin >> x;
        x--;
        cout << "y: ";
        cin >> y;
        y--;
    }
    if(shipArrangement.arrangement[y][x]!=-1){
        cout << "命中" << endl;
        auto tmpShip = shipCorrection.correction[shipArrangement.arrangement[y][x]];
        tmpShip.hp--;
        //hit
        return 'H';
    }
    for(int i=0; i<DYA.size(); i++){
        int targetX=x+DXA[i];
        int targetY=y+DYA[i];
        if(DataAnalyzer::checkValidPosition(targetX,targetY)&&shipArrangement.arrangement[targetY][targetX]!=-1){
            cout << "波高し" << endl;
            //wave
            return 'W';
        }
    }
    //miss
    return 'M';
}

void Partner::move(){
    char direction;
    int count;
    while(!(direction=='n'||direction=='s'||direction=='e'||direction=='w')){
        cout << "動く方向を入力(n,s,e,w):" << endl;
        cin >> direction;
    }
    while(!(count==1||count==2)){
        cout << "動くマスの数を入力" << endl;
        cin >> count;
        cout << "マス" << endl;
    }
    cout << direction << "方向に" << count << "マス移動" << endl;
}

int main(){
    //船を配置する工程
    //-------------------------------------------
    ShipCorrection shipcorrection;
    ShipArrangeMent shipArrangement;
    shipArrangement.set(MAPWIDTH,MAPHEIGHT);
    //最適な船の配置を探索
    vector<vector<int>> checkedPosition(MAPHEIGHT,vector<int>(MAPWIDTH,0));
    vector<pair<int,int>> bestPosition(SHIPNUM);
    for(int i=0; i<SHIPNUM; i++){
        pair<int,int> tmp=DataAnalyzer::findBestPos(checkedPosition);
        bestPosition[i].first=tmp.first;
        bestPosition[i].second=tmp.second;
        checkedPosition[tmp.first][tmp.second]=-1;
    }
    //船の座標・データをセットする
    for(int i=0; i<SHIPNUM; i++){
        Ship s;
        s.set(bestPosition[i].first,bestPosition[i].second,HP,i+1);
        shipcorrection.setCorrection(s);
        shipArrangement.setShipPosition(shipcorrection.correction[i]);
    }
    // shipArrangement.showArrangement();
    //-------------------------------------------
    //ゲームの開始
    //-------------------------------------------
    Player player;
    Partner partner;
    ExpectData expectData;
    expectData.set(MAPWIDTH,MAPHEIGHT);
    int turn=-1;
    cout << "先行ならば0,後攻ならば1を入力" << endl;
    while(!(turn==0||turn==1))cin >> turn;
    while(true){
        cout << "turn:" << turn << endl;
        expectData.showAttackData();
        cout << endl;
        if(turn%2==0){
            shipArrangement.updateAttackablePosition();
            player.desideAction(expectData,shipArrangement);
            cout << "turn:" << turn << "\n" << endl;
            turn++;
        }
        if(turn%2==1){
            char action='*';
            while(!(action=='a'||action=='m')){
                cout << "攻撃ならばa,移動ならばmを入力" << endl;
                cin >> action;
            }
            if(action=='a'){
                partner.attack(shipArrangement,shipcorrection);
            }
            else {
                partner.move();
            }
            cout << "turn:" << turn << "\n" << endl;
            turn++;
        }
    }
}