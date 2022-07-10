#define vogal(c) (((c)>='\xc0' && (c)<='\xc4') || ((c)>='\xc8' && (c)<='\xcf') || \
		  ((c)>='\xd2' && (c)<='\xd6') || ((c)>='\xd9' && (c)<='\xdc') || \
		  ((c)>='\xe0' && (c)<='\xe4') || ((c)>='\xe8' && (c)<='\xef') || \
		  ((c)>='\xf2' && (c)<='\xf6') || ((c)>='\xf9' && (c)<='\xfc') || \
		  (c)=='a' || (c)=='e' || (c)=='i' || (c)=='o' || (c)=='u' || \
		  (c)=='A' || (c)=='E' || (c)=='I' || (c)=='O' || (c)=='U')
#define consoante(c) (((c)>='A' && (c)<='Z' || (c)>='a' && (c)<='z' || (c)=='\xe7' || (c)=='\xc7') && ! vogal(c))

void hyf(int nu);
void nohyf(int nu);
int vrec   (char a, char b, char c, char d);
int dig    (char a, char b);
int qu     (char a, char b);
int til    (char a);
int dit    (char a, char b);
void cvcv  (void);
void cvcc  (void);
void vcv   (void);
void vccv  (void);
void vccc  (void);
void vvcv  (void);
void vvcc  (void);
void cvvc  (void);
void ccvv  (void);
void ccvc  (void);
void cvvv  (void);
void cvv   (void);
void ccv   (void);
void cvc   (void);
