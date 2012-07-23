#pragma once
#include "DbExpr.h"


template<typename T>
class DbBinaryExpr : public DbExpr<T>
{
public:
	DbBinaryExpr( const string & strOperator, DbExpr<T> * left, DbExpr<T> * right );
	~DbBinaryExpr();

	string								ToSql() const;
	void								Use( Statement & statement ) const;

private:
	string								mOperator;
	DbExpr<T> *							mLeft;
	DbExpr<T> *							mRight;
};


template<typename T>
DbBinaryExpr<T>::DbBinaryExpr( const string & strOperator, DbExpr<T> * left, DbExpr<T> * right )
	: mOperator( strOperator )
	, mLeft( left )
	, mRight( right )
{
}


template<typename T>
DbBinaryExpr<T>::~DbBinaryExpr()
{
	SafeDelete( mLeft );
	SafeDelete( mRight );
}


template<typename T>
string DbBinaryExpr<T>::ToSql() const
{
	return "( " + mLeft->ToSql() + " " + mOperator + " " + mRight->ToSql() + " )";
}


template<typename T>
void DbBinaryExpr<T>::Use( Statement & statement ) const
{
	mLeft->Use( statement );
	mRight->Use( statement );
}