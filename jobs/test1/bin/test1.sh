#/bin/bash
JOB_PATH="`dirname $0`"
echo $JOB_PATH

cd $JOB_PATH
cd ../../../
echo `pwd`

c++ -I lib/eigen-3.4.0 src/maintest.cpp src/libODE.cpp -o bin/maintest
echo "Compilato!"
bin/maintest -1 "$JOB_PATH/../output/prova.m"

cd $JOB_PATH
echo `pwd`
matlab -r grafico_prova  -nosplash -nodesktop