#include "silaba.h"
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <ctype.h>

void hifena(void);

char palavra[100], rec[5]="", hifen[100], e[100];
int cont=0, ppala=0, dg=0, qg=0, ao=0;

void hif(void)
{
 extern FILE *in,
             *out;
 extern char mat1[70],
          mat2[70];
 char letra='\0';
 int contl;

 if((in=fopen(mat2,"rb"))==NULL) { gotoxy(3,2); printf("Disco com problema");
                                   exit(0);
                                 }
 if((out=fopen("kjldsrup.mlw","wb"))==NULL) { gotoxy(3,2); printf("Disco com problema");
                                    exit(0);
                                  }
 cont=0; ppala=0; contl=0;

 letra=getc(in);
 while(letra!=EOF)
  {
   if(palavra[0]=='\0' && letra=='<') { putc(letra,out);
                                        while(letra!='>') { letra=getc(in);
                                                            if(letra==EOF) {letra='>';
                                                                            continue;
                                                                            }
                                                            putc(letra,out);
                                                          }
                                      } else
   if(vogal(letra) || consoante(letra)) palavra[contl++]=letra;
    else {
           if(palavra[0]=='\0') putc(letra,out);
             else { palavra[contl]='\0';
                    hifena();
                    palavra[0]='\0';
                    fseek(in,-1,SEEK_CUR);
                  }
           contl=0;
         }
   letra=getc(in);
  }
 if(palavra[0]=='\0') putc('\x1a',out);
 fcloseall();
 unlink(mat2);
 rename("kjldsrup.mlw", mat2);
}

void hifena(void)
{
 char f[6];
 int tam=0, extra, ex;
 extern FILE *out;

 cont=0; ppala=0, extra=0, ex=0;
 tam=strlen(palavra);
 strcpy(e,palavra);
 hifen[0]='\0';
 if(!vogal(e[0]) && !consoante(e[0])) {hifen[0]=e[0]; cont++;}
 while (cont < tam)
 {
  f[0]=toupper(e[cont]); f[1]=toupper(e[cont+1]); f[2]=toupper(e[cont+2]);
  f[3]=toupper(e[cont+3]); f[4]=toupper(e[cont+4]); f[5]=toupper(e[cont+5]);

  if(f[3]!='\0')
  {
   if (consoante(f[0])) rec[0]='C'; else if (vogal(f[0])) rec[0]='V';
   if (consoante(f[1])) rec[1]='C'; else if (vogal(f[1])) rec[1]='V';
   if (consoante(f[2])) rec[2]='C'; else if (vogal(f[2])) rec[2]='V';
   if (consoante(f[3])) rec[3]='C'; else if (vogal(f[3])) rec[3]='V';
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='C' && rec[3]=='V') {hyf(2); extra=0; continue; }
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='C' && rec[3]=='C') { if(dig(f[2],f[3])==1) hyf(2); else if(f[3]=='S' && f[2]!='S' && (consoante(f[4]) || f[4]=='\0')) hyf(4); else if(f[4]=='\0') hyf(4); else hyf(3); extra=0; continue; }
   if (rec[0]=='V' && rec[1]=='C' && rec[2]=='V') { if(cont==0) nohyf(1); else hyf(1); extra=0; continue; }
   if (rec[0]=='V' && rec[1]=='C' && rec[2]=='C' && rec[3]=='V') {
                                                                   if(dig(f[1],f[2])==1 && cont==0) nohyf(1);
                                                                    else if(dig(f[1],f[2])==1) hyf(1);
                                                                      else hyf(2); extra=0; continue; }
   if (rec[0]=='V' && rec[1]=='C' && rec[2]=='C' && rec[3]=='C') { if(dig(f[2],f[3])==1) hyf(2); else hyf(3); extra=0; continue; }
   if (rec[0]=='V' && rec[1]=='V' && rec[2]=='C' && rec[3]=='V') {hyf(2); extra=0; continue;}
   if (rec[0]=='V' && rec[1]=='V' && rec[2]=='C' && rec[3]=='C') {if(dig(f[2],f[3])==1) hyf(2); else hyf(3); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='V' && rec[3]=='C') { if(qu(f[0],f[1])==1 && consoante(f[3]) && vogal(f[4])) hyf(3);
                                                                    else if(qu(f[0],f[1])==1 && dig(f[3],f[4])) hyf(3);
                                                                    else if(qu(f[0],f[1])==1 && consoante(f[3]) & (consoante(f[4]) || f[4]=='\0')) hyf(4);
                                                                      else if(dit(f[1],f[2])==1 && dig(f[3],f[4])) hyf(3);
                                                                        else if(dit(f[1],f[2])==1 && consoante(f[3]) && vogal(f[4])) hyf(3);
                                                                          else hyf(4);
                                                                           extra=0; continue; }
   if (rec[0]=='C' && rec[1]=='C' && rec[2]=='V' && rec[3]=='V') { if(dit(f[2],f[3])==1 && consoante(f[4]) && (consoante(f[5]) || f[5]=='\0') && !dig(f[4],f[5])) hyf(5);
                                                                     else if(f[5]=='\0') hyf(5); else hyf(4); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='C' && rec[2]=='V' && rec[3]=='C') {if(dig(f[0],f[1])==1 && consoante(f[3])==1 && vogal(f[4])==1) hyf(3);
                                                                   else if(dig(f[0],f[1])==1 && dig(f[3],f[4])==1) hyf(3);
                                                                    else if(dig(f[0],f[1])==1 && consoante(f[4])==1 && consoante(f[5])==1) hyf(5);
                                                                    else if(dig(f[0],f[1])==1 && f[5]!='\0') hyf(4);
                                                                     else if(dig(f[0],f[1])==1 && f[5]=='\0') hyf(5);
                                                                      else if((f[3]=='S' || f[3]=='R') && (consoante(f[4]) || f[4]=='\0')) hyf(4);
                                                                        else if(f[4]=='\0') hyf(4);
                                                                          else hyf(3); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='V' && rec[3]=='V') {if((f[4]=='S' || f[4]=='R' || vogal(f[4])) && f[5]=='\0') hyf(5); else if(f[5]=='\0') hyf(5); else hyf(4); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='V') {if(til(f[1])==1 || dit(f[1],f[2])==1) hyf(3); else hyf(2); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='C' && rec[2]=='V') {hyf(3); extra=0; continue;}
   if (rec[0]=='C' && rec[1]=='V' && rec[2]=='C') {hyf(3); extra=0; continue;}
   fprintf(out,"<\\h>"); extra=cont; cont=tam; ex=1; break;
  } else break;
 }
 if(ex==1) {cont=extra;ex=0;}
 for (;cont<=tam;cont++) { hifen[ppala]=e[cont]; ppala++; }
 strset(e,'\0');
 tam=strlen(hifen);
 if(hifen[tam-1]=='\xfe') hifen[tam-1]='\0';
 fprintf(out,"%s",hifen);
}

int dig(char a, char b)
{
 if ((a=='B' && b=='L') || (a=='B' && b=='R') || (a=='C' && b=='H') ||
     (a=='C' && b=='L') || (a=='C' && b=='R') || (a=='D' && b=='R') ||
     (a=='F' && b=='L') || (a=='F' && b=='R') || (a=='G' && b=='L') ||
     (a=='G' && b=='R') || (a=='L' && b=='H') || (a=='N' && b=='H') ||
     (a=='P' && b=='L') || (a=='P' && b=='R') || (a=='T' && b=='R') ||
     (a=='T' && b=='L') || (a=='V' && b=='L') || (a=='V' && b=='R')) return(1); else return(0);
}

int qu(char a, char b)
{
 if ((a=='Q' || a=='G') && b=='U') return(1); else return(0);
}

int til(char a)
{
 if (a=='\xe3' || a=='\xf5' || a=='\xc3' || a=='\xd5') return(1); else return(0);
}

int dit(char a, char b)
{
 if(vogal(a) && vogal(b)) return(1); else return(0);
}

void hyf(int nu)
{
 int temp;
 for(temp=0;temp<nu;temp++) hifen[ppala++]=e[cont++];
 hifen[ppala++]='\xfe';
}

void nohyf(int nu)
{
 int temp;
 for(temp=0;temp<nu;temp++) hifen[ppala++]=e[cont++];
}
