#!/bin/tcsh -f
#!/bin/csh -f

alias e2h 'set bname=`basename \!:1 .evio`; evio2hipo -s -0.756 -i \!:1 -o {$bname}.hipo'

echo The $0 command is called with $#argv parameters
set Nargs = $#argv

if ($#argv < 3) then
    echo "Usage: "
    echo "  ./thisFile rotNo(0,1,2,3...) lastFileIndex huOrOduLund(0,1)"
    echo "      rotNo: 0, 1, 2, 3, etc ..."
    echo "      lastFileIndex:  17 for example, for SEK lund files."
    echo "      huOrOduLund:    0 for HU/EC lund file and 1 for ODU/SEK lund file."
    echo "      Example:  ./convertEviosToHipo_Arg.csh 1 17 1"
    echo "      If the sim. version is changed, update index after v next to .evio"
    exit
endif

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

echo "\n\n"

#set k = 1
set eviofile = anything.evio
foreach x (`seq -w 0 $argv[2]`)
     #echo $x

    if ($argv[3] == 0) then
	set eviofile = out_lund_e2.1_h_radtail_huV1_09kEvs_Fl${x}v2.evio
    else 
	if ($argv[1] > 0) then
	    set eviofile = out_ep_34118_20rot${argv[1]}_02kEvs_Fl${x}v2.evio
	else
	    set eviofile = out_ep_34118_20_02kEvs_Fl${x}v2.evio
	endif
    endif

    echo "Now running ..."
    echo "e2h ${eviofile}"
    e2h ${eviofile}
end
