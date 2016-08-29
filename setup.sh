#!/usr/bin/env bash


cd besenv
source setupCVS.sh
source setupCMT.sh
cmt config
source setup.sh

cd ../../../TestRelease/TestRelease-00-00-80/cmt/
source setup.sh
cd ../../../kpi/d0bard0


