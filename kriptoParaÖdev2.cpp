/*************************************************************************************
**							    SAKARYA ÜNÝVERSÝTESÝ
**                      BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**                           BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**							   PROGRAMLAMAYA GÝRÝÞ DERSÝ
**
**                      ÖDEV NUMARASI    : 2
**		                ÖÐRENCÝ ADI      : HAKAN EFE TÜYSÜZ
**                      ÖÐRENCÝ NUMARASI : B231210098
**                      DERS GURUBU      : B GURUBU
***************************************************************************************/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>

using namespace std;

struct KriptoPara {        // Bu kýsýmlarda bazý yapý veri türleri tanýmlýyoruz
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

	Hesap():kriptoMiktari(0),gunSayaci(0),ozelHesap(false){}  // Burada yapýcý fonksiyon ile baþlangýç deðerlerini atýyoruz
};

class HesapSistemi {   // Burada sýnýfýmýzý tanýmlayýp içine uygun verileri ve metotlarý yazýyoruz
private:
	static const int MaxHesapAdedi = 100;
	Hesap hesaplar[MaxHesapAdedi];
	int hesapAdedi = 0;

public:
	void hesapOlustur() {     // Bu kýsýmda açýlacak hesabýn türü, þifresi ve ID si belirleniyor
		if (hesapAdedi >= MaxHesapAdedi) {
			cout << "Maksimum hesap sayisina ulasildi!" << endl;
			return;
		}

		Hesap yeniHesap;
		yeniHesap.ID = idUret();

		cout << "Yeni sifre olusturun:";
		cin >> yeniHesap.sifre;
		while (true) {        // Hesap türü için seçim yaptýrýlýyor
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
	void girisYap() {                   // Burada hesabýn ID ve þifre bilgileri doðrulanýyor
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
	void cikisYap() {     // Uygulamadan tamamen çýkýlmaya yarýyor
		cout << "Cikis yapildi." << endl;
	}
	
	void tumHesaplariGoster() {    // Burada açýlan tüm hesaplarýn ID ve para miktarlarý gösteriliyor
		cout << "Tum hesaplar:" << endl;
		for (int i = 0; i < hesapAdedi; ++i) {
			cout << "Hesap ID:" << hesaplar[i].ID << endl;
			cout << "Toplam Kripto Para Sayisi:" << hesaplar[i].kriptoMiktari << endl;
			cout << "Toplam TL:" << hesaplar[i].kriptoPara.deger * hesaplar[i].kriptoMiktari << "TL"<<endl;
			cout << "--------------------------------"<<endl;
		}
	}
private:
	void menuGoster(int kullaniciIndeks) {   // Bu kýsýmda kiþi hesap açýp kullanýcý indeksi -1 den farklý olunca buradaki menüye yönlendiriliyor
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
			cin >> secim;       // Burada kullanýcý açtýðý hesap için yapacaðý iþlemi seçiyor
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

	void kriptoParaAl(int kullaniciIndeks) {    // Burada kullanýcý alacaðý kripto para için vereceði TL miktarýný giriyor
		cout << "Guncel kripto para degeri:" << hesaplar[kullaniciIndeks].kriptoPara.deger << "TL" << endl;
		double alinacakMiktar;
		cout << "Alinacak kripto para icin verilecek TL miktarini giriniz:";
		cin >> alinacakMiktar;
		hesaplar[kullaniciIndeks].kriptoMiktari +=alinacakMiktar/ hesaplar[kullaniciIndeks].kriptoPara.deger;
		cout << "Kripto para alindi." << endl;
	}

	void kriptoParaSat(int kullaniciIndeks)    // Burada kullanýcý hesabýndaki TL miktarýna göre istediði kadar TL'yi çekebiliyor
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
void bakiyeGoster(int kullaniciIndeks) {   // Burada kullanýcý hesabýndaki kripto para ve TL miktarýný görebiliyor
	cout << "Hesapta " << hesaplar[kullaniciIndeks].kriptoMiktari << " adet kripto para bulunmaktadir" << endl;
	double kriptoDegeri = hesaplar[kullaniciIndeks].kriptoPara.deger;
	double bakiyeTL = hesaplar[kullaniciIndeks].kriptoMiktari * kriptoDegeri;
	cout << "Toplam TL degeri:" << bakiyeTL << "TL" << endl;
}

void gunArttir(int kullaniciIndeks) {   // Bu kýsýmda seçilen hesap türüne göre kripto para kuru günlük olarak (Gün arttýr tuþuna basarak) deðiþiyor
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
			int gun2 = rand() % 30 +1;    //Burada gun sayacýnýn her 30 günlük periyotta rastgele günleri önceki periyottan farklý seçtirmeye çalýþtým
			int gun3 = rand() % 30 +1;
		}
		
		int gun1 = rand() % 30 +1;
		int gun2 = rand() % 30 +1;
		int gun3 = rand() % 30 +1;
		
		// Burada rastgele seçilen günlerin gün sayacýna göre tutup tutmadýðý belirleniyor
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
	string idUret() {   // Bu kýsýmda rastgele ID belirleniyor
		srand(time(0));
		string id;
		for (int i = 0; i < 6; ++i) {
			int b = rand() % 10;
			id += to_string(b);
		}
		return id;
	}
	
};

int main() {   // Burada ise son olarak programýn ana fonksiyonunu yazýyoruz 
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