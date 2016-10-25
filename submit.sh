#!/usr/bin/env bash

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn>
# Created [2016-03-28 Mon 07:58]


usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-5s  %-40s\n"  "0.1"      "[run data sample]" 
    printf "\n\t%-5s  %-40s\n"  "0.1.1"    "Run with a few samples" 
    printf "\n\t%-5s  %-40s\n"  "0.1.2"    "Split data_4260 sample with each group 10G"
    printf "\n\t%-5s  %-40s\n"  "0.1.3"    "Submit PBS jobs on data_4260"
    printf "\n\t%-5s  %-40s\n"  "0.1.4"    "Check PBS jobs on data_4260."
    printf "\n\t%-5s  %-40s\n"  "0.1.5"    "Select events."
    printf "\n\t%-5s  %-40s\n"  "0.1.6"    "Submit events selection jobs on data_4260."
    printf "\n\t%-5s  %-40s\n"  "0.1.7"    "Check events jobs on data_4260."
    printf "\n\t%-5s  %-40s\n"  "0.1.8"    "Merge events files." 
    printf "\n\t%-5s  %-40s\n"  "0.1.9"    "Plot momentum distribution with data_4260."
    printf "\n\t%-5s  %-40s\n"  "0.2"      "[run on MC sample]"
    printf "\n\t%-5s  %-40s\n"  "0.2.1"    "Run with a few samples"
    printf "\n\t%-5s  %-40s\n"  "0.2.2"    "Split psi4260 MC sample with each group 4G"
    printf "\n\t%-5s  %-40s\n"  "0.2.3"    "Submit PBS jobs on psi4260 MC sample"     
    printf "\n\t%-5s  %-40s\n"  "0.2.4"    "Check PBS jobs on psi4260 MC sample"     
    printf "\n\t%-5s  %-40s\n"  "0.2.5"    "Select events on psi4260 MC sample"     
    printf "\n\t%-5s  %-40s\n"  "0.2.6"    "Submit PBS jobs to select events on psi4260 MC sample"     
    printf "\n\t%-5s  %-40s\n"  "0.2.7"    "Check events selection jobs on psi4260 MC"
    printf "\n\t%-5s  %-40s\n"  "0.2.8"    "Merge events files on psi4260 MC"
    printf "\n\t%-5s  %-40s\n"  "0.2.9"    "Plot background momentum distribution with psi4260 MC"
    printf "\n\t%-5s  %-40s\n"  "0.2.10"    "Plot momentum distribution with psi4260 MC"
    printf "\n\t%-5s  %-40s\n"  "0.2.11"    "Plot stack momentum distribution with psi4260 MC"
    printf "\n\t%-5s  %-40s\n"  "0.2.12"    "Plot fitting momentum distribution with psi4260 MC--lowmom"
    printf "\n\t%-5s  %-40s\n"  "0.2.13"    "Plot fitting momentum distribution with psi4260 MC--highmom"
    printf "\n\n" 
}


if [[ $# -eq 0 ]]; then
    usage
fi


option=$1

case $option in 
    0.1) echo "Running on data sample..."
	 ;;

    0.1.1) echo "Run with a few events ..."
	   boss.exe jobOptions_dd.txt
	   ;;
    
    0.1.2) echo "Split data_4260 sample with each group 10G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p01/xyz/4260/dst  $HOME/bes/kpi/v0.2/run/samples/data_664p01_xyz4260.txt 10G
	   # made 678 groups 
	   ;;

    0.1.3) echo "Submit PBS jobs on data_4260..."
           mkdir run/data_4260
           mkdir run/log/data_4260
           qsub pbs/qsub_dd_data_xyz4260.sh
	   ;;

    0.1.4) echo "Check PBS jobs on data_4260..."
	   ./python/chk_pbsjobs.py $HOME/bes/kpi/v0.2/run/data_4260  678 
	   ;;
    
    0.1.5) echo  "Select events on data_4260..."
           mkdir run/events/data_4260
           for i in {1..678}
           do
               echo "processing run/data_4260/dd_data_xyz4260-$i.root ..."
               ./python/sel_data_events.py  run/data_4260/dd_data_xyz4260-$i.root  run/events/data_4260/dd_data_xyz4260-$i.root
           done

	   ;; 

    0.1.6) echo "Submit selection PBS jobs on data_4260..."
	   mkdir run/events/data_4260
	   mkdir run/log/events/data_4260  
	   qsub pbs/qsub_dd_events_data_xyz4260.sh  
	   ;;

    0.1.7) echo "Check PBS jobs on events data_4260..."
	   ./python/chk_pbsjobs.py run/events/data_4260  678 
	   ;;

    0.1.8) echo  "Merge root files..."
	   mkdir run/hist/data_4260
	   ./python/mrg_rootfiles.py  run/events/data_4260  run/hist/data_4260 
	   ;; 

    0.1.9) echo  "Plot momentum distribution with data_4260..."
           cd cpp
           root ./plt_data4260_mom.cxx          
 	   ;; 


    
    0.2) echo "Running on MC sample..."
	 ;;

    0.2.1) echo "Run with a few events ..."
	   boss.exe jobOptions_dd.txt
	   ;;
    0.2.2) echo "Split psi4260 MC sample with each group 4G ..."
	   ./python/get_samples.py  /besfs/groups/psip/psipgroup/664p01-MC/4260/res/DD $HOME/bes/kpi/v0.2/run/samples/mc_664p01_psi4260_DD.txt 4G
	   # made 20 groups 
	   ;;

    0.2.3) echo "Submit PBS jobs on psi4260 MC sample..."
	   mkdir run/mc_psi4260
	   mkdir run/log/mc_psi4260  
	   qsub pbs/qsub_dd_mc_psi4260.sh
	   ;;

    0.2.4) echo "Check PBS jobs on psi4260 MC sample..."
	   ./python/chk_pbsjobs.py $HOME/bes/kpi/v0.2/run/mc_psi4260  20 
	   ;;

    0.2.5) echo  "Select events on psi4260 MC sample..."
	   mkdir run/events/mc_psi4260  
	   for i in {1..20}  
	   do  
	       echo "processing run/mc_psi4260/dd_mc_psi4260-$i.root ..."
	       ./python/sel_mc_events.py  run/mc_psi4260/dd_mc_psi4260-$i.root  run/events/mc_psi4260/dd_mc_psi4260-$i.root
	   done   
	   ;; 

    0.2.6) echo "Submit selection PBS jobs on psi4260 sample..."
	   mkdir run/events/mc_psi4260
	   mkdir run/log/events/mc_psi4260  
	   qsub pbs/qsub_dd_events_mc_psi4260.sh  
	   ;;

    0.2.7) echo "Check events selection jobs on psi4260 MC sample..."
	   ./python/chk_pbsjobs.py run/events/mc_psi4260  20 
	   ;;
    
    0.2.8) echo  "Merge events files..."
	   mkdir run/hist/mc_psi4260
	   ./python/mrg_rootfiles.py  run/events/mc_psi4260 run/hist/mc_psi4260 
	   ;; 

    0.2.9) echo  "Plot background momentum distribution with psi4260 MC ..."
           cd cpp
	   root ./plt_bkg.cxx 
	   ;;
    0.2.10) echo  "Plot momentum distribution with psi4260 MC ..."
           cd cpp
	   root ./plt_mom.cxx 
	   ;;
    0.2.11) echo  "Plot stack momentum distribution with psi4260 MC ..."
           cd cpp
	   root ./plt_stack_mom.cxx 
	   ;;
    0.2.12) echo  "Plot fitting momentum distribution with psi4260 MC ..."
           cd cpp
	   root ./plt_mc_lowmom_fit.cxx 
	   ;;
    0.2.13) echo  "Plot fitting momentum distribution with psi4260 MC ..."
           cd cpp
	   root ./plt_mc_highmom_fit.cxx 
	   ;;

esac

