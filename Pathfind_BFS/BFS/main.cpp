#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <queue>
using namespace std;

#define SIZE_X 20
#define SIZE_Y 10
int map[SIZE_X][SIZE_Y];

struct path
{
    int posX, posY; // 현재 좌표
    struct path* parentPath; // 부모 노드 (최단 경로에 사용)
};

void initMap()
{
    //Init
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            map[j][i] = 0;
        }
    }
    map[0][0] = 1;

    int X = 0, Y = 0;
    srand(time(NULL));
    for (int i = 0; i < 100000; i++)
    {
        int rotate = rand() % 4 + 1;

        switch (rotate)
        {
        case 1:
            if (Y == 0) continue;
            if (map[X][Y - 2] == 0)
            { 
                Y--; map[X][Y] = 1;
                Y--; map[X][Y] = 1;
            }
            else  Y -= 2; 
            break;
        case 2:
            if (X >= SIZE_X - 2) continue;
            if (map[X + 2][Y] == 0)
            { 
                X++; map[X][Y] = 1;
                X++; map[X][Y] = 1;
            }
            else  X += 2; 
            break;
        case 3:
            if (Y >= SIZE_Y - 2) continue;
            if (map[X][Y + 2] == 0)
            { 
                Y++; map[X][Y] = 1;
                Y++; map[X][Y] = 1;
            }
            else  Y += 2; 
            break;
        case 4:
            if (X == 0) continue;
            if (map[X - 2][Y] == 0)
            { 
                X--; map[X][Y] = 1;
                X--; map[X][Y] = 1;
            }
            else  X -= 2; 
            break;
        }
    }
}
void drawMap()
{
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            if (map[j][i] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("□");
            }
            else if (map[j][i] == 1) printf("  ");
            else if (map[j][i] == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("■");
            }
        }
        printf("\n");
    }
}

// 정해진 맵 안에서 길찾기 
bool inMap(int xpos, int ypos)
{
    if (xpos >= 0 && xpos < SIZE_X &&
        ypos >= 0 && ypos < SIZE_Y) return true;
    else return false;
}

void findPath()
{
    int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} }; // 현재 좌표에서 상하좌우 이동

    int nowX = 0, nowY = 0;
    int visit[SIZE_X][SIZE_Y] = { 0 }; // 방문 체크

    path* p = new path;
    p->posX = nowX; p->posY = nowX; p->parentPath = nullptr;
    queue<path*> que;
    que.push(p);
    
    visit[nowX][nowY] = 1;

    while (!que.empty())
    {
        nowX = que.front()->posX; nowY = que.front()->posY;
        // 목표 지점에 도달했다면 목표 지점에서 [0, 0]까지 역순으로 경로를 표시
        if (nowX == SIZE_X - 2 && nowY == SIZE_Y - 2) 
        {
            path* printPath = que.front();
            while (printPath->parentPath != nullptr)
            {
                map[printPath->posX][printPath->posY] = 2;
                printPath = printPath->parentPath;
            }
            map[0][0] = 2;

            delete(printPath);
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nextX = nowX + dir[i][0];
            int nextY = nowY + dir[i][1];

            if (inMap(nextX, nextY) &&
                map[nextX][nextY] && !visit[nextX][nextY])
            {
                visit[nextX][nextY] = 1;
                path* nextP = new path;
                nextP->posX = nextX; nextP->posY = nextY; nextP->parentPath = que.front();
                que.push(nextP);
            }
        }
        que.pop();
    }
}

void main()
{
    initMap(); // 랜덤 맵 생성
    findPath();  // BFS 길찾기 
    drawMap(); // 생성된 맵 표시
    
    system("pause");
    return;
}