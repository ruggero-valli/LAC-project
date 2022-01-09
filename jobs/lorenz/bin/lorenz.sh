#/bin/bash

# Define usage
function usage {
        echo "Usage: $(basename $0) [-cxs]" 2>&1
        echo '   -c   compiles the program'
        echo '   -x   executes the program'
        echo '   -s   executes the scripts'
        exit 1
}

# Find project path and job path
cd `dirname $0`
cd ..
JOB_PATH="`pwd`"
cd ../../
PROJECT_PATH="`pwd`"

while getopts ':cxs' OPTION; do
    case "$OPTION" in
    c)
        # Compile
        cd "$JOB_PATH"
        c++ -I  "$PROJECT_PATH/lib/eigen-3.4.0"\
            -I  "$PROJECT_PATH/src"\
                "$PROJECT_PATH/src/"*.cpp\
                src/main.cpp\
                -o bin/main\
            -lm\
        && echo "Compilato!"
        ;;
    x)
        # Execute program
        cd "$JOB_PATH"
        bin/main "$JOB_PATH/output/prova.m"\
        && echo "Eseguito!"
        ;;
    s)
        # Execute scripts
        cd "$JOB_PATH/bin"
        matlab -r grafico_prova  -nosplash -nodesktop\
        && echo "Script eseguito!"
        ;;
    ?)
        usage
        ;;
    esac
done

if [[ ${#} -eq 0 ]]; then
   usage
fi
