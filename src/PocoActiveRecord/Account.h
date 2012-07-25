#pragma once
#include "ActiveRecordBase.h"


class Account : public ActiveRecordBase<Account>
{
public:
	Account();
	~Account();

	static const string					TableName;
	static void							SetupFields();

	string								ToString() const;

public:
	unsigned int						Id;
	unsigned short						Region;
	string								Username;
	string								Password;
};


typedef AutoPtr<Account>				AccountPtr;