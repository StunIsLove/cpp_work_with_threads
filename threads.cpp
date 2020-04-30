#include <iostream>;
#include <math.h>
#include <chrono>;
#include <thread>;

using namespace std;

double integral(double a, double b, double h) {
	for(int i = 0; i < 10; i++) {
		cout << "ID" << this_thread::get_id() << " iteration " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	int i; // счётчик
  	double Integral; // переменная для хранения интеграла

  	double n; // число разбиений n

  	n = (b - a) / h;

  	// интеграл по формуле Симпсона
  	Integral = h * (sin(a) + sin(b)) / 6.0;
  	for(i = 1; i <= n; i++)
		Integral = Integral + 4.0 / 6.0 * h * sin(a + h * (i - 0.5));
  	for(i = 1; i <= n-1; i++)
		Integral = Integral + 2.0 / 6.0 * h * sin(a + h * i);
  	return Integral;
}

int main() {
	setlocale(LC_ALL, "Russian");

	double answer;
	thread t1([&answer](){
            integral(0.0,1.0,0.1);
           });

	for(int i = 0; i < 10; i++) {
		cout << "ID" << this_thread::get_id() << " iteration " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	t1.join();
	cout << "Integral = " << answer << endl;

	return 0;
}
