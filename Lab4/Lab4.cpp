#include <iostream>
#include <Windows.h>
#include <ctime>

double fun(double x) {
	return x * x * x;
}

struct Thread_data
{
	double begin;
	double finish;
	int id;
};

int ILE_WATKOW;

double* tab;

DWORD WINAPI solo_thread(Thread_data* data)
{
	double tmp = 0;
	for (double j = data->begin; j < data->finish; j += 0.0001) {
		tmp += fun(j) * 0.0001;
	}
	tab[data->id] = tmp;
	free(data);
	return 0;
}



int main()
{
	/*std::cout << "Podaj liczbe watkow: ";
	std::cin >> ILE_WATKOW;
	tab = new double[ILE_WATKOW];*/

	/*STARTUPINFOA info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	char tmp[] = "Notepad.exe";
	if (CreateProcessA(NULL, tmp, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);
	}*/
	for (int i = 0; i < 5; i++) {
		ILE_WATKOW = i + 1;
		tab = new double[ILE_WATKOW];

		clock_t begin = clock();
		HANDLE* watki = new HANDLE[ILE_WATKOW];
		for (double j = 0; j < ILE_WATKOW; j++) {
			Thread_data* data = new Thread_data;
			data->begin = (100000 / ILE_WATKOW) * j;
			data->finish = (100000 / ILE_WATKOW) * (j + 1);
			data->id = (int)j;
			watki[(int)j] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solo_thread, data, 0, NULL);
		}

		WaitForMultipleObjects(ILE_WATKOW, watki, true, INFINITE);
		double wynik = 0;
		for (int j = 0; j < ILE_WATKOW; j++) {
			wynik += tab[j];
		}
		std::cout << "liczba watkow: " << ILE_WATKOW << " --- czas wykonywania: " << clock() - begin << " --- wynik: " << wynik << "\n";
		delete[] tab;
	}

	return 0;
}