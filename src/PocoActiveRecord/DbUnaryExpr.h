#pragma once
#include "DbExpr.h"


template<typename T>
class DbUnaryExpr : public DbExpr<T>
{
public:
	DbUnaryExpr( const string & strOperator, DbExpr<T> * expr );
	~DbUnaryExpr();

	string								ToSql() const;
	void								Use( Statement & statement ) const;

private:
	string								mOperator;
	DbExpr<T> *							mExpr;
};


template<typename T>
DbUnaryExpr<T>::DbUnaryExpr( const string & strOperator, DbExpr<T> * expr )
	: mOperator( strOperator )
	, mExpr( expr )
{
}


template<typename T>
DbUnaryExpr<T>::~DbUnaryExpr()
{
	SafeDelete( mExpr );
}


template<typename T>
string DbUnaryExpr<T>::ToSql() const
{
	return "( " + mOperator + " " + mExpr->ToSql() + " )";
}


template<typename T>
void DbUnaryExpr<T>::Use( Statement & statement ) const
{
	mExpr->Use( statement );
}