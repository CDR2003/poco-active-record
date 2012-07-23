#pragma once
#include <vector>
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

	string								GetCreateTableScript() const;
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
string ActiveRecordTable<T>::GetCreateTableScript() const
{
	stringstream stream;
	stream << "CREATE TABLE " << Name << " ( " << endl;
	vector<ActiveRecordField*>::const_iterator it;
	for( it = Fields.begin(); it != Fields.end(); ++it )
	{
		ActiveRecordField * field = *it;
		stream << "\t" << field->GetName() << " " << field->GetType()->ToString();
		stream << ( field->IsNullable() ? "" : " NOT NULL" );
		stream << ( field->IsAutoIncrement() ? " AUTO_INCREMENT" : "" );
		stream << "," << endl;
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

	return stream.str();
}