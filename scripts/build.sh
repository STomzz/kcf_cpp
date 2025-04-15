#!/bin/bash
ScriptPath="$( cd "$(dirname "$BASH_SOURCE")" ; pwd -P )"
BuildPath="${ScriptPath}/../build"


function build()
{
  if [ -d "${ScriptPath}/../bin/" ];then
  rm -rf "${ScriptPath}/../bin/"*
  fi
  
  if [ -d ${BuildPath} ];then
    rm -rf ${BuildPath}
  fi

  mkdir -p ${BuildPath}
  cd ${BuildPath}

  cmake .. \
        -DCMAKE_CXX_COMPILER=g++ \
        -DCMAKE_SKIP_RPATH=TRUE

  if [ $? -ne 0 ];then
    echo "[ERROR] cmake error, Please check your environment!"
    return 1
  fi
  make
  if [ $? -ne 0 ];then
    echo "[ERROR] build failed, Please check your environment!"
    return 1
  fi
  cd - > /dev/null
}

function main()
{
  echo "[INFO] kcf preparation"

  build
  if [ $? -ne 0 ];then
    return 1
  fi

  echo "[INFO] kcf build is complete"
}
main