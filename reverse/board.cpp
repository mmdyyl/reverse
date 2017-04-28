#include "board.h"
int board::winner() const
{
	if (whiteCheeseNum > blackCheeseNum)
	{
		return 0;
	}
	else if (whiteCheeseNum < blackCheeseNum)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int board::gameEnd() const
{
	if (blackAvaliable.size() == 0 && whiteAvaliable.size() == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void board::print() const
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			std::cout << map[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

board board::oneStep(int color, const point& position) const
{
	board tmp=board(*this);
	tmp[position]=color;
    if(color==1)
    {
        tmp.blackCheeseNum++;
    }
    else
    {
        tmp.whiteCheeseNum++;
    }
	tmp.reversecolor(position);
	tmp.initial();
	return tmp;

}

void board::detectAvaliable(int colorflag)
{
	for (int i = 0; i<96; i++)
	{
		std::string direct;
		point node = getbegininfo(i,direct);
		int state = 0;
		
		while (node.x != -1)
		{
			switch (state)
			{
			case 0:
				if (map[node.x][node.y] == colorflag)
				{
					state = 1;
					
				}
				break;
			case 1:
				if (map[node.x][node.y] == !colorflag) {
					state = 2;
				}
				if (map[node.x][node.y] != colorflag && map[node.x][node.y] != !colorflag) {
					state = 0;
				}

				break;
			case 2:
				if (map[node.x][node.y] != colorflag && map[node.x][node.y] != !colorflag) {
					state = 0;
					if (colorflag == 1)
					{
						blackAvaliable.insert(node);
					}
					else
					{
						whiteAvaliable.insert(node);
					}
				}
				if (map[node.x][node.y] == colorflag)
				{
					state = 0;
				}
				break;
			}
			node = nextnode(node, direct);
		}
	}
}


point board::nextnode(point nownode, std::string direct)
{
	point resultnode = nownode;
	if (direct == "t")
	{
		resultnode.y--;
	}
	else if (direct == "d")
	{
		resultnode.y++;
	}
	else if (direct == "l")
	{
		resultnode.x--;
	}
	else if (direct == "r")
	{
		resultnode.x++;
	}
	else if (direct == "tl")
	{
		resultnode.y--;
		resultnode.x--;
	}
	else if (direct == "tr")
	{
		resultnode.x++;
		resultnode.y--;
	}
	else if (direct == "dl")
	{
		resultnode.x--;
		resultnode.y++;
	}
	else if (direct == "dr")
	{
		resultnode.y++;
		resultnode.x++;
	}
	
	if (resultnode.x>7 || resultnode.x<0 || resultnode.y>7 || resultnode.y<0)
	{
		resultnode.x = -1;
		resultnode.y = -1;
	}
	return resultnode;
}

point board::getbegininfo(int index,std::string& direct)
{
	point position;
	
	if (index / 24<1)
	{
		position = point(index%8,0);
		if (index / 8<1)
		{
			direct = "d";
		}
		else if (index / 8<2)
		{
			direct = "dr";
		}
		else
		{
			direct = "dl";
		}
	}
	else if (index / 24<2)
	{
		index = index % 24;
		position = point(0, index % 8);
		if (index / 8<1)
		{
			direct = "r";
		}
		else if (index / 8<2)
		{
			direct = "dr";
		}
		else
		{
			direct = "tr";
		}
	}
	else if (index / 24<3)
	{
		index = index % 24;
		position = point(index % 8, 7);
		if (index / 8<1)
		{
			direct = "t";
		}
		else if (index / 8<2)
		{
			direct = "tl";
		}
		else
		{
			direct = "tr";
		}
	}
	else
	{
		index = index % 24;
		position = point(7, index % 8);
		if (index / 8<1)
		{
			direct = "l";
		}
		else if (index / 8<2)
		{
			direct = "tl";
		}
		else
		{
			direct = "dl";
		}
	}
	return position;
}

void board::reversecolor(point a)
{
	int colorflag = map[a.x][a.y];
	int x = a.x-1;
	int y = a.y;
    std::vector<point> tbd;
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{

        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
		else if (map[x][y] == !colorflag)
		{
            tbd.push_back(point(x,y));

		}
		else
			break;
		x--;
	}
	x = a.x + 1;
	y = a.y;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{

        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));
		}
		else
			break;
		x++;
	}
	x = a.x;
	y = a.y - 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		y--;
	}
	x = a.x;
	y = a.y + 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		y++;
	}
	x = a.x - 1;
	y = a.y - 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		x--;
		y--;
	}
	x = a.x - 1;
	y = a.y + 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		x--;
		y++;
	}
	x = a.x + 1;
	y = a.y + 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		x++;
		y++;
	}
	x = a.x + 1;
	y = a.y - 1;
    tbd.clear();
	while (x >= 0 && y >= 0 && x <= 7 && y <= 7)
	{
        if(map[x][y]==colorflag)
        {
            for(int i=0;i<tbd.size();i++){
                (*this)[tbd[i]]=colorflag;
            }
            if (colorflag == 1)
            {
                blackCheeseNum+=tbd.size();
                whiteCheeseNum-=tbd.size();
            }
            else
            {
                blackCheeseNum-=tbd.size();
                whiteCheeseNum+=tbd.size();
            }
            break;
        }
        else if (map[x][y] == !colorflag)
        {
            tbd.push_back(point(x,y));

        }
		else
			break;
		x++;
		y--;
	}
}

const std::vector<point> board::getAvaliable(int color)
{
    std::vector<point> result;
	if(color==0)
    {
        std::set<point>::iterator it=whiteAvaliable.begin();

        while(it!=whiteAvaliable.end())
        {
            result.push_back(*it);
            it++;
        }
    }
	else
    {
        std::set<point>::iterator it=blackAvaliable.begin();

        while(it!=blackAvaliable.end())
        {
            result.push_back(*it);
            it++;
        }
    }
    return result;
}

void board::initial()
{
	whiteAvaliable.clear();
	blackAvaliable.clear();
	detectAvaliable(1);
	detectAvaliable(0);
}

std::string point::toString() const
{
	std::stringstream ssm;
	ssm<<x<<','<<y;
	return ssm.str();
}

double board::getscore(int color)const{
	if(color==1)
	{
		return blackCheeseNum;
	}
	else
	{
		return whiteCheeseNum;
	}
}

const std::set<point> board::getAvaliableset(int color) {
    if(color==1)
    {
        return blackAvaliable;
    }
    else
    {
        return whiteAvaliable;
    }

}
