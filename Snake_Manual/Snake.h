#pragma once
#include "SnakeConfig.h"
#include <queue>
using namespace std;

#define wall -1
#define blank 0
#define body 1
#define head 2
#define tail 3
#define food 4

struct point
{
	int x;
	int y;
};
class Snake
{
public:
	Snake(void);
	~Snake(void);
	void move(char);
private:
	void gameOver();
	void startGame();
	void getFood();
	void drawScreen();
	bool ifEatFood(point);
private:
	int** iSnake;
	point shead; // 
	point stail; // when no tail, tail euqal head
	queue<point> nextTail;   // if move, tail move here, -1 means no tail
	//char snakeFace; // direction of head facing to 
};
