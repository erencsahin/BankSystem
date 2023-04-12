#include <fstream>
#include <iostream>
#include <map>
using namespace std;

class Account
{
private:
	int hesapno;
	string firstname;
	string lastname;
	float bakiye;
	float miktar;
	static long NextAccountNumber;
public:
	Account() {}
	Account(string fname, string lname, float bakiye);
	int getHesapNo() { return hesapno; }
	string getFirstName() { return firstname; }
	string getLastName() { return lastname; }
	float getBalance() { return bakiye; }

	void ParaYat�rma(float miktar);
	void ParaCekme(float miktar);
	static void setLastAccountNumber(int hesapno);
	static int getLastAccountNumber();
	friend ofstream& operator<<(ofstream& ofs, Account& acc);
	friend ifstream& operator>>(ifstream& ifs, Account& acc);
	friend ostream& operator<<(ostream& os, Account& acc);
};
long Account::NextAccountNumber = 0;

class Bank
{
private:
	map<int, Account> accounts;
public:
	Bank();
	Account OpenAccount(string fname, string lname, float bakiye);
	Account BakiyeSorgu(int hesapno);
	Account ParaYat�rma(int hesapno, float bakiye, float miktar);
	Account ParaCekme(int hesapno, float bakiye, float miktar);
	void HesapSilme(int hesapno);
	void HesaplariGoster();
	~Bank();
};

int main()
{
	setlocale(LC_ALL, "Turkish");
	Bank b;
	Account acc;
	string fname, lname;
	int hesapno;
	int choice;
	float bakiye;
	float miktar;
	int eminmisin;
	cout << "\tHOSGELDINIZ.." << endl;
	do
	{
		cout << "Seceneklerimiz;\t" << endl;
		cout << "Hesap Olusturmak icin '1' basiniz." << endl;
		cout << "Bakiye sorgulama icin '2' basiniz." << endl;
		cout << "Para yatirmak icin '3' basiniz." << endl;
		cout << "Para cekmek icin '4' basiniz." << endl;
		cout << "Hesap silmek icin '5' basiniz." << endl;
		cout << "Hesap ayr�nt�lar�n�z� g�r�nt�lemek icin '6' basiniz." << endl;
		cout << "��k�� i�in '7' basiniz." << endl;
		cout << "L�tfen se�ene�inizi giriniz.";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "L�tfen hesap sahibinin ad�n� giriniz:  ";
			cin >> fname;
			cout << "L�tfen hesap sahibinin soyad�n� giriniz:  ";
			cin >> lname;
			cout << "Tebrikler hesab�n�z olu�turuldu l�tfen aktifle�mesi i�in hesab�n�za bakiye y�kleyin:  ";
			cin >> bakiye;
			acc = b.OpenAccount(fname, lname, bakiye);
			cout << endl << "Hesap olu�turuldu." << endl;
			cout << acc;
			break;
		case 2:
			cout << "Hesab�n�z�n baz� bilgilerine ihtiyac duyuyorum l�tfen hesap numaran�z� girer misiniz." << endl;
			cin >> hesapno;
			acc = b.BakiyeSorgu(hesapno);
			cout << "Baz� hesap ayr�nt�lar�n�z: " << acc;
			break;
		case 3:
			cout << "Hesap numaran�z� giriniz: " << endl;
			cin >> hesapno;
			cout << "Yat�r�lacak miktar� giriniz." << endl;
			cin >> miktar;
			acc = b.ParaYat�rma(hesapno, bakiye, miktar);
			cout << "Paran�z yat�r�ld�.�yi g�nler." << endl;
			cout << acc;
			break;

		case 4:
			cout << "Hesap numaran�z� giriniz:  ";
			cin >> hesapno;
			cout << "\n�ekim yap�lmak istenen tutar:  ";
			cin >> miktar;
			acc = b.ParaCekme(hesapno, bakiye, miktar);
			cout << "�ekim ba�ar�l�.";
			cout << acc;
			break;

		case 5:
			cout << "Silmek istedi�iniz hesap numaras�n� giriniz: ";
			cin >> hesapno;
			cout << "Silmek istedi�inize eminseniz '1' e bas�n�z." << endl;
			cin >> eminmisin;
			if (eminmisin == 0)
			{
				b.HesapSilme(hesapno);
				cout << "Hesabiniz silindi. �yi g�nler dileriz." << endl;
				cout << acc;
			}
			break;
		case 6:
			cout << "T�m hesaplar: ";
			b.HesaplariGoster();
			break;
		case 7:
			break;
		default:
			cout << "L�tfen do�ru tu�lad�g�n�zdan emin olun." << endl;
			exit(0);
			break;
		}
	} while (choice != 7);
	return 0;
}
Account::Account(string fname, string lname, float bakiye)
{
	NextAccountNumber++;
	hesapno = NextAccountNumber;
	firstname = fname;
	lastname = lname;
	this->bakiye = bakiye;
};
void Account::ParaYat�rma(float miktar)
{
	bakiye = bakiye + miktar;
}
void Account::ParaCekme(float miktar)
{
	bakiye = bakiye - miktar;
}
void Account::setLastAccountNumber(int hesapno)
{
	NextAccountNumber = hesapno;
}
int Account::getLastAccountNumber()
{
	return NextAccountNumber;
}
ofstream& operator<<(ofstream& ofs, Account& acc)
{
	ofs << acc.hesapno << endl;
	ofs << acc.firstname << endl;
	ofs << acc.lastname << endl;
	ofs << acc.bakiye << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Account& acc)
{
	ifs >> acc.hesapno;
	ifs >> acc.firstname;
	ifs >> acc.lastname;
	ifs >> acc.bakiye;
	return ifs;
}
ostream& operator<<(ostream& os, Account& acc)
{
	os << "�sim: " << acc.getFirstName() << endl;
	os << "Soyisim: " << acc.getLastName() << endl;
	os << "Hesap numarasi: " << acc.getHesapNo() << endl;
	os << "Bakiye: " << acc.getBalance() << endl;
	return os;
}
Bank::Bank()
{
	Account account;
	ifstream infile;

	infile.open("Bankdata.txt");
	if (!infile)
	{
		cout << "Error 404 not found." << endl;
		return;
	}
	while (!infile.eof())
	{
		infile >> account;
		accounts.insert(pair<int, Account>(account.getHesapNo(), account));
	}
	Account::setLastAccountNumber(account.getHesapNo());
	infile.close();
}
Account Bank::OpenAccount(string fname, string lname, float bakiye)
{
	ofstream outfile;
	Account account(fname, lname, bakiye);
	accounts.insert(pair<int, Account>(account.getHesapNo(), account));
	outfile.open("Bankdata.txt");
	map<int, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
	return account;
}
Account Bank::BakiyeSorgu(int hesapno)
{
	map<int, Account>::iterator itr = accounts.find(hesapno);
	return itr->second;
}
Account Bank::ParaYat�rma(int hesapno, float bakiye, float miktar)
{
	map<int, Account>::iterator itr = accounts.find(hesapno);
	itr->second.ParaYat�rma(miktar);
	return itr->second;
}
Account Bank::ParaCekme(int hesapno, float bakiye, float miktar)
{
	map<int, Account>::iterator itr = accounts.find(hesapno);
	itr->second.ParaCekme(miktar);
	return itr->second;
}
void Bank::HesapSilme(int hesapno)
{
	map<int, Account>::iterator itr = accounts.find(hesapno);
	accounts.erase(hesapno);
}
void Bank::HesaplariGoster()
{
	map<int, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		cout << "Account" << itr->first << endl;
		itr->second;
		cout << endl;
	}
}
Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bankdata.txt", ios::trunc);
	map<int, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
}