#pragma once
#include "Poco/Data/Statement.h"

using namespace Poco::Data;


template<typename T, typename TField>
struct ActiveRecordUseHelper
{
	static void Use( const void * obj, void * offset, Statement & statement )
	{
		typedef TField (T::*FieldType);
		const T * realObj = reinterpret_cast<const T *>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &offset );

		const TField & value = realObj->*realField;
		statement, use( value );
	}
};

typedef void (*ActiveRecordUse)( const void * obj, void * offset, Statement & statement );