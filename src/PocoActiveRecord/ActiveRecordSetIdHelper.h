#pragma once
#include "Poco/Any.h"

using namespace Poco;


template<typename T, typename TField>
struct ActiveRecordSetIdHelper
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, Int16>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef Int16 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = static_cast<Int16>( id );
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, UInt16>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef UInt16 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = static_cast<UInt16>( id );
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, Int32>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef Int32 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = static_cast<Int32>( id );
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, UInt32>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef UInt32 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = static_cast<UInt32>( id );
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, Int64>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef Int64 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = static_cast<Int64>( id );
	}
};


template<typename T>
struct ActiveRecordSetIdHelper<T, UInt64>
{
	static void SetId( void * obj, void * field, UInt64 id )
	{
		typedef UInt64 (T::*FieldType);
		T * realObj = reinterpret_cast<T*>( obj );
		FieldType realField = *reinterpret_cast<FieldType*>( &field );
		(realObj->*realField) = id;
	}
};


typedef void (*ActiveRecordSetId)( void * obj, void * field, UInt64 id );