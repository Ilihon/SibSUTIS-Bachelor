#include <iostream>
#include <fstream>

using namespace std;

int check(unsigned int i);
int shift(unsigned int i, unsigned int bit);
int CRC32(unsigned int polinom, unsigned int registr, string file);

int main() {
    setlocale(LC_ALL, "Russian");
    unsigned int  init = 0xFFFFFFFF, polynom = 0x04C11DB7;
	//unsigned int init = 0xFFFF, polynom = 0x1021;
	//unsigned int  init = 0x00, polynom = 0x07;
	string filename;
    
	cout << "Enter file name:" << endl;
	cin >> filename;    
    unsigned int check = CRC32(polynom, init, filename);
    cout << std::hex;
    cout << "CRC32" << endl;
    cout << "Полином = " << polynom << endl; 
    cout << "Чек сумма = " << check << endl;
	return 0;
}

int reflect(int digit, unsigned short int size){
    int result = 0;
    for(int i = size -1, j = 0; i >= 0 ; i--, j++){
        int bit = ((digit >> j) & 1);
        result = result | (bit << i);
    }
    return result;
}
int CRC32(unsigned int polinom, unsigned int registr, string file) {
    char ch;
    ifstream stream;
    stream.open(file, ifstream::in);
    if (!stream.is_open()) {
        return -1;
    }
    while (stream.get(ch)) {
    	if (stream.eof()) exit;
        //cout << ch << " ";
        char bit;
        for (int i = 0; i < 8; i++){
        	bit = ((ch >> i) & 1) ^ ((registr >> 31) & 1);
          	registr = registr << 1;
          	if (bit) {
            	registr = registr ^ polinom;
          	}
      	}
    }
	//cout << hex << registr << endl;
   // registr = reflect (registr,32);
   registr = registr ^ 0xFFFFFFFF;
    return registr;
}

