#ifndef __CRISP_HH__
#define __CRISP_HH__
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

class crast;
class symtable;
typedef void (*upfun)();

class crisp
{
public:
	crisp();
	crisp(crisp *);
	~crisp();
	void parseexecfile(const char *, unsigned int);
	void parseexecstring(const char *, unsigned int);
	void parsecompfile(const char *, unsigned int);
	void parsecompstring(const char *, unsigned int);

private:
	crisp *upr;
	std::map<unsigned int, symtable *> tbls;	
	llvm::Module *mod;
	llvm::LLVMContext& cnt;
	llvm::IRBuilder<> irb;
	
	void addglobalsyms();
	std::string spaceparen(const char *);
	std::vector<char *> *gettokens(std::vector<std::string> *);
	void freetokens(std::vector<char *> *);

};

#endif

