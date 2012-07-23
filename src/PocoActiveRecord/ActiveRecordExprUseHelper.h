#pragma once
#include "Poco/Data/Statement.h"

using namespace Poco::Data;


template<typename T>
struct ActiveRecordExprUseHelper
{
	static void Use( const void * obj, Statement & statement )
	{
		const T * realObj = reinterpret_cast<const T *>( obj );
		statement, use( *realObj );
	}
};

typedef void (*ActiveRecordExprUse)( const void * obj, Statement & statement );