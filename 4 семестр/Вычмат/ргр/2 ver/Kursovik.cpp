#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <vector>
#define E 2.718281828

using namespace std;

double y1 = 1, y = 1, n = 5, h = 0.2, H = 0.2, x0 = 0, xn = 1, yk = E;
double eps;
	
double y2(double x, double y, double y1) {
	return (pow(E, x) + y + y1) / 3;
}

vector<vector<double> > RungeFour(double h, double y, double y1) {
    double k[4][2];
    int c = xn / h +1;
    double x[c];
    double Y[2];
    vector <vector<double> > Y1;
    vector <double> Y2;
	Y[0] = y;
	Y[1] = y1;
	for (int i = 0; i <= xn / h; i++) {

        x[i] = x0 + h * i;
        printf("%0.8f   %0.8f    %0.8f \n", x[i], Y[0] ,Y[1]);
		k[0][0] = Y[1];
		k[0][1] = y2(x[i], Y[0], Y[1]);
		k[1][0] = Y[1] + h / 2 * k[0][1];
		k[1][1] = y2(x[i] + h / 2, Y[0] + (h / 2) * k[0][0] , Y[1] + h / 2 * k[0][1]);
		k[2][0] = Y[1] + h / 2 * k[1][1];
		k[2][1] = y2(x[i] + h / 2, Y[0] + (h / 2) * k[1][0], Y[1] + h / 2 * k[1][1]);
		k[3][0] = Y[1] + h * k[2][1];
		k[3][1] = y2(x[i] + h, Y[0] + h * k[2][0], Y[1] + h * k[2][1]);
		Y[0] = Y[0] + h / 6 * (k[0][0] + 2 * k[1][0] + 2 * k[2][0] + k[3][0]);
		Y2.push_back(Y[0]);
		Y[1] = Y[1] + h / 6 * (k[0][1] + 2 * k[1][1] + 2 * k[2][1] + k[3][1]);
		Y2.push_back(Y[1]);
		Y1.push_back(Y2);
		Y2.clear();
	}
	cout << endl;
	return Y1;
}

double p2(double y1){
    double h = H;
    double r1, r2;
    int flag = 1;
    int j = 1;
    vector<vector<double> > Y;
    vector<vector<double> > Y1;
    Y = RungeFour(h, y, y1);
    while(flag){
        cout << endl << "  Шаг " << j << " : " << endl;
        h /= 2;
        Y1 = RungeFour(h, y, y1);
        int c1[Y.size()];
        for(int i = 1, t = 1; i < Y.size(); i++){
        	/*
            printf("%d) %0.8f - %0.8f = %0.8f\n",i, Y[i-1][0], Y1[2*i-1][0], fabs(Y[i-1][0]-Y1[2*i-1][0]));
                printf("   %0.8f - %0.8f = %0.8f\n", Y[i-1][t],Y1[2*i-1][t],fabs(Y[i-1][t]-Y1[2*i-1][t]));
                */
            int c = 1;
                if(fabs(Y[i-1][t] - Y1[2*i-1][t]) >= 15 * eps){
                    c *= 0;
                    break;
                } else{
                    c *= 1;
                }
            c1[i-1] = c;
        }
        int f = 1;
        for(int i = 0; i < Y.size(); i++){
            f *= c1[i];
		}
        if(f){
            flag = 0;
           /* cout << "  Кол-во проделанных шагов : " << j << endl;
            cout << "  Конечное значение шага :   h = " << h << endl;
            printf("  %0.8f - %0.8f = %0.8f\n", Y[Y.size() - 1][0], Y1[Y1.size() - 1][0], fabs(Y[Y.size() - 1][0] - Y1[Y1.size() - 1][0]));
            printf("  %0.8f - %0.8f = %0.8f\n", Y[Y.size() - 1][1], Y1[Y1.size() - 1][1], fabs(Y[Y.size() - 1][1] - Y1[Y1.size() - 1][1]));
            */
        	return Y1[Y1.size()-1][1];
		}
        j++;
        Y = Y1;
        Y1.clear();
    }
}

void shooting(){
    vector<vector<double> > Y;
    double k = 0;
    double shot1 = 0, shot2, shot;
    double a = 0;
    double b = 0;
    double p = 0;
    cout << endl << "shooting" << endl;
        while(p2(k) <= yk){
            k++;
            cout << "k = " << k;
        }
        a = k - 1;
        b = k;
		p = (a + b) / 2;
            shot = p2(p);
            printf("y(k), shot: %0.8f, k = %0.8f\n", shot, p);
	while (fabs(shot - yk) > eps) {
        if(shot <= yk){
            a = p;
            p = (a + b) / 2;
        } else if (shot > yk){
            b = p;
            p = (a + b) / 2;
        }
            shot = p2(p);
            printf("y(k), shot: %0.8f, k = %0.8f\n", shot, p);
	}
	system("pause");
	return;
}

int main() {
	setlocale(LC_ALL, "RUS");
	cout<<"  Введите точность eps: "<<endl;
	cin >> eps;
	//RungeFour(h, y, y1);
	p2(y1);
	//shooting();
}

