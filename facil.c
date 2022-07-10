#include <stdio.h>
#include "menufil.h"
extern char mat[400][13], tabfc[52], padrao[52], tabela[52],
	    tabela1[52], letra, ant;
extern int  posi, tab, ets, px;

facil(int modo, int pos)
{
extern FILE *fopen(),
	    *arq1,
	    *arq2;
extern char mat1[70],
	    mat2[70];

 if (modo==0) for(tab=0;tab<53;tab++) {tabela[tab]=tabfc[tab]; tabela1[tab]=padrao[tab];}
  else for(tab=0;tab<53;tab++) {tabela[tab]=padrao[tab]; tabela1[tab]=tabfc[tab];}

 file('d', 'e', 's', modo, pos);
 ant='';
 while(letra != EOF) {
		      tab=0;
		      letra = getc(arq1);
		      if (letra=='\x8d') tab=2;
                      if (letra==' ' && ant==' ') tab=2;
		      if (tab==0 && isletra(letra)) { putc(letra,arq2); ant=letra; tab=2; }
		      if (tab==0) con_ac();
		      if (tab==1 && tabela[posi]!='\0') {putc(tabela[posi],arq2); ant=letra;}
		     }
 letra='';
 fcloseall();
 if (modo==1) remove(mat1);
}