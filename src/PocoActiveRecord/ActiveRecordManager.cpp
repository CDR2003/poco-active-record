#include "ActiveRecordManager.h"
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


string ActiveRecordManager::GetInstallScript() const
{
	string installScript = "";
	list<ActiveRecordITable*>::const_iterator it;
	for( it = mTables.begin(); it != mTables.end(); ++it )
	{
		ActiveRecordITable * table = *it;
		installScript += table->GetCreateTableScript() + "\n\n";
	}

	return installScript;
}


void ActiveRecordManager::InstallTables()
{
	Session session = this->CreateSession();

	list<ActiveRecordITable*>::const_iterator it;
	for( it = mTables.begin(); it != mTables.end(); ++it )
	{
		ActiveRecordITable * table = *it;
		string script = table->GetCreateTableScript();
		session << script, now;
	}
}