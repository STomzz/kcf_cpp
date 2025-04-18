#!/bin/bash
ScriptPath="$( cd "$(dirname "$BASH_SOURCE")" ; pwd -P )"

echo "[INFO] The kcf starts to run"
running_command="./KCF ../video/tv_tuanliu.mkv ../video/tuanliu_video_kcf.mp4 706 679 155 141"
# running_command="./KCF ../video/girl_dance.mp4 ../video/girl_dance_kcf.mp4 255 155 62 60"
cd ${ScriptPath}/../bin
${running_command}
if [ $? -ne 0 ];then
    echo "[INFO] The program runs failed"
else
    echo "[INFO] The program runs successfully"
fi