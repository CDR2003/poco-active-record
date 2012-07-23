#pragma once
#include <string>
#include "Poco/Data/Statement.h"
#include "DbTypes.h"
#include "DefaultDbType.h"
#include "ActiveRecordUseHelper.h"
#include "ActiveRecordSetIdHelper.h"
#include "ActiveRecordSetDynamicValueHelper.h"

using namespace std;
using namespace Poco::Data;


class ActiveRecordField
{
public:
	template<typename T, typename TField>
	ActiveRecordField( TField (T::*field), const DbType * type );
	~ActiveRecordField();

	const string &						GetName() const								{ return mName; }
	void								SetName( const string & name )				{ mName = name; }
	void *								GetDataOffset() const						{ return mDataOffset; }
	const DbType *						GetType() const								{ return mType; }
	unsigned int						GetIndex() const							{ return mIndex; }
	void								SetIndex( unsigned int index )				{ mIndex = index; }
	bool								IsNullable() const							{ return mIsNullable; }
	void								SetNullable( bool isNullable )				{ mIsNullable = isNullable; }
	bool								IsAutoIncrement() const						{ return mIsAutoIncrement; }
	void								SetAutoIncrement( bool isAutoIncrement )	{ mIsAutoIncrement = isAutoIncrement; }

	void								Use( const void * obj, Statement & statement ) const;
	void								SetValue( void * obj, const DynamicAny & value ) const;
	void								SetId( void * obj, UInt64 id ) const;

	ActiveRecordField &					operator=( const ActiveRecordField & that );

private:
	string								mName;
	void *								mDataOffset;
	const DbType *						mType;
	unsigned int						mIndex;
	bool								mIsNullable;
	bool								mIsAutoIncrement;
	ActiveRecordUse						mUseHelper;
	ActiveRecordSetDynamicValue			mSetDynamicValueHelper;
	ActiveRecordSetId					mSetIdHelper;
};


template<typename T, typename TField>
ActiveRecordField::ActiveRecordField( TField (T::*field), const DbType * type )
	: mName( "" )
	, mType( type )
	, mIndex( 0 )
	, mIsNullable( false )
	, mIsAutoIncrement( false )
{
	mDataOffset = *reinterpret_cast<void**>( &field );
	mUseHelper = ActiveRecordUseHelper<T, TField>::Use;
	mSetDynamicValueHelper = ActiveRecordSetDynamicValueHelper<T, TField>::SetDynamicValue;
	mSetIdHelper = ActiveRecordSetIdHelper<T, TField>::SetId;
}