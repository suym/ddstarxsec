#!/bin/bash
    
    Dir=/besfs/groups/nphy/users/xiaosy/yumo/cpp_first_simufit_D0bar/draw/energyISR
    cd ${Dir}
    rm fit_enerISR_dzd_star.dat -f
 
    declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070 4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4260 4310 4360 4390)

    
     dzd_star_a=-11.0584

     dzd_star_b=5.48995

     dzd_star_c=-0.628862 
     
declare -A isr_dzd_star
declare -A isr_dzd_star_err
declare -A ener_all
declare -a ener_input

k=0
y=0
for num_k in `awk '{print $2}' ener_all.dat`
do
   ener_input[${k}]=${num_k}
   k=`expr $k + 1`
done

   echo "${ener_input[@]}"

for num_p in ${array[@]}
do
   ener_all[${num_p}]=${ener_input[$y]}
   y=`expr $y + 1`
done

for i in ${array[@]}
do
    echo "${ener_all[$i]} is $i "
done


for num_m in ${array[@]}
do
   isr_dzd_star[${num_m}]=`echo "scale=4;a=$dzd_star_a+$dzd_star_b*${ener_all[${num_m}]}+$dzd_star_c*${ener_all[${num_m}]}*${ener_all[${num_m}]};if(length(a)==scale(a)) print 0;print a"|bc`
done

for num_l in ${array[@]}
do
   echo "${ener_all[${num_l}]}   ${isr_dzd_star[${num_l}]}" >>${Dir}/fit_enerISR_dzd_star.dat
done






