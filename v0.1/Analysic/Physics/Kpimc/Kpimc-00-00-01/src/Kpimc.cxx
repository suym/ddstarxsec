// e+e- --------->        D0                anti-D0 
//                        |                    |
//                        --> anything         --> K+  pi-  
//by suyumo
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/DeclareFactoryEntries.h"
#include "GaudiKernel/LoadFactoryEntries.h"

    
#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
    
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"

#include "McTruth/McParticle.h"
#include "McTruth/DecayMode.h"
#include "McTruth/MdcMcHit.h"
#include "McTruth/TofMcHit.h"
#include "McTruth/EmcMcHit.h"
#include "McTruth/TofMcHit.h"
#include "McTruth/EmcMcHit.h"
#include "McTruth/MucMcHit.h"
#include "McTruth/McEvent.h"
#include "McTruth/McPrimaryParticle.h"


#include "TMath.h"

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
   
#include "CLHEP/Geometry/Point3D.h"
 

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"             
#include "VertexFit/Helix.h"                  
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/SecondVertexFit.h"

#include "ParticleID/ParticleID.h"

  
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

//
// class declaration
//
class Kpimc : public Algorithm {
  
public:
  Kpimc(const std::string&, ISvcLocator*);
  ~Kpimc(); 
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:
  
  // output file
  std::string m_output_filename;
  bool m_isMonteCarlo; 
  TFile* m_fout;

  
  // define Trees
  TTree* m_tree;

  // common info 
  int m_run;
  int m_event;

  // MC information 
  double m_mc_mom_ee_antiD0_kp;
  double m_mc_mom_ee_antiD0_pim;
  double m_mc_mom_ee_antiD0star_antiD0_kp;
  double m_mc_mom_ee_antiD0star_antiD0_pim;
  double m_mc_mom_ee_D_star_antiD0_kp;
  double m_mc_mom_ee_D_star_antiD0_pim;
  double m_mc_mom_ee_kp;
  double m_mc_mom_ee_pim;
 
  double m_mc1_mom_ee_antiD0D0_kpi;
  double m_mc1_mom_ee_antiD0D0star_kpi;
  double m_mc1_ivtmass_ee_antiD0D0_kpi;
  double m_mc1_ivtmass_ee_antiD0D0star_kpi;
 
  double m_mc2_mom_ee_antiD0starD0_antiD0pi0_kpi;
  double m_mc2_mom_ee_antiD0starD0_antiD0gamma_kpi;
  double m_mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi;
  double m_mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi;
  double m_mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi;
  double m_mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi;
  double m_mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi;
  double m_mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi;

  double m_mc3_mom_ee_D_starDz_antiD0pi_kpi;
  double m_mc3_mom_ee_D_starDzstar_antiD0pi_kpi;
  double m_mc3_ivtmass_ee_D_starDz_antiD0pi_kpi;
  double m_mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi;

  double m_mc4_mom_ee_kpi;
  double m_mc4_ivtmass_ee_kpi;


  // functions
  void book_tree(); 
  void saveGenInfo(); 
};

//
// module declare
//

DECLARE_ALGORITHM_FACTORY( Kpimc )
DECLARE_FACTORY_ENTRIES( Kpimc ) {
  DECLARE_ALGORITHM(Kpimc);
}

LOAD_FACTORY_ENTRIES( Kpimc )

//
// constants
//
//
const double ecms=4.260;
const double ebeam=ecms/2.;
const double PION_MASS = 0.13957;
const double KAON_MASS  = 0.493677;

const static double ctheta( 0.022 );
const static HepLorentzVector p4cm(ecms*sin(ctheta/2.),0.0,0.0,ecms);
const static HepLorentzVector p4cm2(-ecms*sin(ctheta/2.),0.0,0.0,ecms);
const static Hep3Vector LAB2CM( p4cm2.boostVector() );

const int PIONPLUS_PDG_ID = 211;
const int KAONPLUS_PDG_ID = 321;
const int PSI4260_PDG_ID = 9030443;
const int D0_PDG_ID = 421;
const int D0STAR_PDG_ID = 423;
const int DPLUS_PDG_ID = 411;
const int DPLUSSTAR_PDG_ID = 413;
const int PION_PDG_ID = 111;
const int GAMMA_PDG_ID = 22;

//
// member functions
//

Kpimc::Kpimc(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0)
 {;}

StatusCode Kpimc::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd();

  book_tree();

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}

StatusCode Kpimc::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;

  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();


   saveGenInfo(); // only fill tree for the selected events

 return StatusCode::SUCCESS; 
}

StatusCode Kpimc::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Kpimc::~Kpimc() {
}








void Kpimc::book_tree() {

  m_tree=new TTree("mc", "Kpimc");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");


  // MC information 
  if (!m_isMonteCarlo) return;
  m_tree->Branch("mc_mom_ee_antiD0_kp", &m_mc_mom_ee_antiD0_kp, "mc_mom_ee_antiD0_kp/D");
  m_tree->Branch("mc_mom_ee_antiD0_pim", &m_mc_mom_ee_antiD0_pim, "mc_mom_ee_antiD0_pim/D");
  m_tree->Branch("mc_mom_ee_antiD0star_antiD0_kp", &m_mc_mom_ee_antiD0star_antiD0_kp, "mc_mom_ee_antiD0star_antiD0_kp/D");
  m_tree->Branch("mc_mom_ee_antiD0star_antiD0_pim", &m_mc_mom_ee_antiD0star_antiD0_pim, "mc_mom_ee_antiD0star_antiD0_pim/D");
  m_tree->Branch("mc_mom_ee_D_star_antiD0_kp", &m_mc_mom_ee_D_star_antiD0_kp, "mc_mom_ee_D_star_antiD0_kp/D");
  m_tree->Branch("mc_mom_ee_D_star_antiD0_pim", &m_mc_mom_ee_D_star_antiD0_pim, "mc_mom_ee_D_star_antiD0_pim/D");

  m_tree->Branch("mc_mom_ee_kp", &m_mc_mom_ee_kp, "mc_mom_ee_kp/D");
  m_tree->Branch("mc_mom_ee_pim", &m_mc_mom_ee_pim, "mc_mom_ee_pim/D");
  m_tree->Branch("mc3_mom_ee_D_starDz_antiD0pi_kpi", &m_mc3_mom_ee_D_starDz_antiD0pi_kpi, "mc3_mom_ee_D_starDz_antiD0pi_kpi/D");
  m_tree->Branch("mc3_mom_ee_D_starDzstar_antiD0pi_kpi", &m_mc3_mom_ee_D_starDzstar_antiD0pi_kpi, "mc3_mom_ee_D_starDzstar_antiD0pi_kpi/D");
  m_tree->Branch("mc3_ivtmass_ee_D_starDz_antiD0pi_kpi", &m_mc3_ivtmass_ee_D_starDz_antiD0pi_kpi, "mc3_ivtmass_ee_D_starDz_antiD0pi_kpi/D");
  m_tree->Branch("mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi", &m_mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi, "mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi/D");
  m_tree->Branch("mc2_mom_ee_antiD0starD0_antiD0pi0_kpi", &m_mc2_mom_ee_antiD0starD0_antiD0pi0_kpi, "mc2_mom_ee_antiD0starD0_antiD0pi0_kpi/D");
  m_tree->Branch("mc2_mom_ee_antiD0starD0_antiD0gamma_kpi", &m_mc2_mom_ee_antiD0starD0_antiD0gamma_kpi, "mc2_mom_ee_antiD0starD0_antiD0gamma_kpi/D");
  m_tree->Branch("mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi", &m_mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi, "mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi/D");
  m_tree->Branch("mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi", &m_mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi, "mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi/D");
  m_tree->Branch("mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi", &m_mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi, "mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi/D");
  m_tree->Branch("mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi", &m_mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi, "mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi/D");
  m_tree->Branch("mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi", &m_mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi, "mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi/D");
  m_tree->Branch("mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi", &m_mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi, "mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi/D");
  m_tree->Branch("mc1_mom_ee_antiD0D0_kpi", &m_mc1_mom_ee_antiD0D0_kpi, "mc1_mom_ee_antiD0D0_kpi/D");
  m_tree->Branch("mc1_mom_ee_antiD0D0star_kpi", &m_mc1_mom_ee_antiD0D0star_kpi, "mc1_mom_ee_antiD0D0star_kpi/D");
  m_tree->Branch("mc1_ivtmass_ee_antiD0D0_kpi", &m_mc1_ivtmass_ee_antiD0D0_kpi, "mc1_ivtmass_ee_antiD0D0_kpi/D");
  m_tree->Branch("mc1_ivtmass_ee_antiD0D0star_kpi", &m_mc1_ivtmass_ee_antiD0D0star_kpi, "mc1_ivtmass_ee_antiD0D0star_kpi/D");

}




  void Kpimc::saveGenInfo() {
  SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

   int nee_antiD0_k_truth=0;
   int nee_antiD0_pi_truth=0;
   int nee_antiD0star_antiD0_k_truth=0;
   int nee_antiD0star_antiD0_pi_truth=0;
   int nee_D_star_antiD0_k_truth=0;
   int nee_D_star_antiD0_pi_truth=0;
   int nk_truth=0;
   int npi_truth=0;

   int nee_antiD0star_truth=0;
   int nee_antiD0_truth=0;
   int nee_D_star_truth=0;

   int nee_antiD0star_pi0_truth=0;
   int nee_antiD0star_gamma_truth=0;
   int nee_antiD0star_antiD0_truth=0;
   int nee_D_star_pi_truth=0;
   int nee_D_star_antiD0_truth=0;

   int nee_D0_truth=0;
   int nee_D0star_truth=0;
   int nee_Dz_truth=0;
   int nee_Dzstar_truth=0;
   int nee_anything_truth=0;
   int nantiD0star_anything_truth=0;
   int nD_star_anything_truth=0;

   std::vector<HepLorentzVector>  P_ee_antiD0_k, P_ee_antiD0_pi, P_k, P_pi, P_ee_antiD0star_antiD0_k, P_ee_antiD0star_antiD0_pi;
   std::vector<HepLorentzVector>  P_ee_D_star_antiD0_k, P_ee_D_star_antiD0_pi; 

   P_ee_antiD0_k.clear();
   P_ee_antiD0_pi.clear();
   P_ee_antiD0star_antiD0_k.clear();
   P_ee_antiD0star_antiD0_pi.clear();
   P_ee_D_star_antiD0_k.clear();
   P_ee_D_star_antiD0_pi.clear();
   P_k.clear();
   P_pi.clear();

   Event::McParticleCol::iterator iter_mc=mcParticleCol->begin();
   for (; iter_mc != mcParticleCol->end(); iter_mc++){
    if ((*iter_mc)->primaryParticle()) continue;
    if (!(*iter_mc)->decayFromGenerator()) continue;

    HepLorentzVector  mctrue_track = (*iter_mc)->initialFourMomentum();

    if(((*iter_mc)->mother()).particleProperty()==PSI4260_PDG_ID)
       { nee_anything_truth++;  }
    if(((*iter_mc)->mother()).particleProperty()==-D0STAR_PDG_ID)
      {   nantiD0star_anything_truth++;}
    if(((*iter_mc)->mother()).particleProperty()==-DPLUSSTAR_PDG_ID)
      {   nD_star_anything_truth++;}

    if(((*iter_mc)->mother()).particleProperty()==-D0STAR_PDG_ID){
              if((*iter_mc)->particleProperty()==-D0_PDG_ID)
              {  nee_antiD0star_antiD0_truth++;    }
              if((*iter_mc)->particleProperty()==GAMMA_PDG_ID)
              {  nee_antiD0star_gamma_truth++;     }
              if((*iter_mc)->particleProperty()==PION_PDG_ID)
              {  nee_antiD0star_pi0_truth++;       }
       }

    if(((*iter_mc)->mother()).particleProperty()==-DPLUSSTAR_PDG_ID){
              if((*iter_mc)->particleProperty()==-D0_PDG_ID)
              {  nee_D_star_antiD0_truth++;    }
              if((*iter_mc)->particleProperty()==-PIONPLUS_PDG_ID)
              {  nee_D_star_pi_truth++;       }
      }
             
              
       
     

    if(((*iter_mc)->mother().mother()).particleProperty()==PSI4260_PDG_ID){
        if(((*iter_mc)->mother()).particleProperty()==-D0_PDG_ID){
              if((*iter_mc)->particleProperty()==KAONPLUS_PDG_ID)
                   {
                        m_mc_mom_ee_antiD0_kp = mctrue_track.rho();
                        P_ee_antiD0_k.push_back(mctrue_track);
                        nee_antiD0_k_truth++;   
                       }
              
              if((*iter_mc)->particleProperty()==-PIONPLUS_PDG_ID)
                    {
               	       m_mc_mom_ee_antiD0_pim= mctrue_track.rho();
                       P_ee_antiD0_pi.push_back(mctrue_track);
                       nee_antiD0_pi_truth++;
                      }
        }
    }
     
   if(((*iter_mc)->mother().mother().mother()).particleProperty()==PSI4260_PDG_ID){
       if(((*iter_mc)->mother().mother()).particleProperty()==-D0STAR_PDG_ID){
          if(((*iter_mc)->mother()).particleProperty()==-D0_PDG_ID){
              if((*iter_mc)->particleProperty()==KAONPLUS_PDG_ID)
                {
                        m_mc_mom_ee_antiD0star_antiD0_kp = mctrue_track.rho();
                        P_ee_antiD0star_antiD0_k.push_back(mctrue_track);
                        nee_antiD0star_antiD0_k_truth++;  
                }
              if((*iter_mc)->particleProperty()==-PIONPLUS_PDG_ID)
                {
                        m_mc_mom_ee_antiD0star_antiD0_pim = mctrue_track.rho();
                        P_ee_antiD0star_antiD0_pi.push_back(mctrue_track);
                        nee_antiD0star_antiD0_pi_truth++;  
                }

              }
         }
     }
                   
   if(((*iter_mc)->mother().mother().mother()).particleProperty()==PSI4260_PDG_ID){
       if(((*iter_mc)->mother().mother()).particleProperty()==-DPLUSSTAR_PDG_ID){
          if(((*iter_mc)->mother()).particleProperty()==-D0_PDG_ID){
              if((*iter_mc)->particleProperty()==KAONPLUS_PDG_ID)
                {
                        m_mc_mom_ee_D_star_antiD0_kp = mctrue_track.rho();
                        P_ee_D_star_antiD0_k.push_back(mctrue_track);
                        nee_D_star_antiD0_k_truth++;  
                }
              if((*iter_mc)->particleProperty()==-PIONPLUS_PDG_ID)
                {
                        m_mc_mom_ee_D_star_antiD0_pim = mctrue_track.rho();
                        P_ee_D_star_antiD0_pi.push_back(mctrue_track);
                        nee_D_star_antiD0_pi_truth++;  
                }
           }
       }
   }
               

    if(((*iter_mc)->mother()).particleProperty()==PSI4260_PDG_ID){
   	   if((*iter_mc)->particleProperty()==D0_PDG_ID)
   	      {  nee_D0_truth++;  }
   	   if((*iter_mc)->particleProperty()==-D0_PDG_ID)
   	   	  {  nee_antiD0_truth++;  }
   	   if((*iter_mc)->particleProperty()==D0STAR_PDG_ID)
   	   	  {  nee_D0star_truth++;  }
   	   if((*iter_mc)->particleProperty()==-D0STAR_PDG_ID)
   	   	  {  nee_antiD0star_truth++;  }
   	   if((*iter_mc)->particleProperty()==DPLUS_PDG_ID)
   	   	  {  nee_Dz_truth++;  }
   	   if((*iter_mc)->particleProperty()==DPLUSSTAR_PDG_ID)
   	   	  {  nee_Dzstar_truth++;  }
   	   if((*iter_mc)->particleProperty()==-DPLUSSTAR_PDG_ID)
   	   	  {  nee_D_star_truth++;  }
           
   }


    if((*iter_mc)->particleProperty()==KAONPLUS_PDG_ID)
      {
        m_mc_mom_ee_kp= mctrue_track.rho();
        P_k.push_back(mctrue_track);
        nk_truth++;
       }
       if((*iter_mc)->particleProperty()==-PIONPLUS_PDG_ID)
      {
        m_mc_mom_ee_pim= mctrue_track.rho();
        P_pi.push_back(mctrue_track);
        npi_truth++;
       }


    }
       

     if(nee_antiD0_k_truth==1&&nee_antiD0_pi_truth==1)
      {
             HepLorentzVector P_ee_antiD0_kpi = (P_ee_antiD0_k[0]+P_ee_antiD0_pi[0]);
             P_ee_antiD0_kpi.boost(LAB2CM);
             if(nee_D0_truth==1&&nee_anything_truth==2&&nee_antiD0_truth==1)
               {   m_mc1_mom_ee_antiD0D0_kpi=P_ee_antiD0_kpi.rho();
                   m_mc1_ivtmass_ee_antiD0D0_kpi=P_ee_antiD0_kpi.m(); }
             if(nee_D0star_truth==1&&nee_anything_truth==2&&nee_antiD0_truth==1)
               {   m_mc1_mom_ee_antiD0D0star_kpi=P_ee_antiD0_kpi.rho(); 
                   m_mc1_ivtmass_ee_antiD0D0star_kpi=P_ee_antiD0_kpi.m();  }

      }


      if(nee_antiD0star_antiD0_k_truth==1&&nee_antiD0star_antiD0_pi_truth==1 )
    {
             HepLorentzVector P_ee_antiD0star_antiD0_kpi = (P_ee_antiD0star_antiD0_k[0]+P_ee_antiD0star_antiD0_pi[0]);
             P_ee_antiD0star_antiD0_kpi.boost(LAB2CM);
            if(nee_D0_truth==1&&nee_antiD0star_pi0_truth==1&&nee_anything_truth==2&&nee_antiD0star_truth==1&&nee_antiD0star_antiD0_truth==1&&nantiD0star_anything_truth==2)
             {  m_mc2_mom_ee_antiD0starD0_antiD0pi0_kpi=P_ee_antiD0star_antiD0_kpi.rho();
                m_mc2_ivtmass_ee_antiD0starD0_antiD0pi0_kpi=P_ee_antiD0star_antiD0_kpi.m();  }
            if(nee_D0_truth==1&&nee_antiD0star_gamma_truth==1&&nee_anything_truth==2&&nee_antiD0star_truth==1&&nee_antiD0star_antiD0_truth==1&&nantiD0star_anything_truth==2)
             {  m_mc2_mom_ee_antiD0starD0_antiD0gamma_kpi=P_ee_antiD0star_antiD0_kpi.rho(); 
                m_mc2_ivtmass_ee_antiD0starD0_antiD0gamma_kpi=P_ee_antiD0star_antiD0_kpi.m(); }
            if(nee_D0star_truth==1&&nee_antiD0star_pi0_truth==1&&nee_anything_truth==2&&nee_antiD0star_truth==1&&nee_antiD0star_antiD0_truth==1&&nantiD0star_anything_truth==2)
             {  m_mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi=P_ee_antiD0star_antiD0_kpi.rho(); 
                m_mc2_ivtmass_ee_antiD0starD0star_antiD0pi0_kpi=P_ee_antiD0star_antiD0_kpi.m(); }
            if(nee_D0star_truth==1&&nee_antiD0star_gamma_truth==1&&nee_anything_truth==2&&nee_antiD0star_truth==1&&nee_antiD0star_antiD0_truth==1&&nantiD0star_anything_truth==2)
             {  m_mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi=P_ee_antiD0star_antiD0_kpi.rho(); 
                m_mc2_ivtmass_ee_antiD0starD0star_antiD0gamma_kpi=P_ee_antiD0star_antiD0_kpi.m(); }


  } 


     if( nee_D_star_antiD0_k_truth==1&&nee_D_star_antiD0_pi_truth==1 )
      {
             HepLorentzVector P_ee_D_star_antiD0_kpi = (P_ee_D_star_antiD0_k[0]+P_ee_D_star_antiD0_pi[0]);
             P_ee_D_star_antiD0_kpi.boost(LAB2CM);
           if(nee_Dz_truth==1&&nee_D_star_pi_truth==1&&nee_anything_truth==2&&nee_D_star_truth==1&&nee_D_star_antiD0_truth==1&&nD_star_anything_truth==2)
              {   m_mc3_mom_ee_D_starDz_antiD0pi_kpi=P_ee_D_star_antiD0_kpi.rho();
                  m_mc3_ivtmass_ee_D_starDz_antiD0pi_kpi=P_ee_D_star_antiD0_kpi.m();}
           if(nee_Dzstar_truth==1&&nee_D_star_pi_truth==1&&nee_anything_truth==2&&nee_D_star_truth==1&&nee_D_star_antiD0_truth==1&&nD_star_anything_truth==2)
              {   m_mc3_mom_ee_D_starDzstar_antiD0pi_kpi=P_ee_D_star_antiD0_kpi.rho();
                  m_mc3_ivtmass_ee_D_starDzstar_antiD0pi_kpi=P_ee_D_star_antiD0_kpi.m();}

        }


if( nk_truth>0&&npi_truth>0)
   {
       for ( int i7=0;i7<nk_truth;i7++)
        {
         for ( int i8=0;i8<npi_truth;i8++)
          {  
            HepLorentzVector P4_kpi = (P_k[i7]+P_pi[i8]);
            P4_kpi.boost(LAB2CM); 
            
            m_mc4_ivtmass_ee_kpi=P4_kpi.m();
            m_mc4_mom_ee_kpi=P4_kpi.rho();
            m_tree->Fill();
            m_mc1_mom_ee_antiD0D0_kpi=0; 
            m_mc1_mom_ee_antiD0D0star_kpi=0; 
            m_mc2_mom_ee_antiD0starD0_antiD0pi0_kpi=0;
            m_mc2_mom_ee_antiD0starD0_antiD0gamma_kpi=0;
            m_mc2_mom_ee_antiD0starD0star_antiD0pi0_kpi=0;
            m_mc2_mom_ee_antiD0starD0star_antiD0gamma_kpi=0;
            m_mc3_mom_ee_D_starDz_antiD0pi_kpi=0;
            m_mc3_mom_ee_D_starDzstar_antiD0pi_kpi=0;
         }
       }
   }



}
    

