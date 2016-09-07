----------> uses
# use GaudiInterface GaudiInterface-* External
# use BesCLHEP * External
# use PartPropSvc * 
# use CASTOR * LCG_Interfaces
# use ExHelloWorld * BesExamples
# use PipiJpsiAlg PipiJpsiAlg-* Analysis/Physics/PsiPrime
# use AbsCor AbsCor-* Analysis/PhotonCor
# use CalibSvc CalibSvc-* Calibration
# use tofcalgsec tofcalgsec-* Tof
# use OfflineEventLoopMgr * Control
# use Reconstruction Reconstruction-* 
# use MdcDedxAlg MdcDedxAlg-* Reconstruction
# use MucRecAlg MucRecAlg-* Reconstruction
# use TofRec TofRec-* Reconstruction
# use TofEnergyRec TofEnergyRec-* Reconstruction
# use MdcTrkRecon MdcTrkRecon-* Reconstruction/MdcPatRec
# use MdcxReco MdcxReco-* Reconstruction/MdcPatRec
# use EmcRec EmcRec-* Reconstruction
# use EmcTimeRec EmcTimeRec-* Reconstruction
# use MdcFastTrkAlg MdcFastTrkAlg-* Reconstruction
# use TrkExtAlg TrkExtAlg-* Reconstruction
# use EsTimeAlg EsTimeAlg-* Reconstruction
# use KalFitAlg KalFitAlg-* Reconstruction
# use TrkReco TrkReco-* Reconstruction
# use EventAssembly EventAssembly-* Reconstruction
# use PrimaryVertexAlg PrimaryVertexAlg-* Reconstruction
# use VeeVertexAlg VeeVertexAlg-* Reconstruction
# use BeamParamsAlg BeamParamsAlg-* Reconstruction
# use DTagSkim DTagSkim-* Reconstruction
# use LumTauAlg LumTauAlg-* 
# use T0Dummy T0Dummy-* Reconstruction
# use DiGamAlg DiGamAlg-* DQA
# use BesSim BesSim-* Simulation/BOOST
# use MdcTunningSvc MdcTunningSvc-* Simulation/BOOST
# use BesEventMixer BesEventMixer-* Simulation
# use Trigger Trigger-* Trigger
# use TrigMakerAlg TrigMakerAlg-* Event
# use EventFilter EventFilter-* 
# use HltMakerAlg HltMakerAlg-* Event
# use EventPreSelect EventPreSelect-* EvtPreSelect
# use EventWriter EventWriter-* EvtPreSelect
# use CalibEventSelect CalibEventSelect-* EvtPreSelect
# use DimuPreSelect DimuPreSelect-* EvtPreSelect
# use Gam4pikpAlg Gam4pikpAlg-* Analysis/ControlSamples
# use RootIO RootIO-* Event
# use RawDataCnv RawDataCnv-* Event
# use RawDataProviderSvc RawDataProviderSvc-* Event
# use MagneticField MagneticField-* 
# use BesVisAlg * EventDisplay
# use PartPropSvc * 
# use KKMC KKMC-* Generator
# use BesEvtGen BesEvtGen-* Generator
# use Bhwide Bhwide-* Generator
# use Ekhara Ekhara-* Generator
# use Bhagen Bhagen-* Generator/BesGenInterface
# use Ddgen Ddgen-* Generator/BesGenInterface
# use Ddprod Ddprod-* Generator/BesGenInterface
# use Dsdgen Dsdgen-* Generator/BesGenInterface
# use Dssgen Dssgen-* Generator/BesGenInterface
# use Epscat Epscat-* Generator/BesGenInterface
# use Fff Fff-* Generator/BesGenInterface
# use Ffgen Ffgen-* Generator/BesGenInterface
# use Fsfgen Fsfgen-* Generator/BesGenInterface
# use Gamma2 Gamma2-* Generator/BesGenInterface
# use Howl Howl-* Generator/BesGenInterface
# use Koralbe Koralbe-* Generator/BesGenInterface
# use KK2f KK2f-* Generator/BesGenInterface
# use Kstark Kstark-* Generator/BesGenInterface
# use Lund Lund-* Generator/BesGenInterface
# use Lund_crm Lund_crm-* Generator/BesGenInterface
# use Mugen Mugen-* Generator/BesGenInterface
# use P2bb P2bb-* Generator/BesGenInterface
# use P2epem P2epem-* Generator/BesGenInterface
# use P2mumu P2mumu-* Generator/BesGenInterface
# use Ppgen Ppgen-* Generator/BesGenInterface
# use Radee Radee-* Generator/BesGenInterface
# use Radgg Radgg-* Generator/BesGenInterface
# use Radmu Radmu-* Generator/BesGenInterface
# use Rhopi Rhopi-* Generator/BesGenInterface
# use Sagerx Sagerx-* Generator/BesGenInterface
# use Tauprd Tauprd-* Generator/BesGenInterface
# use Tester Tester-* Generator/BesGenInterface
# use Twogam Twogam-* Generator/BesGenInterface
# use V2llg V2llg-* Generator/BesGenInterface
# use Babayaga Babayaga-* Generator
# use RunEventNumberAlg RunEventNumberAlg-* Event
# use Pi0EtaToGGRecAlg Pi0EtaToGGRecAlg-* Reconstruction
# use DTagAlg DTagAlg-* Reconstruction
#
# Selection :
use CMT v1r20p20081118 (/afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib)
----------> tags
CMTv1 (from CMTVERSION)
CMTr20 (from CMTVERSION)
CMTp20081118 (from CMTVERSION)
Linux (from uname) package CMT implies [Unix]
x86_64-linux (from HOSTTYPE)
amd64_linux26 (from CMTCONFIG)
x86_64 (from package CMT)
slc55 (from package CMT)
gcc432 (from package CMT)
Unix (from package CMT) excludes [WIN32 Win32]
----------> CMTPATH
