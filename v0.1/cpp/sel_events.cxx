#include "TTree.h"
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
void sel_events()
{
  TChain *t_data4 = new TChain ("mc4");
  
 
  t_data4->Add("/afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.1/run/hist/mc_psi4260/dd_mc_psi4260_merged_1.root");


  Double_t  mc4_mom_ee_kpi, mc4_ivtmass_ee_kpi, mc1_mom_ee_antiD0D0_kpi, mc1_mom_ee_antiD0D0star_kpi, mc1_mom_ee_kpi, mc1_ivtmass_ee_kpi,
  mc2_mom_ee_antiD0starD0_antiD0pi0_kpi, mc2_mom_ee_antiD0starD0_antiD0gamma_kpi, mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi, mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi, mc2_mom_ee_kpi, mc2_ivtmass_ee_kpi, mc3_mom_ee_D_starDz_antiD0pi_kpi, mc3_mom_ee_D_starDzstar_antiD0pi_kpi, mc3_mom_ee_kpi, mc3_ivtmass_ee_kpi; 


  t_data4->SetBranchAddress("mc4_mom_ee_kpi",&mc4_mom_ee_kpi);
  t_data4->SetBranchAddress("mc4_ivtmass_ee_kpi",&mc4_ivtmass_ee_kpi);
  t_data4->SetBranchAddress("mc1_mom_ee_antiD0D0_kpi",&mc1_mom_ee_antiD0D0_kpi);
  t_data4->SetBranchAddress("mc1_mom_ee_antiD0D0star_kpi",&mc1_mom_ee_antiD0D0star_kpi);
  t_data4->SetBranchAddress("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi",&mc2_mom_ee_antiD0starD0_antiD0pi0_kpi);
  t_data4->SetBranchAddress("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi",&mc2_mom_ee_antiD0starD0_antiD0gamma_kpi);
  t_data4->SetBranchAddress("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi",&mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi);
  t_data4->SetBranchAddress("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi",&mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi);
  t_data4->SetBranchAddress("mc3_mom_ee_D_starDz_antiD0pi_kpi",&mc3_mom_ee_D_starDz_antiD0pi_kpi);
  t_data4->SetBranchAddress("mc3_mom_ee_D_starDzstar_antiD0pi_kpi",&mc3_mom_ee_D_starDzstar_antiD0pi_kpi);
  

  TFile* outputF = new TFile("../run/hist/mc_psi4260/testdd.root", "recreate");
  TTree* DDkpi4 = t_data4->CloneTree(0);


  int n_total=0,n_slec=0,n_slec1=0,n_slec2=0,n_slec3=0,n_slec4=0,n_slec5=0,n_slec6=0,n_slec7=0,n_slec8=0,n_slec9=0;
  for(int i=0; i<t_data4->GetEntries(); i++){
     t_data4->GetEntry(i);
     n_slec4++;
     { 
       if(mc4_ivtmass_ee_kpi>1.84984&&mc4_ivtmass_ee_kpi<1.87984)
      { DDkpi4->Fill();}
     }
}

  DDkpi4->Write();



  outputF->Close();
  cout<<"slec4  events="<<n_slec4<<endl;


}

