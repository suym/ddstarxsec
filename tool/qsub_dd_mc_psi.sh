#!/bin/bash
# Script to submit PBS jobs 



date

hostname

Dir=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0_kpi


if [[ $# -eq 0 ]]; then
    printf "NAME\n\tqsub.sh - Main driver to qsub programs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./qsub_dd_mc_psi.sh [OPTION]"
    printf "\nOPTIONS\n"
    printf "\n\t%-5s  %-40s\n"  "1"  "boss 664p01  lxslc5"
    printf "\n\t%-5s  %-40s\n"  "2"  "boss 665p01  lxslc6"
fi

option=$1

case $option in
    1) echo "boss 664p01..."
       declare -a array=(3900 4010 4090 4190 4210 4220 4230 4245 4260 4310 4360 4390) #664-p01
       cd $HOME/bes/kpi/v0.2
       source setup_664p01.sh
          for num in ${array[@]}
       do
          cd ${Dir}/${num}/
          #boss.condor D0barD0_kpi_${num}.txt
          #boss.condor D0barD0_kpi_${num}_rec.txt
          boss.condor D0barD0_kpi_${num}_ana.txt

       done
       cd ${Dir}/
       date
       ;;
    2) echo "boss 665p01..."
       declare -a array=(3890 3950 3980 4030 4040 4055 4070 4120 4140 4150 4170 ) # 665-p01
       cd $HOME/bes/kpi/v0.2
       source setup_665p01.sh
          for num in ${array[@]}
       do
          cd ${Dir}/${num}/
          #boss.condor D0barD0_kpi_${num}.txt
          #boss.condor D0barD0_kpi_${num}_rec.txt
          boss.condor D0barD0_kpi_${num}_ana.txt

       done
       cd ${Dir}/
       date
       ;;
esac


