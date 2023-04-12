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

	void ParaYatýrma(float miktar);
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
	Account ParaYatýrma(int hesapno, float bakiye, float miktar);
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
		cout << "Hesap ayrýntýlarýnýzý görüntülemek icin '6' basiniz." << endl;
		cout << "Çýkýþ için '7' basiniz." << endl;
		cout << "Lütfen seçeneðinizi giriniz.";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Lütfen hesap sahibinin adýný giriniz:  ";
			cin >> fname;
			cout << "Lütfen hesap sahibinin soyadýný giriniz:  ";
			cin >> lname;
			cout << "Tebrikler hesabýnýz oluþturuldu lütfen aktifleþmesi için hesabýnýza bakiye yükleyin:  ";
			cin >> bakiye;
			acc = b.OpenAccount(fname, lname, bakiye);
			cout << endl << "Hesap oluþturuldu." << endl;
			cout << acc;
			break;
		case 2:
			cout << "Hesabýnýzýn bazý bilgilerine ihtiyac duyuyorum lütfen hesap numaranýzý girer misiniz." << endl;
			cin >> hesapno;
			acc = b.BakiyeSorgu(hesapno);
			cout << "Bazý hesap ayrýntýlarýnýz: " << acc;
			break;
		case 3:
			cout << "Hesap numaranýzý giriniz: " << endl;
			cin >> hesapno;
			cout << "Yatýrýlacak miktarý giriniz." << endl;
			cin >> miktar;
			acc = b.ParaYatýrma(hesapno, bakiye, miktar);
			cout << "Paranýz yatýrýldý.Ýyi günler." << endl;
			cout << acc;
			break;

		case 4:
			cout << "Hesap numaranýzý giriniz:  ";
			cin >> hesapno;
			cout << "\nÇekim yapýlmak istenen tutar:  ";
			cin >> miktar;
			acc = b.ParaCekme(hesapno, bakiye, miktar);
			cout << "Çekim baþarýlý.";
			cout << acc;
			break;

		case 5:
			cout << "Silmek istediðiniz hesap numarasýný giriniz: ";
			cin >> hesapno;
			cout << "Silmek istediðinize eminseniz '1' e basýnýz." << endl;
			cin >> eminmisin;
			if (eminmisin == 0)
			{
				b.HesapSilme(hesapno);
				cout << "Hesabiniz silindi. Ýyi günler dileriz." << endl;
				cout << acc;
			}
			break;
		case 6:
			cout << "Tüm hesaplar: ";
			b.HesaplariGoster();
			break;
		case 7:
			break;
		default:
			cout << "Lütfen doðru tuþladýgýnýzdan emin olun." << endl;
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
void Account::ParaYatýrma(float miktar)
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
	os << "Ýsim: " << acc.getFirstName() << endl;
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
Account Bank::ParaYatýrma(int hesapno, float bakiye, float miktar)
{
	map<int, Account>::iterator itr = accounts.find(hesapno);
	itr->second.ParaYatýrma(miktar);
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