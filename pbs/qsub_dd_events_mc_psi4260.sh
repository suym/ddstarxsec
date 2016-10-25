#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-07-14 Thu 09:31] 

#PBS -N sel
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/kpi/v0.2/run/log/events/mc_psi4260/dd_mc_psi4260.log 
#PBS -t 1-20%200


date

hostname

cd $HOME/bes/kpi/v0.2/
source setup.sh

./python/sel_mc_events.py run/mc_psi4260/dd_mc_psi4260-$PBS_ARRAYID.root run/events/mc_psi4260/dd_mc_psi4260-$PBS_ARRAYID.root

date




