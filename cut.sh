#!/bin/bash

filename=$1
roll=$2

  
   var=$( echo $line | cut -d " " -f 1 )
   var1=$( echo $line | cut -d " " -f 2 )
   var2=$( echo $line | cut -d " " -f 3 )
   var3=$( echo $line | cut -d " " -f 4 )
   
   
  
     if [[ $roll == $var ]]
     then

     echo "$var1"
     echo "$var2"
     echo "$var3"

     avg=$(( $var1 + $var2 +$var3 ))
     
     echo "-n"
     echo "$avg"  
   
     
     fi   
 
  
  





done < $filename
