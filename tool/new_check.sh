#!/bin/bash
#suyumo

Dir=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0_kpi

if [[ $# -eq 0 ]]; then
    printf "NAME\n\tcheck.sh - Main driver to check programs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./check.sh [OPTION]"
    printf "\nOPTIONS\n"
    printf "\n\t%-5s  %-40s\n"  "1"  "check sim  "
    printf "\n\t%-5s  %-40s\n"  "2"  "check rec  "
    printf "\n\t%-5s  %-40s\n"  "3"  "check ana  "
fi

declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070 4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4260 4310 4360 4390)
declare -a successful_job
declare -a failed_job
declare -A ECMS_job
declare -a failed_job_size
declare -a successful_job_size

i=0
j=0
k=0

option=$1

case $option in
    1) echo "check sim..."
    for num in ${array[@]}
  do
    cd ${Dir}/$num
    str=`grep "ApplicationMgr       INFO Application Manager Finalized successfully"  D0barD0_kpi_${num}.txt.bosslog | awk '{print $6}'`
    size=`du -h D0barD0_Kpixv_${num}.rtraw`    

    if [ "$str" = "successfully" ]; then
       echo "$num is ok"
       successful_job[$i]=$num
       successful_job_size[$i]=$size
       i=`expr $i + 1`    
    else
       echo "$num is not ok"
       failed_job[$j]=$num
       failed_job_size[$j]=$size
       j=`expr $j + 1`    
    fi
       k=`expr $k + 1`    
  done
    echo "   "
    echo "   "
    echo " all failed jobs size"
    echo "   "
    for kk in ${failed_job_size[@]}
  do
    echo "    $kk      "
    echo "  ----------------------------------------   "
  done
    echo "   "
    echo "   "
    echo " all successful jobs size "
    echo "   "
    for kkk in ${successful_job_size[@]}
  do
    echo "    $kkk      "
    echo "  ----------------------------------------   "
  done
    echo "   "
    echo "   "
    echo "check sim results"
    echo "   "
    echo "   "
    echo "all jobs is $k"
    echo "all successful jobs is $i"
    echo "all successful jobs : ${successful_job[*]}"
    echo "all failed jobs is $j"
    echo "all failed jobs : ${failed_job[*]}"
    echo "   "
     date
       ;;
    2) echo "check rec..."
    for num in ${array[@]}
  do
    cd ${Dir}/$num
    str=`grep "ApplicationMgr       INFO Application Manager Finalized successfully"  D0barD0_kpi_${num}_rec.txt.bosslog | awk '{print $6}'`
    size=`du -h D0barD0_Kpixv_${num}.dst`    

    if [ "$str" = "successfully" ]; then
       echo "$num is ok"
       successful_job[$i]=$num
       successful_job_size[$i]=$size
       i=`expr $i + 1`
    else
       echo "$num is not ok"
       failed_job[$j]=$num
       failed_job_size[$j]=$size
       j=`expr $j + 1`
    fi
       k=`expr $k + 1`
  done
    echo "   "
    echo "   "
    echo " all failed jobs size"
    echo "   "
    for kk in ${failed_job_size[@]}
  do
    echo "    $kk      "
    echo "  ----------------------------------------   "
  done
    echo "   "
    echo "   "
    echo " all successful jobs size "
    echo "   "
    for kkk in ${successful_job_size[@]}
  do
    echo "    $kkk      "
    echo "  ----------------------------------------   "
  done
    echo "   "
    echo "   "
    echo "check rec results"
    echo "   "
    echo "   "
    echo "all jobs is $k"
    echo "all successful jobs is $i"
    echo "all successful jobs : ${successful_job[*]}"
    echo "all failed jobs is $j"
    echo "all failed jobs : ${failed_job[*]}"
    echo "   "
     date
       ;;
    3) echo "check ana..."
    for num in ${array[@]}
  do
    cd ${Dir}/$num
    str=`grep "ApplicationMgr       INFO Application Manager Finalized successfully"  D0barD0_kpi_${num}_ana.txt.bosslog | awk '{print $6}'`
    ecms=`grep "ECMS  =="  D0barD0_kpi_${num}_ana.txt.bosslog | awk '{print $3}'`
    
    if [ "$str" = "successfully" ]; then
       echo "$num is ok"
       successful_job[$i]=$num
       ECMS_job[$num]=$ecms
       i=`expr $i + 1`
    else
       echo "$num is not ok"
       failed_job[$j]=$num
       j=`expr $j + 1`
    fi
       k=`expr $k + 1`
  done
    for kk in ${array[@]}
  do
    echo "    $kk  is  ${ECMS_job[$kk]}    "
  done
    echo "   "
    echo "   "
    echo "check ana results"
    echo "   "
    echo "   "
    echo "all jobs is $k"
    echo "all successful jobs is $i"
    echo "all successful jobs : ${successful_job[*]}"
    echo "all failed jobs is $j"
    echo "all failed jobs : ${failed_job[*]}"
    echo "   "
     date
       ;;
esac
