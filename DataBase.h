#pragma once
#include <sqlite3.h>
#include<map>
#include"Types.h"
namespace SQLite3DataBaseTools
{
using namespace std;

//overwrapper for C-style connection.
class DataBase
{
private:
	sqlite3* db  = nullptr;
	string error_message;

	int ok; //put here value from sqlite library
public:
	DataBase(const string& path);
	~DataBase();

	bool is_ok();
	string get_error_message();

	bool run_request(const string& request);
};

//functions to create special requests to database
extern string make_create_request(const map<string, SQLtype*>& data, const string& table_name);
extern string make_insert_request(const map<string, SQLtype*>& data, const string& table_name);
};

