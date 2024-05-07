/*************************************************************************************
**							    SAKARYA �N�VERS�TES�
**                      B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**                           B�LG�SAYAR M�HEND�SL��� B�L�M�
**							   PROGRAMLAMAYA G�R�� DERS�
**
**                      �DEV NUMARASI    : 2
**		                ��RENC� ADI      : HAKAN EFE T�YS�Z
**                      ��RENC� NUMARASI : B231210098
**                      DERS GURUBU      : B GURUBU
***************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>

using namespace std;

struct KriptoPara {        // Bu k�s�mlarda baz� yap� veri t�rleri tan�ml�yoruz
	string ad;
	double deger;
};

struct Hesap {

	string ID;
	string sifre;
	int hesapTuruSecim;
	KriptoPara kriptoPara;
	double kriptoMiktari;
	int gunSayaci;
	bool ozelHesap;

	Hesap():kriptoMiktari(0),gunSayaci(0),ozelHesap(false){}  // Burada yap�c� fonksiyon ile ba�lang�� de�erlerini at�yoruz
};

class HesapSistemi {   // Burada s�n�f�m�z� tan�mlay�p i�ine uygun verileri ve metotlar� yaz�yoruz
private:
	static const int MaxHesapAdedi = 100;
	Hesap hesaplar[MaxHesapAdedi];
	int hesapAdedi = 0;

public:
	void hesapOlustur() {     // Bu k�s�mda a��lacak hesab�n t�r�, �ifresi ve ID si belirleniyor
		if (hesapAdedi >= MaxHesapAdedi) {
			cout << "Maksimum hesap sayisina ulasildi!" << endl;
			return;
		}

		Hesap yeniHesap;
		yeniHesap.ID = idUret();

		cout << "Yeni sifre olusturun:";
		cin >> yeniHesap.sifre;
		while (true) {        // Hesap t�r� i�in se�im yapt�r�l�yor
			cout << "Lutfen hesap turunu seciniz:" << endl;
			cout << "1) Genel Hesap" << endl;
			cout << "2) Ozel Hesap" << endl;
			int hesapTur;
			cin >> hesapTur;
			
			if (hesapTur == 1)
				break;
			else if (hesapTur == 2) {
				yeniHesap.ozelHesap = true;
				break;
			}
			else
				cout << "Gecersiz secim!" << endl;	
		}
		yeniHesap.kriptoPara.ad = "Hakancoin";
		yeniHesap.kriptoPara.deger = 1.0f;
		yeniHesap.kriptoMiktari = 0;

		hesaplar[hesapAdedi] = yeniHesap;
		++hesapAdedi;
		cout << "Hesap olusturuldu." << endl;
		cout << "ID:" << yeniHesap.ID << endl;
	}
	void girisYap() {                   // Burada hesab�n ID ve �ifre bilgileri do�rulan�yor
		string girilenID, girilenSifre;

		cout << "ID giriniz:";
		cin >> girilenID;

		cout << "Sifreyi giriniz:";
		cin >> girilenSifre;

		int kullaniciIndeks = -1;

		for (int i = 0; i < hesapAdedi; ++i) {
			if (hesaplar[i].ID == girilenID and hesaplar[i].sifre == girilenSifre) {
				kullaniciIndeks = i;
				break;
			}
		}

		if (kullaniciIndeks != -1) {
			menuGoster(kullaniciIndeks);
		}
		else {
			cout << "Giris basarisiz . Hatali ID veya sifre" << endl;
		}
		
	}
	void cikisYap() {     // Uygulamadan tamamen ��k�lmaya yar�yor
		cout << "Cikis yapildi." << endl;
	}
	
	void tumHesaplariGoster() {    // Burada a��lan t�m hesaplar�n ID ve para miktarlar� g�steriliyor
		cout << "Tum hesaplar:" << endl;
		for (int i = 0; i < hesapAdedi; ++i) {
			cout << "Hesap ID:" << hesaplar[i].ID << endl;
			cout << "Toplam Kripto Para Sayisi:" << hesaplar[i].kriptoMiktari << endl;
			cout << "Toplam TL:" << hesaplar[i].kriptoPara.deger * hesaplar[i].kriptoMiktari << "TL"<<endl;
			cout << "--------------------------------"<<endl;
		}
	}
private:
	void menuGoster(int kullaniciIndeks) {   // Bu k�s�mda ki�i hesap a��p kullan�c� indeksi -1 den farkl� olunca buradaki men�ye y�nlendiriliyor
		while (true) {
			cout << "***********************************" << endl;
			cout << "Yapacaginiz islemi seciniz" << endl;
			cout << "1) Kripto para al" << endl;
			cout << "2) kripto para sat" << endl;
			cout << "3) Bakiye" << endl;
			cout << "4) Gun arttir" << endl;
			cout << "5) Cikis" << endl;
			cout << "***********************************" << endl;

			int secim;
			cin >> secim;       // Burada kullan�c� a�t��� hesap i�in yapaca�� i�lemi se�iyor
			switch (secim) {
			case 1:
				kriptoParaAl(kullaniciIndeks);
				break;
			case 2:
				kriptoParaSat(kullaniciIndeks);
				break;
			case 3:
				bakiyeGoster(kullaniciIndeks);
				break;
			case 4:
				gunArttir(kullaniciIndeks);
				break;
			case 5:
				return;
			default:
				cout << "Gecersiz secim , Tekrar deneyin" << endl;
				break;
			}
		}
	}

	void kriptoParaAl(int kullaniciIndeks) {    // Burada kullan�c� alaca�� kripto para i�in verece�i TL miktar�n� giriyor
		cout << "Guncel kripto para degeri:" << hesaplar[kullaniciIndeks].kriptoPara.deger << "TL" << endl;
		double alinacakMiktar;
		cout << "Alinacak kripto para icin verilecek TL miktarini giriniz:";
		cin >> alinacakMiktar;
		hesaplar[kullaniciIndeks].kriptoMiktari +=alinacakMiktar/ hesaplar[kullaniciIndeks].kriptoPara.deger;
		cout << "Kripto para alindi." << endl;
	}

	void kriptoParaSat(int kullaniciIndeks)    // Burada kullan�c� hesab�ndaki TL miktar�na g�re istedi�i kadar TL'yi �ekebiliyor
	{
		cout << "Guncel kripto para degeri:" << hesaplar[kullaniciIndeks].kriptoPara.deger << "TL" << endl;
		double satilacakMiktar;
		cout << "Hesaptan cekilecek TL miktarini giriniz:";
		cin >> satilacakMiktar;
	if(hesaplar[kullaniciIndeks].kriptoMiktari>=satilacakMiktar/hesaplar[kullaniciIndeks].kriptoPara.deger){
		hesaplar[kullaniciIndeks].kriptoMiktari-=satilacakMiktar/ hesaplar[kullaniciIndeks].kriptoPara.deger;
		cout << "Kripto para satildi" << endl;
	}
	else {
		cout << "Satilacak kripto para bulunamadi" << endl;
	}
}
void bakiyeGoster(int kullaniciIndeks) {   // Burada kullan�c� hesab�ndaki kripto para ve TL miktar�n� g�rebiliyor
	cout << "Hesapta " << hesaplar[kullaniciIndeks].kriptoMiktari << " adet kripto para bulunmaktadir" << endl;
	double kriptoDegeri = hesaplar[kullaniciIndeks].kriptoPara.deger;
	double bakiyeTL = hesaplar[kullaniciIndeks].kriptoMiktari * kriptoDegeri;
	cout << "Toplam TL degeri:" << bakiyeTL << "TL" << endl;
}

void gunArttir(int kullaniciIndeks) {   // Bu k�s�mda se�ilen hesap t�r�ne g�re kripto para kuru g�nl�k olarak (G�n artt�r tu�una basarak) de�i�iyor
	hesaplar[kullaniciIndeks].gunSayaci++;
	if (!hesaplar[kullaniciIndeks].ozelHesap) {
		if (hesaplar[kullaniciIndeks].gunSayaci % 15 == 0) {
			hesaplar[kullaniciIndeks].kriptoPara.deger *= 0.95f;
		}
		else {
			hesaplar[kullaniciIndeks].kriptoPara.deger *= 1.01;
		}
		cout << "Gun arttirildi" << endl;
		cout << "Gun sayisi:" << hesaplar[kullaniciIndeks].gunSayaci << endl;
		cout << "Guncel kripto para degeri: " << hesaplar[kullaniciIndeks].kriptoPara.deger << "TL" << endl;
	}
	else if (hesaplar[kullaniciIndeks].ozelHesap)
	{
		
		if (hesaplar[kullaniciIndeks].gunSayaci % 30 == 0) { 
			srand(time(0));
			int gun1 = rand() % 30 +1;
			int gun2 = rand() % 30 +1;    //Burada gun sayac�n�n her 30 g�nl�k periyotta rastgele g�nleri �nceki periyottan farkl� se�tirmeye �al��t�m
			int gun3 = rand() % 30 +1;
		}
		
		int gun1 = rand() % 30 +1;
		int gun2 = rand() % 30 +1;
		int gun3 = rand() % 30 +1;
		
		// Burada rastgele se�ilen g�nlerin g�n sayac�na g�re tutup tutmad��� belirleniyor
		if (hesaplar[kullaniciIndeks].gunSayaci % 30==gun1 or hesaplar[kullaniciIndeks].gunSayaci % 30 == gun2 or hesaplar[kullaniciIndeks].gunSayaci % 30 == gun3) {
			
			
				hesaplar[kullaniciIndeks].kriptoPara.deger *= 0.90f;
			
		}
		else {
			hesaplar[kullaniciIndeks].kriptoPara.deger *= 1.05f;
		}

		cout << "Gun arttirildi" << endl;
		cout << "Gun sayisi:" << hesaplar[kullaniciIndeks].gunSayaci << endl;
		cout << "Guncel kripto para degeri: " << hesaplar[kullaniciIndeks].kriptoPara.deger << "TL" << endl;
	}
}
	string idUret() {   // Bu k�s�mda rastgele ID belirleniyor
		srand(time(0));
		string id;
		for (int i = 0; i < 6; ++i) {
			int b = rand() % 10;
			id += to_string(b);
		}
		return id;
	}
	
};

int main() {   // Burada ise son olarak program�n ana fonksiyonunu yaz�yoruz 
	HesapSistemi sistem;

	while (true) {
		cout << "***********************************" << endl;
		cout << "Yapacaginiz islem secin:" << endl;
		cout << "1) Hesap olustur" << endl;
		cout << "2) Hesaba giris" << endl;
		cout << "3) Tum hesaplari goster" << endl;
		cout << "4) Cikis" << endl;
		cout << "**********************************" << endl;

		int secim;
		cin >> secim;

		switch (secim) {
		case 1:
			sistem.hesapOlustur();
			break;
		case 2:
			sistem.girisYap();
			break;
		case 3:
			sistem.tumHesaplariGoster();
			break;
		case 4:
			sistem.cikisYap();
			return 0;
		default:
			cout << "Gecersiz secim.Tekrar deneyin" << endl;
			break;
		}
	}
	
	return 0;
}