#!/bin/tcsh -f

        #Copied on 3/2/21 from ~/SimStuff/SubmitJobs/createNsubSTEG_GSIM_dcSmearFinal.csh in my JLab CUE home.
##########################
#        This file does the following:
#    1) Takes in a certain number of parameters from the command line as input arguments
#    2) Creates a random number and then puts it in a new file seed.dat
#    3) Creates a input file steg_Eb_Itor.inp for the 3rd STEG executable steg_Linux which has
#         three variables Eb, Itor and the NumberOfEvents to be generated
#    4) Creates a *.csh script to run five executables - last two of STEG, gsim, gpp and user_ana
#    5) Creates a script to submit a job to the Jlab batch farm (with above *.csh in COMMAND: line)
#    6) Submits the script/job to the batch farm using the command 'jsub'
##########################

# First argument is filename
#if ($1 == '') then
if ($# <4) then
echo 'Not enough input parameters/arguments: Needs four - Ebeam, Itorus, EventNum2bSimulated  jobNum'
exit 1
else
set sfn = $1
echo 'Analyzing file for: '$sfn
endif

set jobNum = ${4}

#Make the seed.dat file for STEG (read_map_Linux and steg_Linux)
set LIMIT=100000
set date=`date +%j%H%M%S`
set numa=`expr $date \% $LIMIT`
set numb=`ps | sum | cut -c4-5`
@ random = $numa + $numb * 42

set seed = $random
set jname = seed_{$jobNum}  #for file name such as seed_1.dat

@ m = ${4}
echo 'test'
set numc=`ps | sum | cut -c4-5`
@ rnd = $m * $numc * 273 + $seed
#echo $rnd >> {$jname}_{$m}.dat
echo $rnd >> {$jname}.dat

echo 'The seed this time is: ' $rnd   #


#Make the steg.inp file with the # of events coming from one of the arguments of this file/script
set Ebeam = ${1}
set Itor = ${2}
#set DcSmear = ${3}   #Only one value - assumes the same same smear for all three layers
set EvtNum = ${3}

#spaces on the sides of == and the At-symbol (@) seem to be very important. Otherwise, we get errors
if($Ebeam == 1.054) then
    set RunNum4gpp = 52111
else if($Ebeam == 1.339) then
    set RunNum4gpp = 51180
else if($Ebeam == 1.989) then
    set RunNum4gpp = 51508
else if($Ebeam == 2.256) then
    set RunNum4gpp = 51008
else if($Ebeam == 2.999) then
    set RunNum4gpp = 50774
endif
echo 'What?'

cat <<END > steg_{$Ebeam}_{$Itor}.inp
$Ebeam
-$Itor
0.01
0.0
0.0
2.1
-100.6
6.
45.0
245.0
315.0
0.3
$Ebeam
N
N
$EvtNum
steg.bos

END




#Make a script that runs 5 executables in chain: read_map_Linux, steg_Linux, gsim, gpp and user_ana.
cat <<END > job_launchGSIMgppRecsis${Ebeam}_$jobNum.csh
# LSF script - created by"
#!/bin/tcsh

hostname

#This is a script to run STEG (all 3 execs), GSIM, GPP & RECSIS on already produced proton target events.
cp -f /u/home/adhikari/SimStuff/SubmitJobs/seed_$jobNum.dat seed.dat
cp -f /w/hallb/claseg4/adhikari/GSIM_RECSIS/TestsAll/Tests2011_exGen/StegPrEvents/Test_old_genVdm11tNH3/generateMap/steg_tab${Ebeam}.inp .
/w/hallb/claseg4/adhikari/GSIM_RECSIS/mod_osip_bost/mod_osip_bostVadim11_64tNH3/steg_tab_Linux < steg_tab${Ebeam}.inp

cp -f /w/hallb/claseg4/adhikari/GSIM_RECSIS/TestsAll/Tests2011_exGen/StegPrEvents/Test_old_genVdm11tNH3/readMap/readMap${Ebeam}_$Itor.inp .
/w/hallb/claseg4/adhikari/GSIM_RECSIS/mod_osip_bost/mod_osip_bostVadim11_64tNH3/read_map_Linux < readMap${Ebeam}_$Itor.inp

mv -f cs_max.dat cs_max1.dat
ln -s cs_max_new.dat cs_max.dat
cp -f /u/home/adhikari/SimStuff/SubmitJobs/steg_${Ebeam}_$Itor.inp .
/w/hallb/claseg4/adhikari/GSIM_RECSIS/mod_osip_bost/mod_osip_bostVadim11_64tNH3/steg_Linux < steg_${Ebeam}_$Itor.inp
h2root steg.hbook

mv -f steg.root /w/work5804/adhikari/steg${Ebeam}_$jobNum.root

####### Now GSIM #############
ln -s steg.bos clas.evt
#/home/adhikari/exec/bin/Linux64RH5/gsim_bat -ffread /home/ripani/eg4_farmjlab/mc_farm32_sim_2998/inputfiles/eg4.bat.ffread -mcin clas.evt -bosout clas.mtc > & gsim.log
/home/claseg4/software/bin/LinuxRHFC8/gsim_bat -ffread /u/home/adhikari/SimStuff/SubmitJobs/eg4.bat.ffreadItor_$Itor -mcin clas.evt -bosout clas.mtc > & gsim.log
echo "GSIM done"

#cp -f clas.mtc.A00 /w/work5804/adhikari/STEG/FilesFromBatch/clas.mtc.A00.${Ebeam}_$jobNum
#cp -f clas.mtc.A00 /w/work5804/adhikari/MorePrSim/gsimOut${Ebeam}_$jobNum.bos

mv -f clas.mtc.A00 /w/work5804/adhikari/gsimOut${Ebeam}_$jobNum.bos
mv -f steg.bos /w/work5804/adhikari/steg${Ebeam}_$jobNum.bos

END



#I tried this command directly on the screen, writing some stuff and then typing END in the end.
# cat <<END > job_launch_exGen_$sfn.csh

cat <<END > job_sub_batch

PROJECT: eg4a
TRACK: analysis
#OS: linux64 or <OS name="linux64"/> #https://wiki.jlab.org/cc/external/wiki/index.php/Nehalem_farm_nodes
OS: linux64
#TRACK:   test
JOBNAME: j${jobNum}_${Ebeam}
#COMMAND: mkdir /u/home/adhikari/public_html/EG4/WiggleStudy/50639_652_671
#COMMAND: root -b -q /u/home/adhikari/Acceptance/LumDepEffCor/evntNumFcup5.C\(${1},${2},${3},${4}\)
#COMMAND: /u/home/adhikari/Acceptance/LumDepEffCor/evntNumFcup5 ${1} ${2} ${3} ${4}
COMMAND: /u/home/adhikari/SimStuff/SubmitJobs/job_launchGSIMgppRecsis${Ebeam}_$jobNum.csh
MEMORY: 2000 MB
#max memory request allowed: 2147483648
MAIL: adhikari@jlab.org
TIME: 4320
#TIME: 4320 is max. (3 days)
#1400 is in minutes for one day. If the time is less than that it gets higer priority to run. If 1400 is not put it may run for a long time
#INPUT_FILES: #added by myself by disabling the last two because I thought the last two can work only one output file.
#OTHER_FiLES: #This is an alternative to INPUT_FILES (the latter submits many jobs with one for each input file.
#OUTPUT_DATA: Pe6.ps #Whatif I have many output files, not only one?
#OUTPUT_TEMPLATE:/w/work5805/adhikari/@INPUT_DATA@


END

#chmod u+x job_launch_exGen.csh
chmod u+x job_launchGSIMgppRecsis${Ebeam}_$jobNum.csh

jsub job_sub_batch
