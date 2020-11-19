#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
using namespace std;

typedef struct Bloc // structure du bloc
{
	char *cBloc = new char;
	struct Bloc *bSuivant;
}Bloc;

typedef struct ListIp  // structure du list
{
	Bloc* bTete;
	Bloc* bQueue;
}ListIp;

Bloc* creerBloc(char cBloc[]) // creer un bloc
{
	// creer un bloc est initialiser le a partir d'un tableau de char passer en parametre

	Bloc* b = new Bloc;
	for (int i = 0; i < 4; i++) b->cBloc[i] = cBloc[i];
	b->bSuivant = NULL;

	return b;
}

ListIp* creerListIp() // creation de listIp vide
{
	// inialiser la list
	ListIp* l = new ListIp;
	l->bTete = NULL;
	l->bQueue = NULL;
	return l;
}

bool listIpVide(ListIp* l)
{
	return (l->bTete == NULL);
}

/************************************************************************************************/
																							/****/
int longListIp(ListIp* l)																	/****/
{																							/****/
	Bloc* b = l->bTete;																		/****/
	int lng = 0;																			/****/
																							/****/
	while (b != NULL)																		/****/
	{																						/****/
		lng++;																				/****/
		b = b->bSuivant;																	/****/
	}																						/****/
																							/****/
	return lng;																				/****/
}																							/****/
																							/****/
bool supprTete(ListIp* l)																	/****/
{																							/****/
	if (listIpVide(l)) return true;															/****/
																							/****/
	Bloc* b = l->bTete->bSuivant;															/****/
	free(l->bTete);																			/****/
	l->bTete = b;																			/****/
																							/****/
	return true;																			/****/
}																							/****/
																							/****/
bool supprBloc(ListIp* l, int position)														/****/
{																							/****/
	if (position < 1 || position > longListIp(l)) return false;								/****/
																							/****/
	if (position == 1) supprTete(l);														/****/
	else																					/****/
	{																						/****/
		Bloc* b = l->bTete;																	/****/
		Bloc* t;																			/****/
		int p = 1;																			/****/
																							/****/
		while (p < position)																/****/
		{																					/****/
			if (p == position - 1)															/****/
			{																				/****/
				t = b->bSuivant;															/****/
				if (t->bSuivant == NULL)													/****/
				{																			/****/
					l->bQueue = b;															/****/
					b->bSuivant = NULL;														/****/
				}																			/****/
				else b->bSuivant = t->bSuivant;												/****/
				free(t);																	/****/
			}																				/****/
			p++;																			/****/
			b = b->bSuivant;																/****/
		}																					/****/
	}																						/****/
	return true;																			/****/
}																							/****/
																							/****/
bool inserTeteIp(ListIp* l ,char cBloc[])													/****/
{																							/****/
	Bloc* b = creerBloc(cBloc);																/****/
	Bloc* t;																				/****/
																							/****/
	if (b == NULL) return false;															/****/
																							/****/
	t = l->bTete;																			/****/
	l->bTete = b;																			/****/
	l->bTete->bSuivant = t;																	/****/
																							/****/
	if (longListIp(l) == 1) l->bQueue = l->bTete;											/****/
																							/****/
	return true;																			/****/
}																							/****/
																							/****/
bool inserQueueIp(ListIp* l, char cBloc[])													/****/
{																							/****/
	if (listIpVide(l))																		/****/
	{																						/****/
		l->bTete = creerBloc(cBloc);														/****/
		l->bQueue = l->bTete;																/****/
	}																						/****/
	else																					/****/
	{																						/****/
		Bloc* b = creerBloc(cBloc);															/****/
		Bloc* t;																			/****/
		if (b == NULL) return false; // evoid error											/****/
																							/****/
		t = l->bQueue;																		/****/
		t->bSuivant = b;																	/****/
		l->bQueue = b;																		/****/
	}																						/****/
	return true;																			/****/
}																							/****/
																							/****/
bool inserBlocIp(ListIp* l , char cBloc[], int position)									/****/
{																							/****/
																							/****/
	if (position < 1 || position > longListIp(l) + 1) return false;							/****/
																							/****/
	if (position == 1) inserTeteIp(l,cBloc);												/****/
	else if (position == longListIp(l) + 1) inserQueueIp(l,cBloc);							/****/
	else																					/****/
	{																						/****/
		Bloc* b = creerBloc(cBloc);															/****/
		Bloc* t = l->bTete;																	/****/
																							/****/
		if (b == NULL) return false; // evoid error											/****/
																							/****/
		int p = 1;																			/****/
		while (p != position)																/****/
		{																					/****/
			p++;																			/****/
			if (p == position)																/****/
			{																				/****/
				b->bSuivant = t->bSuivant;													/****/
				t->bSuivant = b;															/****/
			}																				/****/
			t = t->bSuivant;																/****/
		}																					/****/
																							/****/
	}																						/****/
	return true;																			/****/
}																							/****/
																							/****/
/************************************************************************************************/

void affListIp(ListIp* l) // affichage de listIp
{
	//cette fonction est pour afficher la listIp
	cout /*<< "Affichage de list ip"*/ << endl;
	if(l->bTete==NULL) cout<<"La list est vide"<<endl;
	else
	{
	   	Bloc* b = l->bTete;  // le var b pour parcourer la listIp
	   	while (b->bSuivant != NULL)
		{
			cout <<"["<< b->cBloc<<"] --> ";  // affichage de chaque bloc + ':'
			b = b->bSuivant;
		}
  	cout<<"["<<b->cBloc<<"]";       // afficher le dernier bloc (Queue) sans ':'
	}
	cout<<endl;
}

bool EstValideIPv6Ch(string ip) // verification d'une string ip valide ou non (Question 1)
{
	if (ip.length() != 39) return false;//39 = 8(blocs) * 4(hexa caracteres) + 7(':')
	
	int t=0; 

	while (t < 36)
	{
		int i=t;  // le var t design le debut de chaque bloc
		for (; i < t + 4;) // cette boucle pour verifier si chaque caractere de bloc(qui commence par t) 
		{
			if (!((ip[i] >= 48 && ip[i] <= 57) || (tolower(ip[i]) >= 'a' && tolower(ip[i]) <= 'f'))) return false;
			// 48(ASCI) : 0 dic|57(ASCI) : 9 dic
			i++;
		}
		if ((ip[i] != ':') && (t < 35))    return false;
		t += 5;  // deplacer au bloc suivant
	}

	return true;
}

ListIp* creerIpv6(string ip) // creation de listIp (Question 2)
{
	ListIp* l = creerListIp();
	
	if(!EstValideIPv6Ch(ip))
	{
		cout<<"le ip n'est pas valide"<<endl;
		return l;
	}
	
	char c[4];   // c pour stocker chaque bloc d'apres le string ip passer en parametre
	for (int i = 0; i < 4; i++)
	{
		c[i] = ip[i];  // le premier bloc (tete ce la list)
	}
	l->bTete = creerBloc(c); // initialisation du tete
	Bloc* b = l->bTete;      // b pour parcourer la list
	int t = 5;           // le var t design le debut de chaque bloc
	for (int i = 1; i < 8; i++)
	{
		int k = t;
		for (; k < t + 4; k++) c[k-t] = ip[k]; //on stock le bloc suivant( d'apres le string ip) dans le tab  c
			
			b->bSuivant = creerBloc(c);        //on remplit le bloc suivant
			
			if(i == 7) l->bQueue = b->bSuivant; // la derniere instruction pour determiner le queue
			
			else b = b->bSuivant;
			
			t += 5; // deplacer au bloc suivant
	}
	return l;
}

bool EstValideIPv6(ListIp *l) // verification d'une list ip (Question 3)
{
	if(listIpVide(l))
	{
		cout<<"La list est vide"<<endl;
		return 0;
	}
	
	Bloc *b=l->bTete;
	string ip = b->cBloc;
	ip+=":";
	for(int i=0;i<6;i++)
	{
		b = b->bSuivant;
		ip+= b->cBloc;
		ip+=":";
	}
	ip+=b->bSuivant->cBloc;
	
	return EstValideIPv6Ch(ip);
}

bool simplifierIPv6(ListIp* l)
{
	if (!EstValideIPv6(l)) return 0;

	Bloc* b = l->bTete;    //b pour parcourer la list
	
	for(int z=0;z<8;z++)  // 8 blocs 
	{ 
		int i = -1;		// i designe le nombre de premiers zero dans chaque bloc
		char c;		
		do {            // compter le nombre de premiers zero
			i++;
			if(i!=4) c = b->cBloc[i];
		}while (c == '0' && i < 4);

		if (i == 4)     // si le bloc contien seul des zeros
		{
			free(b->cBloc);   // 
			b->cBloc = (char*)"0";
		}
		else
		{ 	
			int k = i;
			char* newBloc = new char;
			for (int j = 0; j < 4 - i; j++)
			{
				newBloc[j] = b->cBloc[k];
				k++;
			}
			free(b->cBloc);
			b->cBloc = newBloc;
		}
		b = b->bSuivant;

	}

	return true;
}

bool compresserIPv6(ListIp* l)
{
    simplifierIPv6(l);

	Bloc* b = l->bTete;
	int i = 1, j;
	while (b != NULL)
	{
		if (b == l->bQueue) break;

		j = i;
		if(b->cBloc == (char*)"0" && b->bSuivant->cBloc == (char*)"0")
		{
			while (b->bSuivant->cBloc == (char*)"0")
			{
				j++;
				b = b->bSuivant;
				if (b == l->bQueue) break;
			}
			for (int k = i; k < j; k++)
			{
				supprBloc(l, i);
			}
			b->cBloc = (char*)("::");
			break;
		}
		i++;
		b = b->bSuivant;
		
	}

	return true;
}

bool decompresserIPv6(ListIp* l)
{
	int lg = 9-longListIp(l);
	Bloc* b = l->bTete;
	int position = 1;
	while (b != NULL)
	{
		if (b->cBloc == (char*)"::") break;
		b = b->bSuivant;
		position++;
	}
	if (b == NULL) return false;
	supprBloc(l, position);
	for (int i = 0; i < lg; i++)
	{
		inserBlocIp(l, (char*)"0", position);
	}
	return true;
}





