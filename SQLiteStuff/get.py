#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys


con = lite.connect('user.db')

with con:

    cur = con.cursor()
    cur.execute("SELECT * FROM Users")

    rows = cur.fetchall()

    for row in rows:
        print row

'''
The SQL database query language

SQL has many commands to interact with the database. You can try the commands below from the command line or from the GUI:

sqlite3 user.db
SELECT * FROM Users;
SELECT count(*) FROM Users;
SELECT name FROM Users;
SELECT * FROM Users WHERE id = 2;
DELETE FROM Users WHERE id = 6;

We can use those queries in a Python program such as this one.
'''
