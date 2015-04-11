#ifndef __CRAST_HH__
#define __CRAST_HH__

#include <vector>
#include <cstring>
#include <iostream>

enum asttype
{
	NIL,
	ERROR,
	SYMBOL,
	INT,
	FLOAT,
	STRING,
	LIST,
	ADDOP,
	SUBOP,
	MULOP,
	DIVOP,
	LETOP,
	DEFOP
};

class crast
{
public:
	crast(std::vector<char *> *, std::vector<char *>::iterator &);
	crast(char *);
	~crast();
	asttype type;
	char *val;
	void pcrast();
	std::vector<crast *> chil;


private:
	asttype validnumtype(char *);
};

#endif

