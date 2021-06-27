//11/5/17 https://mandeepsimak.wordpress.com/tag/mysql-c-example/
// Include Header Files
//Compilation: g++ -o mysql_showTables mysql_showTables.cpp `mysql_config --cflags --libs`
//  Following was tried first but didn't work for some reason.
//  g++ -o mysql mysql.cpp -L/usr/local/mysql/include/mysql -lmysqlclient -I/usr/local/mysql/include/mysql
//
#include <iostream>
#include <cstdio>
#include <cstdlib>

// For MySQL Connection
#include <mysql.h>

using namespace std;

// Defining Constant Variables
#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root_password"
//#define DATABASE "test"
#define DATABASE "testKp1" //This database must exist (created previously) for this program to work.
//#define DATABASE "testDBwdCpp"

/*
If the value of DATABASE doesn't match with one of the existing databases in the mysqld localhost, then
it will show the following messages:
=====
Connection Failed
Segmentation fault: 11
=====
But, when I used 'testKp1' as its value (I had created a database of that name yesterday), it showed the following message:
====
Connection Succeeded
Tables in testKp1 database
student
====
 */
int main()
{
    MYSQL *connect;
    connect = mysql_init(NULL);

    if (!connect)
    {
        cout << "Mysql Initialization Failed";
        return 1;
    }

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0,NULL,0);

    if (connect)
    {
        cout << "Connection Succeeded\n";
    }
    else
    {
        cout << "Connection Failed\n";
    }

    MYSQL_RES *res_set;
    MYSQL_ROW row;

    // Replace MySQL query with your query

    mysql_query (connect,"show tables");

    unsigned int i=0;

    res_set=mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Tables in " << DATABASE << " database " << endl;

    while (((row=mysql_fetch_row(res_set)) !=NULL))
    {
        cout << row[i] << endl;
    }

    mysql_close (connect);

    return 0;
}
