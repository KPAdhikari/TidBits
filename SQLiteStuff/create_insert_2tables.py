#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

con = lite.connect('system.db')

with con:

    cur = con.cursor()
    cur.execute("CREATE TABLE Users(Id INT, Name TEXT)")
    cur.execute("INSERT INTO Users VALUES(1,'Michelle')")
    cur.execute("INSERT INTO Users VALUES(2,'Howard')")
    cur.execute("INSERT INTO Users VALUES(3,'Greg')")

    cur.execute("CREATE TABLE Jobs(Id INT, Uid INT, Profession TEXT)")
    cur.execute("INSERT INTO Jobs VALUES(1,1,'Scientist')")
    cur.execute("INSERT INTO Jobs VALUES(2,2,'Marketeer')")
    cur.execute("INSERT INTO Jobs VALUES(3,3,'Developer')")

'''
Creating a user information database

We can structure our data across multiple tables. This keeps our data structured, fast and organized.  If we would have a single table to store everything, we would quickly have a big chaotic mess. What we will do is create multiple tables and use them in a combination. We create two tables:

Users:

    Id     Name
1    1    Michelle
2    2    Howard
3    3    Greg

Jobs:

    Id   Uid    Profession
1    1    1    Scientist
2    2    2    Marketeer
3    3    3    Developer

To create these tables, you can do that by hand in the GUI or use the script above.


The jobs table has an extra parameter, Uid. We use that to connect the two tables in an SQL query:

SELECT users.name, jobs.profession FROM jobs INNER JOIN users ON users.ID = jobs.uid

You can incorporate that SQL query in a Python script (see get2.py). It should output:

$ python get2.py
(u'Michelle', u'Scientist')
(u'Howard', u'Marketeer')
(u'Greg', u'Developer')
'''
