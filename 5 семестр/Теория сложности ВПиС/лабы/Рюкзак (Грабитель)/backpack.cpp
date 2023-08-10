#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int M;
int COL;

void CountBack(int **mas);

int main()
{
	setlocale(0, "");
	cout << "Размер рюкзака: ";
	cin >> M;
	cout << "Количество предметов: ";
	cin >> COL;
	
	int **mas = new int *[COL];
	for(int i=0; i<COL;i++){
		cout<< endl;
		mas[i] = new int[2];
		cout << "Вес " << i+1 << " предмета ";
		cin >> mas[i][0];
		cout << "Ценность " << i+1 << " предмета: ";
		cin >> mas[i][1];
	}
	/*for(int i=0; i<COL;i++){
		cout << mas[i][0] << endl << mas[i][1] << endl;
	}*/
	
	CountBack(mas);

    

    system("pause");
    return 0;
}

void CountBack(int **mas){
	int *buf = new int[COL];
	int *elements = new int[COL];
	int *result = new int[M+1];
	for(int i=0; i<COL;i++){
		buf[i] = 0;
		elements[i]=0;
	}
	for(int i=0; i<M;i++){
		result[i] = 0;
	}
	for(int i =0; i<=M;i++){
		for(int j =0; j<COL;j++){
			if(i-mas[j][0] >=0){
				buf[j]= result[i-mas[j][0]]+mas[j][1];
			}	
		}
		int max = -1;
		for(int j =0; j<COL;j++){
			if(buf[j]>max){
				max = buf[j];
			}	
		}
		result[i] = max;
		for(int j=0; j<COL;j++){
			buf[j] = 0;
		}
	}
	while(M>0){
		int min = 99999999999;
		for(int i =0; i<COL;i++){
			if(mas[i][0]<min){
				min = mas[i][0];
			}	
		}
		if(result[M]-min <0)
			break;
		for(int i =0; i<COL;i++){
			if(M-mas[i][0]>=0){
				if(result[M-mas[i][0]]+mas[i][1] == result[M]){
					buf[i]=1;
					int max = -1;
					for(int j =0; j<COL;j++){
						if(buf[j]>max){
							max = buf[j];
						}	
					}
					elements[i]+=max;
					M-=mas[i][0];
					break;
				}
			}
		}
		for(int j=0; j<COL;j++){
			buf[j] = 0;
		}
	}
    cout << endl;
	int result_w=0,result_v=0;
	for (int m = 0; m < COL; m++) {
		cout << elements[m] << "\t";
		result_w+=elements[m]*mas[m][0];
		result_v+=elements[m]*mas[m][1];
	}
    cout << "\nсумма: "<< result_v << "\t используемый вес: " << result_w << endl;
}
/*
void CountBack(int **mas) {
	int N = COL + 1;
    int res[M + 1][N]{};
    int max, maxmc, tmp, maxi, maxres;
    for (int mc = -1; mc < COL; mc++) {
        int mctmp = 0;
        if (mc == -1) { mctmp = 0; maxmc = mas[mc + 1][0]; }
        else if (mc == COL - 1) { mctmp = mas[mc][0];  maxmc = M + 1; }
            else if (mc != -1) { mctmp = mas[mc][0]; maxmc = mas[mc + 1][0]; }
        for (int i = mctmp; i < maxmc; i++) {
            if (mctmp != 0) {
                max = -9999999;
                maxi = 0;
                if (i == 16) {
                    maxi = 0;
                }
                for (int m = 0; m < mc+1; m++) {
                    tmp = res[i - mas[m][0]][COL] + mas[m][1];
                    if (max <= tmp) { max = tmp; maxi = m; maxres = i - mas[m][0]; }
                }
                res[i][COL] = max;
                for (int m = 0; m < mc+1; m++) {
                    res[i][m] = res[maxres][m];
                }
                res[i][maxi]++;
            }*/
            /*cout << i;
            int result_w=0,result_v=0;
            for (int m = 0; m < COL; m++) {
				cout << "\t"<< res[i][m];
				result_w+=res[i][m]*mas[m][0];
				result_v+=res[i][m]*mas[m][1];
			}
            cout << "\t сумма: "<< result_v << "\t используемый вес: " << result_w << endl;*/
       /* }
    }
    		cout << endl;
            int result_w=0,result_v=0;
            for (int m = 0; m < COL; m++) {
				cout << res[maxmc-1][m] << "\t";
				result_w+=res[maxmc-1][m]*mas[m][0];
				result_v+=res[maxmc-1][m]*mas[m][1];
			}
            cout << "\t сумма: "<< result_v << "\t используемый вес: " << result_w << endl;
}*/
