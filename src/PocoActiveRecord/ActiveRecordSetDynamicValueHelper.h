#pragma once
#include "Poco/DynamicAny.h"

using namespace Poco;


template<typename T, typename TField>
struct ActiveRecordSetDynamicValueHelper
{
	static void SetDynamicValue( void * obj, void * field, const DynamicAny & value )
	{
		typedef TField (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = value.convert<TField>();
	}
};


typedef void (*ActiveRecordSetDynamicValue)( void * obj, void * field, const DynamicAny & value );