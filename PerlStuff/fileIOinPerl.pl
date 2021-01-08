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

open(FH,"<testFile1.txt");
while(<FH>)    # Looping the file contents using the FH as a filehandle.
{
    print "$_";
}
close FH;

## Or equivalently
print "####### reading the file again with a different code-block ... #######\n";

open(FH,"<testFile1.txt");
my @content=<FH>; # specifying the input of the array is FH.
foreach(@content)
{
    print "$_";
}
close FH;


## Now writing out to a file
print "####### Next, writing to test.txt with 'open(FH,\">test.txt\");' ... #######\n";
print "Enter/type something, that will be captured via diamond operator <> and\n";
print "\t that will be written to test.txt.\n";
print "If the test.txt exists already, it will be overwritten, not appended to.\n";

open(FH,">test.txt");
my $var=<>;
print FH $var;
close FH;


## Now appending to a file
print "####### Next, appending to test.txt with 'open(FH,\">>test.txt\");' ... #######\n";
print "Enter/type something and that will be appended to test.txt.\n";
open(FH,">>test.txt");
my $var=<>;
print FH $var;
close FH;
