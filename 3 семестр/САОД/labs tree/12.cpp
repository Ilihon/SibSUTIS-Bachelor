#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <iomanip>
#include <map>
#include <math.h>

using namespace std;

constexpr int BLOCK = 64;//

static size_t search(std::vector<std::pair<char, long double>>& pair, const char& el) { //поиск символа из текста в алфавите
	for (size_t i = 0; i < pair.size(); i++) 
		if (pair[i].first == el) 
			return i;
	return std::string::npos;
}

string Arithmetic(vector<pair<char, long double>> alphabet, const string& text) { // арифметическое кодирование 
	vector<long double> r(text.size() + 1, 0);
	vector<pair<long double, long double>> border(text.size() + 1);
	vector<long double> Q(alphabet.size() + 1, 0);
	
	r[0] = 1;
	border[0].second = 1;
	
	for (int i = 0; i < (int)alphabet.size(); i++) {
		Q[i + 1] = alphabet[i].second + Q[i];							// расчёт вероятностей Q
	}
	
	int m = 0;
	int i = 0;
	for (int i = 1; i <= (int)text.size(); i++) {
		int m = search(alphabet, text[i - 1]) + 1;						//поиск символа в алфавите
		border[i].first = border[i - 1].first + r[i - 1] * Q[m - 1];	//расчёт левой границы
		border[i].second = border[i - 1].first + r[i - 1] * Q[m];		//расчёт правой границы
		r[i] = border[i].second - border[i].first;
	}
	
	int count = (int)ceil(-log2(r.back()));
	
	return (get<1>(ftobs((border.back().second + border.back().first) / 2)).substr(0, (count > (int)text.size() ? text.size() : count)));	//возвращем кодовое слова с нужным размером, если размер блока 
}																																			//больше размера текста, то возвращается с размером текста

int main()
{
	string getlineBuffer = "";
	string text = "";
	
	ifstream file;
	
	file.open("text.txt", ios::in); //читаем файл
	while (getline(file, getlineBuffer)) text += getlineBuffer; 
	file.close();
	getlineBuffer.clear();
	
	// Создаём вектор пар для букв алфавита и их вероятностей
	std::vector<std::pair<char, long double>> alphabet;
	
	// Заполняем уникальными буквами и частотой встречи её в тексте
	for (size_t i = 0; i < text.size(); i++) {
		size_t index = search(alphabet, text[i]); //ищем букву текста в нашем алфавите 
		
		if (index != std::string::npos) //если нашли, то +1 появление в алфавит
			alphabet[index].second += 1.0;
		else alphabet.push_back(std::make_pair(text[i], 1.0)); // если не нашли то добавляем впервые в алфавит
	}
	
	long double ver = 0;
	// Расчитываем вероятности для каждого символа
	for (size_t i = 0; i < alphabet.size(); i++) {
		alphabet[i].second /= (long double)text.size();
		cout << alphabet[i].first << " " << alphabet[i].second << endl;
		ver += alphabet[i].second;									// считаем сумму вероятностей
	}
	cout << endl << "Sum of probability: " << ver << endl << endl; // сумма вероятностей должна быть 1
	
	int size = (int)ceil(text.size() / (double)BLOCK); // расчёт количества блоков на файл
	cout << size << " blocks:" << endl << endl;
	
	for (int i = 0; i < (int)text.size(); i += BLOCK) {
		cout << Arithmetic(alphabet, text.substr(i, BLOCK)); 
		cout << endl;
	}
}
