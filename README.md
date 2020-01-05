# MatrisTabanliSifreleme

1) 27X27 lik matris oluşturulur.

2) Sütun ve satır indisleri ' ' ve (A-Z) olarak kabul edilir.
	i=1 --> ' ', i=2 -->'A'
	j=1 --> ' ', j=2 -->'A'
	(indislerin 1 den başlamasının sebebi tüm matriste işimize yarayacak bir formül ile şifreleme yapmamızdır)
	formül=(X1-1)*27+X2

3) Satır ve sütunların kesişimlerine bulundukları değerlerden 2 karakterli stringler elde edirlir.
	i=0,j=1 --> " A" ; i=1,j=1 --> "AA"

4) Hücrelerin değeri (X1-1)*27+X2 formülü ile hesaplanır.
	"AB" nin hücre değeri (1-1)*27+2 = 29

5) Girilen açık metin 2 karakterli gruplar halinde ele alınır ve formülden hücre değeri bulunur.

6) Bulunan hücre değeri şifreli metine eklenir ve açık metnin sonuna kadar bu işlem tekrar tekrar yapılır.

7) İşlem sonunda şifreli metin elde edilmiş olur.

	örn: "ABAC" kelimesini şifreleyelim
	Öncelikle "AB" ele alınır
	A'nın indisi 2
	B'nin indisi 3
	Hücre değeri=(2-1)*27+3=30
	Bu hücre değerini 3 basamaklı şekilde yazıyoruz
	Şifreli=029

	Sonra "AC" ele alınır
	A'nın indisi 2
	C'nin indisi 4
	Hücre değeri=(2-1)*27+4=31
	Bu hücre değerini 3 basamaklı şekilde yazıyoruz
	Şifreli=029 030

	EKSTRA: Bu şifreli metni karıştırarak çözülmesini daha da zorlaştırıyoruz
	029 030 --> 002903 halini alıyor

	1) İlk karakter alınır (0)
	2) Metin içinde tersten bu karakter aranır (029 030)
	3) Bulunan yere kadar olan kısım kesilir ve metnin başına eklenir

	(0)29 03(0) --> (0)(0)2903 --> 002903
	(0)15(049) -->  (049)(0)15 --> 049015
