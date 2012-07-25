#pragma once
#include <vector>
#include <algorithm>
#include "ActiveRecordITable.h"
#include "ActiveRecordField.h"

using namespace std;


template<typename T>
class ActiveRecordTable : public ActiveRecordITable
{
public:
	~ActiveRecordTable();

	static string						Name;
	static vector<ActiveRecordField*>	Fields;
	static vector<ActiveRecordField*>	PrimaryKeyFields;

	const string &						GetName() const						{ return Name; }
	const vector<ActiveRecordField*> &	GetFields() const					{ return Fields; }
	const vector<ActiveRecordField*> &	GetPrimaryKeyFields() const			{ return PrimaryKeyFields; }

	bool								IsTableCreated( Session & session ) const;
	void								CreateTable( Session & session ) const;
	void								UpdateTable( Session & session ) const;

private:
	vector<string>						GetExistFieldNames( Session & session ) const;
	ActiveRecordField *					GetField( const string & fieldName ) const;
};


template<typename T>
string ActiveRecordTable<T>::Name;

template<typename T>
vector<ActiveRecordField*> ActiveRecordTable<T>::Fields;

template<typename T>
vector<ActiveRecordField*> ActiveRecordTable<T>::PrimaryKeyFields;


template<typename T>
ActiveRecordTable<T>::~ActiveRecordTable()
{
	for_each( Fields.begin(), Fields.end(), SafeDelete<ActiveRecordField> );
	Fields.clear();
	PrimaryKeyFields.clear();
}


template<typename T>
bool ActiveRecordTable<T>::IsTableCreated( Session & session ) const
{
	string sql = "SHOW TABLES LIKE '" + Name + "';";
	Statement statement = ( session << sql );
	statement.execute();
	RecordSet recordSet( statement );

	return recordSet.moveFirst();
}


template<typename T>
void ActiveRecordTable<T>::CreateTable( Session & session ) const
{
	stringstream stream;
	stream << "CREATE TABLE " << Name << " ( " << endl;
	vector<ActiveRecordField*>::const_iterator it;
	for( it = Fields.begin(); it != Fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		stream << "\t" << field->ToSql() << "," << endl;
	}
	
	if( PrimaryKeyFields.empty() == false )
	{
		stream << "\tPRIMARY KEY ( ";
		for( it = PrimaryKeyFields.begin(); it != PrimaryKeyFields.end(); ++it )
		{
			ActiveRecordField * field = *it;
			if( it != PrimaryKeyFields.begin() )
			{
				stream << ", ";
			}
			stream << "" << field->GetName() << "";
		}
		stream << " )" << endl;
	}

	stream << ");";

	session << stream.str(), now;
}


template<typename T>
void ActiveRecordTable<T>::UpdateTable( Session & session ) const
{
	string sql = "ALTER TABLE " + Name;

	bool isFirstAlter = true;

	vector<string> fieldNames = this->GetExistFieldNames( session );
	vector<string>::const_iterator itFieldName;
	for( itFieldName = fieldNames.begin(); itFieldName != fieldNames.end(); ++itFieldName )
	{
		const string & fieldName = *itFieldName;
		ActiveRecordField * field = this->GetField( fieldName );
		if( field == NULL )
		{
			if( isFirstAlter )
			{
				isFirstAlter = false;
			}
			else
			{
				sql += ", ";
			}
			sql += "\n\tDROP COLUMN " + fieldName;
		}
		else
		{
			if( isFirstAlter )
			{
				isFirstAlter = false;
			}
			else
			{
				sql += ", ";
			}
			sql += "\n\tMODIFY COLUMN " + field->ToSql();
		}
	}

	vector<ActiveRecordField*>::const_iterator it;
	for( it = Fields.begin(); it != Fields.end(); ++it )
	{
		const ActiveRecordField * field = *it;
		if( find( fieldNames.begin(), fieldNames.end(), field->GetName() ) == fieldNames.end() )
		{
			if( isFirstAlter )
			{
				isFirstAlter = false;
			}
			else
			{
				sql += ", ";
			}
			sql += "\n\tADD COLUMN " + field->ToSql();
			if( it == Fields.begin() )
			{
				sql += " FIRST";
			}
			else
			{
				vector<ActiveRecordField*>::const_iterator itPrevious = it - 1;
				sql += " AFTER " + (*itPrevious)->GetName();
			}
		}
	}

	session << sql, now;
}


template<typename T>
vector<string> ActiveRecordTable<T>::GetExistFieldNames( Session & session ) const
{
	string sql = "SHOW COLUMNS FROM " + Name + ";";
	Statement statement = ( session << sql );
	statement.execute();

	RecordSet recordSet( statement );

	vector<string> result;
	if( recordSet.moveFirst() == false )
	{
		return result;
	}

	do
	{
		string fieldName = recordSet[0].convert<string>();
		result.push_back( fieldName );
	}
	while( recordSet.moveNext() );

	return result;
}


template<typename T>
ActiveRecordField * ActiveRecordTable<T>::GetField( const string & fieldName ) const
{
	vector<ActiveRecordField*>::const_iterator it;
	for( it = Fields.begin(); it != Fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		if( field->GetName() == fieldName )
		{
			return field;
		}
	}
	return NULL;
}