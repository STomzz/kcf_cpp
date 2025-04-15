#!/bin/bash
ScriptPath="$( cd "$(dirname "$BASH_SOURCE")" ; pwd -P )"

echo "[INFO] The kcf starts to run"
running_command="./KCF"
# running_command="./kcf ../video/girl_dance_kcf.mp4 ../video/girl_dance_kcf.mp4 255 155 62 60"
cd ${ScriptPath}/../bin
${running_command}
if [ $? -ne 0 ];then
    echo "[INFO] The program runs failed"
else
    echo "[INFO] The program runs successfully"
fi