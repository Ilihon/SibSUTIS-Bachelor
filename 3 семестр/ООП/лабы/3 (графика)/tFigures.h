
class tPoint 
{

private:

    
    int dX;
    int dY;
    int rD;
    
protected:
	
	int x;
    int y;
    int color;

public: 


	/// constructor ///
    tPoint() 
    {
    	x = 1 + rand() % 640;
    	y = 1 + rand() % 480;
    	color = 1 + rand() % 15;
        rD = 1 + rand() % 4;
    }
    
    
    /// set ///
    void setX (int x)
    {
    	this -> x = x;
	}
	
	void setY (int n)
	{
		y = n;
	}
	
	void setColor(int n)
	{
		color = n;
	}
	
	void setDX(int n)
	{
		dX = n;
	}
	
	void setDY(int n)
	{
		dY = n;
	}
	
	void setRandDirection(int n)
	{
		rD = n;
	}
	
	
    //// get ////
    int getX()
    {
    	return x;
	}
	
	int getY()
	{
		return y;	
	} 
	
	int getColor()
	{
		return color;
	}
	
	int getDX()
	{
		return dX;
	}
	
	int getDY()
	{
		return dY;
	}
	
	int getRandDirection()
	{
		return rD;
	}
	
	void drawPoint()
	{
		setcolor(this -> getColor());
		circle(this -> getX(),this -> getY(), 1);
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
		int width = 640, height = 480;
		while(x2 > width || x2 < 0)
		{
			x2 = x + rand() % (x + 30);
		}
		
		while(y2 > height || y2 < 0)
		{
			y2 = y + rand() % (y + 30);
		}
	}
	
	void drawSegment()
	{
		moveto(x, y);
		setcolor(color);
		lineto(x2, y2);
	}
};

class tCircle: public tPoint
{
protected:
	int radius;	
	
public:
	tCircle()
	{
		radius = 5 + rand() % 20;
	}
	
	void drawCircle(){
		setcolor(color);
		circle(x, y, radius);
		setfillstyle(1, color);
		floodfill(x, y, color);
	}
};


class tRectangle: public tSegment{
protected:
	int corners[10];
public:
	tRectangle():tSegment()
	{
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
	void drawRectangle(){
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(5, corners);
	}	
};

class tTriangle:public tSegment{
private:
	int corners[8];
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
	}
	void drawTriangle(){
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(4, corners);
	}

};

class tEllipse:public tCircle{
private:
	int secondRadius;
public:
	tEllipse()
	{
		secondRadius = 5 + rand() % 20;
		while(secondRadius == radius)
		{
			secondRadius = 5 + rand() % 20;
		}
		
	}
	void drawEllipse(){
		setcolor(color);
		fillellipse(x,y,radius, secondRadius);
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
	void drawRhombus()
	{
		setfillstyle(1,color);
		setcolor(color);
		fillpoly(5, corners);
	}
};














