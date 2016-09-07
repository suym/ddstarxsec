{
   TChain mcsig4("mc4");
         mcsig4.Add("$HOME/bes/kpi/v0.1/run/hist/mc_psi4260/dd_mc_psi4260_merged_1.root");
   TChain mcsig3("mc4");
         mcsig3.Add("$HOME/bes/kpi/v0.1/run/mc_D0barD0star/D0barD0star.root");


   TChain sig("mc4");
             sig.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barD0_kpi/D0barD0.root");
   TChain sig1("mc4");
             sig1.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barD0star_kpi/D0barD0star_Kpixv.root");
   TChain sig2("mc4");
             sig2.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barD0starpi0_kpi/D0barD0starpi0_Kpixv.root");
   TChain sig3("mc4");
             sig3.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barstarD0_D0bargamma_kpi/D0barstarD0_D0bargamma_Kpixv.root");
   TChain sig4("mc4");
             sig4.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barstarD0_D0barpi0_kpi/D0barstarD0_D0barpi0_Kpixv.root");
   TChain sig5("mc4");
             sig5.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barstarD0star_D0bargamma_kpi/D0barstarD0star_D0bargamma_Kpixv.root");
   TChain sig6("mc4");
             sig6.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D0barstarD0star_D0barpi0_kpi/D0barstarD0star_D0barpi0_Kpixv.root");
   TChain sig7("mc4");
             sig7.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D_starDz_D0barpi_kpi/D_starDz_D0barpi_Kpixv.root");
   TChain sig8("mc4");
             sig8.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/D_starDzstar_D0barpi_kpi/D_starDzstar_D0barpi_Kpixv.root");
   TChain testsig("tree");
             testsig.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/test/Kpi_ana_5w.root");
   TChain test2sig("tree");
             test2sig.Add("/besfs/users/suym/6.6.4.p01/run/Kpi/2test/kpi_ana2_5w.root");
}
