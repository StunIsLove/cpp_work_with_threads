#include <iostream>;
#include <math.h>
#include <chrono>;
#include <thread>;
#include <mutex>;

using namespace std;

mutex mtx;

void integral(double a, double b, double h) {
    unique_lock<mutex> um(mtx);

    int i; // счётчик

	for(int j = 0; j <= 100; j++) {
        double Integral; // переменная для хранения интеграла

        double n; // число разбиений n

        n = (b - a) / h;

        // интеграл по формуле Симпсона
        Integral = h * (sin(a) + sin(b)) / 6.0;
        for(i = 1; i <= n; i++)
            Integral = Integral + 4.0 / 6.0 * h * sin(a + h * (i - 0.5));
        for(i = 1; i <= n-1; i++)
            Integral = Integral + 2.0 / 6.0 * h * sin(a + h * i);

        cout << Integral << endl;

        a = a + 0.1;
        b = b + 0.1;
        h = h + 0.1;

        //this_thread::sleep_for(chrono::milliseconds(20));
    }

    um.unlock();
}

int main() {
	setlocale(LC_ALL, "Russian");

	thread t1(integral,0.0,1.0,0.1);
	thread t2(integral,0.0,2.0,0.2);

	t1.join();
	t2.join();

	return 0;
}

