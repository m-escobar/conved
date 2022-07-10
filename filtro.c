#include "menufil.h"
#include "tabela.h"
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <process.h>
#include <ctype.h>

void menu(void);
int  parametros(void);
void filtra(int pos);
void fim(void);
void padrao_a(int modo, int pos, int edit);
void ventura_pub(int modo, int pos);
void ms_word(int ver, int pos);
void w_star(int modo, int pos);
void mc(int modo, int pos);
void quark(int modo, int pos);
void copia_quark(int pos);

extern void hif(void);
struct PARAM param;
char fonte[13][17]={ "AvantGarde-Book ",
                     "Bodoni          ",
                     "Bodoni-Book     ",
                     "FranklinGotBook ",
                     "FranklinGotRoman",
                     "Futura          ",
                     "Futura-Book     ",
                     "Garamond-Light  ",
                     "Helvetica       ",
                     "HelveticaNeueMed",
                     "HelveticaNeueRom",
                     "Times-Roman     ",
                     "TimesTen-Roman  "
                  };

enum editor { Win_Word,
              MS_Word,
              Pagina_Certa,
              Red_PC,
              Ventura_Pub,
              W_Star,
              Mac,
              MS_Word5,
              QXpress,
              QXWin
         };

FILE *in,
     *out;
char *varg[5],
     pont[20],
     video[200]="",
     mat1[70]="",
     mat2[70]="",
     tabela[55]="",
     tabela1[55]="",
     letra='\0',
     ant='\0';
int  posi=0,
     tab=0,
     ets=0,
     px=0,
     narg;
static int pos;

void main(int argc, char *argv[])
{
 extern int marca[400],
            arq, destino;
 narg=argc;
 varg[1]=argv[1];
 menu();
 clrscr();
 if(destino==QXpress || destino==QXWin) parametros();
 for(pos=1;pos<=arq;pos++) if(marca[pos]==1) filtra(pos);
 fim();
}

void filtra(int pos)
{
 extern char mat[400][13];
 extern int origem,
            destino;
 char label[2]=" o";
 int loc=0;
 char mold1[]="ÕoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¸o",
      mold2[]="³o oFoiolotoroaonodooo:o o o o o o o o o o o o o o o o o o o o³o",
      mold3[]="ÔoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍoÍo¾o";
 window(24, 20, 56, 22);
 puttext(24, 20, 55, 20, mold1);
 puttext(24, 21, 55, 21, mold2);
 puttext(24, 22, 55, 22, mold3);
 while(mat[pos][loc]!='\0') { label[0]=mat[pos][loc];
                              puttext(37+loc,21,37+loc,21,label);
                              loc++;
                            }

 switch(origem)  {  case Win_Word     : ms_word(8, pos); break;
                    case Ventura_Pub  : ventura_pub(0, pos); break;
                    case Pagina_Certa : padrao_a(0, pos, 0); break;
                    case MS_Word      : ms_word(3, pos); break;
                    case Red_PC       : padrao_a(0, pos, 1); break;
                    case W_Star       : w_star(0, pos); break;
                    case Mac          : mc(0,pos); break;
                    case MS_Word5     : ms_word(5, pos); break;
                    case QXWin        : copia_quark(pos); break;
                }
 switch(destino) {  case Ventura_Pub  : ventura_pub(1, pos); break;
                    case Pagina_Certa : padrao_a(1, pos, 0); break;
                    case Mac          : mc(1,pos); break;
                    case QXpress      : quark(1,pos); break;
                    case QXWin        : quark(0,pos); break;
                 }
}

void fim(void)
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

void file(char e1, char e2, char e3, int modo, int pos)
{
 extern char mat[400][13],
             *ext;
 int x, tab=0, last=0;

 strset(mat1,'\x0');
 strset(mat2,'\x0');
 mat1[0]='\x0';
 if(varg[1]==NULL) varg[1]=ext;
 last=strlen(varg[1]);
 px=last;
 for(;last>0;last--) if(varg[1][last]=='\\') {tab=1; break; }
 if(tab==0) { last=px; px=0;
              for(;last>0;last--) if(varg[1][last]==':') break;
         } else px=0;
 if(last>0) for(px=0;px<=last;px++) mat1[px]=varg[1][px];
 for(x=0;x<px;x++) mat2[x]=mat1[x];
 x=0;
 do { mat1[px]=mat[pos][x];
      mat2[px]=mat[pos][x];
      x++; px++;
      if(mat[pos][x]=='\x0') { ets=1; break; }
    } while(mat[pos][x]!='.');

 if (modo==0 && ets==1) { tab=px; for (;tab<13;tab++) mat1[tab]='\0';
                        } else if (modo==0 && ets==0) { mat1[px]='.'; mat1[px+1]=mat[pos][x+1]; mat1[px+2]=mat[pos][x+2]; mat1[px+3]=mat[pos][x+3]; }
 if (modo==0) { mat2[px]='.'; mat2[px+1]='f'; mat2[px+2]='i'; mat2[px+3]='l';
              } else
              { mat1[px]='.'; mat1[px+1]='f'; mat1[px+2]='i'; mat1[px+3]='l';
                mat2[px]='.'; mat2[px+1]=e1; mat2[px+2]=e2; mat2[px+3]=e3;
              }
 for (px+=4;px<70;px++) { if(ets==0) mat1[px]='\0';
                          mat2[px]='\0';
                        }
 if((in=fopen(mat1,"rb"))==NULL) { gotoxy(3, 2); printf("Disco com problema");
                         exit(-1);
                       }
 if((out=fopen(mat2,"wb"))==NULL) { gotoxy(3, 2); printf("Disco com problema");
                                     exit(-1);
                                   }
}

void help(void)
{
 int x, y;
 char help[4001], e='\0';
 x=wherex(); y=wherey();
 window(1, 1, 80, 25);
 gettext(1, 1, 80, 25, help);
 puttext(1,1,80,1,"ÉOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOËOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO»O");
 puttext(1,2,80,2,"ºO O O O O O O O O O OCOoOnOtOrOoOlOeO OdOoO OCOuOrOsOoOrO O O O O O O O O O O O OºO O O O O O O O O O O O OTOeOcOlOaOsO OCOoOmOuOnOsO O O O O O O O O O O O OºO");
 puttext(1,3,80,3,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,4,80,4,"ºO O\x1aO O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OdOiOrOeOiOtOaO O O O O OºO OEOsOpOaO‡OoO O O-O OMOaOrOcOaO/ODOeOsOmOaOrOcOaO OuOmO OaOrOqOuOiOvOoO OºO");
 puttext(1,5,80,5,"ºO O\x1bO O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OeOsOqOuOeOrOdOaO O O O OºO OROeOtOoOrOnOoO O-O OMOaOrOcOaO/ODOeOsOmOaOrOcOaO OuOmO OaOrOqOuOiOvOoO OºO");
 puttext(1,6,80,6,"ºO O\x18O O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO OcOiOmOaO O O O O O O O OºO OEOsOcO O O O O O-O OCOaOnOcOeOlOaO OfOuOnO‡O„OoO O O O O O O O O O O O OºO");
 puttext(1,7,80,7,"ºO O\x19O O O O O O-O OMOoOvOeO OoO OcOuOrOsOoOrO OpOaOrOaO ObOaOiOxOoO O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,8,80,8,"ºO OHOoOmOeO O O-O OPOoOsOiOcOiOoOnOaO OnOoO OpOrOiOmOeOiOrOoO OaOrOqOuOiOvOoO O OÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O");
 puttext(1,9,80,9,"ºO OEOnOdO O O O-O OPOoOsOiOcOiOoOnOaO OnOoO O£OlOtOiOmOoO OaOrOqOuOiOvOoO O O O OºO O O O O O O O OEOdOiOtOoOrOeOsO ODOiOsOpOoOnO¡OvOeOiOsO O O O O O O O O OºO");
 puttext(1,10,80,10,"ºO OPOgO OUOpO O-O OAOvOaOnO‡OaO OpO OgOiOnOaO O O O O O O O O O O O O O O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,11,80,11,"ºO OPOgO ODOnO O-O OROeOtOrOoOcOeOdOeO OpO OgOiOnOaO O O O O O O O O O O O O O O OºO O O_O OCOaOrOtOaO OCOeOrOtOaO O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,12,80,12,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O_O OMOaOcOiOtOoOsOhO O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,13,80,13,"ÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O O O_O OMOsO OWOoOrOdO O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,14,80,14,"ºO O O O O O O O O O O OTOeOcOlOaOsO OdOeO OFOuOnO‡O”OeOsO O O O O O O O O O O O OºO O O_O OMOsO OWOoOrOdO O5O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,15,80,15,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO O O_O OPO OgOiOnOaO OCOeOrOtOaO O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,16,80,16,"ºO OFO1O O O O O-O OMOoOsOtOrOaO OeOsOtOeO OHOeOlOpO O O O O O O O O O O O O O O OºO O O_O OQOuOaOrOkO OXOpOrOeOsOsO O-O OMOaOcO O O O O O O O O O O O O O O OºO");
 puttext(1,17,80,17,"ºO OFO2O O O O O-O OFOiOlOtOrOaO OoOsO OaOrOqOuOiOvOoOsO OmOaOrOcOaOdOoOsO O O O OºO O O_O OQOuOaOrOkO OXOpOrOeOsOsO O-O OWOiOnO O O O O O O O O O O O O O O OºO");
 puttext(1,18,80,18,"ºO OFO3O O O O O-O OMOuOdOaO OoO OEOdOiOtOoOrO OOOrOiOgOeOmO O O O O O O O O O O OºO O O_O OROeOdOaOtOoOrO OPOCO O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,19,80,19,"ºO OFO4O O O O O-O OMOuOdOaO OoO OEOdOiOtOoOrO ODOeOsOtOiOnOoO O O O O O O O O O OºO O O_O OVOeOnOtOuOrOaO OPOuObOlOiOsOhOeOrO O O O O O O O O O O O O O O O OºO");
 puttext(1,20,80,20,"ºO OFO5O O O O O-O OMOaOrOcOaO OtOoOdOoOsO OoOsO OaOrOqOuOiOvOoOsO O O O O O O O OºO O O_O OWOoOrOdO OSOtOaOrO O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,21,80,21,"ºO OFO6O O O O O-O ODOeOsOmOaOrOcOaO OtOoOdOoOsO OoOsO OaOrOqOuOiOvOoOsO O O O O OºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(1,22,80,22,"ºO OAOLOTO OFO O-O OMOuOdOaO OaO OmO OsOcOaOrOaO OdOoOsO OaOrOqOuOiOvOoOsO O O O OÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O");
 puttext(1,23,80,23,"ºO O O O O O O O O O OmOoOsOtOrOaOdOoOsO O O O O O O O O O O O O O O O O O O O O OºO OPOrOoOgOrOaOmOaOdOoOrO:O OEOsOcOoObOaOrO O1O0O/O0O4O/O9O1O O O O O O O OºO");
 puttext(1,24,80,24,"ÈOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÊOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¼O");
 while(e=='\0') e=getch();
 puttext(1, 1, 80, 25, help);
 window(1, 5, 80, 19);
 gotoxy(x,y);
}

void con_ac(void)
{
 extern int tab;
 extern char tabela1[55];
 for (posi=0;posi<55;posi++)
  if (letra==tabela1[posi]) { tab=1; return; }
}

void id_acento(char letra1)
{
 extern char tabws[55][4],
             tabws1[55][4];

 char palavra[4], let='\0';
 int x;
 palavra[0]=letra;  palavra[1]='\b';
 if(letra1=='\x79' && letra1<='\xff') let = letra1 & '\x7f'; else let = letra1;
 palavra[2]=let;
 palavra[3]='\0';

 for (posi=0;posi<55;posi++)
  { for (x=0;x<3;x++) if (palavra[x]==tabws[posi][x]) tab=1; else { tab=0; break; }
    if (tab==1 && x==3) break;
  }

 if(tab==0) for (posi=0;posi<55;posi++)
             { for (x=0;x<3;x++) if (palavra[x]==tabws1[posi][x]) tab=1; else { tab=0; break; }
               if (tab==1 && x==3) break;
             }
}

int pega(void)
{
 switch(toupper(getch())) { case '+': return(0);
                            case '-': return(1);
                            case '\r': return(2);
                          }
 return(0);
}

void invnome(int cx, int cy, int mod)
{
 char vid[36], car;
 int tempo;

 gettext(cx,cy,cx+18,cy,vid);
 if(mod==0) car='o'; else car='O';
 for(tempo=1;tempo<36;tempo+=2) vid[tempo]=car;
 vid[36]='\0';
 puttext(cx,cy,cx+18,cy,vid);
}

void entraval(int cx, int cy)
{
 union REGS regs;
 char alet[2]=" o", let='\0', video[36];
 int x=0, c=0;
 *pont='\0';
 window(cx, cy, cx+18, cy);
 textbackground(RED);
 clrscr();
 gotoxy(1,1);
 gettext(cx,cy,cx+18,cy,video);
 for(c=1;c<36;c+=2) video[c]='o';
 puttext(cx,cy,cx+18,cy,video);
 regs.h.ah=1; regs.h.ch=5; regs.h.cl=6;
 int86(0x10, &regs, &regs);
 for(c=0;c<19;c++) { x=0;
                     let=getch();
                     while((let<'0' || let>'9') && let!='\b' && let!='\x1B' && let!='.' && let!='\r') let=getch();
                     if(let=='\x0D') { pont[c]='\0'; break; }
               if(let=='\b' && c==0) { c--; puttext(cx,cy,cx,cy," o"); gotoxy(cx,cy); x=1;
                            } else if(let=='\b' && x==0) { x=wherex(); gotoxy(c,1);
                                               puttext(cx+c-1,cy,cx+c-1,cy," o");
                                               x=1; c-=2;
                                             }
               if(let=='\x1B') {pont[0]='\0';c=19;}
                else if(x==0 && let=='\0') {let=getch(); c--;}
                     else if(x==0) {x=wherex();
                              alet[0]=let;
                              puttext(c+cx,cy,c+cx,cy,alet);
                              pont[c]=let;
                              gotoxy(c+2,1);
                              x=0;
                             }
               if(c==18) { c=-1; gotoxy(1,1);
                     puttext(cx,cy,cx+18,cy," o o o o o o o o o o o o o o o o o o");
                      }
            }
 regs.h.ah=1;
 regs.h.ch=9;
 regs.h.cl=0;
 int86(0x10, &regs, &regs);
 gettext(cx,cy,cx+18,cy,video);
 for(c=0;c<35;c+=2) {video[c]=' '; video[c+1]='O';}
 video[36]='\0';
 puttext(cx,cy,cx+18,cy,video);
 window(1,1,80,25);
}

int parametros(void)
{
 char temp='\0', alinhamento[][13]= {"justificado ","esquerda    ","direita     ","centralizado"};
 int itemp=0;
 window(1,1,80,25);
 clrscr();
 puttext(20,5,60,5,"ÉOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO»O");
 puttext(20,6,60,6,"ºO O O O O O O O O OPOaOrOaOmOeOtOrOoOsO OdOoO OTOeOxOtOoO O O O O O O O O O O OºO");
 puttext(20,7,60,7,"ÌOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¹O");
 puttext(20,8,60,8,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,9,60,9,"ºO OF oOnOtOeO:O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,10,60,10,"ºO OC oOrOpOoO:O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,11,60,11,"ºO OE nOtOrOeOlOiOnOhOaO:O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,12,60,12,"ºO OA lOiOnOhOaOmOeOnOtOoO:O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,13,60,13,"ºO ODOeOfOeOsOaO:O OEOs qOuOeOrOdOaO:O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,14,60,14,"ºO O O O O O O O O OD iOrOeOiOtOaO:O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,15,60,15,"ºO O O O O O O O O O1O¦OL iOnOhOaO:O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,16,60,16,"ºO OH iOfOeOnOaOrO:O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,17,60,17,"ºO O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O OºO");
 puttext(20,18,60,18,"ÈOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍOÍO¼O");

 param.fonte=11; strcpy(param.corpo,"10"); strcpy(param.entrelinha,"12"); param.alinhamento=just;
 strcpy(param.esq,"0"); strcpy(param.dir,"0"); strcpy(param.fline,"0"); param.justif=1; param.nfonte=13;

 gotoxy(29,9); printf("%s",fonte[param.fonte]);
 gotoxy(29,10); printf("%s",param.corpo);
 gotoxy(34,11); printf("%s",param.entrelinha);
 gotoxy(35,12); printf("%s",alinhamento[param.alinhamento]);
 gotoxy(40,13); printf("%s",param.esq);
 gotoxy(40,14); printf("%s",param.dir);
 gotoxy(40,15); printf("%s",param.fline);
 gotoxy(31,16); if(param.justif==0) printf("N„o"); else printf("Sim");

 while(temp!='\r') { temp=getch();
                     switch(toupper(temp)) { case 'F': invnome(29,9,0);
                                                       while((itemp=pega())!=2) { if(itemp==0 && param.fonte<param.nfonte-1) param.fonte++;
                                                                                   else if(itemp==1 && param.fonte>0) param.fonte--;
                                                                                  gotoxy(29,9);
                                                                                  printf("%s",fonte[param.fonte]);
                                                                                }
                                                       invnome(29,9,1);
                                                       break;
                                             case 'C': entraval(29,10);
                                                       if(pont[0]!='\0') strcpy(param.corpo,pont);
                                                       gotoxy(29,10);
                                                       printf("%s",param.corpo);
                                                       break;
                                             case 'E': entraval(34,11);
                                                       if(pont[0]!='\0') strcpy(param.entrelinha,pont);
                                                       gotoxy(34,11);
                                                       printf("%s",param.entrelinha);
                                                       break;
                                             case 'A': invnome(35,12,0);
                                                       while((itemp=pega())!=2) { if(itemp==0 && param.alinhamento<3) param.alinhamento++;
                                                                                   else if(itemp==1 && param.alinhamento>0) param.alinhamento--;
                                                                                  gotoxy(35,12);
                                                                                  printf("%s",alinhamento[param.alinhamento]);
                                                                             }
                                                       invnome(35,12,1);
                                                       break;
                                             case 'S': entraval(40,13);
                                                       if(pont[0]!='\0') strcpy(param.esq,pont);
                                                       gotoxy(40,13);
                                                       printf("%s",param.esq);
                                                       break;
                                             case 'D': entraval(40,14);
                                                       if(pont[0]!='\0') strcpy(param.dir,pont);
                                                       gotoxy(40,14);
                                                       printf("%s",param.dir);
                                                       break;
                                             case 'L': entraval(40,15);
                                                       if(pont[0]!='\0') strcpy(param.fline,pont);
                                                       gotoxy(40,15);
                                                       printf("%s",param.fline);
                                                       break;
                                             case 'H': gotoxy(31,16); if(param.justif==1) { param.justif=0; printf("N„o"); }
                                                                       else { param.justif=1; printf("Sim"); }
                                                       break;
                                             case '\x1b': return(1);
                                           }
                   }
 return(0);
}

void copia_quark(int pos)
{
 char letra='\x0';

 file('o', 'u', 't', 0, pos);
 while(letra!=EOF)
                  {
                    letra=getc(in);
                    putc(letra,out);
                  }
 putc('\x1a',out);
 fcloseall();
}
