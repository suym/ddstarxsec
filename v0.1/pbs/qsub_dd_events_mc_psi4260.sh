#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-07-14 Thu 09:31] 

#PBS -N sel
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/kpi/v0.1/run/log/events/mc_psi4260/dd_mc_psi4260.log 
#PBS -t 1-5%200


date

hostname

cd $HOME/bes/kpi/v0.1/
source setup.sh

./python/sel_events.py run/mc_psi4260/dd_mc_psi4260-$PBS_ARRAYID.root run/events/mc_psi4260/dd_mc_psi4260-$PBS_ARRAYID.root

date




