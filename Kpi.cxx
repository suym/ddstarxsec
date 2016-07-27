// e+e- --------->        D*                          anti-D0 
//                        |                            |
//                        --> D0  pi0                  --> K+  pi- 
//                             |    |
//                             |    -->  gamma  gamma 
//                             --> K-  pi+ 
//by su
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
    
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
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
using CLHEP::Hep3Vector;          //3维向量
using CLHEP::Hep2Vector;          //2维向量
using CLHEP::HepLorentzVector;    //洛伦兹向量
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
   typedef HepGeom::Point3D<double> HepPoint3D;  //typedef定义类型
#endif 
#include "KpiAlg/Kpi.h"

#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"             // Vertex顶点
#include "VertexFit/Helix.h"                  //Helix螺旋
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/SecondVertexFit.h"

#include "ParticleID/ParticleID.h"

#include <vector>

const double ecms=4.260;
const double ebeam=ecms/2.;
const double mpi = 0.13957;
const double mK  = 0.493677;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
const double velc = 299.792458;   // tof path unit in mm

const static double ctheta( 0.022 );
const static HepLorentzVector p4cm(ecms*sin(ctheta/2.),0.0,0.0,ecms);
const static HepLorentzVector p4cm2(-ecms*sin(ctheta/2.),0.0,0.0,ecms);
const static Hep3Vector LAB2CM( p4cm2.boostVector() );

typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
typedef std::vector<HepLorentzVector> Vp4;

//declare one counter
static int counter[10]={0,0,0,0,0,0,0,0,0,0};
/////////////////////////////////////////////////////////////////////////////
// instructor function
Kpi::Kpi(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  //Declare the properties
    declareProperty("debug", debug = 1);
    declareProperty("EnergyThreshold", m_energyThreshold=0.04);
    declareProperty("GammaAngleCut", m_gammaAngleCut=20.0);
    declareProperty("Test5C", m_test5C = 1);   
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Kpi::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in initialize()" << endmsg;
  StatusCode status;
  NTuplePtr nt1(ntupleSvc(), "FILE1/tree");
  if ( nt1 ) m_tuple1 = nt1;
  else {
    m_tuple1 = ntupleSvc()->book ("FILE1/tree", CLID_ColumnWiseTuple, "Kpi N-Tuple");
    if ( m_tuple1 )    {

    status = m_tuple1->addItem ("Mpi0", m_pi0); //invarious mass of gammagamma
    status = m_tuple1->addItem ("MD0star", m_D0star);   //invarious mass of k-pi+gammagamma
    status = m_tuple1->addItem ("Manti_D0", m_anti_D0);  //invarious mass of k+pi-
    status = m_tuple1->addItem ("MD0", m_D0); //invarious mass of k-pi+
    status = m_tuple1->addItem ("MManti_D0", m_MManti_D0);   //recoil mass of k- pi+ gammagamma
    status = m_tuple1->addItem ("MMD0star", m_MMD0star);   //recoil mass of pi- k+
    
    status = m_tuple1->addItem ("MMpi0", m_MMpi0);   
    status = m_tuple1->addItem ("MMD0antiD0", m_MMD0antiD0);  
    status = m_tuple1->addItem ("chi2", m_chi2);
    status = m_tuple1->addItem ("psip",  m_psip);
    
    status = m_tuple1->addItem ("chisqD0",  m_chisqD0);
    status = m_tuple1->addItem ("Gamnumber",  m_Gamnumber);
   // status = m_tuple1->addItem ("chargedTrk",  m_chargedTrk);
    
    status = m_tuple1->addItem ("D0p",  m_D0p);
    status = m_tuple1->addItem ("Mbc",  m_Mbc);
    status = m_tuple1->addItem ("deltaE",  m_deltaE);
    
    status = m_tuple1->addItem ("chisqanti_D0",  m_chisqanti_D0);
   
    status=m_tuple1->addItem("indexmc",m_nmcps,0,100);
    status=m_tuple1->addIndexedItem("pdgid",m_nmcps,m_pid);
    status=m_tuple1->addIndexedItem("motheridx",m_nmcps,m_midx);
    status = m_tuple1->addItem ("costheta",  m_costheta);
    status = m_tuple1->addItem ("cosalpha",  m_cosalpha);
  
    
    status = m_tuple1->addItem ("ee_antiD0_k_p_mc",  m_ee_antiD0_k_p_mc);
    status = m_tuple1->addItem ("ee_antiD0_pi_p_mc",  m_ee_antiD0_pi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0star_antiD0_k_p_mc",  m_ee_antiD0star_antiD0_k_p_mc);
    status = m_tuple1->addItem ("ee_antiD0star_antiD0_pi_p_mc",  m_ee_antiD0star_antiD0_pi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0star_pi0_p_mc",  m_ee_antiD0star_pi0_p_mc);
    status = m_tuple1->addItem ("ee_antiD0star_gamma_p_mc",  m_ee_antiD0star_gamma_p_mc);
    status = m_tuple1->addItem ("ee_D0_p_mc",      m_ee_D0_p_mc);
    status = m_tuple1->addItem ("ee_D0star_p_mc",          m_ee_D0star_p_mc);
    status = m_tuple1->addItem ("ee_D_star_antiD0_k_p_mc",     m_ee_D_star_antiD0_k_p_mc);
    status = m_tuple1->addItem ("ee_D_star_antiD0_pi_p_mc",  m_ee_D_star_antiD0_pi_p_mc);
    status = m_tuple1->addItem ("ee_D_star_pi_p_mc",  m_ee_D_star_pi_p_mc); 
    status = m_tuple1->addItem ("ee_Dz_p_mc",  m_ee_Dz_p_mc);
    status = m_tuple1->addItem ("ee_Dzstar_p_mc",  m_ee_Dzstar_p_mc);
    status = m_tuple1->addItem ("ee_pi0_p_mc",  m_ee_pi0_p_mc);
    status = m_tuple1->addItem ("k_p_mc",  m_k_p_mc);
    status = m_tuple1->addItem ("pi_p_mc",  m_pi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0_kpi_p_mc",  m_ee_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0D0_kpi_p_mc",  m_ee_antiD0D0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0D0star_kpi_p_mc",  m_ee_antiD0D0star_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0D0pi0_kpi_p_mc",  m_ee_antiD0D0pi0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0D0starpi0_kpi_p_mc",  m_ee_antiD0D0starpi0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0D0starpi0pi0_kpi_p_mc",  m_ee_antiD0D0starpi0pi0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0star_antiD0_kpi_p_mc",  m_ee_antiD0star_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0_antiD0_kpi_p_mc",  m_ee_antiD0starD0_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0_antiD0pi0_kpi_p_mc",  m_ee_antiD0starD0_antiD0pi0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0_antiD0gamma_kpi_p_mc",  m_ee_antiD0starD0_antiD0gamma_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0star_antiD0_kpi_p_mc",  m_ee_antiD0starD0star_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0star_antiD0pi0_kpi_p_mc",  m_ee_antiD0starD0star_antiD0pi0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0star_antiD0gamma_kpi_p_mc",  m_ee_antiD0starD0star_antiD0gamma_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0pi0_antiD0_kpi_p_mc",  m_ee_antiD0starD0pi0_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_antiD0starD0starpi0_antiD0_kpi_p_mc",  m_ee_antiD0starD0starpi0_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_star_antiD0_kpi_p_mc",  m_ee_D_star_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDz_antiD0_kpi_p_mc",  m_ee_D_starDz_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDz_antiD0pi_kpi_p_mc",  m_ee_D_starDz_antiD0pi_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDzstar_antiD0_kpi_p_mc",  m_ee_D_starDzstar_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDzstar_antiD0pi_kpi_p_mc",  m_ee_D_starDzstar_antiD0pi_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDzpi0_antiD0_kpi_p_mc",  m_ee_D_starDzpi0_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("ee_D_starDzstarpi0_antiD0_kpi_p_mc",  m_ee_D_starDzstarpi0_antiD0_kpi_p_mc);
    status = m_tuple1->addItem ("kpi_p_mc",  m_kpi_p_mc);
    status = m_tuple1->addItem ("kpi_m_mc",  m_kpi_m_mc);
 
     }
      else    {
	log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
	return StatusCode::FAILURE;
      }
    }

    NTuplePtr nt0(ntupleSvc(), "FILE1/mc");
    if ( nt0 ) m_tuple0 = nt0;
    else {
    m_tuple0 = ntupleSvc()->book ("FILE1/mc", CLID_ColumnWiseTuple, "mc");
    if ( m_tuple0 )    {
             

   // topology
    status = m_tuple0->addItem ("rec", m_rec0);
    status = m_tuple0->addItem ("run", m_run0); 
    
    status=m_tuple0->addItem("indexmc",m_nmcps0,0,100);
    status=m_tuple0->addIndexedItem("pdgid",m_nmcps0,m_pid0);
    status=m_tuple0->addIndexedItem("motheridx",m_nmcps0,m_midx0);

    status = m_tuple0->addItem ("ee_antiD0_k_p_mc0",  m_ee_antiD0_k_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0_pi_p_mc0",  m_ee_antiD0_pi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0star_antiD0_k_p_mc0",  m_ee_antiD0star_antiD0_k_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0star_antiD0_pi_p_mc0",  m_ee_antiD0star_antiD0_pi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0star_pi0_p_mc0",  m_ee_antiD0star_pi0_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0star_gamma_p_mc0",  m_ee_antiD0star_gamma_p_mc0);
    status = m_tuple0->addItem ("ee_D0_p_mc0",      m_ee_D0_p_mc0);
    status = m_tuple0->addItem ("ee_D0star_p_mc0",          m_ee_D0star_p_mc0);
    status = m_tuple0->addItem ("ee_D_star_antiD0_k_p_mc0",     m_ee_D_star_antiD0_k_p_mc0);
    status = m_tuple0->addItem ("ee_D_star_antiD0_pi_p_mc0",  m_ee_D_star_antiD0_pi_p_mc0);
    status = m_tuple0->addItem ("ee_D_star_pi_p_mc0",  m_ee_D_star_pi_p_mc0); 
    status = m_tuple0->addItem ("ee_Dz_p_mc0",  m_ee_Dz_p_mc0);
    status = m_tuple0->addItem ("ee_Dzstar_p_mc0",  m_ee_Dzstar_p_mc0);
    status = m_tuple0->addItem ("ee_pi0_p_mc0",  m_ee_pi0_p_mc0);
    status = m_tuple0->addItem ("k_p_mc0",  m_k_p_mc0);
    status = m_tuple0->addItem ("pi_p_mc0",  m_pi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0_kpi_p_mc0",  m_ee_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0D0_kpi_p_mc0",  m_ee_antiD0D0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0D0star_kpi_p_mc0",  m_ee_antiD0D0star_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0D0pi0_kpi_p_mc0",  m_ee_antiD0D0pi0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0D0starpi0_kpi_p_mc0",  m_ee_antiD0D0starpi0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0D0starpi0pi0_kpi_p_mc0",  m_ee_antiD0D0starpi0pi0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0star_antiD0_kpi_p_mc0",  m_ee_antiD0star_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0_antiD0_kpi_p_mc0",  m_ee_antiD0starD0_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0_antiD0pi0_kpi_p_mc0",  m_ee_antiD0starD0_antiD0pi0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0_antiD0gamma_kpi_p_mc0",  m_ee_antiD0starD0_antiD0gamma_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0star_antiD0_kpi_p_mc0",  m_ee_antiD0starD0star_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0star_antiD0pi0_kpi_p_mc0",  m_ee_antiD0starD0star_antiD0pi0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0star_antiD0gamma_kpi_p_mc0",  m_ee_antiD0starD0star_antiD0gamma_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0pi0_antiD0_kpi_p_mc0",  m_ee_antiD0starD0pi0_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_antiD0starD0starpi0_antiD0_kpi_p_mc0",  m_ee_antiD0starD0starpi0_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_star_antiD0_kpi_p_mc0",  m_ee_D_star_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDz_antiD0_kpi_p_mc0",  m_ee_D_starDz_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDz_antiD0pi_kpi_p_mc0",  m_ee_D_starDz_antiD0pi_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDzstar_antiD0_kpi_p_mc0",  m_ee_D_starDzstar_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDzstar_antiD0pi_kpi_p_mc0",  m_ee_D_starDzstar_antiD0pi_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDzpi0_antiD0_kpi_p_mc0",  m_ee_D_starDzpi0_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("ee_D_starDzstarpi0_antiD0_kpi_p_mc0",  m_ee_D_starDzstarpi0_antiD0_kpi_p_mc0);
    status = m_tuple0->addItem ("kpi_p_mc0",  m_kpi_p_mc0);


}
    else    {
    log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple0) << endmsg;
    return StatusCode::FAILURE;
      }
    }




  //
  //--------end of book--------
  //

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Kpi::execute() {
  
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  counter[0]++;
//  setFilterPassed(false); 
  SmartDataPtr<Event::EventHeader>      eventHeader(eventSvc(),"/Event/EventHeader");
  SmartDataPtr<EvtRecEvent>             evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
  SmartDataPtr<EvtRecTrackCol>          evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);
  if(evtRecEvent->totalTracks()>50)  { return StatusCode::SUCCESS;}
  int m_run0 = eventHeader->runNumber();
  int m_rec0 = eventHeader->eventNumber();
   

      int nee_antiD0_k_truth0=0;
      int nee_antiD0_pi_truth0=0;
      int nee_antiD0star_antiD0_k_truth0=0;
      int nee_antiD0star_antiD0_pi_truth0=0; 
      int nee_antiD0star_pi0_truth0=0;
      int nee_antiD0star_gamma_truth0=0;
      int nee_D0_truth0=0;
      int nee_D0star_truth0=0;
      int nee_D_star_antiD0_k_truth0=0;
      int nee_D_star_antiD0_pi_truth0=0;
      int nee_D_star_pi_truth0=0;
      int nee_Dz_truth0=0;
      int nee_Dzstar_truth0=0;
      int nee_pi0_truth0=0;
      int nk_truth0=0;
      int npi_truth0=0;
      int nee_anything_truth0=0;

      Vp4 P0_ee_antiD0_k;
      Vp4 P0_ee_antiD0_pi;
      Vp4 P0_ee_antiD0star_antiD0_k;
      Vp4 P0_ee_antiD0star_antiD0_pi;
      Vp4 P0_ee_D_star_antiD0_k;
      Vp4 P0_ee_D_star_antiD0_pi;
      Vp4 P0_k;
      Vp4 P0_pi;
      P0_ee_antiD0_k.clear();
      P0_ee_antiD0_pi.clear();
      P0_ee_antiD0star_antiD0_k.clear();
      P0_ee_antiD0star_antiD0_pi.clear();
      P0_ee_D_star_antiD0_k.clear();
      P0_ee_D_star_antiD0_pi.clear();
      P0_k.clear();
      P0_pi.clear();
    
     
      if (eventHeader->runNumber()<0)
    {
    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
    if(!mcParticleCol)
      {
        std::cout<<"Could not retrieve McParticelCol"<<std::endl;
        return(StatusCode::FAILURE);  
      }
    Event::McParticleCol::iterator iter_mc0=mcParticleCol->begin();
    m_nmcps0=0;
    bool jpsiDecay0(false);
    int rootIndex0(-1);
    for (;iter_mc0!=mcParticleCol->end();iter_mc0++)
      {
        if((*iter_mc0)->primaryParticle()) continue;
        if(!(*iter_mc0)->decayFromGenerator()) continue;
        if((*iter_mc0)->particleProperty()==9030443)
          {
            jpsiDecay0=true;
            rootIndex0=(*iter_mc0)->trackIndex();
          }
        if(!jpsiDecay0) continue;
        m_pid0[m_nmcps0]=(*iter_mc0)->particleProperty();
        if(((*iter_mc0)->mother()).particleProperty()==9030443) m_midx0[m_nmcps0]=((*iter_mc0)->mother()).trackIndex()-rootIndex0;
        else m_midx0[m_nmcps0]=((*iter_mc0)->mother()).trackIndex()-rootIndex0-1;
        if((*iter_mc0)->particleProperty()==9030443) m_midx0[m_nmcps0]=0;
        m_nmcps0++;

        HepLorentzVector  mctrue_track0 = (*iter_mc0)->initialFourMomentum();

          
        if(((*iter_mc0)->mother()).particleProperty()==9030443)
       { nee_anything_truth0++;  }
            
         if((*iter_mc0)->particleProperty()==321&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==9030443)
       {  
         m_ee_antiD0_k_p_mc0 = mctrue_track0.rho();
         P0_ee_antiD0_k.push_back(mctrue_track0);
         nee_antiD0_k_truth0++;
       }
        if((*iter_mc0)->particleProperty()==-211&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0_pi_p_mc0= mctrue_track0.rho();
        P0_ee_antiD0_pi.push_back(mctrue_track0);
        nee_antiD0_pi_truth0++;
       }
        if((*iter_mc0)->particleProperty()==321&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==-423&&((*iter_mc0)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_antiD0_k_p_mc0= mctrue_track0.rho();
        P0_ee_antiD0star_antiD0_k.push_back(mctrue_track0);
        nee_antiD0star_antiD0_k_truth0++;
       }
        if((*iter_mc0)->particleProperty()==-211&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==-423&&((*iter_mc0)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_antiD0_pi_p_mc0= mctrue_track0.rho();
        P0_ee_antiD0star_antiD0_pi.push_back(mctrue_track0);
        nee_antiD0star_antiD0_pi_truth0++;
       }
        if((*iter_mc0)->particleProperty()==111&&((*iter_mc0)->mother()).particleProperty()==-423&&((*iter_mc0)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_pi0_p_mc0= mctrue_track0.rho();
        nee_antiD0star_pi0_truth0++;
       }
        if((*iter_mc0)->particleProperty()==22&&((*iter_mc0)->mother()).particleProperty()==-423&&((*iter_mc0)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_gamma_p_mc0= mctrue_track0.rho();
        nee_antiD0star_gamma_truth0++;
       }
        if((*iter_mc0)->particleProperty()==421&&((*iter_mc0)->mother()).particleProperty()==9030443)
      {
        m_ee_D0_p_mc0= mctrue_track0.rho();
        nee_D0_truth0++;
       }
        if((*iter_mc0)->particleProperty()==423&&((*iter_mc0)->mother()).particleProperty()==9030443)
      {
        m_ee_D0star_p_mc0= mctrue_track0.rho();
        nee_D0star_truth0++;
       }
        if((*iter_mc0)->particleProperty()==321&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==-413&&((*iter_mc0)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_antiD0_k_p_mc0= mctrue_track0.rho();
        P0_ee_D_star_antiD0_k.push_back(mctrue_track0);
        nee_D_star_antiD0_k_truth0++;
       }
        if((*iter_mc0)->particleProperty()==-211&&((*iter_mc0)->mother()).particleProperty()==-421&&((*iter_mc0)->mother().mother()).particleProperty()==-413&&((*iter_mc0)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_antiD0_pi_p_mc0= mctrue_track0.rho();
        P0_ee_D_star_antiD0_pi.push_back(mctrue_track0);
        nee_D_star_antiD0_pi_truth0++;
       }
       if((*iter_mc0)->particleProperty()==-211&&((*iter_mc0)->mother()).particleProperty()==-413&&((*iter_mc0)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_pi_p_mc0= mctrue_track0.rho();
        nee_D_star_pi_truth0++;
       }
       if((*iter_mc0)->particleProperty()==411&&((*iter_mc0)->mother()).particleProperty()==9030443)
      {
        m_ee_Dz_p_mc0= mctrue_track0.rho();
        nee_Dz_truth0++;
       }
        if((*iter_mc0)->particleProperty()==413&&((*iter_mc0)->mother()).particleProperty()==9030443)
      {
        m_ee_Dzstar_p_mc0= mctrue_track0.rho();
        nee_Dzstar_truth0++;
       }
       if((*iter_mc0)->particleProperty()==111&&((*iter_mc0)->mother()).particleProperty()==9030443)
      {
        m_ee_pi0_p_mc0= mctrue_track0.rho();
        nee_pi0_truth0++;
       }
       if((*iter_mc0)->particleProperty()==321)
      {
        m_k_p_mc0= mctrue_track0.rho();
        P0_k.push_back(mctrue_track0);
        nk_truth0++;
       }
       if((*iter_mc0)->particleProperty()==-211)
      {
        m_pi_p_mc0= mctrue_track0.rho();
        P0_pi.push_back(mctrue_track0);
        npi_truth0++;
       }

     }
       for (int i1=0;i1<nee_antiD0_k_truth0;i1++)
       {
         for (int i2=0;i2<nee_antiD0_pi_truth0;i2++)
          {
            m_ee_antiD0_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            if(nee_D0_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
             m_ee_antiD0D0_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
             m_ee_antiD0D0star_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            }
            if(nee_D0_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
             m_ee_antiD0D0pi0_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
             m_ee_antiD0D0starpi0_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==2&&nee_anything_truth0==4)
            {
             m_ee_antiD0D0starpi0pi0_kpi_p_mc0=(P0_ee_antiD0_k[i1]+P0_ee_antiD0_pi[i2]).rho();
            }

          }
        }
        for (int i3=0;i3<nee_antiD0star_antiD0_k_truth0;i3++)
       {
         for (int i4=0;i4<nee_antiD0star_antiD0_pi_truth0;i4++)
          {
            m_ee_antiD0star_antiD0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            if(nee_D0_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0_antiD0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0_truth0==1&&nee_pi0_truth0==0&&nee_antiD0star_pi0_truth0==1&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0_antiD0pi0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0_truth0==1&&nee_pi0_truth0==0&&nee_antiD0star_gamma_truth0==1&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0_antiD0gamma_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0star_antiD0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==0&&nee_antiD0star_pi0_truth0==1&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0star_antiD0pi0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==0&&nee_antiD0star_gamma_truth0==1&&nee_anything_truth0==2)
            {
            m_ee_antiD0starD0star_antiD0gamma_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }

            if(nee_D0_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
            m_ee_antiD0starD0pi0_antiD0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }
            if(nee_D0star_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
            m_ee_antiD0starD0starpi0_antiD0_kpi_p_mc0=(P0_ee_antiD0star_antiD0_k[i3]+P0_ee_antiD0star_antiD0_pi[i4]).rho();
            }

          }
        }

       for (int i5=0;i5<nee_D_star_antiD0_k_truth0;i5++)
       {
         for (int i6=0;i6<nee_D_star_antiD0_pi_truth0;i6++)
          {  
            m_ee_D_star_antiD0_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();

            if(nee_Dz_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
              m_ee_D_starDz_antiD0_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
            if(nee_Dz_truth0==1&&nee_pi0_truth0==0&&nee_D_star_pi_truth0==1&&nee_anything_truth0==2)
            {
              m_ee_D_starDz_antiD0pi_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
            if(nee_Dzstar_truth0==1&&nee_pi0_truth0==0&&nee_anything_truth0==2)
            {
              m_ee_D_starDzstar_antiD0_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
            if(nee_Dzstar_truth0==1&&nee_pi0_truth0==0&&nee_D_star_pi_truth0==1&&nee_anything_truth0==2)
            {
              m_ee_D_starDzstar_antiD0pi_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
            if(nee_Dz_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
              m_ee_D_starDzpi0_antiD0_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
            if(nee_Dzstar_truth0==1&&nee_pi0_truth0==1&&nee_anything_truth0==3)
            {
              m_ee_D_starDzstarpi0_antiD0_kpi_p_mc0=(P0_ee_D_star_antiD0_k[i5]+P0_ee_D_star_antiD0_pi[i6]).rho();
            }
         }
       }

       for (int i7=0;i7<nk_truth0;i7++)
        {
         for (int i8=0;i8<npi_truth0;i8++)
          {  
            m_kpi_p_mc0=(P0_k[i7]+P0_pi[i8]).rho();
          }
        }

   m_tuple0->write();
   
  }

       

  Hep3Vector xorigin(0,0,0);
  Hep3Vector eorigin(0,0,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  double* dbv = vtxsvc->PrimaryVertex();
  double* vv = vtxsvc->SigmaPrimaryVertex();
  if(vtxsvc->isVertexValid()){
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
    eorigin.setX(vv[0]);//xyz
    eorigin.setY(vv[1]);
    eorigin.setZ(vv[2]);
  }

//++++++++++++ select six good charged tracks ++++++++
  Vint iGood, ipip, ipim,  ikap, ikam;
  iGood.clear();
  ipip.clear();
  ipim.clear();
  ikap.clear();
  ikam.clear();
  Vp4 ppip, ppim, pkap, pkam;
  ppip.clear();
  ppim.clear();
  pkap.clear();
  pkam.clear();

  int nCharge = 0; double visibleE = 0;
  for(int i = 0; i < evtRecEvent->totalCharged(); i++){
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
    if (!(*itTrk)->isMdcKalTrackValid()) continue;
    RecMdcKalTrack *mdcKalTrk = (*itTrk)->mdcKalTrack();
   double phi0=mdcTrk->helix(1);
   double x0=mdcTrk->x();
   double y0=mdcTrk->y();
   double z0=mdcTrk->z();
   double xv=xorigin.x();
   double yv=xorigin.y();
   double Rxy=(x0-xv)*cos(phi0)+(y0-yv)*sin(phi0);

   HepVector a = mdcTrk->helix();
   HepSymMatrix Ea = mdcTrk->err();
   HepPoint3D point0(0.,0.,0.);   
   HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
   VFHelix helixip(point0,a,Ea);
   helixip.pivot(IP);
   HepVector vecipa = helixip.a();

   double  Rvxy0=fabs(vecipa[0]);  //the nearest distance to IP in xy plane
   double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
   double  Rvphi0=vecipa[1];

    HepLorentzVector tracktemp = (0,0,0,0);
    tracktemp.setPx(mdcTrk->px());
    tracktemp.setPy(mdcTrk->py());
    tracktemp.setPz(mdcTrk->pz());
    double p3 = tracktemp.mag();
   visibleE += sqrt(p3*p3+mpi*mpi);
   if(fabs(Rvz0) >= 10.0) continue;
   if(fabs(Rvxy0) >= 1.0) continue;

    iGood.push_back((*itTrk)->trackId());
    nCharge += mdcTrk->charge();
  } // Finish Good Charged Track Selection

  int nGood = iGood.size();
  log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
  if ( nGood < 2/* || nCharge != 0*/ ){ return StatusCode::SUCCESS; }
  counter[1]++;  
// PID For pi+ pi- k+ k-

   ParticleID *pid = ParticleID::instance();

   for(int i = 0; i < nGood; i++) {
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[i];
    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();
    RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack();
  
    SmartRefVector<RecTofTrack> tofTrkCol=(*itTrk)->tofTrack();
    SmartRefVector<RecTofTrack>::iterator iter_tof=tofTrkCol.begin();

    pid->init();
    pid->setMethod(pid->methodProbability()); //or methodLikelihood or methodNeutronNetwork
    pid->setChiMinCut(4);
    pid->setRecTrack(*itTrk);
    pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2()| pid->useEmc()); //use PID sub-system pid->useEmc() pid->useMuc()
    pid->identify(pid->onlyPion() | pid->onlyKaon()| pid->onlyProton() );    // seperater Pion/Kaon
    pid->calculate();
    
    if(pid->probPion() > 0.001 && (pid->probPion() > pid->probKaon()) &&(pid->probPion() > pid->probProton())){
    RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
    HepLorentzVector ptrk;
    ptrk.setPx(mdcTrk->px());
    ptrk.setPy(mdcTrk->py());
    ptrk.setPz(mdcTrk->pz());
    double p3 = ptrk.mag();
    ptrk.setE(sqrt(p3*p3+mpi*mpi));

     if(mdcTrk->charge() >0) {  //pi+
      ipip.push_back(iGood[i]);
      ppip.push_back(ptrk);
//probility 

      }
      else if(mdcTrk->charge()<0) {  //pi-
      ipim.push_back(iGood[i]);
      ppim.push_back(ptrk);
//probility 
     }
}
  if(pid->probKaon() > 0.001 && (pid->probKaon() > pid->probPion()) &&(pid->probKaon() > pid->probProton()) ){
    RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);
    HepLorentzVector ptrk;
    ptrk.setPx(mdcTrk->px());
    ptrk.setPy(mdcTrk->py());
    ptrk.setPz(mdcTrk->pz());
    double p3 = ptrk.mag();
    ptrk.setE(sqrt(p3*p3+mK*mK));

     if(mdcTrk->charge() >0) {  //k+
      ikap.push_back(iGood[i]);
      pkap.push_back(ptrk);
//probility 

      }
      else if(mdcTrk->charge()<0) {  //k-
      ikam.push_back(iGood[i]);
      pkam.push_back(ptrk);
//probility 

   }
} 


}
//if(debug == 1) {   std::cout << "****************debug 4 ******************"<< std::endl;}
    int npip = ipip.size();
    int npim = ipim.size();
    int nkap = ikap.size();
    int nkam = ikam.size();
    if((npim*nkap) < 1) return StatusCode::SUCCESS;
    counter[2]++;

 

       WTrackParameter wvpimTrk, wvkapTrk ;  
           
          for(int b = 0; b < npim; b++){
            RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+ipim[b]))->mdcKalTrack();
            wvpimTrk = WTrackParameter(mpi, pimTrk->getZHelix(), pimTrk->getZError());

            for(int c = 0; c < nkap; c++){
              RecMdcKalTrack *kapTrk = (*(evtRecTrkCol->begin()+ikap[c]))->mdcKalTrack();
              wvkapTrk = WTrackParameter(mK,  kapTrk->getZHelixK(), kapTrk->getZErrorK());
     
  


           VertexFit* vtxfit = VertexFit::instance(); 
          // SecondVertexFit *svtxfit = SecondVertexFit::instance();

           HepPoint3D vx(0., 0., 0.);
           HepSymMatrix Evx(3, 0);
           double bx = 1E+6;
           double by = 1E+6;
           double bz = 1E+6;
           Evx[0][0] = bx*bx;
           Evx[1][1] = by*by;
           Evx[2][2] = bz*bz;

           VertexParameter vxpar;
           vxpar.setVx(vx);
           vxpar.setEvx(Evx);


           vtxfit->init();
           vtxfit->AddTrack(0,  wvpimTrk);
           vtxfit->AddTrack(1,  wvkapTrk);
           vtxfit->AddVertex(0, vxpar,0, 1);
           //vtxfit->Fit(0);
           if(!vtxfit->Fit(0)) continue;
          // vtxfit->BuildVirtualParticle(0); 
           vtxfit->Swim(0); 

           HepLorentzVector  P_kpi_mc = (ppim[b]+pkap[c]);
           P_kpi_mc.boost(LAB2CM);
          
           m_MMD0star =(p4cm-P_kpi_mc ).m();
           m_chisqanti_D0 = vtxfit->chisq();
           m_anti_D0 =(P_kpi_mc).m();
           m_D0p = (P_kpi_mc).rho();
           m_deltaE =ebeam-(P_kpi_mc).e();
           m_Mbc = sqrt(ebeam*ebeam-m_D0p*m_D0p);
           m_costheta = (P_kpi_mc).cosTheta();
          // m_cosalpha = cos(ppim[b].angle(pkap[c])*180/3.1415);

           
         
         }
    }
       
    //************************************************************
    //MC information after particls going through detectors
    //************************************************************
 
     
      int nee_antiD0_k_truth=0;
      int nee_antiD0_pi_truth=0;
      int nee_antiD0star_antiD0_k_truth=0;
      int nee_antiD0star_antiD0_pi_truth=0; 
      int nee_antiD0star_pi0_truth=0;
      int nee_antiD0star_gamma_truth=0;
      int nee_D0_truth=0;
      int nee_D0star_truth=0;
      int nee_D_star_antiD0_k_truth=0;
      int nee_D_star_antiD0_pi_truth=0;
      int nee_D_star_pi_truth=0;
      int nee_Dz_truth=0;
      int nee_Dzstar_truth=0;
      int nee_pi0_truth=0;
      int nk_truth=0;
      int npi_truth=0;
      int nee_anything_truth=0;

      Vp4 P_ee_antiD0_k;
      Vp4 P_ee_antiD0_pi;
      Vp4 P_ee_antiD0star_antiD0_k;
      Vp4 P_ee_antiD0star_antiD0_pi;
      Vp4 P_ee_D_star_antiD0_k;
      Vp4 P_ee_D_star_antiD0_pi;
      Vp4 P_k;
      Vp4 P_pi;
      P_ee_antiD0_k.clear();
      P_ee_antiD0_pi.clear();
      P_ee_antiD0star_antiD0_k.clear();
      P_ee_antiD0star_antiD0_pi.clear();
      P_ee_D_star_antiD0_k.clear();
      P_ee_D_star_antiD0_pi.clear();
      P_k.clear();
      P_pi.clear(); 

      if (eventHeader->runNumber()<0)
    {
    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(),"/Event/MC/McParticleCol");
    if(!mcParticleCol)
      {
        std::cout<<"Could not retrieve McParticelCol"<<std::endl;
        return(StatusCode::FAILURE);  
      }
    Event::McParticleCol::iterator iter_mc=mcParticleCol->begin();
    m_nmcps=0;
    bool jpsiDecay(false);
    int rootIndex(-1);
    for (;iter_mc!=mcParticleCol->end();iter_mc++)
      {
        if((*iter_mc)->primaryParticle()) continue;
        if(!(*iter_mc)->decayFromGenerator()) continue;
        if((*iter_mc)->particleProperty()==9030443)
          {
            jpsiDecay=true;
            rootIndex=(*iter_mc)->trackIndex();
          }
        if(!jpsiDecay) continue;
        m_pid[m_nmcps]=(*iter_mc)->particleProperty();
        if(((*iter_mc)->mother()).particleProperty()==9030443) m_midx[m_nmcps]=((*iter_mc)->mother()).trackIndex()-rootIndex;
        else m_midx[m_nmcps]=((*iter_mc)->mother()).trackIndex()-rootIndex-1;
        if((*iter_mc)->particleProperty()==9030443) m_midx[m_nmcps]=0;
        m_nmcps++;

        HepLorentzVector  mctrue_track = (*iter_mc)->initialFourMomentum();
       
        if(((*iter_mc)->mother()).particleProperty()==9030443)
       { nee_anything_truth++;  }

        if((*iter_mc)->particleProperty()==321&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==9030443)
       {  
         m_ee_antiD0_k_p_mc = mctrue_track.rho();
         P_ee_antiD0_k.push_back(mctrue_track);
         nee_antiD0_k_truth++;
       }
        if((*iter_mc)->particleProperty()==-211&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0_pi_p_mc= mctrue_track.rho();
        P_ee_antiD0_pi.push_back(mctrue_track);
        nee_antiD0_pi_truth++;
       }
        if((*iter_mc)->particleProperty()==321&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==-423&&((*iter_mc)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_antiD0_k_p_mc= mctrue_track.rho();
        P_ee_antiD0star_antiD0_k.push_back(mctrue_track);
        nee_antiD0star_antiD0_k_truth++;
       }
        if((*iter_mc)->particleProperty()==-211&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==-423&&((*iter_mc)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_antiD0_pi_p_mc= mctrue_track.rho();
        P_ee_antiD0star_antiD0_pi.push_back(mctrue_track);
        nee_antiD0star_antiD0_pi_truth++;
       }
        if((*iter_mc)->particleProperty()==111&&((*iter_mc)->mother()).particleProperty()==-423&&((*iter_mc)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_pi0_p_mc= mctrue_track.rho();
        nee_antiD0star_pi0_truth++;
       }
        if((*iter_mc)->particleProperty()==22&&((*iter_mc)->mother()).particleProperty()==-423&&((*iter_mc)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_antiD0star_gamma_p_mc= mctrue_track.rho();
        nee_antiD0star_gamma_truth++;
       }
        if((*iter_mc)->particleProperty()==421&&((*iter_mc)->mother()).particleProperty()==9030443)
      {
        m_ee_D0_p_mc= mctrue_track.rho();
        nee_D0_truth++;
       }
        if((*iter_mc)->particleProperty()==423&&((*iter_mc)->mother()).particleProperty()==9030443)
      {
        m_ee_D0star_p_mc= mctrue_track.rho();
        nee_D0star_truth++;
       }
        if((*iter_mc)->particleProperty()==321&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==-413&&((*iter_mc)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_antiD0_k_p_mc= mctrue_track.rho();
        P_ee_D_star_antiD0_k.push_back(mctrue_track);
        nee_D_star_antiD0_k_truth++;
       }
        if((*iter_mc)->particleProperty()==-211&&((*iter_mc)->mother()).particleProperty()==-421&&((*iter_mc)->mother().mother()).particleProperty()==-413&&((*iter_mc)->mother().mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_antiD0_pi_p_mc= mctrue_track.rho();
        P_ee_D_star_antiD0_pi.push_back(mctrue_track);
        nee_D_star_antiD0_pi_truth++;
       }
       if((*iter_mc)->particleProperty()==-211&&((*iter_mc)->mother()).particleProperty()==-413&&((*iter_mc)->mother().mother()).particleProperty()==9030443)
      {
        m_ee_D_star_pi_p_mc= mctrue_track.rho();
        nee_D_star_pi_truth++;
       }
       if((*iter_mc)->particleProperty()==411&&((*iter_mc)->mother()).particleProperty()==9030443)
      {
        m_ee_Dz_p_mc= mctrue_track.rho();
        nee_Dz_truth++;
       }
        if((*iter_mc)->particleProperty()==413&&((*iter_mc)->mother()).particleProperty()==9030443)
      {
        m_ee_Dzstar_p_mc= mctrue_track.rho();
        nee_Dzstar_truth++;
       }
       if((*iter_mc)->particleProperty()==111&&((*iter_mc)->mother()).particleProperty()==9030443)
      {
        m_ee_pi0_p_mc= mctrue_track.rho();
        nee_pi0_truth++;
       }
       if((*iter_mc)->particleProperty()==321)
      {
        m_k_p_mc= mctrue_track.rho();
        P_k.push_back(mctrue_track);
        nk_truth++;
       }
       if((*iter_mc)->particleProperty()==-211)
      {
        m_pi_p_mc= mctrue_track.rho();
        P_pi.push_back(mctrue_track);
        npi_truth++;
       }

     }
       for (int i1=0;i1<nee_antiD0_k_truth;i1++)
       {
         for (int i2=0;i2<nee_antiD0_pi_truth;i2++)
          {
            HepLorentzVector P_ee_antiD0_kpi = (P_ee_antiD0_k[i1]+P_ee_antiD0_pi[i2]);
             P_ee_antiD0_kpi.boost(LAB2CM);
            m_ee_antiD0_kpi_p_mc=P_ee_antiD0_kpi.rho();
            if(nee_D0_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
             m_ee_antiD0D0_kpi_p_mc=P_ee_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
             m_ee_antiD0D0star_kpi_p_mc=P_ee_antiD0_kpi.rho();
            }
            if(nee_D0_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
             m_ee_antiD0D0pi0_kpi_p_mc=P_ee_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
             m_ee_antiD0D0starpi0_kpi_p_mc=P_ee_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==2&&nee_anything_truth==4)
            {
             m_ee_antiD0D0starpi0pi0_kpi_p_mc=P_ee_antiD0_kpi.rho();
            }

          }
        }
        for (int i3=0;i3<nee_antiD0star_antiD0_k_truth;i3++)
       {
         for (int i4=0;i4<nee_antiD0star_antiD0_pi_truth;i4++)
          {
             HepLorentzVector P_ee_antiD0star_antiD0_kpi = (P_ee_antiD0star_antiD0_k[i3]+P_ee_antiD0star_antiD0_pi[i4]);
             P_ee_antiD0star_antiD0_kpi.boost(LAB2CM);
            m_ee_antiD0star_antiD0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            if(nee_D0_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0_antiD0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0_truth==1&&nee_pi0_truth==0&&nee_antiD0star_pi0_truth==1&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0_antiD0pi0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0_truth==1&&nee_pi0_truth==0&&nee_antiD0star_gamma_truth==1&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0_antiD0gamma_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0star_antiD0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==0&&nee_antiD0star_pi0_truth==1&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0star_antiD0pi0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==0&&nee_antiD0star_gamma_truth==1&&nee_anything_truth==2)
            {
            m_ee_antiD0starD0star_antiD0gamma_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }

            if(nee_D0_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
            m_ee_antiD0starD0pi0_antiD0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }
            if(nee_D0star_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
            m_ee_antiD0starD0starpi0_antiD0_kpi_p_mc=P_ee_antiD0star_antiD0_kpi.rho();
            }

          }
        }

       for (int i5=0;i5<nee_D_star_antiD0_k_truth;i5++)
       {
         for (int i6=0;i6<nee_D_star_antiD0_pi_truth;i6++)
          {  
             HepLorentzVector P_ee_D_star_antiD0_kpi = (P_ee_D_star_antiD0_k[i5]+P_ee_D_star_antiD0_pi[i6]);
             P_ee_D_star_antiD0_kpi.boost(LAB2CM);
            m_ee_D_star_antiD0_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();

            if(nee_Dz_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
              m_ee_D_starDz_antiD0_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
            if(nee_Dz_truth==1&&nee_pi0_truth==0&&nee_D_star_pi_truth==1&&nee_anything_truth==2)
            {
              m_ee_D_starDz_antiD0pi_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
            if(nee_Dzstar_truth==1&&nee_pi0_truth==0&&nee_anything_truth==2)
            {
              m_ee_D_starDzstar_antiD0_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
            if(nee_Dzstar_truth==1&&nee_pi0_truth==0&&nee_D_star_pi_truth==1&&nee_anything_truth==2)
            {
              m_ee_D_starDzstar_antiD0pi_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
            if(nee_Dz_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
              m_ee_D_starDzpi0_antiD0_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
            if(nee_Dzstar_truth==1&&nee_pi0_truth==1&&nee_anything_truth==3)
            {
              m_ee_D_starDzstarpi0_antiD0_kpi_p_mc=P_ee_D_star_antiD0_kpi.rho();
            }
         }
       }

       for (int i7=0;i7<nk_truth;i7++)
        {
         for (int i8=0;i8<npi_truth;i8++)
          {  
             HepLorentzVector P_kpi = (P_k[i7]+P_pi[i8]);
             P_kpi.boost(LAB2CM);
            m_kpi_p_mc=P_kpi.rho();
            m_kpi_m_mc=P_kpi.m();
          }
        }


  }
         m_tuple1->write();
         counter[4]++;

  

    

return StatusCode::SUCCESS;
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
StatusCode Kpi::finalize() {

  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;
  std::cout << "able:MC Truth==  " << counter[9] << std::endl;
  std::cout << "able:the totale events is==  " << counter[0] << std::endl;
  std::cout << "at least 2 track is==  " << counter[1] << std::endl;
  std::cout << " 1 pi and 1 k is==  " << counter[2] << std::endl;
  std::cout << "Ngam>=2 is == " << counter[3] << std::endl;
  std::cout << "final ntupe  == " << counter[4] << std::endl;

  return StatusCode::SUCCESS;
}

