#include <vld.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Poco/Data/Statement.h"
#include "Poco/Data/MySQL/Connector.h"
#include "ActiveRecordManager.h"
#include "Account.h"
#include "Player.h"

using namespace std;
using namespace Poco;
using namespace Poco::Data;


int main()
{
	cout << "Connecting to database..." << endl;
	ActiveRecordManager::GetInstance()->Initialize( "host=localhost;user=root;password=123456;db=test_ar" );
	ActiveRecordManager::GetInstance()->AddTable<Account>();
	ActiveRecordManager::GetInstance()->AddTable<Player>();

	cout << "Updating database schemas..." << endl;
	try
	{
		ActiveRecordManager::GetInstance()->UpdateTableSchemas();
	}
	catch( const Exception & e )
	{
		cout << e.displayText() << endl;
	}
	cout << "Update completed." << endl;

	Account account;
	account.Username = "shixin";
	account.Password = "jiaban";
	
	account.Save();

	vector<AccountPtr> result;
	Account::FindAll( result, DbField( &Account::Id ) >= 20 && DbField( &Account::Id ) < 25, DbOrderBy<Account>( &Account::Username ), 2 );

	for( vector<AccountPtr>::const_iterator it = result.begin(); it != result.end(); ++it )
	{
		AccountPtr account = *it;
		cout << account->ToString() << endl;
	}

	system( "PAUSE" );
	return 0;
}