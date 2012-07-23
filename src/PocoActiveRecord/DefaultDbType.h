#pragma once
#include "DbTypes.h"


template<typename T>
struct DefaultDbType;


template<>
struct DefaultDbType<bool>
{
	static const DbBool * GetType()
	{
		return new DbBool();
	}
};


template<>
struct DefaultDbType<char>
{
	static const DbTinyInt * GetType()
	{
		return new DbTinyInt( false );
	}
};


template<>
struct DefaultDbType<unsigned char>
{
	static const DbTinyInt * GetType()
	{
		return new DbTinyInt( true );
	}
};


template<>
struct DefaultDbType<short>
{
	static const DbSmallInt * GetType()
	{
		return new DbSmallInt( false );
	}
};


template<>
struct DefaultDbType<unsigned short>
{
	static const DbSmallInt * GetType()
	{
		return new DbSmallInt( true );
	}
};


template<>
struct DefaultDbType<int>
{
	static const DbInt * GetType()
	{
		return new DbInt( false );
	}
};


template<>
struct DefaultDbType<unsigned int>
{
	static const DbInt * GetType()
	{
		return new DbInt( true );
	}
};


template<>
struct DefaultDbType<float>
{
	static const DbFloat * GetType()
	{
		return new DbFloat();
	}
};


template<>
struct DefaultDbType<double>
{
	static const DbDouble * GetType()
	{
		return new DbDouble();
	}
};


template<>
struct DefaultDbType<string>
{
	static const DbVarChar * GetType()
	{
		return new DbVarChar( DbVarChar::DefaultLength );
	}
};
