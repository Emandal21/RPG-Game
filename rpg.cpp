#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <cmath>

using namespace std;

void pocetak(){
    cout<<"Ucitavanje igre"<<endl; //Prva funkcija koja se poziva. Ispisuje se animacija loadinga
	Sleep(1000);
	for(int i=1; i<=15; i++){
        cout << ".";
        Sleep(300);
	}
	system("cls");
}
void Menu()
{
	cout<<"1. Igraj"<<endl;
	cout<<"2. Najbolji rezultati"<<endl;
	cout<<"3. Ugasi igricu"<<endl;
}

string convert(string& ime, int x){
    /* Neophodan dio funkcije rezultati, konvertuje preostali hp protivnika u string i vraca string sastavljen od imena
        igraca i njegovog hp-a */
    string rezultat="";
	string cifre="0123456789";
	int brojevi[10]={0,1,2,3,4,5,6,7,8,9};
	int i=0;
	while(x!=0){
        if(x%10==brojevi[i]){
            rezultat+=cifre[i];
            x/=10;
            i=0;
        }
        i++;
	}
	string rjesenje="";
	// Posto do ovog dijela dobijamo string broja u naopakom redoslijedu slijedeca petlja ga obrce
	for(int i=rezultat.length()-1; i>=0; i--){
        rjesenje+=rezultat[i];
	}
	ime = ime + " " + rjesenje;
    return ime;
}

void rezultati(string ime, int a)
{
    ifstream unos;
    ofstream ispis;

    int x; //Pohranimo ostatak hp-a u x
    x=a;

    string nesto = convert(ime, x); //Rezultat pozivanja funkcije convert pospremamo u varijablu nesto koja ce
    unos.open("score.txt");         // predstavljati eventualno novi highscore
    string niz[5];
    for(int i=0; i<5; i++){ // U niz ubacili trenutnih top 5
        getline(unos, niz[i]);
    }
    unos.close();

    string prvi=niz[0];
    if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]) > int(prvi[prvi.length()-1])+int(prvi[prvi.length()-2])){ //Provjeravamo da li je novi score novi high score
        // Ako je high score onda ga stavljamo na prvo mjesto a ostatak pomjeramo ka dole respektivno
        niz[4]=niz[3];
        niz[3]=niz[2];
        niz[2]=niz[1];
        niz[1]=niz[0];
        niz[0]=nesto;
    }
// Ako nije najbolji score onda provjeravamo da li je drugi najbolji score
    else if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) <= int(prvi[prvi.length()-1])+int(prvi[prvi.length()-2])*10){ // Poredim sa zadnja dva elementa stringa
           string drugi=niz[1];
           if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) > int(drugi[drugi.length()-1])+int(drugi[drugi.length()-2])*10){ // Analogna logika za ostatak cijeli
                // Ako je drugi najbolji score stavljamo ga na drugu poziciju a ostatak pomjeramo ka dole
                niz[4]=niz[3];
                niz[3]=niz[2];
                niz[2]=niz[1];
                niz[1]=nesto;
                }
                // Ako nije ni drugi najbolji score onda provjeravamo da li je treci najbolji score
           else if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) <= int(drugi[drugi.length()-1])+int(drugi[drugi.length()-2]*10)){
                    string treci=niz[2];
                    if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) > int(treci[treci.length()-1])+int(treci[treci.length()-2]*10)){
                        niz[4]=niz[3];
                        niz[3]=niz[2];
                        niz[2]=nesto;
                        }
                    // Ako je cetvrti najbolji rezultat, analogija prethodnim slucajevima
                    else if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) <= int(treci[treci.length()-1])+int(treci[treci.length()-2]*10)){
                            string cetvrti=niz[3];
                            if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) > int(cetvrti[cetvrti.length()-1])+int(cetvrti[cetvrti.length()-2]*10)){
                                niz[4]=niz[3];
                                niz[3]=nesto;
                                }
                            // Ako je peti najbolji rezultat
                            // U slucaju da trenutni score nije u top5 nije vrijedan spomena tako da ga necemo ni pohranjivati
                            else if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) <= int(cetvrti[cetvrti.length()-1])+int(cetvrti[cetvrti.length()-2]*10)){
                                    string peti=niz[4];
                                    if(int(nesto[nesto.length()-1])+int(nesto[nesto.length()-2]*10) > int(peti[peti.length()-1])+int(peti[peti.length()-2]*10)){
                                        niz[4]=nesto;
                                    }
                                }
                        }
                }
    }

    ispis.open("score.txt", ofstream::out | ofstream::trunc); // Ovim funkcijama brisemo sve podatke koji su dosad bili spaseni u fajlu
                                                              // Ideja je na to mjesto ubaciti nove podatke a stare smo vec pospremili u niz koji je naveden na pocetku funkcije
    for(int i=0; i<5; i++){
        ispis<<niz[i]<<endl; // U niz stavljam novih top 5
    }
    ispis.close();
}

void statistike(int igrac[],int protivnik1[],int protivnik2[],int protivnik3[])
{
	igrac[0]=60; //max HP
	igrac[1]=60; //trenutni HP
	igrac[2]=15; //napad
	igrac[3]=0; //specijalna moc 1
	igrac[4]=0; //specijalna moc 2
	igrac[5]=0; //specijalna moc 3
	igrac[6]=1; //trenutni nivo
	igrac[7]=0; //hp eliksir
	igrac[8]=0; //mana eliksir
	igrac[9]=0; //mana

	protivnik1[0]=45; //max HP
	protivnik1[1]=45; //trenutni HP
	protivnik1[2]=15; //napad

	protivnik2[0]=50; //max HP
	protivnik2[1]=50; //trenutni HP
	protivnik2[2]=20; //napad

	protivnik3[0]=55; //max HP
	protivnik3[1]=55; //trenutni HP
	protivnik3[2]=25; //napad
}

void zagonetka1(int igrac[])
{
	char odgovor;
	cout<<"Na pocetku ste igre. Ako je matematika vasa jaca strana,\nonda cete lahko savladati sve protivnike."<<endl;
	cout<<"Imate mogucnost da u startu budete u prednosti..."<<endl;
	system("PAUSE");
	system("cls");
	cout<<"Ukoliko tacno odgovorite na postavljenu zagonetku dobijate \nsurvival pack koji ce vam pomoci u pobjedjivanju protivnika."<<endl;
	cout<<"Zagonetka: Koliko krajeva ima sest i po stapova?"<<endl;
	cout<<"a) 6"<<endl;
	cout<<"b) 7"<<endl;
	cout<<"c) 14"<<endl;
	cout<<"d) 13"<<endl;
	cout<<endl;
	cout<<"Vas odgovor je: ";
	cin>>odgovor;
	while(odgovor!='a' and odgovor!='b' and odgovor!='c' and odgovor!='d' and odgovor!='A' and odgovor !='B' and odgovor!='C' and odgovor!='D')
	{
		cout<<"Pogresan unos, unesite ponovo: ";
		cin>>odgovor;
	}
	Sleep(1000);
	system("cls");
	if(odgovor=='c' or odgovor=='C')
	{
		cout<<"Poznajete osnove logike. Zasluzili ste survival pack:"<<endl;
		cout<<"Mana: 20"<<endl;
		cout<<"Mana eliksir: 1"<<endl;
		cout<<"HP eliksir: 1"<<endl;
		cout<<"Specijalna moc: Udarac Uscumlicem"<<endl;
		Sleep(5000);
		system("cls");
		igrac[3]++; //Dobijamo specijalan napad
		igrac[8]=1; //mana eliksir
		igrac[9]=20; //mana
		igrac[7]=1; //hp eliksir
	}
	else
	{
		cout<<"Ljasko Veliki: HA HA HA! Samo cudo ce vam pomoci da prezivite."<<endl;
		Sleep(3000);
		system("cls");
		igrac[8]=0;
		igrac[9]=0;
		igrac[7]=0;
	}
}

void zagonetka2(int igrac[])
{
	char odgovor;
	cout<<"Uspjesno ste savladali prostor realnih brojeva, ali to je tek pocetak"<<endl;
	cout<<"Pred vama je jos jedan matematicki problem..."<<endl;
	system("PAUSE");
	system("cls");
	cout<<"Ukoliko tacno odgovorite na postavljenu zagonetku dobijate survival pack \nkoji ce vam pomoci u pobjedjivanju ostalih protivnika."<<endl;
	cout<<"Zagonetka: Rjesenje jednacine x^2 - 2*x + 1 = 0 je: "<<endl;
	cout<<"a) 5"<<endl;
	cout<<"b) 1"<<endl;
	cout<<"c) 2"<<endl;
	cout<<"d) 1/2"<<endl;
	cout<<endl;
	cout<<"Vas odgovor je: ";
	cin>>odgovor;
	while(odgovor!='a' and odgovor!='b' and odgovor!='c' and odgovor!='d' and odgovor!='A' and odgovor !='B' and odgovor!='C' and odgovor!='D')
	{
		cout<<"Pogresan unos, unesite ponovo: ";
		cin>>odgovor;
	}
	Sleep(1000);
	system("cls");
	if(odgovor=='b' or odgovor=='B')
	{
		cout<<"Vi ocigledno valdate matematikom. Ljasko Veliki vam daruje survival pack:"<<endl;
		cout<<"Mana: 30"<<endl;
		cout<<"Mana eliksir: 2"<<endl;
		cout<<"HP eliksir: 2"<<endl;
		cout<<"Specijalna moc: Udarac Bermanom"<<endl;
		Sleep(5000);
		system("cls");
		igrac[4]++;//Otkljucavamo novi specijalni napad
		igrac[8]+=2;//mana eliksir
		igrac[9]+=30;//mana
		igrac[7]+=2;//hp eliksir
	}
	else
	{
		cout<<"Ljasko Veliki: Ne nadaj se previse. Bez survival packa sljedeci nivo nikad neces preci!"<<endl;
		Sleep(3000);
		system("cls");
	}
}

void zagonetka3(int igrac[])
{
	char odgovor;
	cout<<"Ni prostor R na 2 nije predstavljao problem za vas."<<endl;
	cout<<"Sljedeci na redu je R na 3, ali prije toga zadatak..."<<endl;
	system("PAUSE");
	system("cls");
	cout<<"Ukoliko tacno odgovorite na postavljenu zagonetku dobijate survival pack \nkoji ce vam pomoci u pobjedjivanju ostalih protivnika."<<endl;
	cout<<"Zagonetka: Povrsina kruga sa centrom u koordinatnom pocetku, poluprecnika 2 cm je:"<<endl;
	cout<<"a) 2*pi"<<endl;
	cout<<"b) (2*pi)^2"<<endl;
	cout<<"c) pi"<<endl;
	cout<<"d) 4*pi"<<endl;
	cout<<endl;
	cout<<"Vas odgovor je: ";
	cin>>odgovor;
	while(odgovor!='a' and odgovor!='b' and odgovor!='c' and odgovor!='d' and odgovor!='A' and odgovor !='B' and odgovor!='C' and odgovor!='D')
	{
		cout<<"Pogresan unos, unesite ponovo: ";
		cin>>odgovor;
	}
	Sleep(1000);
	system("cls");
	if(odgovor=='d' or odgovor=='D')
	{
		cout<<"Survival pack je vas:"<<endl;
		cout<<"Mana: 40"<<endl;
		cout<<"Mana eliksir: 3"<<endl;
		cout<<"HP eliksir: 3"<<endl;
		cout<<"Specijalna moc: Udarac Veneom"<<endl;
		Sleep(5000);
		system("cls");
		igrac[5]++;//najjaci specijalan napad
		igrac[8]+=3;//mana eliksir
		igrac[9]+=40;//mana
		igrac[7]+=3;//hp eliksir
	}
	else
	{
		cout<<"Ljasko Veliki: Mozda ste savladali prostor R na 2, ali to vam ne garantuje zivot!"<<endl;
		Sleep(3000);
		system("cls");
	}
}

void status(int igrac[], int protivnik[], string ime){
    //Funkcija koja je u stalnoj komunikaciji s najosnovnijom funkcijom "borba", ispisuje trenutno stanje u borbi
    string ime_protivnika;
    if (protivnik[0] == 45) ime_protivnika = "Protivnik 1";
    else if (protivnik[0] == 50) ime_protivnika = "Protivnik 2";
    else if (protivnik[0] == 55) ime_protivnika = "Protivnik 3";
    cout << ime << "\t\t\t\t\t\t" << ime_protivnika<<endl;
    cout << endl << "Health: " << igrac[1] << "/" << igrac[0] << "\tMana: " << igrac[9] << "\t\t\t" << "Health: " << protivnik[1] << "/" << protivnik[0];
}

int critical(int napad){
    //U slucaju da se u uzme 1 iz niza igrac dobija jaci napad povecan za 40%
    int sansa[10]={1,0,0,0,1,0,0,0,1,0};
    srand(time(0));
    int critical=rand()%10;

    int unos=napad;
    if(sansa[critical]==1){
        cout << "Critical hit!\n";
        Sleep(100);
        return floor(unos*1.40);
    }
    else{
        return unos;
    }
}

void opcije(){
	cout<<"1. Napad"<<endl;
	cout<<"2. Specijalni napad"<<endl;
	cout<<"3. Inventory"<<endl;
}

void borba(int igrac[], int protivnik[],int& napad, int& hp1, int& hp2, string ime){
    while(hp1>0 and hp2>0)
	{
    	status(igrac, protivnik, ime);
    	cout<<endl;
        opcije();
		Sleep(300);

        int izbor;
        cin >> izbor;
		Sleep(300);
        while(izbor!=1 && izbor!=2 && izbor!=3)
		{
            cout << "Greska unosa, probajte ponovo: \n";
            cin >> izbor;
			Sleep(300);
        }

        if(izbor==1)
		{
            int damage=critical(napad);
            cout << "Napravili ste " << damage << " stete!\n";
            Sleep(500);
            hp2-=damage;
            if(hp2<=0)
			{
                break;
            }
        }
        else if (izbor==3)
        {
            if(igrac[8]==0 and igrac[7]==0)
            {
                cout<<"Ne posjedujete nijedan eliksir."<<endl;
                Sleep(1000);
                system("cls");
                borba(igrac, protivnik, napad, igrac[1], protivnik[1], ime);
            }
            int x;
            if (igrac[7] >0)
            {
                cout<<"1. HP eliksir: "<<igrac[7]<<endl;
            }
            if(igrac[8]>0)
            {
                cout<<"2. Mana eliksir: "<<igrac[8]<<endl;
            }
            cout<<"Biram: ";
            cin>>x;
            while(x!=1 and x!=2)
            {
                cout<<"Greska, unesi ponovo: ";
                cin>>x;
            }
            if(x==1)
            {
                if(igrac[1]<=45) igrac[1]+=15;
                else igrac[1]=60;
                igrac[7]-=1;
            }
            else if(x==2)
            {
                igrac[9]+=20;
                igrac[8]-=1;
        	}
        }
        else if(izbor==2)
        {
            if(igrac[3]!=1 and igrac[4]!=1 and igrac[5]!=1)
            {
                cout<<"Nemate supermoci."<<endl;
                Sleep(1000);
                system("cls");
                borba(igrac, protivnik, napad, igrac[1], protivnik[1], ime);
            }
            int x;
            if(igrac[3]==1) cout<<"1. Pozovi Uscumlica"<<endl;
            if(igrac[4]==1) cout<<"2. Pozovi Bermana"<<endl;
            if(igrac[5]==1) cout<<"3. Pozovi Venea"<<endl;
            cout<<"Biram: ";
            cin>>x;
            while(x!=1 and x!=2 and x!=3)
            {
                cout<<"Pogresan unos, unesi ponovo: ";
                cin>>x;
            }

            if(x==1)
            {
            	if(igrac[9]>=20)
            	{
                	cout<<"Uscumlic zadaje strasan udarac."<<endl;
                	cout<<"Napravili ste 20 stete."<<endl;
                	protivnik[1]-=20;
                	igrac[9]-=20;
                	Sleep(1000);
                }
                else cout<<"Nemate dovoljno mane za odabrani napad."<<endl;
            }
            else if(x==2)
            {
            	if(igrac[9]>=25)
            	{
                	cout<<"Berman je ucinio svoje."<<endl;
                	cout<<"Napravili ste 25 stete."<<endl;
                	protivnik[1]-=25;
                	igrac[9]-=25;
                	Sleep(1000);
                }
                else cout<<"Nemate dovoljno mane za odabrani napad."<<endl;

            }
            else if(x==3)
            {
            	if(igrac[9]>=30)
            	{
                	cout<<"Protiv Venea niko nema sanse."<<endl;
                	cout<<"Napravili ste 30 stete."<<endl;
                	protivnik[1]-=30;
                	igrac[9]-=30;
                	Sleep(1000);
                }
                else cout<<"Nemate dovoljno mane za odabrani napad."<<endl;
            }
        }
        if(hp2<=0) cout<<"Predjen level."<<endl;
        else
		{
        	cout << "\nProtivnikov potez! Protivnik napada: \n";
			Sleep(1000);
        	int damage=critical(rand()%20+1);
        	cout << "\nGubite " << damage << " stete!"<<endl;
        	Sleep(500);
        	hp1-=damage;
        	if(hp1<=0)
			{
				system("cls");
        	    break;
        	}
        	Sleep(2000);
        	cout << "\n\nSlijedeci potez.";
        	Sleep(500);
        	system("cls");
        }
    }
    if(hp1 > 0)
	{
    	if(igrac[1]<=50) igrac[1]+=10;
        else igrac[1]=60;
    	cout<<"Preden level"<<endl;
    	Sleep(1000);
    	system("cls");
	}
	else
	{
		cout<<"Vi ne zasluzujete zivjeti na ovoj planeti..."<<endl;
		Sleep(1500);
		system("cls");
		cout<<"Kraj igre!"<<endl;
		exit(1);
	}
}
void prica()
{
	cout<<"Na vlast je dosao novi diktator, Ljasko Veliki, koji smatra da je \nZemlja planeta samo za matematicare. \nSvi oni koji ne poznaju osnove matematike ne zasluzuju zivjeti."<<endl;
	cout<<"Da bi prezivio moras savladati tri velika polja: prostor R, R na 2 i R na 3."<<endl;
	cout<<"Prvi na redu je prostor relanih brojeva. Zapamti, Ljasko je nemilosrdan. Sretno!"<<endl;
	system("PAUSE");
	system("cls");
}

int main()
{
	string ime;
	int izbor;
	int igrac[9], protivnik1[3], protivnik2[3], protivnik3[3];
	pocetak();
	cout<<"Unesite vase ime: ";
	cin>>ime;
	Sleep(2000);
	system("cls");
	Menu();
	cout<<endl;
	cin>>izbor;
	while(izbor!=1 and izbor!=2 and izbor!=3)
	{
		cout<<"Pogresan unos. Unesite ponovo: ";
		cin>>izbor;
	}
	system("cls");
	if(izbor==1)
	{
		prica();
		statistike(igrac, protivnik1, protivnik2, protivnik3);
		zagonetka1(igrac);
		borba(igrac, protivnik1, igrac[2], igrac[1], protivnik1[1], ime);
		zagonetka2(igrac);
		borba(igrac, protivnik2, igrac[2], igrac[1], protivnik2[1], ime);
		zagonetka3(igrac);
		borba(igrac, protivnik3, igrac[2], igrac[1], protivnik3[1], ime);
		cout<<"Cestitamo. Zasluzujete zivjeti na planeti Zemlji."<<endl;
		Sleep(2000);
		system("cls");
		ifstream unos;
        unos.open("score.txt");
        string nesto="";
        cout << "Najbolji rezultati:"<<endl<<endl;
        rezultati(ime, igrac[1]);
        while(!unos.eof()){ // Dokle god nismo naisli na kraj fajla
            getline(unos,nesto,'\n'); // Ispis high score-a
            cout << nesto <<endl;
        }
        unos.close();
		cout<<"Zelite li opet igrati? \n1. Da \n2. Ne"<<endl;
		int a;
		cin>>a;
		while(a!=1 and a!=2)
		{
			cout<<"Pograsn unos, unesite ponovo: ";
			cin>>a;
		}
		if(a==1) main();
		else exit(1);
	}
	else if(izbor==2) {
        ifstream unos;
        unos.open("score.txt");
        string nesto="";
        cout << "Najbolji rezultati:"<<endl<<endl;
        while(!unos.eof()){ // Dokle god nismo naisli na kraj fajla
            getline(unos,nesto,'\n'); // Ispis high score-a
            cout << nesto <<endl;
        }
        unos.close();
	}
	else if(izbor==3) exit(1);

	return 0;

}
