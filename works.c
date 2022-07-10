#include "menufil.h"
#include <stdio.h>

void ident_works(FILE *in);

extern char mat[400][13], tabms5[55], padrao[55], tabela[55],
	    tabela1[55], letra, ant;
extern int  posi, tab, ets, px;
long tami=0;

void works(int pos)
{
 extern FILE *in,
	     *out;
 extern char mat1[70],
	     mat2[70];
 char prox='\0';
 ant='\0';

 for(tab=0;tab<55;tab++) { tabela[tab]=padrao[tab]; tabela1[tab]=tabms5[tab];}

 file('w', 'p', 's', 0, pos);
 ident_works(in);
 while(tami>0) {
                tab=0;
                letra = getc(in);
                if (letra=='\xa6' || letra=='\xa7' || letra=='\xa8' || letra=='\xad' ||
                    letra=='\xae' || letra=='\xaf') {putc(letra,out); ant=letra; tab=2; tami--; continue;}
                if (letra=='\xc4') {putc('\xc5',out); ant=letra; tab=2; tami--; continue;}
                if (letra=='\xd2') {putc('\xa2',out); ant=letra; tab=2; tami--; continue;}
                if (letra=='\xd3') {putc('\xa5',out); ant=letra; tab=2; tami--; continue;}
                if (letra=='\xf9') {putc('\xf8',out); ant=letra; tab=2; tami--; continue;}
                if (letra==' ' && ant==' ') {tab=2; tami--;}
                if (letra=='<') { tami--;
                                  while(letra!='>') { putc(letra,out);
                                                      letra=getc(in);
                                                      tami--;
                                                    }
                                  putc('>',out);
                                  continue;
                                }
                if (letra=='\r') { prox = getc(in);
		                   if(prox=='\n') { putc('\r',out);
					            putc('\n',out);
					            ant=letra;
						    tab=2;
						    prox='\0';
						    tami-=2;
			         		  }
			            else fseek(in,-1,SEEK_CUR);
				 }
	        if (tab==0 && letra=='\r') { tab=2; tami--;}
                if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; tami--; ant=letra;}
                if (tab==0) con_ac();
                if (tab==1 && tabela[posi]=='\0') { tami--; tab=2;}
                if (tab==0) tami--; else if (tab==1) {putc(tabela[posi],out); tami--; ant=letra;}
              }
 letra='\0';
 putc('\x1a',out);
 fcloseall();
}

void ident_works(FILE *in)
{
 long tam1=0, tam2=0, c1=0, c2=0, c3=0, c4=0;

 fseek(in,37,SEEK_CUR);
 c1=getc(in); c2=getc(in);
 c3=getc(in); c4=getc(in);
 if(c1>0) c1=c1*0x100;
 tam1 = c1 + c2;
 if(c4>0) c4*=0x100;
 tam2 = (c3 + c4) * 0x100;
 tami=(tam1+tam2)-257;

 fseek(in,215,SEEK_CUR);
}
