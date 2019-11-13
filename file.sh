#!/bin/bash

filename=$1
roll=$2
while IFS= read -r line
do
  
  var=$( echo $line | awk '{print $1}')
  var1=$( echo $line | awk '{print $2}')
  var2=$( echo $line | awk '{print $3}')
  var3=$( echo $line | awk '{print $4}')
 
  
  if [[ $roll == $var ]]
  then
  
     avg=$(( $var1 + $var2 + $var3 ))
     
     avg=$(( $avg ))  

     echo "$avg"
   
  fi
  
  





done < $filename
