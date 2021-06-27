//11/5/17: http://zetcode.com/db/mysqlc/
// How to compile:  gcc -o mysql_c_test1 mysql_c_test1.c `mysql_config --cflags --libs`
#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
  printf("MySQL client version: %s\n", mysql_get_client_info());

  exit(0);
}
