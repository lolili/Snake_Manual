// Snake_Manual.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Snake.h"
#include <conio.h>
#include<iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	Snake snake;
	int ch;
	int last = 105;
    while (1){
        if (_kbhit()){
            ch = _getch();
			//cout<<ch<<" ";
			if(last == ch || abs(last-ch) == 2)continue;
			if(ch == 105) {last = ch; snake.move('U');}
			if(ch == 107) {last = ch; snake.move('D');}
			if(ch == 106) {last = ch; snake.move('L');}
			if(ch == 108) {last = ch; snake.move('R');}
        }
		else
		{
			if(last == 105) snake.move('U');
			if(last == 107) snake.move('D');
			if(last == 106) snake.move('L');
			if(last == 108) snake.move('R');
		}
    }
	return 0;
}

