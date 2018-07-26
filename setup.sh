DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export TNM_PATH=$DIR
export PYTHONPATH=$TNM_PATH/python:$PYTHONPATH
export LD_LIBRARY_PATH=$TNM_PATH/lib:$LD_LIBRARY_PATH
echo "TNM_PATH=$TNM_PATH"
