#include <iostream>
#include <thread>
#include <chrono>

using namespace  std;
int cs = 0;

void counter()
{
	
    cs+=1;
}

int main()
{
	cout<<"suppose: 9000"<<endl;
	for(int i = 0; i < 100; ++i )
	{
		thread th(counter);
    thread th2(counter);
    thread th3(counter);    
    th.detach();
    th2.detach();
    th3.detach();
	}
 	   

    
    cout<<"result:  "<<cs<<endl;
    return 0;
}

