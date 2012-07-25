#include "Account.h"


const string Account::TableName = "accounts";


Account::Account()
	: Id( 0 )
	, Region( 0 )
	, Username( "" )
	, Password( "" )
{
}


Account::~Account()
{
}


void Account::SetupFields()
{
	AddField( "id", &Account::Id, true, true, true );
	AddField( "region", &Account::Region );
	AddField( "username", &Account::Username );
	AddField( "password", &Account::Password );
	SetPrimaryKey( &Account::Id );
}


string Account::ToString() const
{
	stringstream stream;
	stream << "id: " << Id << ", ";
	stream << "username: " << Username << ", ";
	stream << "password: " << Password;
	return stream.str();
}