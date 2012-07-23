#include "Account.h"


const string Account::TableName = "accounts";


Account::Account()
{
}


Account::~Account()
{
}


void Account::SetupFields()
{
	AddField( "id", &Account::Id, false, true );
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