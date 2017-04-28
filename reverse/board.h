#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<sstream>
class point
{
	friend class board;
public:
	point():
		x(0), y(0)
	{}
	point(int a, int b) :
		x(a), y(b)
	{}
	bool operator==(const point& a)
	{
		if(a.x==x&&a.y==y)
			return 1;
		else
			return 0;
	}
	bool operator<(const point& a) const
	{
		if(x<a.x)
			return true;
		else if(x==a.x)
		{
			if(y<a.y)
				return true;
		}
		return false;
	}
	std::string toString() const;
private:
	int x;
	int y;
};
class board
{
public:
	board():
		map(),whiteCheeseNum(2),blackCheeseNum(2),whiteAvaliable(),blackAvaliable()
	{
		for (int i = 0; i < 8; i++)
		{
			map.push_back(std::vector<int>(8, -1));
		}
		map[3][3] = 0;
		map[3][4] = 1;
		map[4][3] = 1;
		map[4][4] = 0;
		initial();
	}
	int& operator[](point n)
	{
		return map[n.x][n.y];
	}
	//board(board bd);
	int winner() const;
	int gameEnd() const;
	double getscore(int color)const;
	void print() const;
	board oneStep(int color, const point& position) const;
	const std::vector<point> getAvaliable(int color);
    const std::set<point> getAvaliableset(int color);
private:
	std::vector<std::vector<int>> map;
	int whiteCheeseNum;
	int blackCheeseNum;
	std::set<point> whiteAvaliable;
	std::set<point> blackAvaliable;
	void initial();
	void detectAvaliable(int colorflag);
	point nextnode(point nownode, std::string direct);
	point getbegininfo(int index, std::string& direct);
	void reversecolor(point a);
};

