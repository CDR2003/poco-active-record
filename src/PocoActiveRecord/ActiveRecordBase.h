#pragma once
#include <string>
#include <vector>
#include <climits>
#include "Poco/Data/RecordSet.h"
#include "ActiveRecordTable.h"
#include "ActiveRecordManager.h"
#include "DbExprPtr.h"
#include "DbOrderBy.h"

using namespace std;
using namespace Poco;


template<typename T>
class ActiveRecordBase : public RefCountedObject
{
public:
	enum Relation
	{
		HasOne,
		HasMany,
		BelongsToOne,
		BelongsToMany
	};

	typedef AutoPtr<T>					TPtr;

	ActiveRecordBase();
	virtual ~ActiveRecordBase();

	bool								IsNewRecord() const						{ return mIsNewRecord; }

										template<typename TPrimaryKey>
	static AutoPtr<T>					Find( const TPrimaryKey & primaryKey );

	static AutoPtr<T>					FindOne( DbExprPtr<T> & exprPtr );

	static void							FindAll( vector<TPtr> & result, DbExprPtr<T> & exprPtr, DbOrderBy<T> order = DbOrderBy<T>(), UInt32 limit = INT_MAX );
	static void							FindAll( list<TPtr> & result, DbExprPtr<T> & exprPtr, DbOrderBy<T> order = DbOrderBy<T>(), UInt32 limit = INT_MAX );

										template<typename TPrimaryKey>
	static void							Destroy( const TPrimaryKey & primaryKey );

	void								Save();
	void								Destroy();

protected:
										template<typename TField>
	static void							AddField( const string & fieldName, TField (T::*field), bool isNotNull = true, bool isUnique = false, bool isAutoIncrement = false );
										template<typename TField>
	static void							AddField( const string & fieldName, TField (T::*field), const DbType * type, bool isNotNull = true, bool isUnique = false, bool isAutoIncrement = false );
										template<typename TField>
	static void							SetPrimaryKey( TField (T::*field) );

private:
	typedef ActiveRecordTable<T>		TableType;

	static RecordSet					FindAll( DbExprPtr<T> & exprPtr, DbOrderBy<T> order, UInt32 limit );

	void								InsertToDatabase();
	void								UpdateToDatabase();
	string								GetCommaSeperatedColumnNames( bool includeAutoColumns ) const;
	string								GetCommaSeperatedQuestionMarks( bool includeAutoColumns ) const;

	bool								mIsNewRecord;
};


template<typename T>
ActiveRecordBase<T>::ActiveRecordBase()
	: mIsNewRecord( true )
{
}


template<typename T>
ActiveRecordBase<T>::~ActiveRecordBase()
{
}


template<typename T>
template<typename TPrimaryKey>
AutoPtr<T> ActiveRecordBase<T>::Find( const TPrimaryKey & primaryKey )
{
	string sql = "SELECT * FROM " + TableType::Name + " WHERE";
	poco_assert( TableType::PrimaryKeyFields.size() == 1 );
	ActiveRecordField * field = TableType::PrimaryKeyFields.front();
	sql += " " + field->GetName() + " = ?";

	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );

	statement, use( primaryKey );

	statement, upperLimit( 1 );
	statement.execute();

	RecordSet recordSet( statement );
	if( recordSet.moveFirst() == false )
	{
		return NULL;
	}

	T * obj = new T();
	obj->mIsNewRecord = false;
	for( size_t i = 0; i < TableType::Fields.size(); i++ )
	{
		ActiveRecordField * field = TableType::Fields[i];
		field->SetValue( obj, recordSet[i] );
	}

	return obj;
}


template<typename T>
AutoPtr<T> ActiveRecordBase<T>::FindOne( DbExprPtr<T> & exprPtr )
{
	list<TPtr> result;
	FindAll( exprPtr, result, DbOrderBy(), 1 );

	if( result.empty() )
	{
		return NULL;
	}
	
	return result.front();
}


template<typename T>
void ActiveRecordBase<T>::FindAll( vector<TPtr> & result, DbExprPtr<T> & exprPtr, DbOrderBy<T> order, UInt32 limit )
{
	RecordSet recordSet = FindAll( exprPtr, order, limit );
	result.clear();
	if( recordSet.moveFirst() == false )
	{
		return;
	}

	bool hasMore = false;
	do
	{
		T * obj = new T();
		obj->mIsNewRecord = false;
		for( size_t i = 0; i < TableType::Fields.size(); i++ )
		{
			ActiveRecordField * field = TableType::Fields[i];
			field->SetValue( obj, recordSet[i] );
		}
		result.push_back( obj );
		hasMore = recordSet.moveNext();
	}
	while( hasMore );
}


template<typename T>
void ActiveRecordBase<T>::FindAll( list<TPtr> & result, DbExprPtr<T> & exprPtr, DbOrderBy<T> order, UInt32 limit )
{
	RecordSet recordSet = FindAll( exprPtr, order, limit );
	result.clear();
	if( recordSet.moveFirst() == false )
	{
		return;
	}

	bool hasMore = false;
	do
	{
		T * obj = new T();
		obj->mIsNewRecord = false;
		for( size_t i = 0; i < TableType::Fields.size(); i++ )
		{
			ActiveRecordField * field = TableType::Fields[i];
			field->SetValue( obj, recordSet[i] );
		}
		result.push_back( obj );
		hasMore = recordSet.moveNext();
	}
	while( hasMore );
}


template<typename T>
template<typename TPrimaryKey>
void ActiveRecordBase<T>::Destroy( const TPrimaryKey & primaryKey )
{
	string sql = "DELETE FROM " + TableType::Name + " WHERE";
	poco_assert( TableType::PrimaryKeyFields.size() == 1 );
	ActiveRecordField * field = TableType::PrimaryKeyFields.front();
	sql += " " + field->GetName() + " = ?";

	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );

	statement, use( primaryKey );

	statement.execute();
}


template<typename T>
void ActiveRecordBase<T>::Save()
{
	if( mIsNewRecord )
	{
		this->InsertToDatabase();
	}
	else
	{
		this->UpdateToDatabase();
	}
}


template<typename T>
void ActiveRecordBase<T>::Destroy()
{
	string sql = "DELETE FROM " + TableType::Name + " WHERE";
	vector<ActiveRecordField*>::const_iterator it;
	for( it = TableType::PrimaryKeyFields.begin(); it != TableType::PrimaryKeyFields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( it != TableType::PrimaryKeyFields.begin() )
		{
			sql += " AND";
		}
		sql += " " + field->GetName() + " = ?";
	}

	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );

	for( it = TableType::PrimaryKeyFields.begin(); it != TableType::PrimaryKeyFields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		field->Use( this, statement );
	}

	statement.execute();
}


template<typename T>
template<typename TField>
void ActiveRecordBase<T>::AddField( const string & fieldName, TField (T::*field), bool isNotNull, bool isUnique, bool isAutoIncrement )
{
	AddField( fieldName, field, DefaultDbType<TField>::GetType(), isNotNull, isUnique, isAutoIncrement );
}


template<typename T>
template<typename TField>
void ActiveRecordBase<T>::AddField( const string & fieldName, TField (T::*field), const DbType * type, bool isNotNull, bool isUnique, bool isAutoIncrement )
{
	ActiveRecordField * fieldInfo = new ActiveRecordField( field, type );
	fieldInfo->SetName( fieldName );
	fieldInfo->SetNotNull( isNotNull );
	fieldInfo->SetUnique( isUnique );
	fieldInfo->SetAutoIncrement( isAutoIncrement );
	ActiveRecordTable<T>::Fields.push_back( fieldInfo );
}


template<typename T>
template<typename TField>
void ActiveRecordBase<T>::SetPrimaryKey( TField (T::*field) )
{
	void * offset = *reinterpret_cast<void**>( &field );
	const vector<ActiveRecordField*> & fieldInfos = ActiveRecordTable<T>::Fields;
	vector<ActiveRecordField*>::const_iterator it;
	for( it = fieldInfos.begin(); it != fieldInfos.end(); ++it )
	{
		ActiveRecordField * fieldInfo = *it;
		if( offset == fieldInfo->GetDataOffset() )
		{
			ActiveRecordTable<T>::PrimaryKeyFields.push_back( fieldInfo );
			return;
		}
	}

	poco_assert( ! "Primary key field did not found." );
}


template<typename T>
RecordSet ActiveRecordBase<T>::FindAll( DbExprPtr<T> & exprPtr, DbOrderBy<T> order, UInt32 limit )
{
	string sql = "SELECT * FROM " + TableType::Name + " WHERE " + exprPtr.GetExpr()->ToSql();
	sql += order.ToSql();
	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );
	exprPtr.GetExpr()->Use( statement );
	
	if( limit != INT_MAX )
	{
		statement, Poco::Data::limit( limit );
	}

	statement.execute();

	exprPtr.Release();

	return RecordSet( statement );
}


template<typename T>
void ActiveRecordBase<T>::InsertToDatabase()
{
	string sql = "INSERT INTO " + TableType::Name;
	sql += " ( " + this->GetCommaSeperatedColumnNames( false ) + " ) VALUES";
	sql += " ( " + this->GetCommaSeperatedQuestionMarks( false ) + " );";

	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );

	const vector<ActiveRecordField*> & fields = TableType::Fields;
	vector<ActiveRecordField*>::const_iterator it;
	for( it = fields.begin(); it != fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( field->IsAutoIncrement() )
		{
			continue;
		}
		field->Use( this, statement );
	}

	statement.execute();

	if( TableType::PrimaryKeyFields.empty() == false )
	{
		ActiveRecordField * primaryKey = TableType::PrimaryKeyFields.front();
		UInt64 id = AnyCast<UInt64>( session.getProperty( "insertId" ) );
		primaryKey->SetId( this, id );
	}
}


template<typename T>
void ActiveRecordBase<T>::UpdateToDatabase()
{
	string sql = "UPDATE " + TableType::Name + " SET ";
	vector<ActiveRecordField*>::const_iterator it;
	for( it = TableType::Fields.begin(); it != TableType::Fields.end(); ++it )
	{
		if( it != TableType::Fields.begin() )
		{
			sql += ", ";
		}
		ActiveRecordField * field = *it;
		sql += field->GetName() + " = ?";
	}
	sql += " WHERE ";
	for( it = TableType::PrimaryKeyFields.begin(); it != TableType::PrimaryKeyFields.end(); ++it )
	{
		if( it != TableType::PrimaryKeyFields.begin() )
		{
			sql += ", ";
		}
		ActiveRecordField * field = *it;
		sql += field->GetName() + " = ?";
	}

	Session session = ActiveRecordManager::GetInstance()->CreateSession();
	Statement statement = ( session << sql );

	for( it = TableType::Fields.begin(); it != TableType::Fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		field->Use( this, statement );
	}
	for( it = TableType::PrimaryKeyFields.begin(); it != TableType::PrimaryKeyFields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		field->Use( this, statement );
	}

	statement.execute();
}


template<typename T>
string ActiveRecordBase<T>::GetCommaSeperatedColumnNames( bool includeAutoColumns ) const
{
	string sql = "";
	const vector<ActiveRecordField*> & fields = TableType::Fields;
	vector<ActiveRecordField*>::const_iterator it;
	int paramCount = 0;
	for( it = fields.begin(); it != fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( field->IsAutoIncrement() )
		{
			continue;
		}

		if( paramCount > 0 )
		{
			sql += ", ";
		}
		sql += field->GetName();
		paramCount++;
	}

	return sql;
}


template<typename T>
string ActiveRecordBase<T>::GetCommaSeperatedQuestionMarks( bool includeAutoColumns ) const
{
	string sql = "";
	const vector<ActiveRecordField*> & fields = TableType::Fields;
	vector<ActiveRecordField*>::const_iterator it;
	int paramCount = 0;
	for( it = fields.begin(); it != fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( field->IsAutoIncrement() )
		{
			continue;
		}

		if( paramCount > 0 )
		{
			sql += ", ";
		}
		sql += "?";
		paramCount++;
	}

	return sql;
}