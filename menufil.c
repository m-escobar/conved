#include "menufil.h"
#include <conio.h>
#include <errno.h>
#include <dos.h>
#include <dir.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>

void menu(void);
void j_ini(void);
void dir(void);
void mos_arq(void);
void def_max(void);
void inverte(int cond);
void letesp(void);
void arq_naoexiste(void);
void orig_dest(int modo);
void l_tela(void);
void help(void);
void marca_tudo(int tipo);
int  redir(void);
void cancela(void);
void matriz(int tag);

extern int narg;
extern char *varg[];
char mat[400][13],
     dest[2700]="",
     *ext;
int  arq=0, max_x=0, max_y=0, cpage, marca[400], narq, origem, destino, erro=0;

void menu(void)
{
 if (narg<2) ext="*.doc"; else ext=varg[1];
 j_ini();
 dir();
 if(erro==0) { mos_arq();
	       def_max();
	     }
 inverte(0);
 letesp();
 puttext(1, 5, 80, 20, dest);
}

void j_ini(void)
{
 int  linha;
 char linsup[] ="ÕÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¸",
      linmei[] ="³                                                                              ³",
      lininf[] ="ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´",
      linin1[] ="ÔÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¾";

 clrscr();
 window(1, 19, 80, 20);
 puttext(1, 19, 80, 19, linmei);
 puttext(1, 20, 80, 20, linin1);
 window(1, 5, 80, 19);
 puttext(1, 5, 80, 5, linsup);
 for (linha=6;linha<18;linha++) puttext(1, linha, 80, linha, linmei);
 puttext(1, 18, 80, 18, lininf);
 gotoxy(2, 2);
 textattr(BLACK);
 textbackground(LIGHTGRAY);
 cprintf("         Bureau Bandeirante - USO EXCLUSIVO         Vers„o: Julho 92          ");
 puttext(5 ,17,13,17,"Arquivo: ");
 puttext(30,17,39,17,"Total: 0  ");
 puttext(50,17,62,17,"Marcados: 0  ");
 puttext(69,17,77,17,"[F1] Help");
}

void dir(void)
{
 union REGS regs;
 struct ffblk ffblk;
 int nome=0;
 arq=0; errno=0;
 findfirst(ext, &ffblk, 1);
 if (errno != 0) { arq_naoexiste(); erro=1; return; }
 arq+=1;
 for (nome=0;nome<14;nome++) mat[arq][nome]=ffblk.ff_name[nome];
 do { findnext(&ffblk);
      if (errno != 0) { break; }
      arq+=1;
      for (nome=0;nome<14;nome++) mat[arq][nome]=ffblk.ff_name[nome];
    } while(errno == 0);
 qsort((void *)mat, arq+1, sizeof(mat[0]), sort_function);
 textattr(WHITE);
 textbackground(BLUE);
 gotoxy(37, 13); cprintf("%d  ",arq);
 gotoxy(4, 8);
 regs.h.ah=1;
 regs.h.ch=9;
 regs.h.cl=0;
 int86(0x10, &regs, &regs);
 cpage=1; erro=0;
}

void letesp(void)
{
 union scan { int c;
              char ch[2];
            } sc;

 int x=4, y=8, page, fim=0;

 origem=0; destino=8;
 orig_dest(2);
 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 inverte(0);
 do  {
      sc.c=getch();
      if((sc.ch[0]==0x20) || (sc.ch[0]==0x0D)) { inverte(1); sc.ch[1]=0; sc.ch[0]=77; }
      if((sc.ch[1]==0 && sc.ch[0]==72) && y==8) if (x > max_x) y=max_y; else y=max_y+1;
      if(sc.ch[1]==0 && sc.ch[0]==72) { inverte(0); y-=1;  gotoxy(x, y); inverte(0); } /*sobe*/
      if((sc.ch[1]==0 && sc.ch[0]==80) && y==max_y) y=7;
      if((sc.ch[1]==0 && sc.ch[0]==80) && y+1==max_y) if (x > max_x) y=7;
      if(sc.ch[1]==0 && sc.ch[0]==80) { inverte(0); y+=1;  gotoxy(x, y); inverte(0); } /*desce*/
      if((sc.ch[1]==0 && sc.ch[0]==77) && x==64) if (y!=max_y) { inverte(0); x=4; y++; gotoxy(x, y); inverte(0); sc.ch[0]=0; }
      if((sc.ch[1]==0 && sc.ch[0]==77) && y==max_y && x==max_x) sc.ch[0]=0;
      if(sc.ch[1]==0 && sc.ch[0]==77) { inverte(0); x+=15; gotoxy(x, y); inverte(0); } /*direita*/
      if((sc.ch[1]==0 && sc.ch[0]==75) && x==4 && y==8) sc.ch[0]=0;
      if((sc.ch[1]==0 && sc.ch[0]==75) && x==4) {y--; if (y==max_y) x=max_x+15; else x=79;}
      if(sc.ch[1]==0 && sc.ch[0]==75) {inverte(0); x-=15; gotoxy(x, y); inverte(0);} /*esquerda*/
      if(sc.ch[1]==0 && sc.ch[0]==71) {inverte(0); x=4; y=8; gotoxy(x, y); inverte(0);} /*home*/
      if(sc.ch[1]==0 && sc.ch[0]==79) {inverte(0); x=max_x; y=max_y; gotoxy(x, y); inverte(0);} /*end*/
      if(sc.ch[1]==0 && sc.ch[0]==73) if (cpage>1) { cpage--; l_tela(); mos_arq(); def_max(); x=4; y=8;} /*PgUp*/
      if(sc.ch[1]==0 && sc.ch[0]==81) if (cpage<page) { cpage++; l_tela(); mos_arq(); def_max(); x=4; y=8;} /*PgDn*/
      if(sc.ch[1]==0 && sc.ch[0]==0x3b) help();
      if(sc.ch[1]==0 && sc.ch[0]==0x3d) orig_dest(0);
      if(sc.ch[1]==0 && sc.ch[0]==0x3e) orig_dest(1);
      if(sc.ch[1]==0 && sc.ch[0]==0x3c) fim=1; else fim=0;
      if(sc.ch[1]==0 && sc.ch[0]==0x3f) if(narq!=arq) {marca_tudo(1); x=4; y=8;}
      if(sc.ch[1]==0 && sc.ch[0]==0x40) if(narq!=0) {marca_tudo(0); x=4; y=8;}
      if(sc.ch[1]==0 && sc.ch[0]==0x21) {page=redir(); x=4; y=8;}
      if(sc.ch[0]==0x1B) cancela();
      } while (fim==0);
}

void marca_tudo(int tipo)
{
 int x;
 if (tipo==0) { for(x=0;x<=400;x++) marca[x]=0;
                l_tela();
                mos_arq();
                def_max();
                gotoxy(4,8);
                narq=0;
              } else { for(x=0;x<=400;x++) marca[x]=1;
                       l_tela();
                       mos_arq();
                       def_max();
                       gotoxy(4,8);
                       narq=arq;
                     }
 gotoxy(60, 13); cprintf("%d   ",narq);
 gotoxy(4,8);
}

int redir(void)
{
 union REGS regs;
 char alet[2]=" o", let='\0',
      mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
      mold2[]="³o oNooovoao oMo osocoaoroao:o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o³o",
      mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";
 int x=0, c=0;
 *ext='\0';
 window(9, 10, 71, 12);
 puttext(9, 10, 71, 10, mold1);
 puttext(9, 11, 71, 11, mold2);
 puttext(9, 12, 71, 12, mold3);
 gotoxy(17,2);
 regs.h.ah=1;
 regs.h.ch=5;
 regs.h.cl=6;
 int86(0x10, &regs, &regs);
 for(c=0;c<45;c++) { x=0;
                     let=getch();
                     if(let=='\x0D') { *(ext+c)='\0'; break; }
		     if(let=='\b' && c==0) { c--; puttext(25,11,25,11," o"); gotoxy(17,2); x=1;
					   } else if(let=='\b' && x==0) { x=wherex(); gotoxy(x-1,2);
									  puttext(x+7,11,x+7,11," o");
									  x=1; c-=2;
									}
		     if(let=='\x1B') cancela();
		      else if(x==0 && let=='\0') {let=getch(); c--;}
			      else if(x==0) {x=wherex();
					     alet[0]=let;
					     puttext(x+8,11,x+8,11,alet);
					     *(ext+c)=let;
					     gotoxy(x+1,2);
					     x=0;
					    }
		     if(c==44) { c=-1; gotoxy(17,2);
				 puttext(25,11,69,11," o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o");
			       }
		  }
 regs.h.ah=1;
 regs.h.ch=9;
 regs.h.cl=0;
 int86(0x10, &regs, &regs);
 for(x=0;x<400;x++) marca[x]=0;
 narq=0; cpage=1;
 l_tela();
 dir();
 mos_arq();
 def_max();
 gotoxy(60,13); cprintf("%d   ",narq);
 gotoxy(4,8);
 if(arq%40!=0) return(arq/40+1); else return(arq/40);
}

void matriz(int tag)
{
 int posy=0, posx=0, x;
 posx = wherex();
 posy = wherey();
 switch (posx) { case  4: x=((cpage-1)*40)+1+((posy-8)*5); break;
		 case 19: x=((cpage-1)*40)+2+((posy-8)*5); break;
		 case 34: x=((cpage-1)*40)+3+((posy-8)*5); break;
		 case 49: x=((cpage-1)*40)+4+((posy-8)*5); break;
		 case 64: x=((cpage-1)*40)+5+((posy-8)*5); break;
               };
 if (tag==0) { marca[x]=0; narq--; } else { marca[x]=1; narq++; }
 gotoxy(60,13); cprintf("%d   ",narq); gotoxy(posx, posy);
}

void inverte(int cond)
{
 int posy=0, posx=0,
     cont, local, fim,
     cor1=0x1f, cor2=0x2f, cor3=0x30, cor4=0x70;
 char ch='\0',
      d_inv[30] = "",
      chr[3]="",
      name[3]="";

 posx = wherex();
 posy = wherey();
 if (cond!=1)
  { gettext(posx, posy, posx+11, posy, d_inv);
    if ( d_inv[1] == cor1) ch = cor2;
    if ( d_inv[1] == cor2) ch = cor1;
    if ( d_inv[1] == cor3) ch = cor4;
    if ( d_inv[1] == cor4) ch = cor3;
    cont=0; name[0]='\0';
    while (name[0]!='.') { name[0]=d_inv[cont];
                           if (name[0]=='.') { cont+=2; break; }
                           name[1]=cor1;
                           puttext(14+(cont/2), 17, 14+(cont/2), 17, name);
                           if (cont<18) cont+=2; else break;
                         }
    local=cont-2;
    if (local<21) { name[0]='\0'; name[1]=cor1;
                   for(;local<21;local+=2) puttext(14+(local/2), 17, 14+(local/2), 17, name);
                  }
    name[0]='.';
    puttext(22, 17, 22, 17, name);
    local=0; fim=cont+6;
    for(;cont<fim;cont+=2) { name[0]=d_inv[cont];
                            name[1]=cor1;
                            puttext(23+local, 17, 23+local, 17, name);
                            local++;
                          }

    for (cont=1;cont<24;cont+=2) d_inv[cont] = ch;
    puttext(posx, posy, posx+11, posy, d_inv);
  } else {  gettext(posx-1, posy, posx-1, posy, d_inv);
            if (d_inv[0]=='\x7') { chr[0]=' ';   chr[1]= cor1; matriz(0); }
                            else { chr[0]='\x7'; chr[1]= cor3; matriz(1); }
            puttext(posx-1, posy, posx-1, posy, chr);
            gettext(posx, posy, posx+11, posy, d_inv);
            if ( d_inv[1] == cor2) ch = cor4; else ch = cor2;
            for (cont=1;cont<24;cont+=2) d_inv[cont] = ch;
            puttext(posx, posy, posx+11, posy, d_inv);
         }
}

void def_max(void)
{
 int pos, page;
 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 if (arq<=40) pos=arq; else if (cpage!=page) pos=40;
                       else pos=arq%40;
 if (pos%5 == 0) max_y= 7 + (pos/5);
  else max_y= 8 + (pos/5);
 if (pos%5 == 0) max_x= 64;
  else max_x= 4 + ((arq%5-1)*15);
}

void arq_naoexiste(void)
{
 unsigned char e='\0',
               mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
               mold2[]="³o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o o³o",
               mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";

 puttext(24, 10, 55, 10, mold1);
 puttext(24, 11, 55, 11, mold2);
 puttext(24, 12, 55, 12, mold3);
 gotoxy(26, 7);
 cprintf("Arquivo nao existe tecle ESC");
 while(e != '\x1B') e = getch();
 redir();
}

void mos_arq(void)
{
 char marc[3]={'\x7','0','\0'},
      video[25]="";
 int page, x=4, y=4, ini=0, fim=0, loc=0;
 if(arq%40 != 0) page=arq/40+1; else page=arq/40;
 ini=((cpage-1)*40)+1;
 if(ini<=0) ini=1;
 if (cpage<page) fim=40*cpage; else fim=arq;
 if(fim==0) { if(arq<=40) fim=arq; else fim=40; }
 if (marca[ini]==1) { while(mat[ini][loc]!='\0') { video[loc*2]=mat[ini][loc];
						   video[loc*2+1]='0';
                                                   loc++;
                                                 }
		      while(loc<=11) { video[loc*2]=' ';
				       video[loc*2+1]='0';
                                       loc++;
                                     }
                      gotoxy(x, y);
                      puttext(x-1, y+4, x-1, y+4, marc);
                      puttext(x, y+4, x+11, y+4, video);
                      ini++; x+=15;
                    }
 while(ini <= fim)
  {
   loc=0;
   gotoxy(x, y);
   if (marca[ini]==1) { while(mat[ini][loc]!='\0') { video[loc*2]=mat[ini][loc];
						     video[loc*2+1]='0';
                                                     loc++;
                                                   }
                        while(loc<=11) { video[loc*2]=' ';
					 video[loc*2+1]='0';
                                         loc++;
                                       }
                        video[loc*2]='\0';
                        puttext(x-1, y+4, x-1, y+4, marc);
                        puttext(x, y+4, x+11, y+4, video);
		      } else cprintf("%s",mat[ini]);
   ini++;
   if (x == 64) { x=4; y++; } else { x+=15; }
  }
 gotoxy(4, 8);
 inverte(0);
}

void l_tela(void)
{
 window(3, 8, 75, 16);
 textbackground(BLUE);   
 clrscr();
 window(1, 5, 80, 19);
}

void orig_dest(int modo)
{
 char editor[10][37]={"Win Word          ",
	             "MS Word           ",
		     "P gina Certa      ",
		     "Redator PC        ",
                     "Ventura Publisher ",
                     "Word Star         ",
                     "Macintosh         ",
                     "MS Word 5         ",
                     "QuarkXpress - Mac ",
                     "QuarkXpress - Win ",
		    };
 union scan { int c;
              char ch[2];
            } sc;
 int filtro, fim=0;

 puttext(6,19,13,19,"Origem: ");
 puttext(48,19,56,19,"Destino: ");
 if (modo!=2) { if (modo==0) { filtro=origem;
                               puttext(33, 19, 33 ,19, "\x1b›");
                             } else { filtro=destino;
                                      puttext(76, 19, 76, 19, "\x1b›");
                                     }
		if(modo==1) do { sc.c=getch();       /* destino */
		     if(sc.ch[1]==0 && sc.ch[0]==71) filtro=2;
		     if(sc.ch[1]==0 && sc.ch[0]==79) filtro=9;
		     if(sc.ch[1]==0 && sc.ch[0]==72) if(filtro==2) filtro=2;
                                                      else if(filtro==6) filtro=2;
                                                       else if(filtro==8) filtro=6;
                                                        else if(filtro==9) filtro=8;
		     if(sc.ch[1]==0 && sc.ch[0]==80) if(filtro==9) filtro=9;
                                                      else if(filtro==8) filtro=9;
                                                       else if(filtro==6) filtro=8;
                                                        else if(filtro==2) filtro=6;
                     if(sc.ch[0]==0x1B) break;
		     if(sc.ch[0]==0x0D) fim=1;
		     if(modo==0) puttext(14,19,31,19,editor[filtro]);
			    else puttext(57,19,74,19,editor[filtro]);
                    } while (fim!=1);
		if(modo==0) do { sc.c=getch();       /* origem */
		     if(sc.ch[1]==0 && sc.ch[0]==71) filtro=0;
		     if(sc.ch[1]==0 && sc.ch[0]==79) filtro=9;
		     if(sc.ch[1]==0 && sc.ch[0]==72) if(filtro==0) filtro=0; else filtro--;
		     if(sc.ch[1]==0 && sc.ch[0]==80) if(filtro==9) filtro=9; else filtro++;
		     if(sc.ch[0]==0x1B) break;
		     if(sc.ch[0]==0x0D) fim=1;
		     if(modo==0) puttext(14,19,31,19,editor[filtro]);
			    else puttext(57,19,74,19,editor[filtro]);
                    } while (fim!=1);

                if (modo==0 && fim==1) origem=filtro;
                if (modo==1 && fim==1) destino=filtro;
              }
 puttext(14,19,31,19,editor[origem]);
 puttext(57,19,74,19,editor[destino]);
 puttext(33,19,33,19," ");
 puttext(76,19,76,19," ");
}

void cancela(void)
{
 union REGS regs;
 regs.h.ah=1;
 regs.h.ch=5;
 regs.h.cl=6;
 int86(0x10, &regs, &regs);
 window(1, 1, 80, 25);
 textbackground(BLACK);
 clrscr();
 exit(0);
}

int sort_function( const void *a, const void *b)
{
   return( strcmp((char *)a,(char *)b) );
}
