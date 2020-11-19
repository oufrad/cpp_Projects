#include <iostream>
#include "Josephus.h"
#include "IPv6.h"
#include"Stock.h"
#include "StockArbre.h"

using namespace std;




int main(int argc, char** argv) {
	


	string ip = "fe80:0000:0000:0000:0000:00FE:0000:0000";  
	ListIp* l = creerIpv6(ip);
	
	simplifierIPv6(l);
	affListIp(l);
	compresserIPv6(l);
	affListIp(l);
	decompresserIPv6(l);
	affListIp(l);



	/*StockAvence* s = creerStockAvence();
	
	ajouteProduitAvence(s, "ecran", 10, 2);
	ajouteProduitAvence(s, "clavier", 10, 2);
	ajouteProduitAvence(s, "modem", 10, 2);
	ajouteProduitAvence(s, "cd", 10, 2);
	ajouteProduitAvence(s, "usb", 10, 2);

	affStockAvence(s->root);*/




	system("pause");
	return 0;
}
