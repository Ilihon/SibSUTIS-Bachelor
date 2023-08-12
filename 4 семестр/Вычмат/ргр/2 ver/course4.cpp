#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <vector>
#define E 2.718281828
using namespace std;

double x0 = 0, xn = 1, yo = 1, yk = E, H=0.2, h=0.2, shag;
int p=2;
double e;
int N=5;


double fsy(double x, double y_1, double y) {
    //return (x+2)*pow(E, x);
	return (pow(E, x)+y+y_1)/3;
	//return x*y_1+y;
}
vector<double> Eiler(double h, int n, double yd){
    double r[p], result[p];
    r[0]=yo+h*yd;
    r[1]=yd+h*fsy(x0, yd, yo);
    //cout<<1<<") "<<r<<endl;
    double x[n];
    for(int i=1; i<n; i++){
        x[i]=x0+h*i;
        for(int t=0; t<p-1; t++)
            result[t]=r[t]+r[t+1]*h;
        result[p-1]=r[p-1]+fsy(x[i], r[p-1], r[0])*h;
        //cout<<i+1<<") "<<result<<endl;
        for(int t=0; t<p; t++)
            r[t]=result[t];
    }
    vector<double> Y;
    for(int t=0; t<p; t++)
        Y.push_back(r[t]);
    return Y;
}
vector<double> rk2p(double h, int n, double yd){
    double r[p], result[p];
    r[0]=yo+h/2*(yd+yd+h/2*fsy(x0, yd, yo));
    r[1]=yd+h/2*(fsy(x0, yd, yo)+fsy(x0+h, yd+h/2*fsy(x0, yd, yo), yo+h/2*yd));
    //cout<<1<<") "<<r<<endl;
    double x[n];
    x[0]=x0;
    for(int i=1; i<n; i++){
        x[i]=x0+h*i;
        for(int t=0; t<p-1; t++)
            result[t]=r[t]+h/2*(r[t+1]+r[t+1]+h/2*fsy(x[i], r[t+1], r[t]));
        result[p-1]=r[p-1]+h/2*(fsy(x[i], r[p-1], r[0])+fsy(x[i]+h, r[p-1]+h/2*fsy(x[i], r[p-1], r[0]), r[0]+h/2*r[p-1]));
        //cout<<i+1<<") "<<result<<endl;
        for(int t=0; t<p; t++)
            r[t]=result[t];
    }
    vector<double> Y;
    for(int t=0; t<p; t++)
        Y.push_back(r[t]);
    return Y;
}
vector<double> rk2v(double h, int n, double yd){
    double r[p], result[p];
    r[0]=yo+h*(yd+h/2*fsy(x0, yd, yo));
    r[1]=yd+h*fsy(x0+h/2, yd+h/2*fsy(x0, yd, yo), yo+h/2*yd);
    //cout<<1<<") "<<r<<endl;
    double x[n];
    x[0]=x0;
    for(int i=1; i<n; i++){
        x[i]=x0+h*i;
        for(int t=0; t<p-1; t++)
            result[t]=r[t]+h*(r[t+1]+h/2*fsy(x[i], r[t+1], r[t]));
        result[p-1]=r[p-1]+h*fsy(x[i]+h/2, r[p-1]+h/2*fsy(x[i], r[p-1], r[0]), r[0]+h/2*r[p-1]);
        //cout<<i+1<<") "<<result<<endl;
        for(int t=0; t<p; t++)
            r[t]=result[t];
    }
    vector<double> Y;
    for(int t=0; t<p; t++)
        Y.push_back(r[t]);
    return Y;
}
vector<double> rk4(double h, int n, double yd){
    double r[p], result[p];
    double k[4][p];
    k[0][0]=yd;
    k[0][1]=fsy(x0, yd, yo);
    k[1][0]=yd+h/2*k[0][1];
    k[1][1]=fsy(x0+h/2, yd+h/2*k[0][1], yo+k[0][0]*h/2);
    k[2][0]=yd+h/2*k[1][1];
    k[2][1]=fsy(x0+h/2, yd+h/2*k[1][1], yo+k[1][0]*h/2);
    k[3][0]=yd+h*k[2][1];
    k[3][1]=fsy(x0+h, yd+h*k[2][1], yo+k[2][0]*h);
    r[0]=yo+h/6*(k[0][0]+2*k[1][0]+2*k[2][0]+k[3][0]);
    r[1]=yd+h/6*(k[0][1]+2*k[1][1]+2*k[2][1]+k[3][1]);
    //cout<<1<<") "<<r<<endl;
    double x[n];
    x[0]=x0;
    for(int i=1; i<n; i++){
        x[i]=x0+h*i;
        for(int t=0; t<p-1; t++){
            k[0][t]=r[t+1];
            k[0][t+1]=k[3][t+1];
            k[1][t]=r[t+1]+h/2*k[0][1];
            k[1][t+1]=fsy(x[i]+h/2, r[t+1]+h/2*k[0][1], r[t]+k[0][0]*h/2);
            k[2][t]=r[t+1]+h/2*k[1][1];
            k[2][t+1]=fsy(x[i]+h/2, r[t+1]+h/2*k[1][1], r[t]+k[1][0]*h/2);
            k[3][t]=r[t+1]+h*k[2][1];
            k[3][t+1]=fsy(x[i]+h, r[t+1]+h*k[2][1], r[t]+k[2][0]*h);
            result[t]=r[t]+h/6*(k[0][0]+2*k[1][0]+2*k[2][0]+k[3][0]);
        }
        result[p-1]=r[p-1]+h/6*(k[0][1]+2*k[1][1]+2*k[2][1]+k[3][1]);
        //cout<<i+1<<") "<<result<<endl;
        for(int t=0; t<p; t++){
            r[t]=result[t];
        }
    }
    vector<double> Y;
    for(int t=0; t<p; t++)
        Y.push_back(r[t]);
    return Y;
}

//vector<<double> p2e(double yd){
double p2e(double yd){
    double h=H;
    double r1, r2;
    int flag=1;
    int j=1;
    vector<vector<double> > Y;
    vector<vector<double> > Y1;
    //Y.push_back(yo);
    //Y1.push_back(yo);
    Y1.push_back(Eiler(0.2, 5, yd));
    //cout<<xn<<"   "<<Y1[0][0]<<endl;
    //cout<<"    "<<Y1[0][1]<<endl;
    printf("%0.1f   %0.8f\n       %0.8f\n", xn, Y1[0][0], Y1[0][1]);
    Y1.clear();
    for(int i=0; i<N; i++){
        Y.push_back(Eiler(h, i+1, yd));
    }
    /*for(int i=1; i<=Y.size(); i++){
        cout<<x0+i*h<<" "<<Y[i-1][0]<<endl;
        for(int t=1; t<Y[i-1].size(); t++)
            cout<<"    "<<Y[i-1][t]<<endl;
    }
    system("pause");*/
    while(flag){
        cout<<endl<<"step "<<j<<":"<<endl;
        h/=2;
        for(int i=0; i<2*Y.size(); i++){
            Y1.push_back(Eiler(h, i+1, yd));
        }
        int c1[Y.size()];
        for(int i=1; i<=Y.size(); i++){
            printf("%d) %0.8f-%0.8f=%0.8f\n",i,Y[i-1][0],Y1[2*i-1][0],fabs(Y[i-1][0]-Y1[2*i-1][0]));
            for(int t=1; t<Y[i-1].size(); t++)
                printf("   %0.8f-%0.8f=%0.8f\n",Y[i-1][t],Y1[2*i-1][t],fabs(Y[i-1][t]-Y1[2*i-1][t]));
            int c=1;
            for (int t=0; t<Y[i-1].size(); t++){
                if(fabs(Y[i-1][t]-Y1[2*i-1][t])>=e){
                    c*=0;
                    break;
                } else{
                    c*=1;
                }
            }
            c1[i-1]=c;
        }
        int f=1;
        for(int i=0; i<Y.size(); i++)
            f*=c1[i];
        if(f){
            flag=0;
            cout<<"the final value was reached at step N"<<j<<":   h="<<h<<endl;
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][0],Y1[Y1.size()-1][0],fabs(Y[Y.size()-1][0]-Y1[Y1.size()-1][0]));
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][1],Y1[Y1.size()-1][1],fabs(Y[Y.size()-1][1]-Y1[Y1.size()-1][1]));
            return Y1[Y1.size()-1][1];
        }
        j++;
        Y=Y1;
        Y1.clear();
    }
}

//vector<double> p2rk2(int a, double yd){
double p2rk2(int a, double yd){
    double h=H;
    double r1, r2;
    int flag=1;
    int j=1;
    vector<vector<double> > Y;
    vector<vector<double> > Y1;
    if(a==2){
        Y1.push_back(rk2p(0.2, 5, yd));
        //cout<<xn<<"   "<<Y1[0][0]<<endl;
        //cout<<"    "<<Y1[0][1]<<endl;
    }
    if(a==3){
        Y1.push_back(rk2v(0.2, 5, yd));
        //cout<<xn<<"   "<<Y1[0][0]<<endl;
        //cout<<"    "<<Y1[0][1]<<endl;
    }
    printf("%0.1f   %0.8f\n       %0.8f\n", xn, Y1[0][0], Y1[0][1]);
    Y1.clear();
    //Y.push_back(yo);
    //Y1.push_back(yo);
    for(int i=0; i<N; i++){
        if(a==2)
            Y.push_back(rk2p(h, i+1, yd));
        if(a==3)
            Y.push_back(rk2v(h, i+1, yd));
    }
    /*for(int i=1; i<=Y.size(); i++){
        cout<<x0+i*h<<" "<<Y[i-1][0]<<endl;
        for(int t=1; t<Y[i-1].size(); t++)
            cout<<"    "<<Y[i-1][t]<<endl;
    }*/
    while(flag){
        cout<<endl<<"step "<<j<<":"<<endl;
        h/=2;
        for(int i=0; i<2*Y.size(); i++){
            if(a==2)
                Y1.push_back(rk2p(h, i+1, yd));
            if(a==3)
                Y1.push_back(rk2v(h, i+1, yd));
        }
        int c1[Y.size()];
        for(int i=1; i<=Y.size(); i++){
            printf("%d) %0.8f-%0.8f=%0.8f\n",i,Y[i-1][0],Y1[2*i-1][0],fabs(Y[i-1][0]-Y1[2*i-1][0]));
            for(int t=1; t<Y[i-1].size(); t++)
                printf("   %0.8f-%0.8f=%0.8f\n",Y[i-1][t],Y1[2*i-1][t],fabs(Y[i-1][t]-Y1[2*i-1][t]));
            int c=1;
            for (int t=0; t<Y[i-1].size(); t++){
                if(fabs(Y[i-1][t]-Y1[2*i-1][t])>=3*e){
                    c*=0;
                    break;
                } else{
                    c*=1;
                }
            }
            c1[i-1]=c;
        }
        int f=1;
        for(int i=0; i<Y.size(); i++)
            f*=c1[i];
        if(f){
            flag=0;
            cout<<"the final value was reached at step N"<<j<<":   h="<<h<<endl;
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][0],Y1[Y1.size()-1][0],fabs(Y[Y.size()-1][0]-Y1[Y1.size()-1][0]));
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][1],Y1[Y1.size()-1][1],fabs(Y[Y.size()-1][1]-Y1[Y1.size()-1][1]));
            return Y1[Y1.size()-1][1];
        }
        j++;
        Y=Y1;
        Y1.clear();

    }
}

//vector<double> p2rk4(double yd){
double p2rk4(double yd){
    double h=H;
    double r1, r2;
    int flag=1;
    int j=1;
    vector<vector<double> > Y;
    vector<vector<double> > Y1;
    //Y.push_back(yo);
    //Y1.push_back(yo);
    Y1.push_back(rk4(0.2, 5, yd));
    //cout<<xn<<"   "<<Y1[0][0]<<endl;
    //cout<<"    "<<Y1[0][1]<<endl;
    printf("%0.1f   %0.8f\n       %0.8f\n", xn, Y1[0][0], Y1[0][1]);
    Y1.clear();
    for(int i=0; i<N; i++){
        Y.push_back(rk4(h, i+1, yd));
    }
    /*for(int i=1; i<=Y.size(); i++){
        cout<<x0+i*h<<"   "<<Y[i-1][0]<<endl;
        for(int t=1; t<Y[i-1].size(); t++)
            cout<<"    "<<Y[i-1][t]<<endl;
    }*/
    while(flag){
        cout<<endl<<"step "<<j<<":"<<endl;
        h/=2;
        for(int i=0; i<2*Y.size(); i++){
            Y1.push_back(rk4(h, i+1, yd));
        }
        int c1[Y.size()];
        for(int i=1; i<=Y.size(); i++){
            printf("%d) %0.8f-%0.8f=%0.8f\n",i,Y[i-1][0],Y1[2*i-1][0],fabs(Y[i-1][0]-Y1[2*i-1][0]));
            for(int t=1; t<Y[i-1].size(); t++)
                printf("   %0.8f-%0.8f=%0.8f\n",Y[i-1][t],Y1[2*i-1][t],fabs(Y[i-1][t]-Y1[2*i-1][t]));
            int c=1;
            for (int t=0; t<Y[i-1].size(); t++){
                if(fabs(Y[i-1][t]-Y1[2*i-1][t])>=15*e){
                    c*=0;
                    break;
                } else{
                    c*=1;
                }
            }
            c1[i-1]=c;
        }
        int f=1;
        for(int i=0; i<Y.size(); i++)
            f*=c1[i];
        if(f){
            flag=0;
            shag=h;
            cout<<"the final value was reached at step N"<<j<<":   h="<<h<<endl;
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][0],Y1[Y1.size()-1][0],fabs(Y[Y.size()-1][0]-Y1[Y1.size()-1][0]));
            printf("%0.8f-%0.8f=%0.8f\n",Y[Y.size()-1][1],Y1[Y1.size()-1][1],fabs(Y[Y.size()-1][1]-Y1[Y1.size()-1][1]));
            return Y1[Y1.size()-1][1];
        }
        j++;
        Y=Y1;
        Y1.clear();
    }
}
void shooting(int v){
    vector<vector<double> > Y;
    double k=0;
    double shot1=0, shot2, shot;
    double a = 0;
    double b = 0;
    double c = 0;
    if(v==1){
        while(p2e(k)<=yk){
            shot1 = p2e(k);
            k++;
        }
        shot2 = p2e(k);
    }
    if(v==2){
        while(p2rk2(2,k)<=yk){
            shot1 = p2rk2(2,k);
            k++;
        }
        shot2 = p2rk2(2,k);
    }
    if(v==3){
        while(p2rk2(3,k)<=yk){
            shot1 = p2rk2(3,k);
            k++;
        }
        shot2 = p2rk2(3,k);
    }
    if(v==4){
        while(p2rk4(k)<=yk){
            shot1 = p2rk4(k);
            k++;
        }
        shot2 = p2rk4(k);
    }
	if (fabs(shot1 - yk) <= e) {
        printf("y(k): %0.8f, k = %0.8f\n", shot1, k-1);
        for(int i=0; i<N*(H/shag); i++)
            Y.push_back(rk4(shag, i+1, k-1));
        for(int i=1; i<=Y.size(); i++){
            printf("%f   %0.8f\n", x0+i*shag, Y[i-1][0]);
            for(int t=1; t<Y[i-1].size(); t++)
                printf("         %0.8f\n", Y[i-1][0]);
        }
        return;
	} else if (fabs(shot2 - yk) <= e) {
        printf("y(k): %0.8f, k = %0.8f\n", shot2, k);
        for(int i=0; i<N*(H/shag); i++)
            Y.push_back(rk4(shag, i+1, k));
        for(int i=1; i<=Y.size(); i++){
            printf("%f   %0.8f\n", x0+i*shag, Y[i-1][0]);
            for(int t=1; t<Y[i-1].size(); t++)
                printf("         %0.8f\n", Y[i-1][0]);
        }
        return;
    } else {
        a = k-1;
        b = k;
		c = (a + b) / 2;
        if(v==1){
            shot = p2e(c);
        }
        if(v==2){
            shot = p2rk2(2,c);
        }
        if(v==3){
            shot = p2rk2(3,c);
        }
        if(v==4){
            shot = p2rk4(c);
        }
	}
	while (fabs(shot - yk) > e) {
        if(shot<=yk){
            a = c;
            c = (a + b) / 2;
        } else if (shot>yk){
            b = c;
            c = (a + b) / 2;
        }
        if(v==1){
            shot = p2e(c);
        }
        if(v==2){
            shot = p2rk2(2,c);
        }
        if(v==3){
            shot = p2rk2(3,c);
        }
        if(v==4){
            shot = p2rk4(c);
        }
	}
	printf("y(k), shot: %0.8f, k = %0.8f\n", shot, c);
	system("pause");
    for(int i=0; i<N*(H/shag); i++)
        Y.push_back(rk4(shag, i+1, c));
	for(int i=1; i<=Y.size(); i++){
        printf("%f   %0.8f\n", x0+i*shag, Y[i-1][0]);
        for(int t=1; t<Y[i-1].size(); t++)
            printf("         %0.8f\n", Y[i-1][0]);
    }
	return;
}

int main() {
    /*cout<<"Eps = ";
    cin>>e;
    cout<<"Eiler: "<<endl;
    Eiler(H, 3);
    cout<<"R-K 2 P: "<<endl;
    rk2p(H, 3);
    cout<<"R-K 2 V: "<<endl;
    rk2v(H, 3);
    cout<<"R-K 4: "<<endl;
    rk4(H, 3);*/
    cout<<"Eps = ";
    cin>>e;
    int a;
    cout<<"1.Eiler"<<endl;
    cout<<"2.R-K 2 P"<<endl;
    cout<<"3.R-K 2 V"<<endl;
    cout<<"4.R-K 4"<<endl;
    cin>>a;
    vector<double> y;
    switch(a){
    case 1:
        cout<<"Eiler pereschet: "<<endl;
        //y=p2e();
        //for(int t=0; t<y.size(); t++)
            //cout<<y[t]<<endl;
            //printf("%0.8f\n", y[t]);
        shooting(a);
        break;
    case 2:
        cout<<"R-K 2 P pereschet: "<<endl;
        //y=p2rk2(a);
        //for(int t=0; t<y.size(); t++)
            //cout<<y[t]<<endl;
            //printf("%0.8f\n", y[t]);
        shooting(a);
        break;
    case 3:
        cout<<"R-K 2 V pereschet: "<<endl;
        //y=p2rk2(a);
        //for(int t=0; t<y.size(); t++)
            //cout<<y[t]<<endl;
            //printf("%0.8f\n", y[t]);
        shooting(a);
        break;
    case 4:
        cout<<"R-K 4 pereschet: "<<endl;
        //y=p2rk4();
        //for(int t=0; t<y.size(); t++)
            //cout<<y[t]<<endl;
            //printf("%0.8f\n", y[t]);
        shooting(a);
        break;
    }
	system("pause");
	return 0;
}
