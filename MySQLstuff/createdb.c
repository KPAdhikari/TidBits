//http://zetcode.com/db/mysqlc/
//Compilation command: gcc createdb.c -o createdb -std=c99  `mysql_config --cflags --libs`

#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
    {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }

  //if (mysql_real_connect(con, "localhost", "root", "root_pswd",
  if (mysql_real_connect(con, "localhost", "root", "achamma9",
                         NULL, 0, NULL, 0) == NULL)
    {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
    }

  if (mysql_query(con, "CREATE DATABASE testdb"))
    {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
    }

  mysql_close(con);
  exit(0);
}
