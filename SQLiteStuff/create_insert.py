#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

con = lite.connect('user.db')

with con:

    cur = con.cursor()
    cur.execute("CREATE TABLE Users(Id INT, Name TEXT)")
    cur.execute("INSERT INTO Users VALUES(1,'Michelle')")
    cur.execute("INSERT INTO Users VALUES(2,'Sonya')")
    cur.execute("INSERT INTO Users VALUES(3,'Greg')")

'''
https://pythonspot.com/python-database-programming-sqlite-tutorial/
The script above will store data into a new database called user.db

SQLite is a database management system that uses tables. These tables can have relations with other tables: it’s called relational database management system or RDBMS.  The table defines the structure of the data and can hold the data.  A database can hold many different tables. The table gets created using the command:

    cur.execute("CREATE TABLE Users(Id INT, Name TEXT)")

We add  records into the table with these commands:

    cur.execute("INSERT INTO Users VALUES(2,'Sonya')")
    cur.execute("INSERT INTO Users VALUES(3,'Greg')")

The first value is the ID. The second value is the name.  Once we run the script the data gets inserted into the database table Users:

      Id       Name
1     1        Michelle
2     2        Sonya
3     3        Greg


######### SQLite query data #################

We can explore the database using two methods:  the command line and a graphical interface.

From console: To explore using the command line type these commands:

sqlite3 user.db
.tables
SELECT * FROM Users;

This will output the data in the table Users.

sqlite&gt; SELECT * FROM Users;
1|Michelle
2|Sonya
3|Greg

From GUI: If you want to use a GUI instead, there is a lot of choice. Personally I picked sqllite-man but there are many others. We install using:

sudo apt-get install sqliteman

We start the application sqliteman. A gui pops up.

Press File > Open > user.db.  It appears like not much has changed, do not worry, this is just the user interface.  On the left is a small tree view, press Tables > users. The full table including all records will be showing now.

This GUI can be used to modify the records (data) in the table and to add new tables.

kp:
Following are 3 different free GUIs I could find on google (after a quick search):
DB Browser for SQLite: http://sqlitebrowser.org/
SQLite Studio: https://sqlitestudio.pl/index.rvt
SQLPro for SQLite: https://www.sqlitepro.com/


################## The SQL database query language ################

SQL has many commands to interact with the database. You can try the commands below from the command line or from the GUI:

sqlite3 user.db
SELECT * FROM Users;
SELECT count(*) FROM Users;
SELECT name FROM Users;
SELECT * FROM Users WHERE id = 2;
DELETE FROM Users WHERE id = 6;

We can use those queries in a Python program (see get.py)
'''
