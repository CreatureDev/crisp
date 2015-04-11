#include "crast.hh"

crast::crast(std::vector<char *> *tok, std::vector<char *>::iterator &it)
{	
	if(it == tok->end())
	{
		val = '\0';
		type = ERROR;
		return;
	}
	type = NIL;
	val = (*it);
	switch(std::strlen(*it))
	{
	case 1:
		switch((*it)[0])
		{
		case '+':
			type = ADDOP;
			it++;
			break;
		case '-':
			type = SUBOP;
			it++;
			break;
		case '/':
			type = DIVOP;
			it++;
			break;
		case '*':
			type = MULOP;
			it++;
			break;
		}
		break;
	case 3:
		if(!std::strcmp((*it), "let"))
		{
			type = LETOP;
			it++;
		}
		break; 
	case 4:
		if(!std::strcmp((*it), "defv"))
		{
			type = DEFOP;
			it++;
		}
		break;
	}
	if(type == NIL)
		type = LIST;	
	while(it != tok->end() && (*it)[0] != ')')
	{
		if((*it)[0] == '(')
		{
			it++;
			chil.push_back(new crast(tok, it));
		}
		else
		{
			chil.push_back(new crast(*it));
			it++;
		}
		if(chil.back()->type == ERROR)
		{
			type = ERROR;
			return;
		}
	}
	if(it != tok->end())
		it++;
	if(type != LIST && chil.size() != 2)
		type = ERROR;
}

crast::crast(char *in)
{
	val = in;
	switch(in[0])
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
			type = validnumtype(in);
			break;
		case '"':
			if(in[std::strlen(in) - 1] != '"')
				type = ERROR;
			else
				type = STRING;
			break;
		case '-':
		if(in[1] >= '0' && in[1] <= '9')
		{
			type = validnumtype(&in[1]);
			return;
		}
		case '+':
		case '/':
		case '*':
			if(in[1] == '\0')
			{
				type = ERROR;
				return;
			}
		default:
			type = SYMBOL;
			break;
	}
}

asttype crast::validnumtype(char *in)
{
	char *cur = in;
	int dec = 0;
	while(*cur)
	{
		switch(*cur)
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
			break;
		case '.':
			if(dec)
				return ERROR;
			dec++;
			break;
		default:
			return ERROR;
			break;
		}
		cur++;
	}
	if(dec)
		return FLOAT;
	return INT;
}

crast::~crast()
{
	while(!chil.empty())
	{
		delete chil.back();
		chil.pop_back();
	}
}

void crast::pcrast()
{
	unsigned int i;
	std::cout << type << " " << val << std::endl;
	for(i = 0; i < chil.size(); i++)
		chil[i]->pcrast();
}

