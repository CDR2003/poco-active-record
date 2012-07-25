#include "ActiveRecordField.h"


ActiveRecordField::~ActiveRecordField()
{
	SafeDelete( mType );
}


string ActiveRecordField::ToSql() const
{
	string sql = mName + " " + mType->ToString();
	sql += ( mIsNotNull ? " NOT NULL" : "" );
	sql += ( mIsUnique ? " UNIQUE" : "" );
	sql += ( mIsAutoIncrement ? " AUTO_INCREMENT" : "" );
	return sql;
}


ActiveRecordField & ActiveRecordField::operator=( const ActiveRecordField & that )
{
	mName = that.mName;
	mDataOffset = that.mDataOffset;
	mType = that.mType;
	mIndex = that.mIndex;
	mIsNotNull = that.mIsNotNull;
	mIsUnique = that.mIsUnique;
	mIsAutoIncrement = that.mIsAutoIncrement;
	return *this;
}


void ActiveRecordField::Use( const void * obj, Statement & statement ) const
{
	mUseHelper( obj, mDataOffset, statement );
}


void ActiveRecordField::SetValue( void * obj, const DynamicAny & value ) const
{
	mSetDynamicValueHelper( obj, mDataOffset, value );
}


void ActiveRecordField::SetId( void * obj, UInt64 id ) const
{
	mSetIdHelper( obj, mDataOffset, id );
}