#include "DataBase.h"
using namespace SQLite3DataBaseTools;

DataBase::DataBase(const string& path)
{
	ok = sqlite3_open(path.c_str(), &db);
	if (!ok) error_message = sqlite3_errmsg(db);
}
DataBase::~DataBase()
{
	sqlite3_close(db);
}

bool DataBase::is_ok()
{
	return ok  == SQLITE_OK;
}
string DataBase::get_error_message()
{
	return error_message;
}
bool DataBase::run_request(const string& request)
{
	char* error_message = nullptr;
	int result = sqlite3_exec(db, request.c_str(), NULL, NULL, &error_message);
	
	if (error_message != nullptr)
		this->error_message = error_message;

	return result == SQLITE_OK;
}

string SQLite3DataBaseTools::make_create_request(const map<string, SQLtype*>& data, const string& table_name)
{
	string request = "CREATE TABLE "+table_name+"( ";

	size_t counter = 0;
	for (auto row : data)
	{
		switch (row.second->type)
		{
		case SQL_TYPES::PRIMARY_KEY: request += row.first + " INT PRIMARY KEY NOT NULL";
		break;
		case SQL_TYPES::INTEGER: request += row.first + " INT NOT NULL"; break;
		case SQL_TYPES::REAL:    request += row.first + " REAL";    break;
		case SQL_TYPES::TEXT:    request += row.first + " TEXT";    break;
		case SQL_TYPES::BOOLEAN: request += row.first + " BOOLEAN"; break;
		}

		if (counter + 1 != data.size())request += ", ";
		counter++;
	}
	request += ")";
	return request;
}
string SQLite3DataBaseTools::make_insert_request(const map<string, SQLtype*>& data, const string& table_name)
{
	string request = "INSERT INTO " + table_name + " (";

	size_t counter = 0;
	for (auto row : data)
	{
		request += row.first;
		if(counter + 1 != data.size()) request += ",";
		++counter;
	}
	request += ") VALUES (";

	counter = 0;
	for (auto row : data)
	{
		SQLtype* type_ptr = row.second;
		
		switch (row.second->type)
		{
		case SQL_TYPES::PRIMARY_KEY: request += to_string(static_cast<PrimaryKey*>(type_ptr)->key);
		break;
		case SQL_TYPES::INTEGER: request += to_string(static_cast<Integer*>(type_ptr)->value); break;
		case SQL_TYPES::REAL:    request += to_string(static_cast<Real*>(type_ptr)->value);    break;
		case SQL_TYPES::TEXT:    request += "'"+static_cast<Text*>(type_ptr)->value+"'";               break;
		case SQL_TYPES::BOOLEAN: request += to_string(static_cast<Boolean*>(type_ptr)->value); break;
		}

		if (counter + 1 != data.size()) request += ",";
		counter++;
	}
	request += ")";

	return request;
}