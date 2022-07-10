#include "menufil.h"
#include <stdio.h>

void hif(void);

extern char mat[400][13], mac[55], padrao[55], tabela[55],
         tabela1[55], letra, ant, fonte[13][17];
extern int  posi, tab, ets, px;
char fon[13][20]= { "Avant Garde",
                    "Bodoni",
                    "Bodoni Book",
                    "FranklinGothic",
                    "FranklinGothic No.2",
                    "Futura",
                    "Futura Book",
                    "Garamond",
                    "Helvetica",
                    "65 Helvetica Medium",
                    "55 Helvetica Roman",
                    "Times",
                    "TimesTen Roman"
                  };

void quark(int modo, int pos)
{
 extern FILE *in,
             *out;
 extern char mat1[70],
             mat2[70];
 extern struct PARAM param;
 char prox='\0';
 int tam=0, atam=0;
 ant='\0';

 if (modo==0) for(tab=0;tab<55;tab++) { tabela[tab]=padrao[tab]; tabela1[tab]=padrao[tab]; }
      else for(tab=0;tab<55;tab++) { tabela[tab]=mac[tab]; tabela1[tab]=padrao[tab]; }

 if(param.justif==1) hif();
 file('x', 't', 'g', 1, pos);

 fprintf(out,"<f\"%s\"",fon[param.fonte]);
 fprintf(out,"z%s",param.corpo);
 fprintf(out,"*p(%s,%s,%s,%s,0,0,g)",param.esq,param.fline,param.dir,param.entrelinha);
 if(param.alinhamento==just) fprintf(out,"*J>");
  else if(param.alinhamento==dire) fprintf(out,"*R>");
        else if(param.alinhamento==esqu) fprintf(out,"*L>");
              else fprintf(out,"*C>");

 while(letra != EOF) {
                      tab=0;
                      letra = getc(in);
                      if(letra=='\xa6') { putc('\xbb',out); ant=letra; tab=2; continue;}
                      if(letra=='\xa7') { putc('\xbc',out); ant=letra; tab=2; continue;}
                      if(letra=='\xa8') { putc('\xc0',out); ant=letra; tab=2; continue;}
                      if(letra=='\xad') { putc('\xc1',out); ant=letra; tab=2; continue;}
                      if(letra=='\xae') { putc('\xc7',out); ant=letra; tab=2; continue;}
                      if(letra=='\xaf') { putc('\xc8',out); ant=letra; tab=2; continue;}
                      if(letra=='\xc5') { putc('\xd1',out); ant=letra; tab=2; continue;}
                      if(letra=='\xa2') { putc('\xd2',out); ant=letra; tab=2; continue;}
                      if(letra=='\xa5') { putc('\xd3',out); ant=letra; tab=2; continue;}
                      if(letra=='\xf8') { putc('\xa5',out); ant=letra; tab=2; continue;}

                      if(letra=='<') {putc('<',out);tab=2;}
                      if(letra=='>') {putc('>',out);tab=2;}
                      if(letra=='\x2') { while((letra=getc(in))!='\x3') { tam++;
                                                                         if(letra==EOF) {atam=1; break;}
                                                                        }
                                         if(atam!=0) {fseek(in,(tam-1)*-1,SEEK_CUR); tam=0;atam=0;letra='\0';}
                                         tab=2;
                                        }
                      if (letra==' ' && ant==' ') tab=2;
                      if(letra=='\xfe') {fprintf(out,"<\\h>");letra='\0';tab=2;}
                      if (letra=='\r') { prox = getc(in);
                      if (prox=='\n') { putc('\r',out);
                                        ant=letra;
                                        tab=2;
                                        prox='\0';
                                      }
                        else fseek(in,-1,SEEK_CUR);
                         }
                if (tab==0 && letra=='\r') { putc('\r',out); tab=2;}
                if (tab==0 && isletra(letra)) { putc(letra,out); ant=letra; tab=2;}
                if (tab==0) con_ac();
                if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],out); ant=letra; tab=0;}
               }

 letra='\0';
 if(modo==0) putc('\x1a',out);
 fcloseall();
 remove(mat1);
}
