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
static int ctrl_len[16];
static int CTRL = 0;
static int ALT = 0;
static int SHIFT = 0;
static int len1,len2,n,ialt;
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
	int i;
	ialt = 0;
	int sct = open(scancodes_filename, O_RDONLY);
	len1 = fgets(mala_slova, MAX, sct);
	len1--;
	len2 = fgets(velika_slova, MAX, sct);
	close(sct);
	int cm = open(mnemonic_filename, O_RDONLY);
	n = fgets(tmp, 10, cm);
	n = atoi(tmp);
	int g;
	char gs[10];
	for(i=0;i<n;i++){
		g = fgets(ctrl_map[i], MAX, cm);
		ctrl_len[i] = g-2;
		itoa(ctrl_len[i],gs);
		print(gs);
		print(ctrl_map[i]);
	}
	print(mala_slova);
	print("\n");
	print(velika_slova);
	close(cm);
}

int process_scancode(int scancode, char *buffer)
{
	int result;
	/*
		Your code goes here!
		Remember, only inline assembly.
		Good luck!
	*/
	__asm__ __volatile__ (
		"xorl %%ebx,%%ebx;"
		"cmpl $200, %%edx;"
		"je SHIFT1;"
		"cmpl $201, %%edx;"
		"je CTRL1;"
		"cmpl $202 , %%edx;"
		"je ALTL1;"
		"cmpl $300, %%edx;"
		"je SHIFT0;"
		"cmpl $301, %%edx;"
		"je CTRL0;"
		"cmpl $302 , %%edx;"
		"je ALTL0;"
		"jmp END;"
		"SHIFT1:;"
		"movl $1, (SHIFT);"
		"jmp END;"
		"CTRL1:;"
		"movl $1,(CTRL);"
		"jmp END;"
		"ALTL1:;"
		"movl $1,(ALT);"
		"movl $0,(ialt);"
		"jmp END;"
		"SHIFT0:;"
		"movl $0, (SHIFT);"
		"jmp END;"
		"CTRL0:;"
		"movl $0,(CTRL);"
		"jmp END;"
		"ALTL0:;"
		"movl $0,(ALT);"
		"jmp ATLL2;"
		"END:;"
		
		"cmpl $128,%%edx;"
		"jg EN1;"
		"cmpl $1, (SHIFT);"
		"je VELIKA_SLOVAL;"
		"cld;"
		"leal mala_slova, %%esi;"
		//"decl %%edx;"
		"addl %%edx,%%esi;"
		"movsb;"
		"decl %%edi;"
		"incl %%ebx;"
		"jmp KK;"
		
		"VELIKA_SLOVAL:;"
		//"cmpl $50,%%edx;"
		//"jg KK;"
		"cld;"
		"leal velika_slova, %%esi;"
		//"decl %%edx;"
		"addl %%edx,%%esi;"
		"movsb;"
		"decl %%edi;"
		"incl %%ebx;"
		
		"KK:;"
		"cmpl $0, (CTRL);"
		"je EN;"
		"cld;"
		//"leal ctrl_len,%%eax;"
		"leal ctrl_map, %%esi;"
		"movl (n),%%ecx;"
		"CTRLL:;"
		"cmpsb;"
		"je NASO;"
		"decl %%edi;"
		"addl $65,%%esi;"
		"incl %%eax;"
		"loop CTRLL;"
		"cmpl 0,%%ecx;"
		"je EN1;"
		"NASO:;"
		
		"addl $1,%%esi;"
		"decl %%edi;"
		
		"xorl %%ebx,%%ebx;"
		"xorl %%ecx,%%ecx;"
		"movl $64,%%ecx;"
		"movl %%esi,%%edx;"
		"N:;"
		"lodsb;"
		"cmpb $10,%%al;"
		"je POSLE;"
		//"repe movsb;"
		"incl %%ebx;"
		"loop N;"
		"POSLE:;"
		"movl %%edx,%%esi;"
		"movl %%ebx,%%ecx;"
		"rep movsb;"
		
		/*"xorl %%ebx, %%ebx;"
		"xorl %%ecx, %%ecx;"
		"movl (%%eax), %%ecx;"
		*/
		
		/*
		"PREPISUJ:;"
		"inc %%ebx;"
		"movsb;"		
		"loop PREPISUJ;"
		*/
		//"movl (%%eax)"
		
		
		/*
		"decl %%edi;"
		"xorl %%ecx,%%ecx;"
		"movl (%%eax),%%ecx;"
		"movl (%%eax),%0;"
		"rep movsb;"
		*/
		
		"ALTLL:;"
		//"movl $0,(ialt);"
		"imul $10,(ialt),%%eax;"
		"subl $48,(%%edi);"
		"addl (%%edi),%%eax;"
		"movl %%eax,ialt;"
		"jmp EN1;"
		
		"ATLL2:;"
		"movl (ialt), %%eax;"
		"stosb;"
		"movl $1 ,%%ebx;"
		//"movb (ialt),%%edi;"
		"movl $0,(ialt);"
		"jmp EN1;"
		
		"EN:;"
		"cmpl $1,(ALT);"
		"je ALTLL;"
		"EN1:;"
		//"KK:;"
		:"=b"(result)
		:"d"(scancode),"D" (buffer)
	
	);
	/*vardump(ALT);
	vardump(CTRL);
	vardump(SHIFT);
	vardump(ialt);*/
	return result;
}
