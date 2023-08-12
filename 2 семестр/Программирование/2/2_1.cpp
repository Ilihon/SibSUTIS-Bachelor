#include <iostream>

using namespace std;

void f(){
    int n;
    cin>>n;
    if (n != 0){
    	if(n>0){
        cout<<n<<" ";
        }
        f();
    }
}
int main(){
    f();
    cout<<endl;
    system("pause");
    return 0;
}
