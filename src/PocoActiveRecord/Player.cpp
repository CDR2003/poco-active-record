#include "Player.h"


const string Player::TableName = "players";


Player::Player()
{
}


Player::~Player()
{
}


void Player::SetupFields()
{
	AddField( "id", &Player::Id, true, true, true );
	AddField( "name", &Player::Name );
	AddField( "description", &Player::Description, new DbText() );
	SetPrimaryKey( &Player::Id );
}