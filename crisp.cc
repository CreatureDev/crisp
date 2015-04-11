#include "crisp.hh"
#include <fstream>
#include "crast.hh"

typedef void *(*addreqfun)(unsigned int);	

std::string crisp::spaceparen(const char *in)
{
	std::string ret = std::string(in);
	std::string::iterator it = ret.begin();
	if(*(it+1) != ' ')
		it = ret.insert(it+1, ' ') - 1;
	it++;
	for(; it != ret.end(); it++)
	{
		if(*it == '(')
		{
			if(*(it+1) != ' ')
				it = ret.insert(it+1, ' ') - 1;
			if(*(it-1) != ' ')
				it = ret.insert(it, ' ') + 1;
		}
		else
		if(*it == ')')
		{
			if(*(it+1) != ' ')
				it = ret.insert(it+1, ' ') - 1;
			if(*(it-1) != ' ')
				it = ret.insert(it, ' ') + 1;
		}
	}
	return ret;
}

std::vector<char *> *crisp::gettokens(std::vector<std::string> *in)
{
	char *str, *tok;
	unsigned int i, j;
	std::vector<char *> *ret = new std::vector<char *>();
	for(i = 0, j = 0; i < in->size(); i++)
	{
		j += (*in)[i].length() + 1;
	}
	str = new char[j];
	std::strcpy(str, (*in)[0].c_str());
	if(str[0] != '(')
	{
		delete ret;
		delete[] str;
		return 0;
	}
	for(i = 1; i < in->size(); i++)
	{
		std::strcat(str, " ");
		std::strcat(str, (*in)[i].c_str());
	}
	tok = std::strtok(str, " ");
	while(tok)
	{
		if(std::strlen(tok))
			ret->push_back(tok);
		tok = std::strtok(0, " ");
	}
	return ret;
}

void crisp::freetokens(std::vector<char *> *ded)
{
	if(!ded->empty())
	{
		delete[] (*ded)[0];
	}
	delete ded;
}

void crisp::parseexecstring(const char *str, unsigned int id)
{

}

void crisp::parsecompstring(const char *str, unsigned int id)
{

}

void crisp::parseexecfile(const char *fil, unsigned int id)
{
	char *lb = new char[256];

	std::ifstream fst;
	std::vector<std::string> *lvc;
	std::vector<char *> *toks;
	crast *ast;
	lvc = new std::vector<std::string>();
	fst.open(fil, std::ifstream::in);
	fst.getline(lb, 256);
	while(fst.good())
	{
		lvc->push_back(spaceparen(lb));
		fst.getline(lb, 256);
	}
	fst.close();	
	delete[] lb;
	
	toks = gettokens(lvc);
	delete lvc;
	if(!toks)
	{
		std::cout << "script must begin with a '('" << std::endl;
		return;
	}
	std::vector<char *>::iterator it;
	it = toks->begin();
	ast = new crast(toks, it);
	delete ast;
	freetokens(toks);

}

void crisp::parsecompfile(const char *fil, unsigned int id)
{
	int i = 0;
	char lb[256];
	std::ifstream fst;
	fst.open(fil, std::ifstream::in);
	fst.getline(lb, 256);
	while(fst.good())
	{
		++i;
		fst.getline(lb, 256);
	}
	fst.close();
}

crisp::crisp() :
cnt(llvm::getGlobalContext()), irb(cnt)
{

	upr = 0;
	addglobalsyms();
}

crisp::crisp(crisp *p) :
cnt(llvm::getGlobalContext()), irb(cnt)
{

	upr = p;
}

crisp::~crisp()
{
	if(upr)
		return;
	irb.~IRBuilder<>();
	cnt.~LLVMContext();
}

void crisp::addglobalsyms()
{
	
}

extern "C"
{

crisp *createcrispenv(crisp *parent)
{
	crisp *ret;
	if(parent)
		ret = new crisp(parent);
	else
		ret = new crisp();
	return ret;
}

void cleancrispenv(crisp *ded)
{
	delete ded;
}

void execfile(crisp *cr, const char *fin, unsigned int id)
{
	cr->parseexecfile(fin, id);
}

void compfile(crisp *cr, const char *fin, unsigned int id)
{
	cr->parsecompfile(fin, id);
}

}

