#!/usr/bin/perl
###!/usr/local/bin/perl
use strict;

#Ref: https://www.guru99.com/perl-tutorials.html

#Special variables in Perl are those which have some predefined meaning. These variables are denoted with either real Name or Punctuation symbols. We have a special variable for all the Perl supported Variables like scalar special variables, Array special variables, hash special variables. Most of the special variables that we use are of scalars.

#When we want to use the special variable with its name, then we have to load a Perl module 'use English,' to explicitly say Perl interpreter that we are going to use special variables using its Name.


my $string="This is a kind of dynamic array";
my @array;
@array=split('a',$string);
foreach(@array)
{
    print "$_ \n";     # This is a special variable which stores the current value.
    #print "$ARG, ";
}

print " filename with \$0: $0\n"; #Stores the file name of the Perl script.
#print " filename with \$PROGRAM_NAME: $PROGRAM_NAME\n";

print " \$/: $/\n"; # The input record separator, this has a default value of '\n' which is newline character
print " \$.: $.\n"; # Holds the current line number of the file that is being read
print " \$#: $#\n"; #This variable is used for output format while printing numbers.
print "Running process # with \$\$: $$\n"; #Will hold the running process number of Perl interpreter
print "Status code : Pipe and system call. The return status of the \n";
print "\t command executed with \$\?: $?\n"; #Status code : Pipe and system call. The return status of the command executed.
print "Real UID with \$\<: $<\n"; #Holds the real UID (user id) of the process running the script.
print "Effective UID with \$\>: $>\n"; #Holds the effective UID of the process running the script.
print "Real Group ID or GID with \$\(: $(\n"; #Holds the real GID (group id) of the process running the script.
print "Eff. Group ID or GID with \$\(: $(\n"; #Holds the effective GID of the process running the script
print "Current filename with \$ARGV: $ARGV\n"; #Name of the current file, when <> is used.





######## Array Special Variables #######3
print "\n\n\n ########## Array Special Variables ####### \n";
print "\@INC: @INC \n"; #Holds a list of paths, where Perl library modules or scripts can be looked into while executing the current script. This @INC is used by use and require statements to look into those paths for library modules.

print "Command line args with \@ARGV (doesn't include filename): @ARGV \n"; #Stores the command line arguments passed (doesn't include the filename)

#print "@_ \n"; #Used in subroutines, while passing the parameters to the subroutines.

#print "@F \n"; #This is the array into which the input lines are stored when auto split –a (command line switch is used).


########## Hash Special Variables #######
print "\n\n ########## Hash Special Variables ####### \n";
print "\%INC: %INC \n"; # The file name will be the keys; values will be the path to those files. Used by do, use and require.
print "\%ENV: %ENV \n"; # System environmental variables.
print "\%SIG: %SIG \n"; # Signals handler.
