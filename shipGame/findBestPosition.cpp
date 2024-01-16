#include <iostream>
#include <vector>
#include <array>

using namespace std;

const int GRID_SIZE = 5;
const int NUM_SUBMARINES = 4;

array<array<bool, GRID_SIZE>, GRID_SIZE> initializeGrid() {
    return array<array<bool, GRID_SIZE>, GRID_SIZE>{};
}

pair<int, int> findBestPosition(const array<array<bool, GRID_SIZE>, GRID_SIZE>& grid) {
    int maxCoverage = 0;
    pair<int, int> bestPosition;
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (!grid[x][y]) {
                int coverage = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && !grid[nx][ny]) {
                            coverage++;
                        }
                    }
                }
                cout << "x:" << x << " y:" << y << " coverage:" << coverage << endl;
                if (coverage > maxCoverage) {
                    maxCoverage = coverage;
                    bestPosition = make_pair(x, y);
                }
            }
        }
    }
    cout << bestPosition.first << " " << bestPosition.second << endl;
    return bestPosition;
}

void printGrid(const array<array<char, GRID_SIZE>, GRID_SIZE>& grid) {
    for (const auto& row : grid) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}

int main() {
    //潜水艦の座標を入れておくvector
    vector<pair<int, int>> submarinePositions;
    //マップ
    auto grid = initializeGrid();
    //ベストポジションを探す
    for (int i = 0; i < NUM_SUBMARINES; i++) {
        auto [x, y] = findBestPosition(grid);
        submarinePositions.emplace_back(x, y);
        grid[x][y] = true;
    }

    //表示用のvector?
    array<array<char, GRID_SIZE>, GRID_SIZE> displayGrid{};
    for (auto& row : displayGrid) {
        row.fill('.');
    }

    //
    for (auto [x, y] : submarinePositions) {
        displayGrid[x][y] = 'S';
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (0 <= nx && nx < GRID_SIZE && 0 <= ny && ny < GRID_SIZE && displayGrid[nx][ny] != 'S') {
                    displayGrid[nx][ny] = 'X';
                }
            }
        }
    }

    printGrid(displayGrid);
    return 0;
}
