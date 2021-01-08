#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html
use strict;

#Initially, when I used 'use strict', I got following error (for the following
#  two lines of code that starts with 'print %hash')
#       Global symbol "%hash" requires explicit package name at 6/7
#       Execution of ./hashesLikeDictsInPythonEtc.pl aborted due to compilation errors.
# Initially, the following two lines were line 6 and 7.
# This issue is due to the fact that When you have 'use strict;' you have to declare variables.
# So, when I commented out the 'use strict;' line, it did work even without declarations
#     see the other file without Strict tag.
my %hash=( 'Sainath' => 23, 'Krishna' => 24, 'Shruthi' => 25); # This is how we create a hash.
my %hash=('Sainath',23,'Krishna',24,'Shruthi',25);# This way of assigning is called list.
print %hash;
print %hash;
print "\n Krishna: ";
print $hash{'Krishna'};
print "\n";
%hash=( 'Tom' => 23);
my %newHash=%hash; # Assigning hash to a new hash print %newHash;
print %newHash;
print "\n";
$newHash{'Jim'}=25;
$newHash{'John'}=26;
$newHash{'Harry'}=27;
print %newHash;
print "\n";
delete $newHash{'Jim'};#This will delete an entry from the hash.
my @array=%newHash; #Without 'my' again we get "Global symbol "@array" requires explicit package name" error
print "@array\n";
