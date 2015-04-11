#include <stdio.h>
#include <stdlib.h>
#include "crisp.h"

#define TESTSIZE 0x5
#define DATSIZE (sizeof(float) * TESTSIZE)
#define FUNSIZE (sizeof(void (*)(void)) * TESTSIZE)
#define CRSSIZE (sizeof(crisp *) * TESTSIZE)

static float *xp;
static float *yp;
static float *zp;

static float *xr;
static float *yr;
static float *zr;
static float *wr;

void *xposaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &xp[ent];
	return 0;
}

void *yposaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &yp[ent];
	return 0;
}

void *zposaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &zp[ent];
	return 0;
}

void *xrotaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &xr[ent];
	return 0;
}

void *yrotaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &yr[ent];
	return 0;
}

void *zrotaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &zr[ent];
	return 0;
}

void *wrotaddr(unsigned int ent)
{
	if(--ent < TESTSIZE)
		return &wr[ent];
	return 0;
}

static crisp *glb, *cmd, *log;

typedef void (*upfun)(void);

upfun *update;

int main(int argc, char **argv)
{
	xp = (float *) malloc(DATSIZE);
	yp = (float *) malloc(DATSIZE);
	zp = (float *) malloc(DATSIZE);
	xr = (float *) malloc(DATSIZE);
	yr = (float *) malloc(DATSIZE);
	zr = (float *) malloc(DATSIZE);
	wr = (float *) malloc(DATSIZE);
	update = (void (**)(void)) malloc(FUNSIZE);
	
	glb = createcrispenv('\0');
	cmd = createcrispenv(glb);
	log = createcrispenv(glb);

	xp[0] = 0.1f;
	execfile(glb, "exectest.cr", 1);
	compfile(glb, "comptest.cr", 1);

	free(update);
	free(xp);
	free(yp);
	free(zp);
	free(xr);
	free(yr);
	free(zr);
	free(wr);
	cleancrispenv(log);
	cleancrispenv(cmd);
	cleancrispenv(glb);
	return 0;
}

