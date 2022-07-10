#include <stdio.h>
#include "menufil.h"
#define vogal(c) ((c)=='a' || (c)=='e' || (c)=='i' || (c)=='o' || (c)=='u' ||\
                  (c)=='A' || (c)=='E' || (c)=='I' || (c)=='O' || (c)=='U')

extern char mat[400][13],
            tabwp[52],
            padrao[52],
            tabela[52],
	    tabela1[52],
            letra, ant;
extern int  posi, tab, ets, px;

w_perfect(int modo, int pos)
{
 extern FILE *fopen(),
	     *in,
	     *out;
 extern char mat1[70],
	     mat2[70];
 char temp='';
 if (modo==0) for(tab=0;tab<53;tab++) {tabela[tab]=padrao[tab]; tabela1[tab]=tabwp[tab];}
  else for(tab=0;tab<53;tab++) {tabela[tab]=tabwp[tab]; tabela1[tab]=padrao[tab];}

 file('d', 'e', 's', modo, pos);
 ant=' ';
/* while(ant==' ') {  letra=getc(in);
                    if(feof(in)!=0) {ant='1'; continue;}
		    if(letra=='\xc5') { if((letra=getc(in))=='\x0') { if((letra=getc(in))=='\xb') { if((letra=getc(in))=='\xd0') {
                                                                                                                                   ant=''; continue;
                                                                                                                                 } else fseek(in,-3,SEEK_CUR);
                                                                                                  } else fseek(in,-2,SEEK_CUR);
                                                                    } else fseek(in,-1,SEEK_CUR);
                                      }
		 }
 if(ant=='1') fseek(in,0,SEEK_SET);
*/
 fseek(in,8998,SEEK_SET);
 while(feof(in)==0) { tab=0;
                      letra = getc(in);
                      if (semuso(letra)==1) { temp=letra;
                                              letra='';
                                              while(letra!=temp) { letra=getc(in);
                                                                   if(feof(in)!=0) letra=temp;
                                                                 }
                                              tab=2;
                                            }
                      if (letra=='\x83') if(getc(in)=='\x0a') { fputs("\r\n",out); tab=2; } else fseek(in,-1,SEEK_CUR);
                      if (letra=='\x0d') letra=' ';
                      if (letra=='\xa9' || letra=='\xaa') letra='-';
                      if (letra=='\x0a') { fputs("\r\n",out); tab=2; ant=letra;}
                      if (letra==' ' && ant==' ') tab=2;

                      if (tab==0 && isletra(letra)) { putc(letra,out); tab=2;ant=letra;}
	              if (tab==0 && letra=='\xc0') { letra=getc(in);
                                                     con_ac();
                                                     if(tab==1 && tabela[posi]!='\0') putc(tabela[posi],out);
                                                     ant=letra; tab=2;
                                                     getc(in);
                                                     getc(in);
                                                   }
                     }
 letra='';
 putc('\x1a',out);
 fcloseall();
 if (modo==1) remove(mat1);
}

semuso(char c)
{
 if(c=='\xc3' || c=='\xc4' || c=='\xd0' || c=='\xd5' || c=='\xc2' || c=='\xc6' || c=='\xd4' || c=='\xd3' || c=='\xc1') return(1); else return(0);
}
