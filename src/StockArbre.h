#include <iostream>
#include <string.h>

using namespace std;

typedef struct ProduitArbre
{
	string label;
	int Qnt;
	double prixU;
	struct ProduitArbre* pGauche;
	struct ProduitArbre* pDroit;
}ProduitArbre;

typedef struct StockArbre
{
	ProduitArbre* root;
}StockArbre;

StockArbre* creerStockArbre()
{
	StockArbre* S = new StockArbre;
	S->root = NULL;

	return S;
}

ProduitArbre* creerProduitArbre(string label, int quantite, double prixU)
{
	ProduitArbre* P = new ProduitArbre;
	P->label = label;
	P->prixU = prixU;
	P->Qnt = quantite;
	P->pDroit = NULL;
	P->pGauche = NULL;

	return P;
}

bool stockVideArbre(StockArbre* st)
{
	return (st->root == NULL);
}

void affStockArbre(ProduitArbre* root)
{
	if (root != NULL)
	{
		cout << "\t|Produit       :  " << root->label << endl;
		cout << "\t|Quantite      :  " << root->Qnt << " Unites" << endl;
		cout << "\t|Prix unitaire :  " << root->prixU << " Dhs" << endl;
		cout << "\t---------------------------" << endl;
		if (root->pDroit != NULL || root->pGauche != NULL)
		{
			affStockArbre(root->pGauche);
			affStockArbre(root->pDroit);
		}
	}
}

ProduitArbre* ExisteArbre(StockArbre*st,string lbl)
{
	if (stockVideArbre(st)) return NULL;
	
	ProduitArbre* p = st->root;

	while (p != NULL)
	{
		if (p->label == lbl) break;
		else if (lbl > p->label) p = p->pDroit;
		else p = p->pGauche;
	}

	return p;
}

bool ajouteProduitArbre(StockArbre* st, string lbl, int Qnt, double prixU)
{
	if (ExisteArbre(st, lbl) != NULL)
	{
		ExisteArbre(st, lbl)->Qnt += Qnt;
		ExisteArbre(st, lbl)->prixU = prixU;
		return true;
	}

	ProduitArbre* p = creerProduitArbre(lbl, Qnt, prixU);

	if (stockVideArbre(st))
	{
		st->root = p;
		return true;
	}

	ProduitArbre* p2;
	p2 = st->root;

	while (p2 != NULL)
	{
		if (lbl > p2->label)
		{
			if (p2->pDroit == NULL)
			{
				p2->pDroit = p;
				return true;
			}
			else p2 = p2->pDroit;
		}
		else
		{
			if (p2->pGauche == NULL)
			{
				p2->pGauche = p;
				return true;
			}
			else p2 = p2->pGauche;
		}
	}

	return true;
}

ProduitArbre* suppProduitArbre(ProduitArbre* root, string lbl)
{
	ProduitArbre* pDeleted;
	if (root->label == lbl)
	{
		pDeleted = root;
		if (pDeleted->pGauche == NULL)
			return pDeleted->pDroit;
		else
		{
			root = pDeleted->pGauche;
			while (root->pDroit != NULL)
			{
				root = root->pDroit;
			}
			root->pDroit = pDeleted->pDroit;
			return pDeleted->pGauche;
		}
		free(pDeleted);
	}
	else {
		if (root->label > lbl)
		{
			root->pGauche = suppProduitArbre(root->pGauche, lbl);
		}
		else
		{
			root->pDroit = suppProduitArbre(root->pDroit, lbl);
		}
	}

	return root;
}

bool vendreArbre(StockArbre* st, string lbl, int nbrUnites)
{

	if (ExisteArbre(st, lbl) == NULL) return false;

	ExisteArbre(st, lbl)->Qnt -= nbrUnites;

	if (ExisteArbre(st, lbl)->Qnt < 1) suppProduitArbre(st->root, lbl);

	return true;
}

double prixStockArbre(ProduitArbre* root)
{
	double prix = 0;
	prix += root->prixU * root->Qnt;

	
	if (root->pDroit != NULL)  prix += prixStockArbre(root->pDroit);
	if (root->pGauche != NULL) prix += prixStockArbre(root->pGauche);

	return prix;
}
