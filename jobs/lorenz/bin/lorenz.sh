#/bin/bash
JOB_PATH="`dirname $0`"
echo $JOB_PATH

cd $JOB_PATH
cd ../../../
echo `pwd`

c++ -I lib/eigen-3.4.0 src/mainlorenz.cpp src/libODE.cpp -o bin/lorenz
echo "Compilato!"
bin/lorenz $JOB_PATH/../output/prova.m

cd $JOB_PATH
echo `pwd`
matlab -r grafico_prova  -nosplash -nodesktop