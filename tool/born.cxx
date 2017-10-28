#include "TMath.h"
#include <math.h>
#include <fstream.h>
#include <iomanip.h>
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <math.h>
#include <Math/ProbFunc.h>
#include <Math/ProbFuncMathCore.h>
gSystem->Load("libRooFit");
using namespace RooFit;
using namespace std;

void born(){
  gROOT->ProcessLine(".x datafile_3890.C"); //3890



  const double MC_num= 25000;
  const double br_D0_kpi= 0.0393;
  const double br_D_star_D0pi= 0.667;
  const double br_D0star_D0pi= 0.655;
  const double br_D0star_D0gam= 0.345;


  const double vp= 1.052;        //3890
  const double int_lum= 7.758;    //3890
const double rad_cor_D0D0= 0.868368; //3890
const double rad_cor_D0D0star= 0.781190; //3890
const double rad_cor_D0D0star_D0= 0.781520; //3890
const double rad_cor_DzD_star= 0.781498; //3890

  const double x1min= 0.09;//3890
  const double x1max= 0.59;//3890
  const double n1bin= 130;//3890
  TCut cut1 = "vtx_mom_kpi>0.09&&vtx_mom_kpi<0.59";//3890


  RooRealVar xreg("xreg", "xreg", x1min,x1max);


  TH1F *hall1= new TH1F("hall1","",n1bin, x1min, x1max);
  TH1F *hall2= new TH1F("hall2","",n1bin, x1min, x1max);
  TH1F *hall3= new TH1F("hall3","",n1bin, x1min, x1max);
  TH1F *hall4= new TH1F("hall4","",n1bin, x1min, x1max);
  TH1F *hall5= new TH1F("hall5","",n1bin, x1min, x1max);

  TCut cut12 = "vtx_coskpi>-0.998";
  TCut cut15 = "abs(vtx_mkpi-1.86484)<0.01625";
  
  t_sig.Draw("vtx_mom_kpi>>hall1",cut15&&cut12&&cut1);
  t_sig1.Draw("vtx_mom_kpi>>hall2",cut15&&cut12&&cut1);
  t_sig3.Draw("vtx_mom_kpi>>hall3",cut15&&cut12&&cut1);
  t_sig4.Draw("vtx_mom_kpi>>hall4",cut15&&cut12&&cut1);
  t_sig7.Draw("vtx_mom_kpi>>hall5",cut15&&cut12&&cut1);

  Double_t D0D0bar_eff= hall1->GetEntries()/MC_num;
  Double_t D0starD0bar_eff= hall2->GetEntries()/MC_num;
  Double_t D0D0barstar_D0barpi_eff= hall3->GetEntries()/MC_num;
  Double_t D0D0barstar_D0bargam_eff= hall4->GetEntries()/MC_num;
  Double_t DzD_star_eff= hall5->GetEntries()/MC_num;

  Double_t sigma[4],sierr[4],born[4],born_err[4];
  ifstream openfile;
  openfile.open("fit_3890.dat");
  for (Int_t i = 0; i<4; i++)
  {
    openfile>>sigma[i];
    openfile>>sierr[i];
  }
 
  born[0]=sigma[0]/(int_lum*D0D0bar_eff*rad_cor_D0D0*vp*br_D0_kpi);
  born_err[0]=sierr[0]/(int_lum*D0D0bar_eff*rad_cor_D0D0*vp*br_D0_kpi);
  born[1]=sigma[1]/(int_lum*D0starD0bar_eff*rad_cor_D0D0star*vp*br_D0_kpi);
  born_err[1]=sierr[1]/(int_lum*D0starD0bar_eff*rad_cor_D0D0star*vp*br_D0_kpi);
  born[2]=sigma[2]/(int_lum*(D0D0barstar_D0barpi_eff*br_D0star_D0pi+D0D0barstar_D0bargam_eff*br_D0star_D0gam)*rad_cor_D0D0star_D0*vp*br_D0_kpi);
  born_err[2]=sierr[2]/(int_lum*(D0D0barstar_D0barpi_eff*br_D0star_D0pi+D0D0barstar_D0bargam_eff*br_D0star_D0gam)*rad_cor_D0D0star_D0*vp*br_D0_kpi);
  born[3]=sigma[3]/(int_lum*DzD_star_eff*rad_cor_DzD_star*vp*br_D0_kpi*br_D_star_D0pi);
  born_err[3]=sierr[3]/(int_lum*DzD_star_eff*rad_cor_DzD_star*vp*br_D0_kpi*br_D_star_D0pi);
  


  ofstream  out;
  out.open("3890_born.dat");

  out<<"the born cross section of D0D0bar"<<"    "<<born[0]<<"    "<<born_err[0]<<endl;
  out<<"the born cross section of D0starD0bar"<<"    "<<born[1]<<"    "<<born_err[1]<<endl;
  out<<"the born cross section of D0D0barstar"<<"    "<<born[2]<<"    "<<born_err[2]<<endl;
  out<<"the born cross section of DzD_star"<<"    "<<born[3]<<"    "<<born_err[3]<<endl;
  out<<"\n"<<endl;
  out<<"The efficiency of D0D0bar "<<"    "<<D0D0bar_eff<<endl;
  out<<"The efficiency of D0starD0bar"<<"    "<<D0starD0bar_eff<<endl;
  out<<"The efficiency of D0D0barstar"<<"    "<<(D0D0barstar_D0barpi_eff*br_D0star_D0pi+D0D0barstar_D0bargam_eff*br_D0star_D0gam)<<endl;
  out<<"The efficiency of D0D0barstar_D0barpi"<<"    "<<(D0D0barstar_D0barpi_eff)<<endl;
  out<<"The efficiency of D0D0barstar_D0bargam"<<"    "<<(D0D0barstar_D0bargam_eff)<<endl;
  out<<"The efficiency of DzD_star"<<"    "<<DzD_star_eff<<endl;
  

  cout<<"the born cross section of D0D0bar"<<"    "<<born[0]<<"    "<<born_err[0]<<endl;
  cout<<"the born cross section of D0starD0bar"<<"    "<<born[1]<<"    "<<born_err[1]<<endl;
  cout<<"the born cross section of D0D0barstar"<<"    "<<born[2]<<"    "<<born_err[2]<<endl;
  cout<<"the born cross section of DzD_star"<<"    "<<born[3]<<"    "<<born_err[3]<<endl;
  cout<<"\n"<<endl;
  cout<<"The efficiency of D0D0bar "<<"    "<<D0D0bar_eff<<endl;
  cout<<"The efficiency of D0starD0bar"<<"    "<<D0starD0bar_eff<<endl;
  cout<<"The efficiency of D0D0barstar"<<"    "<<(D0D0barstar_D0barpi_eff*br_D0star_D0pi+D0D0barstar_D0bargam_eff*br_D0star_D0gam)<<endl;
  cout<<"The efficiency of D0D0barstar_D0barpi"<<"    "<<(D0D0barstar_D0barpi_eff)<<endl;
  cout<<"The efficiency of D0D0barstar_D0bargam"<<"    "<<(D0D0barstar_D0bargam_eff)<<endl;
  cout<<"The efficiency of DzD_star"<<"    "<<DzD_star_eff<<endl;
  cout<<"The ratio of  D0barpi "<<"    "<< (1/((D0D0barstar_D0barpi_eff/D0D0barstar_D0bargam_eff)*1.9+1))*1.9*(D0D0barstar_D0barpi_eff/D0D0barstar_D0bargam_eff)<<endl;
  cout<<"The ratio of  D0bargam "<<"    "<< (1/((D0D0barstar_D0barpi_eff/D0D0barstar_D0bargam_eff)*1.9+1))<<endl;


}
