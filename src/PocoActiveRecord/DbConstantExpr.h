#pragma once
#include <string>
#include "DbExpr.h"
#include "ActiveRecordExprUseHelper.h"

using namespace std;


template<typename T>
class DbConstantExpr : public DbExpr<T>
{
public:
	template<typename TValue>
	DbConstantExpr( const TValue & value );
	DbConstantExpr( const char * value );
	DbConstantExpr( const string & value );
	DbConstantExpr( const DbConstantExpr<T> & that );
	~DbConstantExpr();

	string								ToSql() const;
	void								Use( Statement & statement ) const;

	DbConstantExpr<T> &					operator=( const DbConstantExpr<T> & that );

private:
	void *								mData;
	size_t								mSize;
	bool								mIsString;
	ActiveRecordExprUse					mUseHelper;
};


template<typename T>
template<typename TValue>
DbConstantExpr<T>::DbConstantExpr( const TValue & value )
	: mIsString( false )
{
	mSize = sizeof( TValue );
	mData = new char[mSize];
	memcpy( mData, &value, mSize );
	mUseHelper = ActiveRecordExprUseHelper<TValue>::Use;
}


template<typename T>
DbConstantExpr<T>::DbConstantExpr( const char * value )
	: mIsString( true )
{
	mSize = strlen( value ) + 1;
	mData = new string( value );
	mUseHelper = ActiveRecordExprUseHelper<string>::Use;
}


template<typename T>
DbConstantExpr<T>::DbConstantExpr( const string & value )
	: mIsString( true )
{
	mSize = value.size() + 1;
	mData = new string( value );
	mUseHelper = ActiveRecordExprUseHelper<string>::Use;
}


template<typename T>
DbConstantExpr<T>::DbConstantExpr( const DbConstantExpr<T> & that )
{
	mIsString = that.mIsString;
	mSize = that.mSize;
	if( mIsString )
	{
		mData = new string( *reinterpret_cast<string>( that.mData ) );
	}
	else
	{
		mData = new char[mSize];
		memcpy( mData, that.mData, mSize );
	}
	mUseHelper = that.mUseHelper;
}


template<typename T>
DbConstantExpr<T>::~DbConstantExpr()
{
	if( mIsString )
	{
		string * str = reinterpret_cast<string*>( mData );
		delete str;
	}
	else
	{
		SafeDeleteArray( mData );
	}
}


template<typename T>
string DbConstantExpr<T>::ToSql() const
{
	return "?";
}


template<typename T>
void DbConstantExpr<T>::Use( Statement & statement ) const
{
	mUseHelper( mData, statement );
}


template<typename T>
DbConstantExpr<T> & DbConstantExpr<T>::operator=( const DbConstantExpr<T> & that )
{
	if( mIsString )
	{
		string * str = reinterpret_cast<string*>( mData );
		delete str;
	}
	else
	{
		SafeDeleteArray( mData );
	}
	
	mIsString = that.mIsString;
	mSize = that.mSize;
	if( mIsString )
	{
		mData = new string( *reinterpret_cast<string>( that.mData ) );
	}
	else
	{
		mData = new char[mSize];
		memcpy( mData, that.mData, mSize );
	}
	mUseHelper = that.mUseHelper;
}