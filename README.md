# SQLite3-Tools
this little library is basic overwrapper for C-style sqlite3.


# What it can do?
1. Generate requests.<br>
2. Run requests.<br>
3. Connect to SQLite3 data base.<br>

# Examples

1. Basics

### A. Connection
```c++
#include"DataBase.h"

using namespace SQLite3DataBaseTools;
int main()
{
  DataBase db("test.db");
  return 0;
}
```
<br>

When DataBase object is created, it tries to connect to data base file,provided as argument to constructor.<br>
Yes, there is only one way to connect to data base - to create DataBase object.<br>
So to check is connection correct, you should run:```db.is_ok()```<br>
Also you can get error message text with:```db.get_error_message()```. It returns std::string.<br>

### B. Requests<br>
I split them into 2 classes SET/GET.<br>

The main difference is their result. SET requests don't return anything.<br>
They can be correct or incorrect, but GET requests always return something.<br>

There are 3 functions to run requests:
```c++
bool run_set_request(const string& request);
map<string, SQLtype*> run_get_request(const string& request);
map<string, SQLtype*> run_get_request(const string& request,function<bool(string, SQLtype*)>& predicat);
```
These are public function of DataBase class. First of all, let's see at run_get_request<br>
As all request runners it gets request as ```std::string```, also it returns boolean value.<br>
If it's true, then everthing worked ok.<br>

you can run GET-request without any predicat of ```WHERE``` part.<br>
For example:
```sql
SELECT * 
FROM some_table;
```

Or you can write some predicat:
```sql
SELECT *
FROM some_table
WHERE ID > 4;
```

For first case run get request with no any predicat.<br>
For second case run get request with predicat, where first pred argument is field name and second one is its value.<br>

### C. Request generation
Currently it's able to generate ```CREATE```, ```SELECT```, ```INSERT```, ```UPDATE```, ```DELETE``` operations.<br>
Header file with ```DataBase``` class provides several functions to generates these requests.<br>

```c++
string make_create_request(const map<string, SQLtype*>& data, const string& table_name);
string make_insert_request(const map<string, SQLtype*>& data, const string& table_name);
string make_select_request(const string& table_name);
string make_select_request(const string& table_name,
			   const vector<string>& fields);
string make_update_request(const map<string,SQLtype*>& fields_to_update,
			   const string& table_name);
string make_delete_request(const string& table_name,
			   const map<string, SQLtype*>& fields_to_update);
```

Let's see them closer.<br>

1. To create table you need pass to function hash table of field names and its types,<br>
    values can be omitted, because they aren't used in creation of DB table.<br>

2. But when you insert data, you obviosly need to set values you want, related<br>
    to some specific field name.<br>
    
3. You can select everything from table so use ```make_select_request(const string& table_name),```<br>
    but if you need to select special fields, then you should the second version, where second parameter is<br>
    vector with fields' names, that should be selected. Also if you need to use some predicat(```WHERE```)<br>
    you should run this request with special c++ lambda function, representing predicat<br>
    
4. So to update table you should generate special request, where first argument is hash table of field name and it's value,<br>
    second argument is name of table you need to update.<br>
   
5. To delete some elements, you pass name of table, and hash table with field name and it's value, all names are supposed to be deleted<br>

### D. SQLtype

SQLite3 has special data type system, so i created classes to represent them.<br>
```SQLtype``` is abstract class for all types, it's used to provide polymorphic functions.<br>
So, in depths there are ```Primarykey``, ```Integer```, ```Real```, ```Boolean```, ```Text```.<br>

Anyway, all you need is to understand what is SQLtype.<br>
