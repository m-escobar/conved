#include "menufil.h"
#include <stdio.h>

int con_vp1(void);
int con_vp(FILE *in);

extern char mat[400][13], padrao[55], tabvp[55][6], tabela[55],
	    letra, ant;
extern int posi, tab, ets, px;

void ventura_pub(int modo, int pos)
{
 extern FILE *in,
	     *out;
 extern char mat1[70],
	     mat2[70];
 char prox='\0';
 if (modo==0) for(tab=0;tab<55;tab++) tabela[tab]=padrao[tab];

 file('t', 'x', 't', modo, pos);
 ant='\0';
if (modo==0) {
 while(letra != EOF) {
                      tab=0;
                      letra = getc(in);
                      if (letra==' ' && ant==' ') tab=2;
                      if (letra=='\r') { prox = getc(in);
                                         if (prox=='\n') { putc('\r',out);
                                                           putc('\n',out);
                                                           ant=letra;
                                                           tab=2;
                                                           prox='\0';
                                                         } else tab=2;
                                        }
                      if (tab==0 && letra=='@') { fputs("\2@",out);
                                                  while(letra!='=') { letra=getc(in);
                                                                      if(letra=='=') continue;
                                                                      putc(letra,out);
                                                                    }
                                                  putc('\3',out);
                                                  fseek(in,1,SEEK_CUR);
                                                  continue;
                                                }
                      if (tab==0 && letra=='<') con_vp(in);
                      if (tab==0 && letra=='<') {putc('\2',out); continue;}
                      if (tab==0 && letra=='>') {putc('\3',out);continue;}
                      if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; ant=letra;}
                      if (tab==1 && tabela[posi]!='\0') {putc(tabela[posi],out); ant=letra;}
                     }
             } else {
 while(letra != EOF) {
                      tab=0;
                      letra = getc(in);
                      if (letra=='\r') { prox = getc(in);
                                         if (prox=='\n') { putc('\r',out);
                                                           putc('\n',out);
                                                           ant=letra;
                                                           tab=2;
                                                           prox='\0';
                                                         }
                                        }
                      if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; ant=letra;}
                      if (tab==0) tab=con_vp1();
		      if (tab==1 && tabvp[posi][0]!='\0') {fputs(tabvp[posi],out); ant=letra;}
                     }
                    }
 letra='\0';
 putc('\x1a',out);
 fcloseall();
 if (modo==1) remove(mat1);
}

int con_vp(FILE *in)
{
 int x;
 char palavra[6]="";
  palavra[0]=letra;
  if ((palavra[1]=getc(in))==EOF) { tab=0; return(0); }
  if ((palavra[2]=getc(in))==EOF) { tab=0; fseek(in, -1, SEEK_CUR); return(0); }
  if ((palavra[3]=getc(in))==EOF) { tab=0; fseek(in, -2, SEEK_CUR); return(0); }
  if ((palavra[4]=getc(in))==EOF) { tab=0; fseek(in, -3, SEEK_CUR); return(0); }
  palavra[5]='\x0';

 for (posi=0;posi<55;posi++)
  { for (x=0;x<6;x++) if (palavra[x]==tabvp[posi][x]) tab=1; else { tab=0; break; }
    if (tab==1 && x==6) break;
  }
 if (tab==0) fseek(in, -4, SEEK_CUR);
 return(0);
}

int con_vp1(void)
{
  for (posi=0;posi<55;posi++)
   if (letra==padrao[posi]) { tab=1; return(tab); }
  return(0);
}
