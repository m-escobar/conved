#include <stdio.h>
#include "menufil.h"
extern char mat[400][13], tabrd70[52], padrao[52], tabela[52],
	    tabela1[52], letra, ant;
extern int  posi, tab, ets, px;

rd_7000(int modo, int pos)
{
extern FILE *fopen(),
	    *arq1,
	    *arq2;
extern char mat1[70],
	    mat2[70];

 if (modo==0) for(tab=0;tab<53;tab++) {tabela[tab]=tabrd70[tab]; tabela1[tab]=padrao[tab];}
  else for(tab=0;tab<53;tab++) {tabela[tab]=padrao[tab]; tabela1[tab]=tabrd70[tab];}

 file('d', 'e', 's', modo, pos); fseek(arq1, 771, SEEK_CUR);
 ant='';
 while(letra != EOF) { tab=0;
		       letra = getc(arq1);
                       if (letra==' ' && ant==' ') tab=2;
		       if (letra=='\r') { putc('\r',arq2);
					  putc('\n',arq2);
					  ant=letra;
					  fseek(arq1, 3, SEEK_CUR);
					  tab=2;
					}
		       if (tab==0 && isletra(letra)) { putc(letra,arq2); tab=2; ant=letra;}
		       if (tab==0) con_ac();
		       if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],arq2); ant=letra;}
		     }
 letra='';
 fcloseall();
 if (modo==1) remove(mat1);
}
