#pragma once
#include "ActiveRecordTable.h"


template<typename T>
class DbOrderBy
{
public:
	enum Order
	{
		Ascending,
		Descending
	};

	DbOrderBy();
	template<typename TField>
	DbOrderBy( TField (T::*field), Order order = Ascending );

	string								ToSql() const;

private:
	string								mFieldName;
	Order								mOrder;
};


template<typename T>
DbOrderBy<T>::DbOrderBy()
	: mFieldName( "" )
	, mOrder( Ascending )
{
}


template<typename T>
template<typename TField>
DbOrderBy<T>::DbOrderBy( TField (T::*field), Order order )
	: mOrder( order )
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
string DbOrderBy<T>::ToSql() const
{
	if( mFieldName.empty() )
	{
		return "";
	}

	string sql = "ORDER BY " + mFieldName + " ";
	switch( mOrder )
	{
	case Ascending:
		sql += "ASC";
		break;
	case Descending:
		sql += "DESC";
		break;
	default:
		poco_assert( ! "Invalid order." );
	}

	return sql;
}