{
   TChain mcsig4("mc4");
         mcsig4.Add("$HOME/bes/kpi/v0.2/run/hist/mc_psi4260/dd_mc_psi4260_merged_1.root");
         //mcsig4.Add("$HOME/bes/kpi/v0.2/run/hist/mc_psi4360/dd_mc_psi4360_merged_1.root");
   TChain mcsig3("mc4");
         mcsig3.Add("$HOME/bes/kpi/v0.2/run/mc_D0barD0star/D0barD0star.root");
   TChain datasig_4260("mc");
         datasig_4260.Add("$HOME/bes/kpi/v0.2/run/hist/data_4260/dd_data_xyz4260_merged_1.root");
   TChain datasig_4360("mc");
         datasig_4360.Add("$HOME/bes/kpi/v0.2/run/hist/data_4360/dd_data_xyz4360_merged_1.root");


   TChain sig("mc4");
             sig.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0_kpi/D0barD0_Kpixv_4260.root");
             //sig.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0_kpi/D0barD0_Kpixv_4360.root");
             //sig.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0_kpi/ISRpsi3770_D0barD0_Kpixv_4260.root");
   TChain sig1("mc4");
             sig1.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0star_kpi/D0barD0star_Kpixv_4260.root");
             //sig.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0_kpi/D0barD0_Kpixv_4360.root");
   TChain sig2("mc4");
             sig2.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0starpi0_kpi/D0barD0starpi0_Kpixv_4260.root");
             //sig2.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barD0starpi0_kpi/D0barD0starpi0_Kpixv_4360.root");
   TChain sig4("mc4");
             sig4.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0_D0bargamma_kpi/D0barstarD0_D0bargamma_Kpixv_4260.root");
             //sig4.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0_D0bargamma_kpi/D0barstarD0_D0bargamma_Kpixv_4360.root");
   TChain sig3("mc4");
             sig3.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0_D0barpi0_kpi/D0barstarD0_D0barpi0_Kpixv_4260.root");
             //sig3.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0_D0barpi0_kpi/D0barstarD0_D0barpi0_Kpixv_4360.root");
   TChain sig6("mc4");
             sig6.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0star_D0bargamma_kpi/D0barstarD0star_D0bargamma_Kpixv_4260.root");
             //sig6.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0star_D0bargamma_kpi/D0barstarD0star_D0bargamma_Kpixv_4360.root");
   TChain sig5("mc4");
             sig5.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0star_D0barpi0_kpi/D0barstarD0star_D0barpi0_Kpixv_4260.root");
             //sig5.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D0barstarD0star_D0barpi0_kpi/D0barstarD0star_D0barpi0_Kpixv_4360.root");
   TChain sig7("mc4");
             sig7.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D_starDz_D0barpi_kpi/D_starDz_D0barpi_Kpixv_4260.root");
             //sig7.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D_starDz_D0barpi_kpi/D_starDz_D0barpi_Kpixv_4360.root");
   TChain sig8("mc4");
             sig8.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D_starDzstar_D0barpi_kpi/D_starDzstar_D0barpi_Kpixv_4260.root");
             //sig8.Add("/besfs/groups/nphy/users/suym/run/ex_mc/D_starDzstar_D0barpi_kpi/D_starDzstar_D0barpi_Kpixv_4360.root");
}
