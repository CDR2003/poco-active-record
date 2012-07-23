#include "Character.h"


string Character::TableName = "characters";


void Character::SetupFields()
{
	AddField( "id", &Character::Id, false, true );
	AddField( "name", &Character::Name );
	SetPrimaryKey( &Character::Id );
}