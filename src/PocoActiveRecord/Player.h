#pragma once
#include "ActiveRecordBase.h"


class Player : public ActiveRecordBase<Player>
{
public:
	Player();
	~Player();

	static const string					TableName;
	static void							SetupFields();

public:
	unsigned int						Id;
	string								Name;
	string								Description;
};

