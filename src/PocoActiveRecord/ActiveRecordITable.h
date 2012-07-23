#pragma once
#include <string>

using namespace std;


class ActiveRecordITable
{
public:
	virtual ~ActiveRecordITable() {}

	virtual string						GetCreateTableScript() const = 0;
};