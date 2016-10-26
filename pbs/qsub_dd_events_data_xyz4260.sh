#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-07-14 Thu 09:31] 

#PBS -N sel_4260
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/kpi/v0.2/run/log/events/data_4260/dd_data_xyz4260.log 
#PBS -t 1-678%300


date

hostname

cd $HOME/bes/kpi/v0.2/
source setup.sh

./python/sel_data_events.py run/data_4260/dd_data_xyz4260-$PBS_ARRAYID.root run/events/data_4260/dd_data_xyz4260-$PBS_ARRAYID.root

date




