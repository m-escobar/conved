#include <stdio.h>
#include "menufil.h"

void id_acento(char letra1);
int  con_ws(void);

extern char mat[400][13],
            padrao[55],
	    tabela[55],
	    tabela1[55],
	    tabws[55][4],
	    tabws1[55][4],
	    tabwsa[55],
            letra,
            ant;
extern int  posi,
	    tab,
	    ets,
            px;

void w_star(int modo, int pos)
{
 extern FILE *in,
             *out;
 extern char mat1[70],
             mat2[70];
 char prox='\0',
      prox1='\0',
      let='\0';

 if (modo==0) for(tab=0;tab<55;tab++) {
            tabela[tab]=padrao[tab];
            tabela1[tab]=tabwsa[tab];}
  else for(tab=0;tab<55;tab++) {tabela[tab]=tabwsa[tab]; tabela1[tab]=padrao[tab];}

 file('d', 'o', 'c', modo, pos);
 ant='\0';

 if (modo==0) {
 while(letra != EOF) {
                      tab=0;
                      letra = getc(in);
                      if(letra=='\x8d') { if((prox=getc(in))==EOF) break;
                                          if (prox=='\n') tab=2; else fseek(in, -1, SEEK_CUR);
                                        }
                      if (letra=='\x1b' || letra=='\x9b') { letra=getc(in);
                                                            con_ac();
                                                            if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],out);
                                                                                                ant=letra;
                                                                                                tab=2;
                                                                                              } else tab=0;
                                                            if((letra=getc(in))!='\x1c') fseek(in,-1,SEEK_CUR);
                                                          }
                      if (letra=='\r') { prox=getc(in);
                                         if(prox=='\x8a') { putc('\r',out);
                                                            putc('\n',out);
                                                            ant=letra;
                                                            tab=2;
                                                          } else fseek(in,-1,SEEK_CUR);
                                       }
                      if(letra>=0x7f || letra<0) let=letra & '\x7f'; else let=letra;
                      if(letra=='\x2') { fprintf(out,"<B>"); tab=2; ant=letra;}
                      if(letra=='\x19') { fprintf(out,"<I>"); tab=2; ant=letra;}
                      if(letra=='\x1d') { while(getc(in)!='\x1d') {}; tab=2; ant=letra;}
                      if(let==' ' && ant==' ') tab=2;
                      if(tab==0) { if((prox=getc(in))==EOF) break;
                                   if(prox=='\n') fputs("\r\n",out);
                                   if(prox=='\x8') { if((prox1=getc(in))==EOF) break;
                                                     id_acento(prox1);
                                                     if(tab==1 && padrao[posi]!='\0') { putc(padrao[posi],out); ant=let; tab=2;}
                                                       else fseek(in, -2, SEEK_CUR);
                                                   } else fseek(in, -1, SEEK_CUR);
                                 }
                      if (tab==0 && isletra(let)) {putc(let,out); ant=let; tab=2;}
                     }
              } else { while(letra != EOF) {
                                            tab=0;
                                            letra = getc(in);
                                            con_ws();
                                            if (tab==0) putc(letra,out);
                                            if (tab==1 && tabws[posi]!='\0') fputs(tabws[posi],out);
                                           }
                     }
 letra='\0';
 fcloseall();
 if (modo==1) remove(mat1);

}

int con_ws(void)
{
  for (posi=0;posi<55;posi++)
   if (letra==padrao[posi]) { tab=1; return(tab); }
  return(0);  //o zero nao e' nada, apenas lixo
}
