I used the following commands in the sqlite3 shell to create a database, etc.
The .sql files were created just as any text file using Emacs editor. we could
use any other text editor. Emacs had the feature of syntax highlighting the
SQL commands/statements/Querries.
=================


1) Go into the sqlite3 shell:

sqlite3

2) To create a database 'first.db'

.open first.db

3) Create a table in the database first.db (we're already inside it)

.read maketable.sql

4) Make User

.read makeuser.sql
