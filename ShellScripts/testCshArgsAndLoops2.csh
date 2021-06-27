#!/bin/tcsh -f
#!/bin/csh -f

echo The $0 command is called with $#argv parameters
set Nargs = $#argv


echo   parameter 1 is $1
echo   parameter 2 is $2
echo   parameter 3 is $3
echo   parameter 4 is $4
echo 1st and on parameters are \"$argv[1-]\" 
echo 2nd and on parameters are \"$argv[2-]\" 

#!/bin/csh
# demoloop.csh - Sample loop script
set j = 1
#while ( $j <= 5 )
while ( $j <= ${Nargs} )
   echo "Welcome $j times"
   echo "parameter $j is " \"$argv[$j]\" 
   @ j++
end

set k = 1
while ($k <= $argv[2])
    echo "this loop is on ${k}th iteration "
    @ k++
end
