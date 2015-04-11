#ifndef __SYMTABLE_HH__
#define __SYMTABLE_HH__
#include <map>

typedef struct symval symval;

enum symtype
{
	ADDRFUNC,
	LIBFUNC,
	GADDR,
	GFUNC,
	LFUNC,
	GVAL,
	LVAL,
	LTYPE,
};

struct symval
{
	
};

class symtable
{
public:
	~symtable();
	symtable();
	
private:
	std::map<std::string, symval *> syms;
}

#endif /* symtable.hh */

