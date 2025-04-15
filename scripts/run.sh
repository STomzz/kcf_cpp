#!/bin/bash
ScriptPath="$( cd "$(dirname "$BASH_SOURCE")" ; pwd -P )"

echo "[INFO] The kcf starts to run"
running_command="./kcf"
cd ${ScriptPath}/../out
${running_command}
if [ $? -ne 0 ];then
    echo "[INFO] The program runs failed"
else
    echo "[INFO] The program runs successfully"
fi