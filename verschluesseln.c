#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "myfunctions.c"
	#define KGRA  "\x1b[90m"
	#define KRED  "\x1B[31m"
	#define KNRM  "\x1B[0m"
	#define KGRN  "\x1B[32m"
	#define KYEL  "\x1B[33m"
	#define KBLU  "\x1B[33m" //in Gelb geändert
	#define KMAG  "\x1B[35m"
	#define KCYN  "\x1B[36m"
	#define KWHT  "\x1B[37m"
	#define ANZ 64
void RahmenZeichnen(int,int,int,int,int);
//int DateiVerschluesseln(int,int,int,int);
int DateiVerschluesseln(char*,char*,char*);
int DateiEntschluesseln(char*,char*,char*);
char* PhraseGenerieren(int);

int main(void)
{
	srand(time(NULL));
	char *RandPhrase,Eingabe,Auswahl,*PhrasePtr,*QuelldateiPtr,*ZieldateiPtr,status=4;
	int i,z;
	RandPhrase=PhraseGenerieren(8);
	char Phrase[255];
	for(i=0;i<8;i++) Phrase[i]=RandPhrase[i];Phrase[i]='\0';PhrasePtr=&Phrase[0];
	char Quelldatei[255]={ "c:/it9source/test.txt" };
	char Zieldatei[255]={ "c:/it9source/test-verschluesselt.txt" };
	char QuelldateiOrdner[255]={ "c:/it9source/" };
	char QuelldateiDatei[255]={ "test.txt" };
	char ZieldateiOrdner[255]={ "c:/it9source/" };
	char ZieldateiDatei[255]={ "test-verschluesselt.txt" };
	do
	{
	//Menü zeichnen
	//Header
	system("cls");
	RahmenZeichnen(2,2,90,22,6);
	gotoxy(3,3);
	printf("%s\tDateien Ver- & Entschluesseln\n\n",KMAG);
	//Hauptmenü
	printf("%s\tq - Quelldatei waehlen",KBLU);
	printf("%s\n\tAktuell : %s",KGRA,Quelldatei);
	printf("%s\n\tz - Zieldatei waehlen",KBLU);
	printf("%s\n\tAktuell : %s",KGRA,Zieldatei);
	printf("%s\n\tp - Verschluesselungsphrase waehlen",KBLU);
	printf("%s\n\tg - Verschluesselungsphrase generieren",KBLU);
	printf("%s\n\tAktuell : %s",KGRA,Phrase);
	printf("%s\n\n\n\tv - Verschluesselung starten",KBLU);
	printf("%s\n\te - Entschluesselung starten",KBLU);
	printf("%s\n\n\tx - Programm beenden\n",KBLU);
		switch(status)
	{
		case 0:printf("\n\t%s[Aktion Erfolgreich]",KGRN);sleep(2);for(i=0;i<20;i++){putch(8);putch(' ');putch(8);}break;
		case 1:printf("\n\t%s[Fehler] Quelldatei konnte nicht geoeffnet werden",KRED);sleep(3);for(i=0;i<49;i++){putch(8);putch(' ');putch(8);};break;
		case 2:printf("\n\t%s[Fehler] Zieldatei konnte nicht geschrieben werden",KRED);sleep(3);for(i=0;i<51;i++){putch(8);putch(' ');putch(8);};break;
		case 3:printf("\n\t%s[Fehler] Quell- & Zieldatei konnten nicht geoeffnet werden",KRED);sleep(3);for(i=0;i<59;i++){putch(8);putch(' ');putch(8);};break;
	}
	printf("%s\n\n\tIhre Auswahl :",KGRA);
	Eingabe=getch();
	printf("%c",Eingabe);
	
	if(Eingabe=='g') //Neue Passphrase generieren
	{
	//Menü zeichnen
	//Header
	int anzahl;
	for(i=0;Phrase[i]!='\0';i++) Phrase[i]='\0';
	do 
	{
		system("cls");
		RahmenZeichnen(2,2,90,22,6);
		gotoxy(3,3);
		printf("%s\tDateien Ver- & Entschluesseln\n\n",KMAG);
		printf("%s\n\n\tAnzahl Zeichen waehlen (8-64) :%s",KBLU,KGRA);
		anzahl=eingabeZahl(2);
	}while(anzahl<8 || anzahl>64);
	RandPhrase=PhraseGenerieren(anzahl);
	for(i=0;i<anzahl;i++) Phrase[i]=RandPhrase[i];
	PhrasePtr=&Phrase[0];
	}
	
	if(Eingabe=='p') //Eigene Passphrase waehlen
	{
	//Menü zeichnen
	//Header
	for(i=0;Phrase[i]!='\0';i++) Phrase[i]='\0';
	system("cls");
	RahmenZeichnen(2,2,90,22,6);
	gotoxy(3,3);
	printf("%s\tDateien Ver- & Entschluesseln\n\n",KMAG);
	printf("%s\n\n\tZeichenkette eingeben (max. 255) :%s",KBLU,KGRA);
	PhrasePtr=eingabeText(255);
	for(i=0;PhrasePtr[i]!='\0';i++) Phrase[i]=PhrasePtr[i];
	PhrasePtr=&Phrase[0];
	}
	
	if(Eingabe=='q') //Quelldatei waehlen
	{
	do
	{
	//Menü zeichnen
	//Header
	system("cls");
	for(i=0;Quelldatei[i]!='\0';i++) Quelldatei[i]='\0';
	RahmenZeichnen(2,2,90,22,6);
	gotoxy(3,3);
	printf("%s\tDateien Ver- & Entschluesseln\n\n",KMAG);
	printf("%s\n\n\n\t[1] Ordner aendern (Aktuell : %s)",KGRA,QuelldateiOrdner);
	printf("%s\n\t[2] Datei aendern (Aktuell : %s)",KGRA,QuelldateiDatei);
	printf("%s\n\t[z] Zurueck",KGRA);
	if(i>255) printf("%s\n\n\t[VORSICHT]%s Pfad zu lang - er wurde nicht vollstaendig gespeichert",KRED,KGRA);
	Auswahl=getch();
	if(Auswahl==49)
	{
		printf("%s\n\n\tOrdnerpfad zur Quelldatei eingeben (max. 255) :%s",KBLU,KGRA);
		for(i=0;QuelldateiOrdner[i]!='\0';i++) QuelldateiOrdner[i]='\0';
		PhrasePtr=eingabeText(255);
		for(i=0;PhrasePtr[i]!='\0';i++) {QuelldateiOrdner[i]=PhrasePtr[i];};
	}
	if(Auswahl==50)
	{
		printf("%s\n\n\tDateiname der Quelldatei eingeben (max. 255) :%s",KBLU,KGRA);
		for(i=0;QuelldateiDatei[i]!='\0';i++) QuelldateiDatei[i]='\0';
		PhrasePtr=eingabeText(255);
		for(i=0;PhrasePtr[i]!='\0';i++) {QuelldateiDatei[i]=PhrasePtr[i];}
	}
//Arrays zusammenlegen	
	char zweiterTeil;
	for(i=0,zweiterTeil=0,z=0;QuelldateiDatei[z]!='\0';i++)
	{
		if(QuelldateiOrdner[i]!='\0')
		{
			Quelldatei[i]=QuelldateiOrdner[i];
		} else (zweiterTeil=1);
		if(zweiterTeil)
		{ 
			Quelldatei[i]=QuelldateiDatei[z];
			z++;
		}
	}
	} while(Auswahl!='z');
	}
	
	if(Eingabe=='z') //Zieldatei waehlen
	{
	do
	{
	//Menü zeichnen
	//Header
	system("cls");
	for(i=0;Zieldatei[i]!='\0';i++) Zieldatei[i]='\0';
	RahmenZeichnen(2,2,90,22,6);
	gotoxy(3,3);
	printf("%s\tDateien Ver- & Entschluesseln\n\n",KMAG);
	printf("%s\n\n\n\t[1] Ordner aendern (Aktuell : %s)",KGRA,ZieldateiOrdner);
	printf("%s\n\t[2] Datei aendern (Aktuell : %s)",KGRA,ZieldateiDatei);
	printf("%s\n\t[z] Zurueck",KGRA);
	if(i>255) printf("%s\n\n\t[VORSICHT]%s Pfad zu lang - er wurde nicht vollstaendig gespeichert",KRED,KGRA);
	Auswahl=getch();
	if(Auswahl==49)
	{
		printf("%s\n\n\tOrdnerpfad zur Zieldatei eingeben (max. 255) :%s",KBLU,KGRA);
		for(i=0;ZieldateiOrdner[i]!='\0';i++) ZieldateiOrdner[i]='\0';
		PhrasePtr=eingabeText(255);
		for(i=0;PhrasePtr[i]!='\0';i++) {ZieldateiOrdner[i]=PhrasePtr[i];};
	}
	if(Auswahl==50)
	{
		printf("%s\n\n\tDateiname der Zieldatei eingeben (max. 255) :%s",KBLU,KGRA);
		for(i=0;ZieldateiDatei[i]!='\0';i++) ZieldateiDatei[i]='\0';
		PhrasePtr=eingabeText(255);
		for(i=0;PhrasePtr[i]!='\0';i++) {ZieldateiDatei[i]=PhrasePtr[i];}
	}
//Arrays zusammenlegen	
	char zweiterTeil;
	for(i=0,zweiterTeil=0,z=0;ZieldateiDatei[z]!='\0';i++)
	{
		if(ZieldateiOrdner[i]!='\0')
		{
			Zieldatei[i]=ZieldateiOrdner[i];
		} else (zweiterTeil=1);
		if(zweiterTeil)
		{ 
			Zieldatei[i]=ZieldateiDatei[z];
			z++;
		}
	}
	} while(Auswahl!='z');
	}
	
	if(Eingabe=='v') //Datei verschluesseln
	{	
	QuelldateiPtr=&Quelldatei[0];
	ZieldateiPtr=&Zieldatei[0];
	PhrasePtr=&Phrase[0];
	status=DateiVerschluesseln(QuelldateiPtr,ZieldateiPtr,PhrasePtr);
	}
	if(Eingabe=='e') //Datei verschluesseln
	{	
	QuelldateiPtr=&Quelldatei[0];
	ZieldateiPtr=&Zieldatei[0];
	PhrasePtr=&Phrase[0];
	status=DateiEntschluesseln(QuelldateiPtr,ZieldateiPtr,PhrasePtr);
	}
	
	}while(Eingabe!='x');

	gotoxy(2,22);
	return 0;
}

char* PhraseGenerieren(int anzahl)
{
	int i,tmp;
	char* ptr;
	static char Phrase[ANZ];
	if (anzahl>ANZ) anzahl=64;
	for (i=0;i<anzahl;i++)
	{
		tmp=rand() % 26 +65;
		Phrase[i]=tmp;
	}
	Phrase[i]='\0';
	ptr=&Phrase[0];
	return ptr;
}

int DateiVerschluesseln(char *QuelldateiPtr,char *ZieldateiPtr,char *PhrasePtr)
{
	FILE *Quelle,*Ziel;
	int temp=0,anz=0;
	char i=0,code=0;
	for(i=0;PhrasePtr[i]!='\0';i++) anz++;
	if((Quelle=fopen(QuelldateiPtr,"r"))==NULL)
	{
		code=1;
	}
	if((Ziel=fopen(ZieldateiPtr,"w"))==NULL)
	{
		if(code==1) code=3; else	code=2;
	}
	if(code==0)
	{		
		i=0;
		while((temp=fgetc(Quelle))!=EOF)
		{
		temp=temp+PhrasePtr[i];
		fputc(temp,Ziel);
		if(i>=anz-1)i=0;else i++;	
		}
		fclose(Quelle);
		fclose(Ziel);
		code=0;	
	}
	return code;
}

int DateiEntschluesseln(char *QuelldateiPtr,char *ZieldateiPtr,char *PhrasePtr)
{
	FILE *Quelle,*Ziel;
	int temp=0,anz=0;
	char i=0,code=0;
	for(i=0;PhrasePtr[i]!='\0';i++) anz++;
	if((Quelle=fopen(QuelldateiPtr,"r"))==NULL)
	{
		code=1;
	}
	if((Ziel=fopen(ZieldateiPtr,"w"))==NULL)
	{
		if(code==1) code=3; else	code=2;
	}
	if(code==0)
	{		
		i=0;
		while((temp=fgetc(Quelle))!=EOF)
		{
		temp=temp-PhrasePtr[i];
		fputc(temp,Ziel);
		if(i>=anz-1)i=0;else i++;	
		}
		fclose(Quelle);
		fclose(Ziel);
		code=0;	
	}
	return code;
}





