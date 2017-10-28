#!/bin/bash
declare -a ener_dzd_star
declare -a cross_dzd_star
Dir=/besfs/groups/nphy/users/xiaosy/yumo/first_iteration_simufit_D0bar/cross_section/spline_cross

cd $Dir 
rm cross_dzd_star.dat -f
m=0
for num_m in `awk '{print $1}' dzd_star.dat`
do
   ener_dzd_star[${m}]=$(printf "%.5f" `echo "scale=5;${num_m}/1"|bc`)
   m=`expr $m + 1`
done
k=0
for num_k in `awk '{print $2}' dzd_star.dat`
do
   cross_dzd_star[${k}]=$(printf "%.2f" `echo "scale=2;${num_k}/1"|bc`)
   k=`expr $k + 1`
done

for((i=0;i<k;i++))
do 
    echo "${ener_dzd_star[$i]}  ${cross_dzd_star[$i]} " >>cross_dzd_star.dat
done







