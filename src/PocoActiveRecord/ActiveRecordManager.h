#pragma once
#include "Poco/Data/SessionPool.h"
#include "ActiveRecordTable.h"
#include <sstream>
#include <iostream>
#include <list>

using namespace std;
using namespace Poco::Data;


class ActiveRecordManager
{
private:
	ActiveRecordManager();
	~ActiveRecordManager();

public:
	static ActiveRecordManager *		GetInstance();

	void								Initialize( const string & connectionString );
	Session								CreateSession() const;

										template<typename T>
	void								AddTable();

	string								GetInstallScript() const;
	void								InstallTables();

private:
	SessionPool *						mSessionPool;
	list<ActiveRecordITable*>			mTables;
};


template<typename T>
void ActiveRecordManager::AddTable()
{
	ActiveRecordTable<T>::Name = T::TableName;
	T::SetupFields();

	mTables.push_back( new ActiveRecordTable<T>() );
}
