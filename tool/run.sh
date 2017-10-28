#!/bin/bash
set +x

##data type, the subdirectory with the name $ecms$iJob
date=job_kpi

##the data file
#dpath=/besfs/groups/psip/psipgroup/664p01-MC/4260/res/DD
 dpath=/besfs/groups/psip/psipgroup/664p01-MC/4260/res/DD
#dpath=/bes3fs/besfs2.tobedel/664-1/jpsi/12mc/dst
#dpath=/bes3fs/besfs2.tobedel/664-1/jpsi/12mc/grid/dst
        
dataFiles=`find $dpath -name "*.dst"`
fileNumber=`find $dpath -name "*.dst" | wc -l`

##the data file number in one job
let nDataFile=3


##the job name with the format $myjob$iJob_run.txt
let iJob=1
myjob=$date

##change something below ONLY when you know what you are dong
let n=0
for recFile in $dataFiles
do 

  #echo $recFile
  let m=n+1

  if [[ ! -e $recFile ]]; then 
    echo "this data file $recFile doesn't exist! "
  else

    line1="$recFile"
    line="process_event "${line1}" 0"

    if [[ $n%$nDataFile -eq 0 ]]; then
      if [[ -e ${myjob}"_0"${iJob}_run.txt ]]; then
        cat run.foot >> ${myjob}"_0"${iJob}_run.txt
        if [ -d ${date} ] ; then
          cd ${date}
          mv ../${myjob}"_0"${iJob}_run.txt ./
          sleep 2
          cd ..
        else 
          mkdir ${date}
          cd ${date}
          mv ../${myjob}"_0"${iJob}_run.txt ./
          sleep 2
          cd ..
        fi
        let iJob++
      fi
      touch  ${myjob}"_0"${iJob}_run.txt
      cat run.head >> ${myjob}"_0"${iJob}_run.txt
    fi

    ##if the last data file in this jobOption file
    if [[ $m%$nDataFile -eq 0 || $m -eq $fileNumber ]]; then
      echo ${line} >> ${myjob}"_0"${iJob}_run.txt
    else
      echo $line,  >> ${myjob}"_0"${iJob}_run.txt
    fi

    let n++
  fi
done

##for the last jobOption file
cat run.foot >> ${myjob}"_0"${iJob}_run.txt
if [ -d ${date} ]; then
  cd ${date}
  mv ../${myjob}"_0"${iJob}_run.txt ./
  cd ..
else
  mkdir ${date}
  cd ${date}
  mv ../${myjob}"_0"${iJob}_run.txt ./
  cd ..
fi

exit 0
