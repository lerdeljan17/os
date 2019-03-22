#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define UTIL_IMPLEMENTATION
#include "utils.h"
#define MAX 128

#define print(x) write(1, x, strlen(x));
static char mala_slova[MAX];
static char velika_slova[MAX];
static char ctrl_map[16][66];
static int CTRL = 0;
static int ALT = 0;
static int SHIFT = 0;

static int code;
/*
	Deklaracije za nizove i tabele ovde
	tabelu za prevodjenje scancodeova i tabelu
	za cuvanje mnemonika cuvati kao staticke
	varijable unutar ovog fajla i ucitavati
	ih uz pomoc funkcije load_config

*/

int find(){
	
}

void load_config(const char *scancodes_filename, const char *mnemonic_filename)
{	
	char tmp[10];
	int len1,len2,n, i;
	int sct = open(scancodes_filename, O_RDONLY);
	len1 = fgets(mala_slova, MAX, sct);
	len2 = fgets(velika_slova, MAX, sct);
	close(sct);
	int cm = open(mnemonic_filename, O_RDONLY);
	n = fgets(tmp, 10, cm);
	n = atoi(tmp);
	for(i=0;i<n;i++){
		fgets(ctrl_map[i], MAX, cm);
		print(ctrl_map[i]);
	}/*
	for(i=0;i<len1;i++){
		//write(1,&mala_slova[i],1);
		print(&mala_slova[i]);
	}
	write(1,"\n",1);
	for(i=0;i<len2;i++){
		//write(1,&velika_slova[i],1);
		print(velika_slova + i);
	}*/
	print(mala_slova);
	print("\n");
	print(velika_slova);
	close(cm);
}

int process_scancode(int scancode, char *buffer)
{
	int result;
	code = scancode;
	/*
		Your code goes here!
		Remember, only inline assembly.
		Good luck!
	*/
	__asm__ __volatile__ (
		"movl (code),%eax;"
		"cmpl $200, %eax;"
		"je SHIFTL;"
		"cmpl $201, %eax;"
		"je CTRLL;"
		"cmpl $202 , %eax;"
		"je ALTL;"
		"SHIFTL:;"
		"movl $1, (SHIFT);"
		"jmp END;"
		"CTRLL:;"
		"movl $1,(CTRL);"
		"jmp END;"
		"ALTL:;"
		"movl $1,(ALT);"
		"END:;"

	
	);
	vardump(ALT);
	vardump(CTRL);
	vardump(SHIFT);

	return result;
}
