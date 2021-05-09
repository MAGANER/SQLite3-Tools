#pragma once
#include<sqlite3.h>
#include<map>
#include<vector>
#define MAP_FUNCTOOLS
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

	bool run_set_request(const string& request);
	map<string, SQLtype*> run_get_request(const string& request);
	map<string, SQLtype*> run_get_request(const string& request,const function<bool(SQLtype*)>& predicat);
private:
	static int get_request_callback(void* data, int argc, char** argv, char** azColName);
};

//functions to create special requests to database
extern string make_create_request(const map<string, SQLtype*>& data, const string& table_name);
extern string make_insert_request(const map<string, SQLtype*>& data, const string& table_name);
extern string make_select_request(const string& table_name);
extern string make_select_request(const string& table_name,
								  const vector<string>& fields);
};

