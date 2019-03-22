#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define SCAN_IMPLEMENTATION
#include "scan.h"
#define print(x) write(1, x, strlen(x));

#define MAX 10

int main(int argc, char *argv[])
{
	int len,isc;
	char sc[MAX];
	char buff[10];
	char file_name[100];
	/* ucitavanje podesavanja */
	write(1, "Unesite ime datoteke\n", strlen("Unesite ime datoteke\n"));
	len = read(0, file_name, 100);
	//write(1,file_name,strlen(file_name));
	file_name[strlen(file_name)-1]= 0;
	//print(file_name);
	//pause();
	load_config("scancodes.tbl","ctrl.map");
	/* ponavljamo: */
		/* ucitavanje i otvaranje test fajla */
		/* parsiranje fajla, obrada scanecodova, ispis */
	int file = open(file_name, O_RDONLY);
	int i;
	while(1){
		
		i = fgets(sc,MAX,file);
		isc = atoi(sc);
		print(sc);
		pause();
		if(isc == 400){
			break;		
		}
		int l = process_scancode(isc, buff);
		pause();
	}
	close(file);
	_exit(0);
		
}
