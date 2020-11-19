#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct Joueur
{
	int numero;
	struct Joueur* jSuivant;
	struct Joueur* jPrecedent;
}Joueur;

Joueur* CreerJoueur(int numero)
{
	Joueur* J = new Joueur;

	J->numero = numero;
	J->jPrecedent = NULL;
	J->jSuivant = NULL;

	return J;
}

typedef struct ListJoseph
{
	int nombre;
	Joueur* Tete;
}ListJoseph;

ListJoseph* creerListJoseph()
{
	ListJoseph* L = new ListJoseph;
	L->nombre = 0;
	L->Tete = NULL;
	return L;
}

bool listVide(ListJoseph L)
{
	return (L.nombre < 1);
}

void affList(ListJoseph L)
{
	if (listVide(L)) cout << "la list est vide";
	else
	{
		Joueur* j = L.Tete;
		cout << "\t";
		do
		{
			cout << j->numero << "\t";
			j = j->jSuivant;
		} while (j != L.Tete);
		cout << endl << endl;
	}
}

ListJoseph* remplirTab(int t[], int size)
{
	ListJoseph* L = creerListJoseph();

	L->nombre = size;
	L->Tete = CreerJoueur(t[0]);

	Joueur* j = L->Tete;

	for (int i = 1; i < size; i++)
	{
		j->jSuivant = CreerJoueur(t[i]);
		j->jSuivant->jPrecedent = j;
		j = j->jSuivant;

	}
	j->jSuivant = L->Tete;
	L->Tete->jPrecedent = j;

	return L;
}

bool eliminer(ListJoseph* L, int p)
{
	if (L == NULL) return 0;

	Joueur * J;
	J = L->Tete;
	while (J->numero != p)
	{
		J = J->jSuivant;
	}

	J->jPrecedent->jSuivant = J->jSuivant;
	J->jSuivant->jPrecedent = J->jPrecedent;
	if (J == L->Tete) L->Tete = J->jSuivant;
	L->nombre--;

	free(J);

	return true;
}

int winner(ListJoseph * L, int debut)
{
	if (L == NULL) return 0;

	Joueur * j = L->Tete;
	int n = L->nombre;

	while (j->numero != debut && n > 0)
	{
		j = j->jSuivant;
		n--;
	}
	if (j->numero != debut) return 0;

	while (L->nombre > 1)
	{
		eliminer(L, j->jSuivant->numero);
		j = j->jSuivant;
		affList(*L);
	}

	return L->Tete->numero;
}

