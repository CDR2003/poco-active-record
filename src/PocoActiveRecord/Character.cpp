#include "Character.h"


string Character::TableName = "characters";


void Character::SetupFields()
{
	AddField( "id", &Character::Id, true, true, true );
	AddField( "name", &Character::Name );
	SetPrimaryKey( &Character::Id );
}