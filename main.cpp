#include <iostream>
#include <fstream>

using namespace std;

int n;
bool type;
fstream file;

void print(int x, bool f) {
	if(f == false){
		file.open("losowa.txt", ios::out|ios::app);
	}
	else{
		file.open("losowa.txt", ios::out);
	}
	cout << x;
	file << x;
	file.close();
}

void shift(int* s){
	for(int temp=n-1; temp>0; temp--){
		s[temp] = s[temp-1];
	}
}

bool checkIfPeriod(int* origin, int* s){
	bool check = true;
	for(int i=0; i<n; i++){
		if(s[i] != origin[i]){
			check = false;
			break;
		}
	}
	
	return check;
}

void lfsr(int* s, int* c){
	int feedback = 0;
	int ctr = 0;
	int* origin = new int[n];
	for(int i=0; i<n; i++){
		origin[i] = s[i];
	}
	do{
		if(ctr==0){
			print(s[n-1], true);
		}
		else{
			print(s[n-1], false);
		}
		if(!type){
			feedback = s[n-1];
			shift(s);
			s[0] = feedback;
		}
		for(int j=0; j<n; j++){
			if(type){
				if(c[j+1] == 1){
					feedback += s[j];
				}
			}
			else{
				if(c[j] == 1 && j!=0){
					s[j] = (s[j] + feedback) % 2;
				}
			}
		}
		if(type){
			shift(s);
			s[0] = feedback%2;
			feedback = 0;	
		}
		ctr++;	
	}while(!checkIfPeriod(origin,s));
	
	cout << "\nWygenerowana sekwencja ma dlugosc: " << ctr << "\n\n";
	delete [] origin;
}

int main() {
	
	cout << "Program sluzy do generowania liczb losowych w sposob imitujacy dzialanie rejestru przesuwnego LFSR.\n" << endl;
	
	cout << "Podaj dlugosc rejestru: ";
	cin >> n;
	while(!n || n<=1){
		cout << "Deklarowana dlugosc rejestru musi byc wieksza od 1! Sprobuj jeszcze raz." << endl;
		cout << "Podaj dlugosc rejestru: ";
		cin >> n;
	}
	
	cout << "Wybierz typ sprzezenia zwrotnego (0 dla wewnetrznego lub 1 dla zewnetrznego): ";
	cin >> type;
	
	int* c = new int[n+1];
	cout << "Wprowadz wektor sprzezenia (0 dla braku sprzezenia lub 1 dla sprzezenia):" << endl;
	int i, cLen;
	if(type){
		c[0] = 1;
		i = 1;
		cLen = n;
		cout << "Wartosc elementu [1]: 1" << endl;
	}
	else{
		c[n] = 1;
		i = 0;
		cLen = n-1;
	}
	for(; i<=cLen; i++){
		cout << "Wartosc elementu [" << i+1 << "]: ";
		cin >> c[i];
		while(c[i] != 0 && c[i] != 1){
			cout << "Niepoprawne dane. Wektor sprzezenia moze przyjac jedynie wartosci 0 lub 1! Sprobuj jeszcze raz." << endl;
			cout << "Wartosc elementu [" << i+1 << "]: ";
			cin >> c[i];
		}
	}
	if(!type){
		cout << "Wartosc elementu [" << n+1 << "]: 1" << endl;
	}
	
	int* s = new int[n];
	cout << "Wprowadz stan poczatkowy rejestru (0 lub 1):" << endl;
	for(i=0; i<n; i++){
		cout << "Wartosc elementu [" << i+1 << "]: ";
		cin >> s[i];
		while(s[i] != 0 && s[i] != 1){
			cout << "Niepoprawne dane. Rejestr moze przyjac tylko wartosci 0 lub 1! Sprobuj jeszcze raz." << endl;
			cout << "Wartosc elementu [" << i+1 << "]: ";
			cin >> s[i];
		}
	}
	
	cout << "\nGeneruje liczbe losowa na podstawie zadanych parametrow..." << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\nWygenerowana sekwencja: ";
	
	lfsr(s,c);


	cout << "\n\n------------------------------------------------------------" << endl;
	cout << "\nWynik generacji zostal zapisany do pliku losowa.txt" << endl;
	
	delete [] s;
	delete [] c;
	return 0;
}
