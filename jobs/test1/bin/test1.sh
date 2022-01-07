#/bin/bash

# Find project path and job path
cd `dirname $0`
cd ..
JOB_PATH="`pwd`"
echo JOB PATH: $JOB_PATH
cd ../../
PROJECT_PATH="`pwd`"
echo PROJECT PATH: $PROJECT_PATH


# Compile
cd "$JOB_PATH"
c++ -I  "$PROJECT_PATH/lib/eigen-3.4.0"\
    -I  "$PROJECT_PATH/src"\
        "$PROJECT_PATH/src/"*.cpp\
        src/main.cpp\
        -o bin/main\
    -lm
echo "Compilato!"

bin/main -1 "$JOB_PATH/output/prova.m"
echo "Eseguito!"

cd "$JOB_PATH"/bin
matlab -r grafico_prova  -nosplash -nodesktop