#!/bin/bash

region=$1
input=$2

if [[ $region == "EU" ]]; then
    joblist=$3
    sed "s;JOBLIST;$joblist;;s;SANDBOX;$input;;" condor/condor_task_template_EU.cfg > tmp.cfg
elif [[ $region == "US" ]]; then
    joblist=$3
    sed "s;JOBLIST;$joblist;;s;SANDBOX;$input;;" condor/condor_task_template_US.cfg > tmp.cfg
elif [[ $region == "hadd" ]]; then
    output=$3
    logout=$4
    sed "s;INPUT;$input;;s;OUTPUT;$output;;s;LOGOUT;$logout;;" condor/condor_task_template_hadd.cfg > tmp.cfg
fi
condor_submit tmp.cfg
#rm tmp.cfg
