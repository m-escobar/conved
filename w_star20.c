#include "menufil.h"
#include <stdio.h>

int init(FILE *in);

extern char mat[400][13], tabwsa[55], padrao[55], tabela[55],
	    tabela1[55], letra, ant;
extern int  posi, tab, ets, px;

void w_star2000(int modo, int pos)
{
 extern FILE *in,
	     *out;
 extern char mat1[20],
	     mat2[20];
 int tipo=0, lix=0;
 char temp='\0';
 if (modo==0) for(tab=0;tab<55;tab++) {tabela1[tab]=tabwsa[tab]; tabela[tab]=padrao[tab];}
  else for(tab=0;tab<55;tab++) {tabela1[tab]=padrao[tab]; tabela[tab]=tabwsa[tab];}


 file('t', 'e', 'x', modo, pos);
 tipo=init(in);
 ant='\0'; letra='\0';
 if(tipo==1)
 {
  while(letra != EOF) {
		      tab=0;
		      letra = getc(in);
                      if (letra==' ' && ant==' ') tab=2;
		      if (letra=='\x7f') { do letra=getc(in); while(letra!='\x7f');
					   tab=2;
					 }
		      if (letra=='\n') { putc('\r',out);
					 putc('\n',out);
					 ant=letra;
					 tab=2;
				       }
		      if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; ant=letra;}
		      if (tab==0) con_ac();
		      if (tab==1 && tabela[posi]!='\0') {putc(tabela[posi],out); ant=letra;}
		     }
 } else {   while(letra != '\xff') {
		                  tab=0;
		                  letra = getc(in);
		                  if(letra=='\xc1') { do letra=getc(in); while(letra!='\xc1');
					              tab=2;
					            }
		                  if(letra=='\xc3') { do letra=getc(in); while(letra!='\xc3');
					              tab=2;
					            }
		                  if(letra=='\xc4') { do letra=getc(in); while(letra!='\xc4');
					              tab=2;
					            }
		                  if(letra=='\xc6') { do letra=getc(in); while(letra!='\xc6');
					              tab=2;
					            }
		                  if(letra=='\xc7') { do letra=getc(in); while(letra!='\xc7');
					              tab=2;
					            }
		                  if(letra=='\xdc') { do letra=getc(in); while(letra!='\xdc');
					              tab=2;
					            }
		                  if(letra=='\xde') { do letra=getc(in); while(letra!='\xde');
					              tab=2;
					            }
                                  if(letra=='\r') letra=' ';
                                  if(letra==' ' && ant==' ') tab=2;
                                  if(letra=='\n') { putc('\r',out);
					            putc('\n',out);
					            ant=letra;
					            tab=2;
				                  }
                                  if(letra=='\xa9') letra='-';
                                  if(letra=='\xe2' && lix==0) { do letra=getc(in); while(letra!='\x8d');
                                                                tab=2; lix=1;
                                                              } else if(letra=='\xe2' && lix==1)
                                                                      { tab=2;lix=0; }
                                  if(letra=='\xe1') { letra=getc(in);
                                                      getc(in);
                                                    }
                                  if(letra=='a') { temp=getc(in);
                                                   if(temp=='\x99') {getc(in);letra='\xe2';}
                                                     else fseek(in,-1,SEEK_CUR);
                                                 }
                                  if(letra=='o') { temp=getc(in);
                                                   if(temp=='\x99') {getc(in);letra='\xf9';}
                                                     else fseek(in,-1,SEEK_CUR);
                                                 }
                                  if(letra=='\x94' || letra=='\x84' || letra=='\xb' || letra=='\xc' || letra=='\x95' || letra=='\x83') tab=2;
                                  if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; ant=letra;}
		                  if (tab==0) con_ac();
		                  if (tab==1 && tabela[posi]!='\0') {putc(tabela[posi],out); ant=letra;}
		                }
        }
 letra='\0';
 putc('\x1a',out);
 fcloseall();
 if (modo==1) remove(mat1);
}

int init(FILE *in)
{
 int inicio=0;
 do {  if((letra=getc(in))==NULL) inicio=2;
       if(letra=='\x7f') if((letra=getc(in))=='v')
                                       { if((letra=getc(in))=='\x7f') inicio=1;
                                              else fseek(in, -2, SEEK_CUR);
                                       } else fseek(in, -1, SEEK_CUR);
    } while(inicio==0);
 if(inicio==2) fseek(in,0,SEEK_SET);
 return(inicio);
}
