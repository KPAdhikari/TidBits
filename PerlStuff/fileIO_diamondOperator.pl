#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

# Perl was designed to manipulate files and I/O operations effectively. Perl main advantage is in file parsing and handling the files. There are many inbuilt functions and operators used during file handling in Perl.
#
# Basically, file operations that are performed with Perl are done using FILEHANDLE. We have to define this FILEHANDLE during the opening of a file for either read or write.
#
# We can open a file using open() function available in Perl.
#
#           open(FILEHANDLE, "filename or complete path of the file");
#
# Now we have opened a file, now a question arises. Is it for reading or writing?
#
# Perl has certain modes, which need to be used to read, write or append a file.
#       (kp: Remember, linux commands also use > or < for redirection of screen outputs to files)
#    * Read – open(my $fh,"<filename or complete path of the file");
#    * Write – open(my $fh,">filename or complete path of the file");
#    * Append – open(my $fh,">>filename or complete path of the file");
#

open(CHECKBOOK,"<testFile1.txt");

#https://alvinalexander.com/perl/edu/articles/pl010002.shtml
#kp: Although, the above website used checkbook used checkbook.txt file for example,
#    I am using my own 'testFile1.txt' file, however, I am still using the same name
#    for the filehandle i.e. CHECKBOOK rather than FH in my other examples.
#
#Now that we’ve opened the checkbook file, we’d like to be able to read what’s in it. Here’s how to read one line of data from the checkbook.txt file:

my $record = <CHECKBOOK>;
print "First line: $record \n";
print "Second line: ", <CHECKBOOK>;
print "Third line: ", <CHECKBOOK>;
#I think if the <filehandle> itself is printed without assigning it to another
#   variable, then it automatically adds the newline character \n as well.

#After this statement is executed, the variable $record contains the contents of the first line of the checkbook file. The <> symbol is called the Perl line reading operator, and in this example we’ve put the checkbook file handle in the line reading operator, indicating that we’d like to read a line from the checkbook file.

#Of course, instead of reading just one line of data, you may want to operate on many lines of data in the checkbook file. Suppose, for example, you want to print every record of information from the checkbook file. Here’s the code to (a) open the checkbook file, (b) print each record from the file, and (c) close the file when you’re finished working with it:

#open (CHECKBOOK, "checkbook.txt");

while ($record = <CHECKBOOK>) {
    print $record;
}
close CHECKBOOK;

print "######## Opening and reading the file again using while loop and '\$_' variable #####\n";
open(FH,"<testFile1.txt");
while(<FH>)    # Looping the file contents using the FH as a filehandle.
{
    print "$_";
}
close FH;

