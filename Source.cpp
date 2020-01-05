#include<iostream>
#include<cmath>
#include<string>
using namespace std;
char alfabe[27];

string toString(int id) {
	//girilen pozitif int deðerini stringe çevirir
	string _id = "";
	int r;
	if (id<0) {
		return "-1";//hata durumu
	}
	else if (id == 0) {
		return "0";
	}
	for (int i = 1; i <= id; i += 0) {
		i *= 10;
		r = (id / (i / 10)) % 10;
		_id = (char)(r + 48) + _id;
	}
	return _id;
}
int toInteger(string _id) {
	//girilen stringi int çevirir (yanlýzca pozitif sayýlarda)
	if (_id[0] == -'-')
	{
		return -1;
	}
	int tmp = 0;
	for (int i = 0; i<_id.length(); i++) {
		if (_id[i] >= 48 || _id[i] <= 57) {
			tmp = tmp + (((int)_id[i]) - 48)*pow(10, _id.length() - 1 - i);
		}
		else {
			return -1;
		}
	}
	return tmp;
}
string toUpper(string kelime) {
	//harfleri buyuk hale getirir
	//ingilizce karakterler dýþýnda birþey varsa boþluk ile deðiþtirir
	for (int i = 0; i < kelime.length(); i++)
	{
		if (kelime[i] >= 'a'&&kelime[i] <= 'z')
		{
			kelime[i] -= 32;
		}
		else if (!(kelime[i] >= 'a' && kelime[i] <= 'z') && !(kelime[i] >= 'A' && kelime[i] <= 'Z') && !(kelime[i] >= 48 && kelime[i] <= 57))
		{
			kelime[i] = ' ';
		}
	}
	return kelime;
}
string input() {
	//string veri girisi
	char tmp[50];
	gets_s(tmp);
	for (int i = 0; i<strlen(tmp); i++) {
		if (tmp[i] == '*' || tmp[i] == '/' || tmp[i] == '-' || tmp[i] == '\\') {
			tmp[i] = ' ';
		}
	}
	return tmp;
}
int indisBul(char x) {
	//karakterin alfabe dizisindeki indisini verir
	if (x == ' ')
		return 0;
	else
		return x - 64;
}
string ucluSayi(int x) {
	//sayýyý üç basamaklý þekilde geri döndürür
	string uclu = toString(x);
	if (x < 10)
		uclu = "00" + uclu;
	else if (x<100)
		uclu = "0" + uclu;
	return uclu;
}

string encrypt2(string kod) {
	char key = kod[0];
	int j = 0;
	for (int i = kod.length() - 1; i > 0; i--)
	{
		if (kod[i] == key)
		{
			j = i;
			break;
		}
	}
	string tmp = "";
	if (j != 0)
	{
		//kendisinden baþka ayný karakterden var demektir
		//yer deðiþtirme iþlemi yapýlýr
		for (int i = j; i < kod.length(); i++)
		{
			tmp += kod[i];
		}
		for (int i = 0; i < j; i++)
		{
			tmp += kod[i];
		}
		return tmp;
	}
	return kod;
}
string decrypt2(string sifreliKod) {
	char key = sifreliKod[0];
	int j = 0;
	for (int i = 1; i < sifreliKod.length(); i++)
	{
		if (sifreliKod[i] == key)
		{
			j = i;
			break;
		}
	}
	string tmp = "";
	if (j != 0)
	{
		//bu metinde yer deðiþtirme uygulanmýþ þimdi geri düzelmeliyiz
		for (int i = j; i < sifreliKod.length(); i++)
		{
			tmp += sifreliKod[i];
		}
		for (int i = 0; i < j; i++)
		{
			tmp += sifreliKod[i];
		}
		return tmp;
	}
	return sifreliKod;
}
string encrypt(string kelime) {
	kelime = toUpper(kelime);
	string sifreli = "";
	if (kelime.length() % 2 != 0)
	{
		kelime += ' ';
	}
	for (int i = 0; i < kelime.length(); i += 2)
	{
		int x1 = indisBul(kelime[i]) + 1;
		int x2 = indisBul(kelime[i + 1]) + 1;
		int sonuc = (x1 - 1) * 27 + x2;
		sifreli += ucluSayi(sonuc);
	}
	return encrypt2(sifreli);
}
string decrypt(string sifreli) {
	sifreli = decrypt2(sifreli);
	string kelime = "";
	for (int i = 0; i < sifreli.length(); i += 3)
	{
		string tmp = "";
		tmp += sifreli[i];
		tmp += sifreli[i + 1];
		tmp += sifreli[i + 2];
		int sonuc = toInteger(tmp);
		int x2 = sonuc % 27;
		if (x2 == 0)
			x2 = 27;

		sonuc -= x2;
		int x1 = sonuc / 27;
		kelime += alfabe[x1];
		kelime += alfabe[x2 - 1];
	}
	return kelime;
}

int main() {
	/*
	1) 27X27 lik matris oluþturulur.
	2) Sütun ve satýr indisleri ' ' ve (A-Z) olarak kabul edilir.
	i=1 --> ' ', i=2 -->'A'
	j=1 --> ' ', j=2 -->'A'
	(indislerin 1 den baþlamasýnýn sebebi tüm matriste iþimize yarayacak bir formül ile þifreleme yapmamýzdýr)
	formül=(X1-1)*27+X2

	3) Satýr ve sütunlarýn kesiþimlerine bulunduklarý deðerlerden 2 karakterli stringler elde edirlir.
	i=0,j=1 --> " A" ; i=1,j=1 --> "AA"
	4) Hücrelerin deðeri (X1-1)*27+X2 formülü ile hesaplanýr.
	"AB" nin hücre deðeri (1-1)*27+2 = 29
	5) Girilen açýk metin 2 karakterli gruplar halinde ele alýnýr ve formülden hücre deðeri bulunur.
	6)	Bulunan hücre deðeri þifreli metine eklenir ve açýk metnin sonuna kadar bu iþlem tekrar tekrar yapýlýr.
	7) Ýþlem sonunda þifreli metin elde edilmiþ olur.
	örn: "ABAC" kelimesini þifreleyelim
	Öncelikle "AB" ele alýnýr
	A'nýn indisi 2
	B'nin indisi 3
	Hücre deðeri=(2-1)*27+3=30
	Bu hücre deðerini 3 basamaklý þekilde yazýyoruz
	Þifreli=029

	Sonra "AC" ele alýnýr
	A'nýn indisi 2
	C'nin indisi 4
	Hücre deðeri=(2-1)*27+4=31
	Bu hücre deðerini 3 basamaklý þekilde yazýyoruz
	Þifreli=029 030

	EKSTRA: Bu þifreli metni karýþtýrarak çözülmesini daha da zorlaþtýrýyoruz
	029 030 --> 002903 halini alýyor

	1) Ýlk karakter alýnýr (0)
	2) Metin içinde tersten bu karakter aranýr (029 030)
	3) Bulunan yere kadar olan kýsým kesilir ve metnin baþýna eklenir

	(0)29 03(0) --> (0)(0)2903 --> 002903
	(0)15(049) -->  (049)(0)15 --> 049015
	*/

	alfabe[0] = ' ';
	for (int i = 1; i < 27; i++)
	{
		alfabe[i] = (char)i + 64;
		cout << alfabe[i] << " ";
	}
	cout << endl;
	cout << "Yanlizca Ingilizce karakterler kullanilmalidir. Aksi halde bosluk olarak degistirilir." << endl;

	while (true) {
		cout << "Sifrelenecek Metin: ";
		string key = input();
		string sifreli = encrypt(key);
		cout << "Sifrelenmis Hali: " << sifreli << endl;
		cout << "   Cozulmus Hali: " << decrypt(sifreli) << endl;
	}
	system("pause");

}
