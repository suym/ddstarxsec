#!/bin/bash

Dir=/besfs/groups/nphy/users/xiaosy/yumo/cpp_first_simufit_D0bar

declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070 4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4260 4310 4360 4390)

declare -a isr_dd
declare -a isr_d0bard0star
declare -a isr_d0barstard0
declare -a isr_dzd_star

declare -A isr_ener_dd
declare -A isr_ener_d0bard0star
declare -A isr_ener_d0barstard0
declare -A isr_ener_dzd_star

i=0
j=0
k=0
m=0

y=0

for num_i in `awk '{print $2}' fit_enerISR_d0bard0.dat`
do
   isr_dd[${i}]=${num_i} 
   i=`expr $i + 1`
done

for num_j in `awk '{print $2}' fit_enerISR_d0bard0star.dat`
do
   isr_d0bard0star[${j}]=${num_j} 
   j=`expr $j + 1`
done

for num_k in `awk '{print $2}' fit_enerISR_d0barstard0.dat`
do
   isr_d0barstard0[${k}]=${num_k} 
   k=`expr $k + 1`
done

for num_m in `awk '{print $2}' fit_enerISR_dzd_star.dat`
do
   isr_dzd_star[${m}]=${num_m} 
   m=`expr $m + 1`
done

for num_y in ${array[@]}
do
   isr_ener_dd[${num_y}]=${isr_dd[$y]}
   isr_ener_d0bard0star[${num_y}]=${isr_d0bard0star[$y]}
   isr_ener_d0barstard0[${num_y}]=${isr_d0barstard0[$y]}
   isr_ener_dzd_star[${num_y}]=${isr_dzd_star[$y]}
   y=`expr $y + 1`
done
for key in ${array[@]}
do
  sed -i '29,32d'  ${Dir}/${key}/born.cxx
  sed -i '28a const double rad_cor_D0D0= '${isr_ener_dd[${key}]}'; //'${key}''  ${Dir}/${key}/born.cxx
  sed -i '29a const double rad_cor_D0D0star= '${isr_ener_d0bard0star[${key}]}'; //'${key}''  ${Dir}/${key}/born.cxx
  sed -i '30a const double rad_cor_D0D0star_D0= '${isr_ener_d0barstard0[${key}]}'; //'${key}''  ${Dir}/${key}/born.cxx
  sed -i '31a const double rad_cor_DzD_star= '${isr_ener_dzd_star[${key}]}'; //'${key}''  ${Dir}/${key}/born.cxx
done




