#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-06-02 Thu 13:29]  

#PBS -N jdata_xyz4260
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/kpi/v0.2/run/log/data_4260/dd_data_xyz4260.log 
#PBS -t 1-678%300




date

hostname

cd $HOME/bes/kpi/v0.2/
source setup.sh 
cd pbs 
boss.exe jobOptions_dd_data_xyz4260.pbs

date


