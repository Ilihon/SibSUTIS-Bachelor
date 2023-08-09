#include <iostream>

using namespace std;

int reflect(int digit, unsigned short int size){
    int result = 0;
    for(int i = size -1, j = 0; i >= 0 ; i--, j++){
        int bit = ((digit >> j) & 1);
        result = result | (bit << i);
    }

    return result;
}

unsigned short int CRC16(){
    unsigned short int crc = 0xFFFF, polynom = 0x1021;
    char bit, byte;


    FILE *input;

    if(!(input = fopen("test.txt", "r"))) {
    	cout<<"File not found"<<endl;
      	return 0;
    }

    fseek(input, 0, SEEK_END);
	int64_t size = ftell(input);
	fseek(input, 0, SEEK_SET);
	
    int byte_counter = 0;

    do {
      byte = fgetc(input);
      for (int j = 0; j < 8; j++){
          bit = ((byte>>(7-j))&1) ^ ((crc >> 15) & 1);
          crc = crc << 1;
          if (bit) {
              crc = crc ^ polynom;
          }
      }
      byte_counter++;
     } while(!feof(input) && byte_counter < size);

    fclose(input);

    return  crc;
}

int CRC32(){
	
     int crc = 0xFFFFFFFF, polynom = 0x04C11DB7;
     char bit, byte;

    FILE *input;

    if(!(input = fopen("test.txt", "r"))) {
		cout<<"File not found"<<endl;
      	return 0;
    }

    int byte_counter = 0;

  	fseek(input, 0, SEEK_END);
	int64_t size = ftell(input);
	fseek(input, 0, SEEK_SET);
	
	//cout<<size<<endl;
	
    do{
      byte = fgetc(input);
      for (int j = 0; j < 8; j++){
          bit = ((byte >> j) & 1) ^ ((crc >> 31) & 1);
          crc = crc << 1;
          if (bit) {
              crc = crc ^ polynom;
          }
      }
      byte_counter++;
     } while(!feof(input) && byte_counter < size);

	cout << hex << crc << endl;
    crc = reflect (crc,32);
    crc = crc ^ 0xFFFFFFFF;

    fclose(input);
    return crc;
}

int main()
{
	int CRC_USHI = 0;
	
	CRC_USHI = CRC32();
	
	cout << "CRC32: " << hex << CRC_USHI << endl;
	
	CRC_USHI = CRC16();
	
	cout << "CRC16: " << hex << CRC_USHI;
}


