#include "menufil.h"
#include <stdio.h>
#include <ctype.h>

#define abre(c) ((c)=='<' || (c)=='\x2')
#define fecha(c) ((c)=='>' || (c)=='\x3')

extern char mat[400][13],
	    padrao[55],
	    letra,
	    ant;
extern int  posi,
	    tab,
	    ets,
	    px;

void padrao_a(int modo, int pos, int edit)
{
 extern FILE *in,
             *out;
 extern char mat1[70],
             mat2[70];
 char prox='\0';
 int jtab=0;
 if(edit==0) file('t', 'e', 'x', modo, pos);
      else if(edit==1) { file('d', 'o', 'c', modo, pos);
                         fseek(in,128,SEEK_CUR);
                       } else file('t','x','t', modo, pos);

 ant='\0';
 while(letra!=EOF)  {
		      tab=0;
		      letra=getc(in);
                      if(letra!=' ') jtab=0;
                      if(letra=='\x2') letra='<';
                      if (letra=='<') { letra=toupper(getc(in));
                                         if((letra=='I' || letra=='F')) { letra=toupper(getc(in));
                                                                          prox=getc(in);
                                                                          if(prox=='\x3') prox='>';
                                                                          if(prox=='>') { if(letra=='I') fprintf(out,"<I>"); tab=2;
                                                                                                       if(letra=='N') fprintf(out,"<B>"); tab=2;
                                                                                                       if(letra=='S') fprintf(out,"<U>"); tab=2;
                                                                                                     } else { fseek(in,-3,SEEK_CUR);
                                                                                                              putc('<',out);
                                                                                                              tab=2;
                                                                                                            }
                                                                        } else { putc('<',out);
                                                                                 fseek(in,-1,SEEK_CUR);
                                                                                 continue;
                                                                               }
                                      }
//                      if (abre(letra)) {putc(letra,out);tab=2;}
                      if (letra==' ' && ant==' ' && edit==2 && jtab==0) {letra='\t';jtab=1;}
		      if (letra=='\n') tab=2;
		      if (letra=='\r') { prox = getc(in);
					  if (prox=='\n') { putc('\r',out);
							    putc('\n',out);
							    tab=2;
							    ant=letra;
							    prox='\0';
							   }
					   else { tab=2; fseek(in,-1,SEEK_CUR);}
					}
		      if (tab==0 && isletra(letra)) { putc(letra,out); ant=letra; tab=2;}
		      if (tab==0) con_cv();
		      if (tab==1 && padrao[posi]!='\0') {putc(padrao[posi],out); ant=letra;}
		     }
 letra='\0';
 fputc('\x1a',out);
 fcloseall();
 if (modo==1) remove(mat1);
}

void con_cv(void)
{
  for (posi=0;posi<55;posi++)
   if (letra==padrao[posi]) { tab=1; return; }
}
