//Data types can be stored in Sqlite3 data base
#pragma once
#include<string>
namespace SQLite3DataBaseTools
{
	enum class SQL_TYPES
	{
		INTEGER,
		PRIMARY_KEY,
		REAL,
		BOOLEAN,
		TEXT
	};
	struct SQLtype
	{
		SQL_TYPES type;
	};
	struct PrimaryKey:SQLtype 
	{ 
		int key; 
		PrimaryKey(int val)
		{
			type = SQL_TYPES::PRIMARY_KEY;
			key = val;
		}
	};
	struct Integer:SQLtype 
	{ 
		int value;
		Integer(int val)
		{
			type = SQL_TYPES::INTEGER;
			value = val;
		}
	};
	struct Real:SQLtype 
	{ 
		float value;
		Real(float val)
		{
			type = SQL_TYPES::REAL;
			value = val;
		}
	};
	struct Boolean:SQLtype 
	{ 
		bool value;
		Boolean(bool val)
		{
			type = SQL_TYPES::BOOLEAN;
			value = val;
		}
	};
	struct Text:SQLtype 
	{ 
		std::string value;
		Text(const std::string& val)
		{
			type = SQL_TYPES::TEXT;
			value = val;
		}
	};
};