#!/bin/bash

Dir=/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barD0_kpi
Dir_first=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/D0barD0_kpi

declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070 4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4260 4310 4360 4390)

for num in ${array[@]}
do

  cd ${Dir_first}
  mkdir ${num}
  cd ${num}/
  cp ${Dir}/${num}/D0barD0_kpi_${num}.txt .
  cp ${Dir}/${num}/D0barD0_kpi_${num}_rec.txt .
  cp ${Dir}/${num}/D0barD0_kpi_${num}_ana.txt .
  cp ${Dir}/${num}/D0bar_Kpi.dec .
  cp ${Dir}/${num}/EvtTop .
  cp /besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/cross_section/spline_cross/cross_d0d0bar.dat .
  mv cross_d0d0bar.dat xs_user.dat
  
done
