#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <chrono>
#include <math.h>


using namespace std;

struct CmdLine{
	string MemType;
	int block_size{};
	int alloc_size{};
	int launch_amount{};
	string filepath{};
};

void parse_arguments(int argc, char *argv[], CmdLine *arguments);
void Clock_ram(int block_size, int alloc_size, int repeats, long long *results, double &absolute, double &relative, double &average);
void Clock_hdd_ssd_flash_write(int block_size, int alloc_size, int repeats, string filename, long long *results, double &absolute, double &relative, double &average);
void Clock_hdd_ssd_flash_read(int block_size, int alloc_size, int repeats, string filename, long long *results, double &absolute, double &relative, double &average);

int main(int argc, char *argv[])
{
	cout.precision(15);
	if( argc < 4)
  {
    printf("Invalid inputs\n ");
    return -1;
  }


	auto arguments = CmdLine();
	parse_arguments(argc,argv,&arguments);
	//cout << arguments.MemType << endl << arguments.block_size << endl << arguments.alloc_size
	// << endl << arguments.launch_amount << endl << arguments.filepath;

	double absolute = 0;
	double relative = 0;
	double average = 0;
	double absolute_read = 0;
	double relative_read = 0;
	double average_read = 0;
	cout << "Start tests..." << endl;
	long long result[arguments.launch_amount];
	long long result_read[arguments.launch_amount];
	if (arguments.MemType == "RAM"){
		Clock_ram(arguments.block_size, arguments.alloc_size, arguments.launch_amount, result, absolute, relative, average);
		/*for(int i = 0; i<arguments.launch_amount;i++){
			cout << result[i]<< endl;
		}*/
	}
	else{
		Clock_hdd_ssd_flash_write(arguments.block_size, arguments.alloc_size, arguments.launch_amount,
			arguments.filepath, result, absolute, relative, average);
		Clock_hdd_ssd_flash_read(arguments.block_size, arguments.alloc_size, arguments.launch_amount,
			arguments.filepath, result_read, absolute_read, relative_read, average_read);
		/*for(int i = 0; i<arguments.launch_amount;i++){
			cout << result[i]<< endl;
		}*/
	}
	//cout << absolute << " - "<< relative << " - " << average <<endl;
	//cout << absolute_read << " - "<< relative_read << " - " << average_read <<endl;

	cout << "All tests done" << endl;


	cout << "Saving results..." << endl;

	ofstream benchmark_output;
	benchmark_output.open("bench result.csv", ios_base::app);
	benchmark_output << "MemoryType;BlockSize;ElementType;BufferSize;LaunchNum;Timer;"
	"WriteTime;AverageWriteTime;WriteBandwidth;AbsErr(write);RelErr(write);ReadTime;"
	"AverageReadTime;ReadBandWidth;AbsErr(read);RelErr(read)" << endl;


	//cout << arguments.MemType << endl << arguments.block_size << endl << arguments.alloc_size
	// << endl << arguments.launch_amount << endl << arguments.filepath;
	for(int i=0; i < /*arguments.launch_amount */1;i++)
	{
		benchmark_output << arguments.MemType << ";"<< arguments.block_size << ";byte;" <<
		arguments.alloc_size << ";" << i+1 << ";chrono;" << result[i] << ";" <<	average << ";" <<
		arguments.block_size / average << ";" << absolute << ";" << relative << ";";

		if(arguments.MemType != "RAM"){
			benchmark_output << result_read[i] << ";" << average_read << ";" <<
			arguments.block_size / average_read << ";" << absolute_read << ";" <<  relative_read << ";";
		}
		else{
			benchmark_output << result[i] << ";" <<	average << ";" <<
			arguments.block_size / average << ";" << absolute << ";" << relative << ";";
		}
		benchmark_output << endl;
	}

	benchmark_output.close();

	cout << "Results saved" << endl;
	return 0;
}

string parse_memory_type(char* str) {
    if (strcmp(str,"RAM")==0)
        return "RAM";
    else if (strcmp(str,"HDD")==0)
        return "HDD";
    else if (strcmp(str,"SSD")==0)
        return "SSD";
    else if (strcmp(str,"flash")==0)
        return "flash";
    else
        throw std::runtime_error("Incorrect memory type");
}

int parse_block_size(char* str) {
	int value = 0;
	char type[10]="\0";
	if(sscanf(str,"%d %s",&value,type)<1)
    {
      printf("Incorrect block size\n");
      return -1;
    }

    if (strcmp(type,"\0")==0)
        return value;
    else if (strcmp(type,"K")==0)
        return value * (1 << 10);
    else if (strcmp(type,"M")==0)
        return value * (1 << 20);
		else
      throw runtime_error("Incorrect block size type");
}

void parse_arguments(int argc, char *argv[], CmdLine *arguments) {
	if (argc > 3) {
    arguments->MemType = parse_memory_type(argv[1]);
  	arguments->block_size = parse_block_size(argv[2]);
  	arguments->launch_amount = atoi(argv[3]);
  	if (arguments->block_size > (4 * (1 << 20)))
      arguments->alloc_size = 4 * (1 << 20);
    else
      arguments->alloc_size = arguments->block_size;
		if(arguments->MemType == "HDD" || arguments->MemType == "SSD" || arguments->MemType == "flash" ){
			if (argc > 4) {
	      arguments->filepath = argv[4];
	    }
			else{
				arguments->filepath = "BenchmarkWritingTest.txt";
			}
		}
  } else {
    throw runtime_error("You must provide memory type, block size and launch amount");
  }
}

void Clock_ram(int block_size, int alloc_size, int repeats, long long *results, double &absolute, double &relative, double &average) {
	long long microseconds;
  for (unsigned int i = 0; i < repeats; ++i) {
    uint8_t *arr;
    int counter = 0;
    auto start_time = chrono::high_resolution_clock::now();
    while (counter < block_size) {
      arr = new uint8_t[alloc_size];
      counter += alloc_size;
    }
    auto stop_time = chrono::high_resolution_clock::now();
    delete[] arr;
    auto result = stop_time  - start_time;
    microseconds = chrono::duration_cast<chrono::nanoseconds>(result).count();
    results[i] = microseconds;
		average += microseconds;
  }
	average = average / repeats;
	absolute = fabs(average - (double)(microseconds));
	relative = absolute / average * 100;
	return;
}

void Clock_hdd_ssd_flash_write(int block_size, int alloc_size, int repeats, string filename, long long *results, double &absolute, double &relative, double &average) {
	long long microseconds;
	uint8_t arr[alloc_size];
  for (unsigned int i = 0; i < repeats; ++i) {
		for (int j = 0; j < alloc_size; ++j) {
			arr[j] = rand() % (1 << 8);
		}
    int counter = 0;
		auto file = ofstream(filename, ios::binary | ios::trunc);
    auto start_time = chrono::high_resolution_clock::now();
    while (counter < block_size) {
			file.write(reinterpret_cast<const char *>(arr), sizeof(arr));
      counter += alloc_size;
    }
    auto stop_time = chrono::high_resolution_clock::now();
		file.close();
    auto result = stop_time  - start_time;
    microseconds = chrono::duration_cast<chrono::nanoseconds>(result).count();
    results[i] = microseconds;
		average += microseconds;
  }
	average = average / repeats;
	absolute = fabs(average - (double)(microseconds));
	relative = absolute / average * 100;
	return;
}

void Clock_hdd_ssd_flash_read(int block_size, int alloc_size, int repeats, string filename, long long *results, double &absolute, double &relative, double &average) {
	long long microseconds;
	uint8_t arr[alloc_size];
  for (unsigned int i = 0; i < repeats; ++i) {
		for (int j = 0; j < alloc_size; ++j) {
			arr[j] = rand() % (1 << 8);
		}
    int counter = 0;
		auto file = fstream(filename, ios::binary | ios::trunc);
    while (counter < block_size) {
			file.write(reinterpret_cast<const char *>(arr), sizeof(arr));
      counter += alloc_size;
    }
		file.close();

		file = fstream(filename, ios::in | ios::binary);
    auto start_time = chrono::high_resolution_clock::now();
		while (!file.eof()) {
				file.read(reinterpret_cast<char *>(arr), sizeof(arr));
		}
    auto stop_time = chrono::high_resolution_clock::now();
		file.close();
    auto result = stop_time  - start_time;
    microseconds = chrono::duration_cast<chrono::nanoseconds>(result).count();
    results[i] = microseconds;
		average += microseconds;
  }
	average = average / repeats;
	absolute = fabs(average - (double)(microseconds));
	relative = absolute / average * 100;
	return;
}
