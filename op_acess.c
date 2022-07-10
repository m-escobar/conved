#include <stdio.h>
#include "menufil.h"
extern char mat[400][13], tabop[52], padrao[52], tabela[52],
	    tabela1[52], letra, ant;
extern int  posi, tab, ets, px;

op_acess(int modo, int pos)
{
extern FILE *fopen(),
	    *arq1,
	    *arq2;
extern char mat1[70],
	    mat2[70];

 int locpos=pos;
 if (modo==0) for(tab=0;tab<53;tab++) {tabela[tab]=tabop[tab]; tabela1[tab]=padrao[tab];}
  else for(tab=0;tab<53;tab++) {tabela[tab]=padrao[tab]; tabela1[tab]=tabop[tab];}

 file('d', 'o', 'c', modo, pos);
 ant='';
 if(modo==0) {
 fseek(arq1, 1029, SEEK_CUR);
 while(letra != '\xff') {
			  tab=0;
			  letra = getc(arq1);
			  if (letra==' ' && ant==' ') tab=2;
			  if (letra=='\0') { putc('\x20',arq2); tab=2; ant=letra; }
			  if (letra=='\r') { putc('\r',arq2);
					     putc('\n',arq2);
					     ant=letra;
					     fseek(arq1, 5, SEEK_CUR);
					     tab=2;
					   }
			  if (tab==0 && isletra(letra)) { putc(letra,arq2); tab=2; ant=letra;}
			  if (tab==0) con_ac();
			  if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],arq2); ant=letra;}
			}
	     } else
  while(letra != EOF) { tab=0;
			letra = getc(arq1);
			if (letra==' ' && ant==' ') tab=2;
			if (letra=='\r') { putc('\r',arq2);
					   putc('\n',arq2);
					   ant=letra;
					   tab=2;
					 }
			if (tab==0 && isletra(letra)) { putc(letra,arq2); tab=2; ant=letra;}
			if (tab==0) con_ac();
			if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],arq2); ant=letra;}
		       }
 letra='';
 fcloseall();
 if (modo==1) remove(mat1);
 pos=locpos;
}
