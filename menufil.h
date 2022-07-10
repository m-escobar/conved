#define isletra(c) (((c)>31 && (c)<123 && (c)!=60 && (c)!=62 && (c)!=92) || (c)==126)

#define just 0
#define esqu 1
#define dire 2
#define cent 3

struct PARAM   { int fonte;
                 int nfonte;
                 int alinhamento;
                 int justif;
                 char corpo[20];
                 char entrelinha[20];
                 char esq[20];
                 char dir[20];
                 char fline[20];
               };

void file(char e1, char e2, char e3, int modo, int pos);
void con_cv(void);
void con_ac(void);
int sort_function( const void *a, const void *b);