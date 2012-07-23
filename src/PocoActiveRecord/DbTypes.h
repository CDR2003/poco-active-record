#pragma once
#include <string>
#include <sstream>
#include "Poco/Poco.h"

using namespace std;


template<typename T>
void SafeDelete( T* & ptr )
{
	if( ptr )
	{
		delete ptr;
		ptr = NULL;
	}
}


template<typename T>
void SafeDeleteArray( T* & ptr )
{
	if( ptr )
	{
		delete[] ptr;
		ptr = NULL;
	}
}


class DbType
{
public:
	virtual string ToString() const = 0;
};


class DbBool : public DbType
{
public:
	string ToString() const
	{
		return "BOOL";
	}
};


class DbTinyInt : public DbType
{
public:
	DbTinyInt( bool isUnsigned )
		: mIsUnsigned( isUnsigned )
	{
	}

	string ToString() const
	{
		return string( "TINYINT" ) + ( mIsUnsigned ? " UNSIGNED" : "" );
	}

private:
	bool mIsUnsigned;
};


class DbSmallInt : public DbType
{
public:
	DbSmallInt( bool isUnsigned )
		: mIsUnsigned( isUnsigned )
	{
	}

	string ToString() const
	{
		return string( "SMALLINT" ) + ( mIsUnsigned ? " UNSIGNED" : "" );
	}

private:
	bool mIsUnsigned;
};


class DbInt : public DbType
{
public:
	DbInt( bool isUnsigned )
		: mIsUnsigned( isUnsigned )
	{
	}

	string ToString() const
	{
		return string( "INT" ) + ( mIsUnsigned ? " UNSIGNED" : "" );
	}

private:
	bool mIsUnsigned;
};


class DbFloat : public DbType
{
public:
	string ToString() const
	{
		return "FLOAT";
	}
};


class DbDouble : public DbType
{
public:
	string ToString() const
	{
		return "DOUBLE";
	}
};


class DbVarChar : public DbType
{
public:
	static const unsigned int DefaultLength = 32;

	DbVarChar( unsigned int length )
		: mLength( length )
	{
	}

	string ToString() const
	{
		stringstream stream;
		stream << "VARCHAR(" << mLength << ")";
		return stream.str();
	}

private:
	unsigned int mLength;
};


class DbText : public DbType
{
public:
	string ToString() const
	{
		return "TEXT";
	}
};


class DbBlob : public DbType
{
public:
	string ToString() const
	{
		return "BLOB";
	}
};