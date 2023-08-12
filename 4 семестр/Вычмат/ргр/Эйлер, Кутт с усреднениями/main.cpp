#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double h = 0.2;
double x0 = 0;
double y0 = 1;

double iteration_1(double x, double y) 
{
	return (x * x) - (2 * y);
}

double iteration_2(double x, double y) 
{
	return y + (h/2) * iteration_1(x, y);
}

int main()
{
	setlocale(LC_ALL, "rus");
	double x = x0;
	vector<double> y = {y0};
	int step;

	cout << "Сколько итераций?\n>";
	cin >> step;
	cout << endl;

	while (step > 0) {
		y.push_back(y[y.size() - 1] + iteration_1(x, y[y.size() - 1]) * h);
		x += h;
		step--;
	}

	cout << "Метод Эйлера:\n";
	for (int i = 0; i < y.size(); i++) {
		cout << y[i] << setw(15);
	}

	cout << "\n\nСколько итераций?\n>";
	cin >> step;
	cout << endl;

	x = x0;
	y.clear();
	y.push_back(y0);

	while (step > 0) {
		y.push_back(y[y.size() - 1] + h * iteration_1(x + (h / 2), iteration_2(x, y[y.size() - 1])));
		x += h;
		step--;
	}
	cout << "Метод Рунге-Кутта с усреднением по времени:\n";
	for (int i = 0; i < y.size(); i++) {
		cout << y[i] << setw(15);
	}

	cout << "\n\nСколько итераций?\n>";
	cin >> step;
	cout << endl;

	x = x0;
	y.clear();
	y.push_back(y0);

	while (step > 0) {
		y.push_back(y[y.size() - 1] + (h / 2) * (iteration_1(x, y[y.size() - 1]) + iteration_1(x + h, iteration_2(x, y[y.size() - 1]))));

		x += h;
		step--;
	}

	cout << "Метод Рунге-Кутта с усреднением по производной:\n";
	for (int i = 0; i < y.size(); i++) {
		cout << y[i] << setw(15);
	}

	return 0;
}
