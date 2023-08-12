#include <iostream>
#include <math.h>
using namespace std;

float step(float x ,int k)
{
    float y=1.0;
    int n;

    if (k<0) x=1.0/x;
    for(n=0;abs(k)>n;n++)
        y=y*x;
    return y;
}

int main()
{
    float b;
    int a;
    cin >>a;cin>>b;
    cout <<step(a, b);

    return 0;
}
