#/bin/bash



cheg_chk=`ps -ef | grep "cheg 7777" | grep -v grep | wc -l`

if [ ${cheg_chk} -eq 0 ]; then
	echo -e "cheg_restart : `date`" >> /Users/jhk/hk/final/script/real_monitor.log
	nohup /Users/jhk/hk/final/cheg 7777 & > /dev/null 2>&1 &
fi

program_chk=`ps -ef | grep "program 8888" | grep -v grep | wc -l`

if [ ${program_chk} -eq 0 ]; then
	echo -e "program_restart : `date`" >> /Users/jhk/hk/final/script/real_monitor.log
	nohup /Users/jhk/hk/final/program 8888 & > /dev/null 2>&1 &
fi


