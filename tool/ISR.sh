#!/bin/bash

Dir_1=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0_kpi/energyISR
Dir_2=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0star_kpi/energyISR
Dir_3=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barstarD0_D0bargamma_kpi/energyISR
Dir_4=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D_starDz_D0barpi_kpi/energyISR
Dir_5=/besfs/groups/nphy/users/xiaosy/yumo/cpp_first_simufit_D0bar/draw/energyISR

cd ${Dir_5}
rm ISR_dd.dat -f
rm ISR_d0bard0star.dat -f
rm ISR_d0barstard0.dat -f
rm ISR_dzd_star.dat -f

declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070 4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4260 4310 4360 4390)

for num in ${array[@]}
do
   cd ${Dir_1}/${num}/
   grep "1+de" *log | awk '{print $9}' | sed 's/+\/-/ /' | sed 's/,/ /'>>$Dir_5/ISR_dd.dat
   
done

for num in ${array[@]}
do
   cd ${Dir_2}/${num}/
   grep "1+de" *log | awk '{print $9}' | sed 's/+\/-/ /' | sed 's/,/ /'>>$Dir_5/ISR_d0bard0star.dat
   
done

for num in ${array[@]}
do
   cd ${Dir_3}/${num}/
   grep "1+de" *log | awk '{print $9}' | sed 's/+\/-/ /' | sed 's/,/ /'>>$Dir_5/ISR_d0barstard0.dat
   
done

for num in ${array[@]}
do
   cd ${Dir_4}/${num}/
   grep "1+de" *log | awk '{print $9}' | sed 's/+\/-/ /' | sed 's/,/ /'>>$Dir_5/ISR_dzd_star.dat
   
done

cd $Dir_5




