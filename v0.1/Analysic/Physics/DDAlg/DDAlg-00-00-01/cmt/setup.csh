# echo "Setting DDAlg DDAlg-00-00-01 in /afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.1/Analysic/Physics"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118
endif
source ${CMTROOT}/mgr/setup.csh

set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=DDAlg -version=DDAlg-00-00-01 -path=/afs/ihep.ac.cn/users/s/suym/bes/kpi/v0.1/Analysic/Physics  -no_cleanup $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

