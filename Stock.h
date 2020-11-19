#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


typedef struct Produit
{
	string label;
	int Qnt;
	double prixU;
	struct Produit *pSuivant;
}Produit;

typedef struct Stock
{
	Produit* pTete;
	Produit* pQueue;
}Stock;

Stock* creerStock()
{ 
 	Stock *S = new Stock;
 	S->pTete = NULL;
 	S->pQueue = NULL;
	
	return S;
}

bool stockVide(Stock *st)
{
	return (st->pTete==NULL);
}

void affStock(Stock* st)
{
	if (stockVide(st)) cout << "le stock est vide" << endl;
	else {
		Produit* p = st->pTete;
		while (p != NULL)
		{
			cout << "Produit       :  " << p->label << endl;
			cout << "Quantite      :  " << p->Qnt << endl;
			cout << "Prix unitaire :  " << p->prixU << endl;
			cout << "----------------------" << endl;
			p = p->pSuivant;
		}
	}

}

Produit* Existe(Stock *st,string lbl)
{
	if (stockVide(st)) return NULL;
	Produit *p = st->pTete;
	while(p != NULL)
	{
		if(p->label == lbl) return p;
		p = p->pSuivant;
	}
	return NULL;
}

Produit* creerProduit(string label,int quantite,double prixU)
{
	Produit *P=new Produit;
	P->label=label;
	P->prixU=prixU;
	P->Qnt=quantite;
	P->pSuivant=NULL;
	
	return P;
}

bool ajouteProduit(Stock *st,string lbl,int Qnt,double prixU)
{
	
	if(Existe(st,lbl) != NULL)
	{
		Existe(st,lbl)->Qnt += Qnt;
		Existe(st,lbl)->prixU = prixU;
	}
	else
	{
		Produit *pro = creerProduit(lbl,Qnt,prixU);
		if (stockVide(st))
		{
		    st->pTete = st->pQueue = pro;
		}
		else
		{
			st->pQueue->pSuivant = pro;
			st->pQueue = pro;
		}		
	}
       return true;
}

bool suppProduit(Stock *st,string lbl)
{
	if(Existe(st,lbl) == NULL) return false;
	
	Produit* t = Existe(st, lbl);
	Produit* p = st->pTete;
	
	while(p->pSuivant->label != t->label)	p = p->pSuivant;
	
	if (t->pSuivant == NULL)
	{
		st->pQueue = p;
		p->pSuivant = NULL;
		free(t);
	}
	else
	{
		p->pSuivant = t->pSuivant;
		free(t);
	}
	
}

bool Vendre(Stock *st,string lbl,int nbrUnites)
{
	if(Existe(st,lbl) == NULL) return false;
	
	Existe(st,lbl)->Qnt -= nbrUnites;
	
	if(Existe(st,lbl)->Qnt < 1) suppProduit(st,lbl);
	
	return true;	
}

double prixStock(Stock *st)
{
	double prix = 0;
	Produit *p = st->pTete;
	while(p!=NULL)
	{
		prix += p->Qnt * p->prixU;
		p = p->pSuivant;
	}
	
	return prix;
}




















