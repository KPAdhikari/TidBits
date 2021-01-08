#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html
#use strict;

#Initially, when I used 'use strict', I got following error (for the following
#  two lines of code that starts with 'print %hash')
#       Global symbol "%hash" requires explicit package name at 6/7
#       Execution of ./hashesLikeDictsInPythonEtc.pl aborted due to compilation errors.
# Initially, the following two lines were line 6 and 7.
# This issue is due to the fact that When you have 'use strict;' you have to declare variables.
# So, when I commented out the 'use strict;' line, it did work, but to have consistency
# as a clean coder, I think I should declare the hash variable first and then print next.
# See thisfileStrict.pl for that.
print %hash=( 'Sainath' => 23, 'Krishna' => 24, 'Shruthi' => 25); # This is how we create a hash.
print %hash=('Sainath',23,'Krishna',24,'Shruthi',25);# This way of assigning is called list.
print "\n";
