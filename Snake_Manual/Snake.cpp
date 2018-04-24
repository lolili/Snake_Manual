#include "StdAfx.h"
#include "Snake.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
using namespace std;

Snake::Snake(void)
{
	string str;
	do
	{
		system("cls");
		cout<<"                                                     "<<endl;
		cout<<"                                                     "<<endl;
		cout<<"                                                     "<<endl;
		cout<<"====================================================="<<endl;
		cout<<"====================   Snake  ======================="<<endl;
		cout<<"====================================================="<<endl;
		cout<<"=========Input y/Y to start or n/N to exit==========="<<endl;
		cout<<"====================================================="<<endl;
		cout<<"=======================>";
		cin>>str;
	}while(str != "y" && str != "Y" && str != "n" && str != "N");
	if(str == "y" || str == "Y")
	{
		iSnake = new int*[sH]; 
		for( int i = 0; i < sH; i++ )
		iSnake[i] = new int[sW];
		for(int i =0; i < sH; i++)
		{
			for(int j = 0; j < sW; j++)
			{
				if(i == 0 || j == 0 || i == sH - 1 || j == sW - 1)
					iSnake[i][j] = wall;
				else iSnake[i][j] = blank; 
			}
		}
		startGame();
	}
	else exit(1);
}
void Snake::gameOver()
{
	string str;
	do
	{
		system("cls");
		cout<<"                                                     "<<endl;
		cout<<"                                                     "<<endl;
		cout<<"                                                     "<<endl;
		cout<<"====================================================="<<endl;
		cout<<"===================  Game  Over  ===================="<<endl;
		cout<<"====================================================="<<endl;
		cout<<"========Input y/Y to restart or n/N to exit=========="<<endl;
		if(resurrect)
			cout<<"===============Input r/R to resurrect================"<<endl;
		cout<<"====================================================="<<endl;
		cout<<"=======================>";
		cin>>str;
	}while(str != "y" && str != "Y" && str != "n" && str != "N" && !(resurrect && (str == "r" || str == "R")));
	if(str == "y" || str == "Y")
	{
		queue<point> empty;
		swap(empty, nextTail);
		str = "r";
	}
	if(str == "r" || str == "R")
	{
		for( int i = 0; i < sH; i++ )
		delete[] iSnake[i];
		delete[] iSnake;
		iSnake = new int*[sH]; 
		for( int i = 0; i < sH; i++ )
			iSnake[i] = new int[sW];
		for(int i =0; i < sH; i++)
		{
			for(int j = 0; j < sW; j++)
			{
				if(i == 0 || j == 0 || i == sH - 1 || j == sW - 1)
					iSnake[i][j] = wall;
				else iSnake[i][j] = blank; 
			}
		}
		startGame();
	}
	else exit(1);
}
void Snake::startGame()
{
	iSnake[sH/2][sW/2] = head; //snake
	shead.x = sH / 2;
	shead.y = sW / 2;
	stail.x = sH / 2;
	stail.y = sW / 2;
	getFood();
	drawScreen();
	return;
}
void Snake::getFood()
{
	srand((unsigned)time(NULL));
	int foodX = 0, foodY = 0;
	do
	{
		foodX = rand() % sH-1;
		foodY = rand() % sW-1;
	}while(iSnake[foodX][foodY] != blank);
	iSnake[foodX][foodY] = food;
	return;
}
void Snake::drawScreen()
{
	system("cls");
//	ofstream file;
//	file.open("log.dat",ios::app);
	for(int i = 0; i < sH; i++)
	{
		for(int j = 0; j < sW; j++)
		{
			switch(iSnake[i][j])
			{
			case wall:
				if(i == 0 || i == sH - 1)
				{
					cout<<"-";
					/*if(debug)
					{
						file<<"-";
					}*/
				}
				else 
				{
					cout<<"|";
					/*if(debug)
					{
						file<<"|";
					}*/
				}
				break;
			case body:
			case tail:
				cout<<"#";
				/*if(debug)
				{
					file<<"#";
				}*/
				break;
			case head:
				cout<<"@";
				/*if(debug)
				{
					file<<"@";
				}*/
				break;
			case food:
				cout<<"*";
				/*if(debug)
				{
					file<<"*";
				}*/
				break;
			default:
				cout<<" ";
				/*if(debug)
				{
					file<<" ";
				}*/
				break;
			}
		}
		cout<<endl;
		/*if(debug)
		{
			file<<endl;
		}*/
	}
//	file.close();
	return;
}
Snake::~Snake(void)
{
}

void Snake::move(char cnextMove)
{
	point nextMove;
	nextMove.x = 0, nextMove.y = 0;
	switch(cnextMove)
	{
	case 'U':
		nextMove.x = shead.x - 1;
		nextMove.y = shead.y;
		break;
	case 'D':
		nextMove.x = shead.x + 1;
		nextMove.y = shead.y;
		break;
	case 'L':
		nextMove.x = shead.x;
		nextMove.y = shead.y - 1;
		break;
	case 'R':
		nextMove.x = shead.x;
		nextMove.y = shead.y + 1;
		break;
	default:
		return;
	}
	if(nextMove.x == 0 || nextMove.y == 0 || (iSnake[nextMove.x][nextMove.y] != blank && iSnake[nextMove.x][nextMove.y] != food))
	{
		gameOver();
		return;
	}
	else
	{
		iSnake[shead.x][shead.y] = body;
		shead = nextMove;
		nextTail.push(shead);
		if(!ifEatFood(nextMove))
		{
			iSnake[stail.x][stail.y] = blank;
			stail = nextTail.front();
			nextTail.pop();
		}
		else
		{
			getFood();
			// rewrite status to tail
		}
		iSnake[nextMove.x][nextMove.y] = head;
		drawScreen();
	}
	return;
}
bool Snake::ifEatFood(point nextMove)
{
	if(iSnake[nextMove.x][nextMove.y] == food)
		return true;
	return false;
}