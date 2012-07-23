#pragma once
#include "DbExpr.h"
#include "DbConstantExpr.h"
#include "DbUnaryExpr.h"
#include "DbBinaryExpr.h"
#include "DbFieldExpr.h"


template<typename T>
class DbExprPtr
{
public:
	DbExprPtr( DbExpr<T> * expr = NULL );
	~DbExprPtr();

	DbExpr<T> *							GetExpr() const					{ return mExpr; }

	void								Release();

private:
	DbExpr<T> *							mExpr;
};


template<typename T>
DbExprPtr<T>::DbExprPtr( DbExpr<T> * expr )
	: mExpr( expr )
{
}


template<typename T>
DbExprPtr<T>::~DbExprPtr()
{
}


template<typename T>
void DbExprPtr<T>::Release()
{
	SafeDelete( mExpr );
}


template<typename T>
DbExprPtr<T> operator-( const DbExprPtr<T> & expr )
{
	return new DbBinaryExpr<T>( "-", expr.GetExpr() );
}


template<typename T>
DbExprPtr<T> operator!( const DbExprPtr<T> & expr )
{
	return new DbBinaryExpr<T>( "!", expr.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator<( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "<", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator<( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "<", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator<( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "<", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator<=( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "<=", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator<=( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "<=", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator<=( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "<=", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator>( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( ">", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator>( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( ">", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator>( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( ">", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator>=( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( ">=", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator>=( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( ">=", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator>=( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( ">=", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator==( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "=", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator==( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "=", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator==( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "=", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator!=( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "!=", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator!=( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "!=", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator!=( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "!=", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator&&( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "&&", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator&&( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "&&", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator&&( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "&&", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator||( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "||", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator||( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "||", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator||( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "||", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator+( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "+", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator+( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "+", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator+( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "+", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator-( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "-", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator-( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "-", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator-( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "-", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator*( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "*", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator*( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "*", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator*( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "*", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator/( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "/", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator/( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "/", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator/( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "/", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TValue>
DbExprPtr<T> operator%( const DbExprPtr<T> & left, const TValue & right )
{
	return new DbBinaryExpr<T>( "%", left.GetExpr(), new DbConstantExpr<T>( right ) );
}

template<typename T, typename TValue>
DbExprPtr<T> operator%( const TValue & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "%", new DbConstantExpr<T>( left ), right.GetExpr() );
}

template<typename T>
DbExprPtr<T> operator%( const DbExprPtr<T> & left, const DbExprPtr<T> & right )
{
	return new DbBinaryExpr<T>( "%", left.GetExpr(), right.GetExpr() );
}


template<typename T, typename TField>
DbExprPtr<T> DbField( TField (T::*field) )
{
	return new DbFieldExpr<T>( field );
}