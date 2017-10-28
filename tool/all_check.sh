#!/bin/bash
#suyumo

Dir_1=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0_kpi
Dir_2=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0star_kpi
Dir_3=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barstarD0_D0bargamma_kpi
Dir_4=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barstarD0_D0barpi0_kpi
Dir_5=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D_starDz_D0barpi_kpi
Dir_6=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/tool

cd ${Dir_6}
rm sim_log -f
rm rec_log -f
rm ana_log -f

if [[ $# -eq 0 ]]; then
    printf "NAME\n\tcheck.sh - Main driver to check programs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./check.sh [OPTION]"
    printf "\nOPTIONS\n"
    printf "\n\t%-5s  %-40s\n"  "1"  "check sim  "
    printf "\n\t%-5s  %-40s\n"  "2"  "check rec  "
    printf "\n\t%-5s  %-40s\n"  "3"  "check ana  "
fi

option=$1

case $option in
    1) echo "check sim..."
       cd ${Dir_1}
       ./new_check.sh 1 >>${Dir_6}/sim_log
       cd ${Dir_2}
       ./new_check.sh 1 >>${Dir_6}/sim_log
       cd ${Dir_3}
       ./new_check.sh 1 >>${Dir_6}/sim_log
       cd ${Dir_4}
       ./new_check.sh 1 >>${Dir_6}/sim_log
       cd ${Dir_5}
       ./new_check.sh 1 >>${Dir_6}/sim_log

       cd ${Dir_6}
       grep "all jobs is " ${Dir_6}/sim_log
       echo "  "
       grep "all successful jobs is " ${Dir_6}/sim_log
       count=0
       ii=`grep "all successful jobs is " sim_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all successful jobs : " ${Dir_6}/sim_log
       echo "  "
       grep "all failed jobs is " ${Dir_6}/sim_log
       count=0
       ii=`grep "all failed jobs is " sim_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all failed jobs : " ${Dir_6}/sim_log

       ;;
    2) echo "check rec..."
       cd ${Dir_1}
       ./new_check.sh 2 >>${Dir_6}/rec_log
       cd ${Dir_2}
       ./new_check.sh 2 >>${Dir_6}/rec_log
       cd ${Dir_3}
       ./new_check.sh 2 >>${Dir_6}/rec_log
       cd ${Dir_4}
       ./new_check.sh 2 >>${Dir_6}/rec_log
       cd ${Dir_5}
       ./new_check.sh 2 >>${Dir_6}/rec_log

       cd ${Dir_6}
       grep "all jobs is " ${Dir_6}/rec_log
       echo "  "
       grep "all successful jobs is " ${Dir_6}/rec_log
       count=0
       ii=`grep "all successful jobs is " rec_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all successful jobs : " ${Dir_6}/rec_log
       echo "  "
       grep "all failed jobs is " ${Dir_6}/rec_log
       count=0
       ii=`grep "all failed jobs is " rec_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all failed jobs : " ${Dir_6}/rec_log

       ;; 
    3) echo "check ana..."
       cd ${Dir_1}
       ./new_check.sh 3 >>${Dir_6}/ana_log
       cd ${Dir_2}
       ./new_check.sh 3 >>${Dir_6}/ana_log
       cd ${Dir_3}
       ./new_check.sh 3 >>${Dir_6}/ana_log
       cd ${Dir_4}
       ./new_check.sh 3 >>${Dir_6}/ana_log
       cd ${Dir_5}
       ./new_check.sh 3 >>${Dir_6}/ana_log

       cd ${Dir_6}

       grep "all jobs is " ${Dir_6}/ana_log
       echo "  "
       grep "all successful jobs is " ${Dir_6}/ana_log
       count=0
       ii=`grep "all successful jobs is " ana_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all successful jobs : " ${Dir_6}/ana_log
       echo "  "
       grep "all failed jobs is " ${Dir_6}/ana_log
       count=0
       ii=`grep "all failed jobs is " ana_log | awk '{print $5}'` 
       for line in  `echo "$ii"`
       do  
           count=`echo "$count+$line" | bc`
       done
       echo "  "
       echo "sum :  $count"
       echo "  "
       grep "all failed jobs : " ${Dir_6}/ana_log
       

       ;; 
esac




