#!/bin/bash

Dir_first=/besfs/groups/nphy/users/xiaosy/yumo/simufit_D0bar


declare -a array=(3890 3900 3950 3980 4010 4030 4040 4055 4070)
declare -a array1=(4090 4120 4140 4150 4170 4190 4210 4220 4230 4245 4310 4360 4390)

for num in ${array[@]}
do

  cd ${Dir_first}/${num}/
  echo "{" > datafile_${num}.C 
  echo "TFile *f_data = new TFile(\"\$HOME/bes/kpi/v0.2/run/hist/data_${num}/dd_data_xyz${num}_merged_1.root\");" >> datafile_${num}.C 
  echo "  TTree *t_data = f_data->Get(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "TChain t_sig(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barD0_kpi/${num}/D0barD0_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig1(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig1.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barD0star_kpi/${num}/D0barD0star_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig4(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig4.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barstarD0_D0bargamma_kpi/${num}/D0barstarD0_D0bargamma_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig3(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig3.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barstarD0_D0barpi0_kpi/${num}/D0barstarD0_D0barpi0_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig7(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig7.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D_starDz_D0barpi_kpi/${num}/D_starDz_D0barpi_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "}" >> datafile_${num}.C 

done

for num in ${array1[@]}
do

  cd ${Dir_first}/${num}/
  echo "{" > datafile_${num}.C 
  echo "TFile *f_data = new TFile(\"\$HOME/bes/kpi/v0.2/run/hist/data_${num}/dd_data_xyz${num}_merged_1.root\");" >> datafile_${num}.C 
  echo "  TTree *t_data = f_data->Get(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "TChain t_sig(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barD0_kpi/${num}/D0barD0_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig1(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig1.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barD0star_kpi/${num}/D0barD0star_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig4(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig4.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barstarD0_D0bargamma_kpi/${num}/D0barstarD0_D0bargamma_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig3(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig3.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D0barstarD0_D0barpi0_kpi/${num}/D0barstarD0_D0barpi0_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig7(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig7.Add(\"/besfs/groups/nphy/users/xiaosy/yumo/third_iteration_ex_mc/D_starDz_D0barpi_kpi/${num}/D_starDz_D0barpi_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "TChain t_sig6(\"D0bar_kpi\");" >> datafile_${num}.C 
  echo "  t_sig6.Add(\"/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0star_D0bargamma_kpi/${num}/D0barstarD0star_D0bargamma_Kpixv_${num}.root\");" >> datafile_${num}.C 
  echo "}" >> datafile_${num}.C 

done

  cd ${Dir_first}


