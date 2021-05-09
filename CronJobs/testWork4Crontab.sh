#!/bin/bash

#https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
#tput setaf 1  #works
echo "${red}Hello from a crontab scheduled Job!" #set-color works too
echo "I have been scheduled to run every 20 min."
echo "I am a bash script named testWork4Crontab.sh."
echo "I dwell in /Users/kpadhikari/GitProj/KPAdhikari/TidBits/CronJobs."
echo "To shut me up you have to open the crontab (for cron-table) with"
echo "    'crontab-e' in the terminal, which will use an editor (either"
echo "    a default one such as 'nano' or something that we choose.) to"
echo "    open the crontab file, where we can put various crontab lines"
echo "    to schedule various jobs - one line per job."
#tput sgr0
echo " We can use 'crontab -l' (l as in 'list') to list the current jobs in crontab."
echo " "
echo " New Line Character: "
echo " Every entry in the crontab should end with a new line. This means there must be "
echo "   a blank line after the last crontab entry, or the last cron job will never run."
echo "${reset}" #reset color works too
