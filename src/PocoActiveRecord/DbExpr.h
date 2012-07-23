#pragma once
#include "Poco/Data/Statement.h"


template<typename T>
class DbExpr
{
public:
	DbExpr();
	virtual ~DbExpr();

	virtual string						ToSql() const = 0;
	virtual void						Use( Statement & statement ) const = 0;
};


template<typename T>
DbExpr<T>::DbExpr()
{
}


template<typename T>
DbExpr<T>::~DbExpr()
{
}