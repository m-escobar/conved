#include "menufil.h"
#include <stdio.h>

void ident_fmt(FILE *in, int ver);

extern char mat[400][13], tabms[55], tabms5[55], padrao[55], tabela[55],
	    tabela1[55], letra, ant;
extern int  posi, tab, ets, px;
long tam=0;

void ms_word(int ver, int pos)
{
 extern FILE *in,
	     *out;
 extern char mat1[70],
	     mat2[70];
 char prox='\0';
 ant='\0';

 if(ver==3) for(tab=0;tab<55;tab++) { tabela[tab]=padrao[tab]; tabela1[tab]=tabms[tab];}
  else if(ver==5) for(tab=0;tab<55;tab++) { tabela[tab]=padrao[tab]; tabela1[tab]=tabms5[tab];}
        else if(ver==8) for(tab=0;tab<55;tab++) { tabela[tab]=padrao[tab]; tabela1[tab]=padrao[tab];}

 file('d', 'o', 'c', 0, pos);
 ident_fmt(in, ver);
 if (tam==0) {
 while(letra != EOF) {
		      tab=0;
		      letra = getc(in);
                      if (letra=='\xa6' || letra=='\xa7' || letra=='\xa8' || letra=='\xad' ||
                          letra=='\xae' || letra=='\xaf') {putc(letra,out); tab=2; continue;}
                      if (letra=='\xc4') {putc('\xc5',out); tab=2; continue;}
                      if (letra=='\xd2') {putc('\xa2',out); tab=2; continue;}
                      if (letra=='\xd3') {putc('\xa5',out); tab=2; continue;}
                      if (letra=='\xf9') {putc('\xf8',out); tab=2; continue;}

                      if (letra=='<') { tam--;
                                        while(letra!='>') { putc(letra,out);
                                                            letra=getc(in);
                                                            tam--;
                                                          }
                                       putc('>',out);
                                       continue;
                                      }

		      if (letra=='\r') { prox = getc(in);
					  if (prox=='\n') { putc('\r',out);
							    putc('\n',out);
							    ant=letra;
							    tab=2;
							    prox='\0';
							   }
					   else fseek(in,-1,SEEK_CUR);
					}
		      if (tab==0 && letra=='\r') { tab=2;}
		      if (tab==0 && isletra(letra)) { putc(letra,out); ant=letra; tab=2;}
		      if (tab==0) con_ac();
		      if (tab==1 && tabela[posi]!='\0') { putc(tabela[posi],out); ant=letra; tab=0;}
		     }
	     } else { while(tam > 0) {
		      tab=0;
		      letra = getc(in);
                      if(letra=='\x02') { tab=2; continue;}
                      if (letra=='\xa6' || letra=='\xa7' || letra=='\xa8' || letra=='\xad' ||
                          letra=='\xae' || letra=='\xaf') {putc(letra,out); ant=letra; tab=2; tam--; continue;}
                      if (letra=='\xc4' && ver!=8) {putc('\xc5',out); ant=letra; tab=2; tam--; continue;}
                      if (letra=='\xd2' && ver!=8) {putc('\xa2',out); ant=letra; tab=2; tam--; continue;}
                      if (letra=='\xd3' && ver!=8) {putc('\xa5',out); ant=letra; tab=2; tam--; continue;}
                      if (letra=='\xf9' && ver!=8) {putc('\xf8',out); ant=letra; tab=2; tam--; continue;}
		      if (letra==' ' && ant==' ') {tab=2; tam--;}
                      if (letra=='<') { tam--;
                                        while(letra!='>') { putc(letra,out);
                                                            letra=getc(in);
                                                            tam--;
                                                          }
                                        putc('>',out);
                                        continue;
                                      }
		      if (letra=='\r') { prox = getc(in);
					  if (prox=='\n') { putc('\r',out);
							    putc('\n',out);
							    ant=letra;
							    tab=2;
							    prox='\0';
							    tam-=2;
							   }
					   else fseek(in,-1,SEEK_CUR);
					}
		      if (tab==0 && letra=='\r') { tab=2; tam--;}
		      if (tab==0 && isletra(letra)) { putc(letra,out); tab=2; tam--; ant=letra;}
		      if (tab==0) con_ac();
		      if (tab==1 && tabela[posi]=='\0') { tam--; tab=2;}
		      if (tab==0) tam--; else if (tab==1) {putc(tabela[posi],out); tam--; ant=letra;}
		     }
		    }
 letra='\0';
 putc('\x1a',out);
 fcloseall();
}

void ident_fmt(FILE *in, int ver)
{
 int fmt=0;
 long tam1=0, tam2=0, c1=0, c2=0, c3=0, c4=0;
 if ((letra=getc(in))=='1') { if ((letra=getc(in))=='\xbe')
					{ fseek(in, 3, SEEK_CUR);
					  if ((letra=getc(in))=='\xab') fmt=1; else fseek(in, -6, SEEK_CUR);
					} else fseek(in, -2, SEEK_CUR);
			       } else fseek(in, -1, SEEK_CUR);
 if(ver==8)
 {
 if ((letra=getc(in))=='\xdb') { if ((letra=getc(in))=='\xa5')
					{ if((letra=getc(in))=='\x2d') fmt=2;
					} else fseek(in, -3, SEEK_CUR);
			       } else fseek(in, -1, SEEK_CUR);
 }

 if (fmt==1) { fseek(in, 8, SEEK_CUR);
	       c1=getc(in); c2=getc(in);
	       c3=getc(in); c4=getc(in);
	       if(c2>0) c2=c2*0x100;
	       tam1 = c1 + c2;
	       if(c3>0) c3*=0x100;
	       tam2 = (c3 + c4) * 0x100;
	       tam  = (tam1 + tam2) - 128;
	       fseek(in, 110, SEEK_CUR);
	     }
 if (fmt==2) { fseek(in, 52, SEEK_SET);
	       c1=getc(in); c2=getc(in);
	       if(c2>0) c2=c2*0x100;
	       tam1 = c1+c2;
	       tam = (tam1 +tam2) +0x100;
	       fseek(in, 384, SEEK_SET);
	     }
}