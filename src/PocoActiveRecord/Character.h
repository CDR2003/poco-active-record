#pragma once
#include "ActiveRecordBase.h"


class Character : public ActiveRecordBase<Character>
{
public:
	static string						TableName;
	static void							SetupFields();

	UInt32								Id;
	string								Name;
};

