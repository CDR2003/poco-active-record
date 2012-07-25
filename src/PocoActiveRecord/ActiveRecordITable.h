#pragma once
#include <string>
#include "ActiveRecordField.h"

using namespace std;


class ActiveRecordITable
{
public:
	virtual ~ActiveRecordITable() {}

	virtual const string &						GetName() const = 0;
	virtual const vector<ActiveRecordField*> &	GetFields() const = 0;
	virtual const vector<ActiveRecordField*> &	GetPrimaryKeyFields() const = 0;

	virtual bool								IsTableCreated( Session & session ) const = 0;
	virtual void								CreateTable( Session & session ) const = 0;
	virtual void								UpdateTable( Session & session ) const = 0;
};