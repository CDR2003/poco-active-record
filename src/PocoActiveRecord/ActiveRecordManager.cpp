#include "ActiveRecordManager.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/MySQL/Connector.h"

using namespace Poco::Data;


ActiveRecordManager::ActiveRecordManager()
{
	MySQL::Connector::registerConnector();
}


ActiveRecordManager::~ActiveRecordManager()
{
	for_each( mTables.begin(), mTables.end(), SafeDelete<ActiveRecordITable> );
	mTables.clear();

	SafeDelete( mSessionPool );

	MySQL::Connector::unregisterConnector();
}


ActiveRecordManager * ActiveRecordManager::GetInstance()
{
	static ActiveRecordManager instance;
	return &instance;
}


void ActiveRecordManager::Initialize( const string & connectionString )
{
	mSessionPool = new SessionPool( "MySQL", connectionString );
}


Session ActiveRecordManager::CreateSession() const
{
	return Session( mSessionPool->get() );
}


void ActiveRecordManager::UpdateTableSchemas()
{
	Session session = this->CreateSession();

	list<ActiveRecordITable*>::const_iterator it;
	for( it = mTables.begin(); it != mTables.end(); ++it )
	{
		ActiveRecordITable * table = *it;
		if( table->IsTableCreated( session ) )
		{
			table->UpdateTable( session );
		}
		else
		{
			table->CreateTable( session );
		}
	}
}