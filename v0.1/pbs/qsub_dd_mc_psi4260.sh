#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-06-02 Thu 13:29]  

#PBS -N jmcpsi4260
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/kpi/v0.1/run/log/mc_psi4260/dd_mc_psi4260.log 
#PBS -t 1-20%200


date

hostname

cd $HOME/bes/kpi/v0.1
source setup.sh 
cd pbs/ 
boss.exe jobOptions_dd_mc_psi4260.pbs

date


