# echo "cleanup cmt_standalone v0 in /afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.2/besenv/cmthome-7.0.2.p01"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtcmt_standalonetempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtcmt_standalonetempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=cmt_standalone -version=v0 -path=/afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.2/besenv/cmthome-7.0.2.p01  $* >${cmtcmt_standalonetempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=cmt_standalone -version=v0 -path=/afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.2/besenv/cmthome-7.0.2.p01  $* >${cmtcmt_standalonetempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtcmt_standalonetempfile}
  unset cmtcmt_standalonetempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtcmt_standalonetempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtcmt_standalonetempfile}
unset cmtcmt_standalonetempfile
exit $cmtcleanupstatus

