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

//船の情報を管理するためのクラス
class Ship{
    private:
        int x;
        int y;
        int hp;
        int number;
    public:
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
        pair<int,int> getPosition(){
            pair<int,int> p = {this->x,this->y};
            return p;
        }
        int getNumber(){
            return this->number;
        }
};
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

class Coverage{
    private:
        int width;
        int height;
        vector<vector<int>> coverage;
    public:
        void set(){
            this->width=MAPWIDTH;
            this->height=MAPHEIGHT;
            this->coverage.assign(this->height,vector<int>(this->width,-1));
        } 
        vector<vector<int>> &getCoverage(){
            return this->coverage;
        }
        void setCoverage(ShipPlacement shipPlacement){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    if(shipPlacement.getArrangement()[i][j]!=-1){
                        this->coverage[i][j]=1;
                        for(int k=0; k<DXA.size(); k++){
                            int targetX=j+DXA[k];
                            int targetY=i+DYA[k];
                            if(DataAnalyzer::checkValidPosition(targetX,targetY)){
                                this->coverage[targetY][targetX]=1;
                            }
                        }
                    }
                }
            }
        }
        //配置を表示
        void showCoverage(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    std::cout << this->coverage[i][j] << " ";
                }
                std::cout << endl;
            }
            cout << endl;
        }
};

class AttackData{
    int width;
    int height;
    vector<vector<int>> attackVector;
    void set(){
            this->width=MAPWIDTH;
            this->height=MAPHEIGHT;
            this->attackVector.assign(this->height,vector<int>(this->width,-1));
    } 
    vector<vector<int>> &getAttackVector(){
            return this->attackVector;
    }
    void showCoverage(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    std::cout << this->attackVector[i][j] << " ";
                }
                std::cout << endl;
            }
            cout << endl;
    }
};

class AttackedData{
    int width;
    int height;
    vector<vector<int>> attackedVector;
    void set(){
            this->width=MAPWIDTH;
            this->height=MAPHEIGHT;
            this->attackedVector.assign(this->height,vector<int>(this->width,-1));
    } 
    vector<vector<int>> &getAttackedVector(){
            return this->attackedVector;
    }
    void showCoverage(){
            for(int i=0; i<this->height; i++){
                for(int j=0; j<this->width; j++){
                    std::cout << this->attackedVector[i][j] << " ";
                }
                std::cout << endl;
            }
            cout << endl;
    }
};

class DataCorrection{
    private:
        ShipPlacement shipPlacement;
        Coverage coverage;
    public:
        void set(ShipPlacement shipPlacement){
            this->shipPlacement=shipPlacement;
        }
        void set(Coverage coverage){
            this->coverage=coverage;
        }
        ShipPlacement getShipPlacement(){
            return this->shipPlacement;
        }
        Coverage getCoverage(){
            return this->coverage;
        }
};

class Player{
    public:
        void decideAction(DataCorrection dataCorrection){
            this->attack(dataCorrection);
        }
        void attack(DataCorrection dataCorrection){
            int x=0;
            int y=0;
            Coverage coverage=dataCorrection.getCoverage();
            for(int i=0; i<MAPHEIGHT; i++){
                for(int j=0; j<MAPWIDTH; j++){
                    if(coverage.getCoverage()[i][j]==1){
                        x=j;
                        y=i;
                    }
                }
            }
        }
        void setAttackResult(DataCorrection dataCorrection){
            cout << "攻撃結果を入力" << endl;
        }
};




class Partner{
    public:
        char attack(DataCorrection dataCorrection);
        void move();
};

char Partner::attack(DataCorrection dataCorrection){
    ShipPlacement shipPlacement = dataCorrection.getShipPlacement();
    vector<vector<int>> arrangement=shipPlacement.getArrangement();
    int x,y;
    x=-1;
    y=-1;

    while(!DataAnalyzer::checkValidPosition(x,y)){
        std::cout << "攻撃する座標を入力" << endl;
        // cout << "y: ";
        std::cout << "y(a~e): ";
        char c;
        cin >> c;
        y=c;
        y-=97;
        std::cout << "x(1~5): ";
        cin >> x;
        x--;
        if(DataAnalyzer::checkValidPosition(x,y)){
            break;
        }
    }
    cout << x << " " << y << endl;
    if(arrangement[y][x]!=-1){
        std::cout << "命中" << endl;
        return 'H';
    }
    for(int i=0; i<DYA.size(); i++){
        int targetX=x+DXA[i];
        int targetY=y+DYA[i];
        if(DataAnalyzer::checkValidPosition(targetX,targetY)&&arrangement[targetY][targetX]!=-1){
            std::cout << "波高し" << endl;
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
    //船を格納しておく配列
    ShipCorrection shipCorrection;
    shipCorrection.set();
    //-------------------------------------------
    //船の設定
    Ship s0;
    s0.set(0,0,HP,0);
    shipCorrection.registerShip(s0);
    Ship s1;
    s1.set(1,0,HP,1);
    shipCorrection.registerShip(s1);
    Ship s2;
    s2.set(0,1,HP,2);
    shipCorrection.registerShip(s2);
    Ship s3;
    s3.set(1,1,HP,3);
    shipCorrection.registerShip(s3);
    ShipPlacement shipPlacement;
    shipPlacement.set(shipCorrection);
    shipPlacement.showArrangement();
    //-------------------------------------------
    //-------------------------------------------
    //データを格納
    DataCorrection dataCorrection;
    Coverage coverage;
    dataCorrection.set(shipPlacement);
    coverage.set();
    coverage.setCoverage(shipPlacement);
    coverage.showCoverage();
    //-------------------------------------------
    //-------------------------------------------
    //コレクションに船を設定
    shipCorrection.registerShip(s0);
    shipCorrection.registerShip(s1);
    shipCorrection.registerShip(s2);
    shipCorrection.registerShip(s3);
    //-------------------------------------------
    //-------------------------------------------
    //対戦相手のインスタンス
    Partner partner;
    //-------------------------------------------
    //-------------------------------------------
    //ゲーム開始
    int turn=-1;
    cout << "先行ならば0,後攻ならば1を入力" << endl;
    dataCorrection.getShipPlacement().showArrangement();
    while(!(turn==0||turn==1))cin >> turn;
     while(true){
        if(turn%2==0){
            cout << "turn:" << turn << "\n" << endl;
            cout << "続行[c],終了[e],戻る[b]" << endl;
            turn++;
        }
        if(turn%2==1){
            char action='*';
            while(!(action=='a'||action=='m'||action=='e'||action=='b')){
                cout << "攻撃[a],移動[m],終了[e],戻る[b]" << endl;
                cin >> action;
            }
            if(action=='a'){
                char result = partner.attack(dataCorrection);
                cout << result << endl;
            }
            else if(action=='m'){
                partner.move();
            }
            else if(action=='e'){
            }
            else if(action=='b'){
            }
            cout << "turn:" << turn << "\n" << endl;
            turn++;
        }
    //-------------------------------------------
    }
}