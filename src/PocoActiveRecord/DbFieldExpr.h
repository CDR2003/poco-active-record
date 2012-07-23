#pragma once
#include "DbExpr.h"
#include "ActiveRecordTable.h"


template<typename T>
class DbFieldExpr : public DbExpr<T>
{
public:
	template<typename TField>
	DbFieldExpr( TField (T::*field) );

	string								ToSql() const;
	void								Use( Statement & statement ) const;

private:
	string								mFieldName;
};


template<typename T>
template<typename TField>
DbFieldExpr<T>::DbFieldExpr( TField (T::*field) )
{
	void * dataOffset = *reinterpret_cast<void**>( &field );

	typedef ActiveRecordTable<T> TableType;
	vector<ActiveRecordField*>::const_iterator it;
	for( it = TableType::Fields.begin(); it != TableType::Fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( field->GetDataOffset() == dataOffset )
		{
			mFieldName = field->GetName();
			return;
		}
	}

	poco_assert( ! "Field has not been registered." );
}


template<typename T>
string DbFieldExpr<T>::ToSql() const
{
	return mFieldName;
}


template<typename T>
void DbFieldExpr<T>::Use( Statement & statement ) const
{
}