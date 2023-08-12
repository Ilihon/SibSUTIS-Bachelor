using namespace std;
class tPoint 
{

private:

    
    int dX;
    int dY;
    
protected:
	
	int x;
    int y;
    int color;
    char direction = 'R';
    int p;
	int z;

public: 


	/// constructor ///
    tPoint() 
    {
    	x = rand() % ((640) - (0) + 1) + (0);
		y=rand()%((480) - (0) + 1) + (0);
    	color = 1 + rand() % 15;
        p = 1;
        z = 1;
    }
    	
    //// get ////	
	int getColor()
	{
		return color;
	}
	
	int getX()
	{
		return x;
	}
	
	int getY()
	{
		return y;
	}
	
	virtual void draw()
	{
		setcolor(this -> getColor());
		circle(this -> getX(),this -> getY(), 1);
	}
	
	virtual void lineMove()
	{
		if(direction == 'R')
		{
			x++;
			if (x == 640)
			{
				direction = 'L';
			}
		} else if (direction == 'L')
		{
			x--;
			if (x == 0)
			{
				direction = 'R';
			}
		}
		
	}
	
	virtual void moveAround()
	{
		
	}

};

class tSegment:public tPoint
{
protected:
	int x2;
	int y2;
	
	
public:
	tSegment()
	{
		int d = 640, ch = 480;
			while(x2 > d || x2 < 0){
				x2 = rand() % ((x + 30) - (x - 30) + 1) + (x - 30);
			}
			while(y2 > ch || y2 < 0){
				y2 = rand() % ((y + 30)-(y - 30) + 1) + (y - 30);
			}
			
			if(x > x2 && y < y2){
				p =- 1;
				z =- 1;
			}
			
			if(x < x2 && y < y2) 
			{
				p =- 1;
			}
			
			if(x > x2 && y > y2) 
			{
				z =- 1;
			}
		
	}
		
	
	void draw() override
	{
		moveto(x, y);
		setcolor(color);
		lineto(x2, y2);
	}
	
	void lineMove() override
	{
		if(direction == 'R')
		{
			x++;
			x2++;
			if (x == 640 || x2 == 640)
			{
				direction = 'L';
			}
		} else if (direction == 'L')
		{
			x--;
			x2--;
			if (x == 0 || x2 == 0)
			{
				direction = 'R';
			}
		}
		
	}
	
	void moveAround() override
	{
		if(y == y2 || y + 1 == y2)
		{
				p=-p;
		}
		
		if(x == x2 || x + 1 == x2)
		{
			z =- z;
		}
		
		x += p;
		x2 += -p;
		y += z;
		y2 += -z;
	}
};

class tCircle: public tPoint
{
protected:
	float radius;	
	
public:
	tCircle()
	{
		radius = rand() % (20 - 5 + 1) + 5;
	}
	
	void draw() override
	{
		setcolor(color);
		circle(x, y, radius);
		setfillstyle(1, color);
		floodfill(x, y, color);
	}
	
	void lineMove() override
	{
		if (direction == 'R')
		{
			x++;
			if (x + radius == 640)
			{
				direction = 'L';
			}
		} else if (direction == 'L')
		{
			x--;
			if (x - radius == 0)
			{
				direction = 'R';
			}
		}
	}
};


class tRectangle: public tSegment{
protected:
	int corners[10];
	int s;
	int u;
	
public:
	tRectangle():tSegment()
	{
		z = 1;
		p = 1;
		s = 1;
		u = 1;
		x2 = rand() % (x + 30 - (x + 1) + 1) + (x + 1);
		y2 = rand() % (y + 50 - (y + 10) + 1) + (y + 10);
		
		corners[0] = x;
		corners[1] = y;
		
		corners[2] = x;
		corners[3] = y2;
		
		corners[4] = x2;
		corners[5] = y2;
		
		corners[6] = x2;
		corners[7] = y;
		
		corners[8] = corners[0];
		corners[9] = corners[1];
		
	}
	
	void draw() override
	{
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(5, corners);
		
	}
	
	void lineMove() override
	{
		if(direction == 'R')
		{
			x++;
			x2++;
			
			corners[0] = x;
		
			corners[2] = x;
		
			corners[4] = x2;
		
			corners[6] = x2;
		
			corners[8] = corners[0];
			
			if (x == 640 || x2 == 640)
			{
				direction = 'L';
			}
			
		} else if (direction == 'L')
		{
			x--;
			x2--;
			
			corners[0] = x;
		
			corners[2] = x;
		
			corners[4] = x2;
		
			corners[6] = x2;
		
			corners[8] = corners[0];
			if (x == 0 || x2 == 0)
			{
				direction = 'R';
			}
		}
		
	}
	
	void moveAround() override
	{
		if((corners[2] == corners[6]) || (corners[2] + 1 == corners[6])){
				z =- z;
		}
		
		if((corners[1] == corners[5]) || (corners[1] + 1 == corners[5])){
			s =- s;
		}
		
		if((corners[0] == corners[4]) || (corners[0] + 1 == corners[4])){
			u =- u;
		}
		
		if((corners[3] == corners[7]) || (corners[3] + 1 == corners[7])){
			p =- p;
		}
		
		corners[0] += -s;
		corners[2] += p;
		corners[4] += s;
		corners[6] += -p;
		corners[8] = corners[0];
		corners[1] += u;
		corners[3] += z;
		corners[5] += -u;
		corners[7] += -z;
		corners[9] = corners[1];
	}	
};

class tTriangle:public tSegment{
private:
	int corners[8];
	int s;
public:
	tTriangle():tSegment()
	{
		corners[0] = x;
		corners[1] = y;
		
		corners[2] = x2;
		corners[3] = y;
		
		corners[4] = x2;
		corners[5] = y2;
		
		corners[6] = corners[0];
		corners[7] = corners[1];
				
		if (y2 > y)
		{
			s = 1;
		}
		
		else
		{
			s = -1;
		}
	}
	
	void draw() override
	{
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(4, corners);
		
	}

	void lineMove() override
	{
		if(direction == 'R')
		{
			x++;
			x2++;
			
			corners[0] = x;
		
			corners[2] = x2;

			corners[4] = x2;
		
			corners[6] = corners[0];
			
			if (x == 640 || x2 == 640)
			{
				direction = 'L';
			}
			
		} else if (direction == 'L')
		{
			x--;
			x2--;
			
			corners[0] = x;
		
			corners[2] = x2;

			corners[4] = x2;
		
			corners[6] = corners[0];
			
			if (x == 0 || x2 == 0)
			{
				direction = 'R';
			}
		}
		
	}
	
	void moveAround() override
	{
		delay(100);
		if (s == 1)
		{
			corners[5] = y - (y2 - y);
			s = -1;
		}
		
		else
		{
			corners[5] = y2;
			s = 1;
		}
			
	}
};

class tEllipse:public tCircle{
private:
	float secondRadius;
	float pro[2];
	float s = 0.25, u;
public:
	tEllipse()
	{
		secondRadius = rand() % (20 - 5 + 1) + 5;
		while(secondRadius == radius)
		{
			secondRadius = rand() % (20 - 5 + 1) + 5;
		}
		
		pro[0] = radius;
		pro[1] = secondRadius;
		
	}
	
	void draw() override
	{
		setcolor(color);
		fillellipse(x, y, radius, secondRadius);
	}
	
	void lineMove() override
	{
		if (direction == 'R')
		{
			x++;
			if (x + radius == 640)
			{
				direction = 'L';
			}
		} else if (direction == 'L')
		{
			x--;
			if (x - radius == 0)
			{
				direction = 'R';
			}
		}
	}
	
	void moveAround() override
	{
		if(pro[0] > pro[1])
		{
			if(radius != pro[1]){
				radius += -s;
				secondRadius += s;
			}
			
			else
			{
				pro[0] = radius;
				pro[1] = secondRadius;
			}
		}
		
		if(pro[0] < pro[1])
		{
			if(radius != pro[1])
			{
				radius += s;
				secondRadius += -s;
			}
			
			else
			{
				pro[0] = radius;
				pro[1] = secondRadius;
			}
		}	
	}
			
};



class tRhombus:public tRectangle{
public:
	tRhombus():tRectangle(){
		x2 = x;
		corners[0] = x;
		corners[1] = y;
		
		corners[2] = x - 20;
		corners[3] = ((y2 - y) / 2) + y;
		
		corners[4] = x;
		corners[5] = y2;
		
		corners[6] = x + 20;
		corners[7] = ((y2 - y) / 2) + y;;
		
		corners[8] = corners[0];
		corners[9] = corners[1];
	}
	
	void draw() override
	{
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(5, corners);
	}
	
	void lineMove() override
	{
		if(direction == 'R')
		{
			x++;
			x2++;
			
			corners[0] = x;
		
			corners[2] = x - 20;
		
			corners[4] = x;
		
			corners[6] = x + 20;
		
			corners[8] = corners[0];
			
			if (x + 20 == 640 || x2 == 640)
			{
				direction = 'L';
			}
			
		} else if (direction == 'L')
		{
			x--;
			x2--;
			
			corners[0] = x;
		
			corners[2] = x - 20;
		
			corners[4] = x;
		
			corners[6] = x + 20;
		
			corners[8] = corners[0];
			
			if (x - 20 == 0 || x2 == 0)
			{
				direction = 'R';
			}
		}
		
	}
	
	void moveAround() override
	{
			if((corners[2] == corners[6]) || (corners[2] + 1 == corners[6])){
				z = -z;
			}
			if((corners[1] == corners[5]) || (corners[1] + 1 == corners[5])){
				s = -s;
			}
			if((corners[0] == corners[4]) || (corners[0] + 1 == corners[4])){
				u =- u;
			}
			if((corners[3] == corners[7]) || (corners[3] + 1 == corners[7])){
				p =- p;
			}
			corners[0] += -s;
			corners[2] += -p;
			corners[4] += s;
			corners[6] += p;
			corners[8] = corners[0];
			corners[1] += -u;
			corners[3] += z;
			corners[5] += u;
			corners[7] += -z;
			corners[9] = corners[1];
	}
};














