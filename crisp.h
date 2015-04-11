#ifndef __CRSIP_H__
#define __CRISP_H__


typedef struct crisp crisp;
typedef void (*upfun)(void);

crisp *createcrispenv(crisp *);
void cleancrispenv(crisp *);
void execfile(crisp *, const char *, unsigned int);
void compfile(crisp *, const char *, unsigned int);

#endif

