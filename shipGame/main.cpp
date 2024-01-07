#include <bits/stdc++.h>
using namespace std;
const int HP = 3;
const int MAPWIDTH=5;
const int MAPHEIGHT=5;
const int SHIPNUM=4;
//味方のターンと相手のターンをそれぞれ0,1とする
int TURN = 0;
vector<int> dx={1,2,-1,-2,0,0,0,0};
vector<int> dy={0,0,0,0,1,2,-1,-2};
vector<vector<int>> v(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
vector<vector<int>> v2(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
void resetMap(){
    v.assign(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
    v2.assign(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
}
void showMap(){
    for(int i=0; i<MAPHEIGHT; i++){
        for(int j=0; j<MAPWIDTH; j++){
            cout << v[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i=0; i<MAPHEIGHT; i++){
        for(int j=0; j<MAPWIDTH; j++){
            cout << v2[i][j] << "   ";
        }
        cout << endl;
    }
}


bool isInScope(int targetX,int targetY){
    if(targetX>=0&&targetX<5&&targetY>=0&&targetY<5){
        // cout << "有効な座標です" << endl;
        return true;
    }
    else{
        // cout << "無効な座標が入力されました" << endl;
        return false;
    }
}

vector<vector<int>>& setTargetMap(){
    if(TURN==0)return v2;
    else return v;
} 
class Ship{
    public:
        int x;
        int y;
        int hp;
        int number;
        void set(int x,int y,int hp,int number);
        void setShip(vector<vector<int>> &v,Ship s);
        void setPosition(int x,int y);
};

vector<Ship> Ships;
vector<Ship> eShips;

vector<Ship>&setTargetShips(){
    if(TURN==0)return Ships;
    else return eShips;
}

void Ship::set(int x,int y,int hp, int number){
            this->x=x;
            this->y=y;
            this->hp=hp;
            this->number=number;
}
void Ship::setShip(vector<vector<int>> &v,Ship s){
    if(isInScope(s.x,s.y)&&v[s.y][s.x]==-1){
        // cout << "(" << s.x+1 << "," << s.y+1 << ")に値を配置しました" << endl; 
        v[s.y][s.x]=s.number;
    }
    // else cout << "すでに船が配置されています" << endl;
}
void Ship::setPosition(int x,int y){
    this->x=x;
    this->y=y;
}
void setShips(){
    for(int i=0; i<SHIPNUM; i++){
        Ships[i].setShip(v,Ships[i]);
        eShips[i].setShip(v2,eShips[i]);
    }
}

bool isAttackable(int x,int y){
    if(isInScope(x,y)==false){
        return false;
    }
    vector<vector<int>> attackablePoint(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
    for(int i=0; i<MAPHEIGHT; i++){
        for(int j=0; j<MAPWIDTH; j++){
            //vの中に配置された船がある時、周囲8マスを攻撃範囲にする
            if(isInScope(x,y)&&v[i][j]!=-1){
                for(int k=0; k<dy.size(); k++){
                    for(int l=0; l<dx.size(); l++){
                        int targetX=j+dx[l];
                        int targetY=i+dy[k];
                        if(isInScope(targetX,targetY))attackablePoint[targetY][targetX]=0;
                    }
                }
            }
        }
    }
    if(attackablePoint[y][x]==0)return true;
    return false;
}
int checkAttackResult(vector<vector<int>> &v,int x,int y){
    //命中,波高し,ミスをそれぞれ0,1,2で返す
    //命中時の処理
    if(v[y][x]!=-1)return 0;
    //その他の判定
    else{
        for(int i=0; i<dy.size(); i++){
            int targetX=x+dx[i];
            int targetY=y+dy[i];
            if(v[targetY][targetX]!=-1){
                return 1;
            }
        }
        return 2;
    }
}
bool attackStep(){
    int x,y;
    cout << "攻撃したい座標を入力" << endl;
    cout << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    x--;
    y--;
    if(isAttackable(x,y)==false){
        cout << "\033[31m攻撃できない座標です\033[m" << endl;
        return false;
    }
    int result = checkAttackResult(setTargetMap(),x,y);
    cout << "(" << x << "," << y << ")を攻撃" << endl;
    if(result==0){
        setTargetShips()[setTargetMap()[y][x]].hp--;
        if(setTargetShips()[setTargetMap()[y][x]].hp==0)cout << "撃沈" << endl;
        cout << "命中" << endl;
        // cout << setTargetShips()[setTargetMap()[y][x]].hp << endl;
    }
    else if(result==1){
        cout << "波高し" << endl;
    }
    else if(result==2){
        cout << "ミス" << endl;
    }
    return true;
}

bool isMovable(vector<vector<int>> &v,int x,int y,Ship s){
    if(isInScope(x,y)==false){
        // cout << x << " " << y << endl;
        // cout <<abs(s.x-x)+abs(s.y-y) << endl;
        return false;
    }
    vector<vector<int>> movablePoint(MAPHEIGHT,vector<int>(MAPWIDTH,-1));
    for(int i=0; i<dy.size(); i++){
            int targetX=s.x+dx[i];
            int targetY=s.y+dy[i];
            // cout << targetX << " " << targetY << endl;
            if(isInScope(targetX,targetY))movablePoint[targetY][targetX]=0;
        }
    if(movablePoint[y][x]==0)return true;
    return false;
}

bool moveStep(){
    int shipNum=-1;
    int x,y;
    cout << "移動したい船を選択:";
    cin >> shipNum;
    shipNum--;
    if(shipNum<0||shipNum>=5){
        cout << "選択できない船です" << endl;
        return false;
    }
    vector<Ship> targetShips = setTargetShips();
    Ship *targetShip = &targetShips[shipNum];
    cout << "移動したい座標を選択:" << endl;
    cout << "x:";
    cin >> x;
    cout << "y:";
    cin >> y;
    x--;
    y--;
    if(isMovable(setTargetMap(),x,y,*targetShip)==false){
        cout << "\033[31m移動できない座標です\033[m" << endl;
        return false;
    }

    setTargetShips()[shipNum].setPosition(x,y);

    targetShips[shipNum].setPosition(x,y);

    cout << "船" << targetShip->number << "を(" << x+1 << "," << y+1 << ")に移動" << endl;
    resetMap();
    setShips();
    return true;
}

int main(){
    showMap();
    Ship s1;
    Ship s2;
    Ship s3;
    Ship s4;
    s1.set(0,0,HP,1);
    s2.set(1,0,HP,2);
    s3.set(2,0,HP,3);
    s4.set(3,0,HP,4);
    Ships={s1,s2,s3,s4};
    Ship se1;
    Ship se2;
    Ship se3;
    Ship se4;
    se1.set(0,4,HP,1);
    se2.set(1,1,HP,2);
    se3.set(2,4,HP,3);
    se4.set(4,4,HP,4);
    eShips={se1,se2,se3,se4};
    //---------------------------------------
    setShips();
    showMap();
    //---------------------------------------
    // while(true){
    //     while(!attackStep()){}
    //     TURN=1;
    //     while(!attackStep()){}
    //     TURN=0;
    // }
    //---------------------------------------
    // while(true){
    //     while(!moveStep()){}
    //     showMap();
    //     TURN=1;
    //     while(!moveStep()){}
    //     showMap();
    //     TURN=0;
    // }
    //---------------------------------------
    while(true){
        int tmp;
        cout << "Player1:attack or move?(0 or 1)" << endl;
        cin >> tmp;
        if(tmp==0)while(!attackStep()){}
        else if(tmp==1) while(!moveStep()){}
        else cout << "無効な操作です" << endl;
        TURN=1;
        cout << "Player2:attack or move?(0 or 1)" << endl;
        cin >> tmp;
        if(tmp==0)while(!attackStep()){}
        else if(tmp==1) while(!moveStep()){}
        else cout << "無効な操作です" << endl;
        TURN=0;
    }
    return 0;
}


//実装すべきもの
//戻る機能
//ヒューリスティスクス