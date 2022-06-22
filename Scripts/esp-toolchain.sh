#! /bin/bash
# shellcheck source=/dev/null

echo "Setting up components for SDK"

. "$IDF_PATH/add_path.sh"

echo "Path Environment Directories:"
printenv PATH

echo "***********The ESP8266 SDK has been setup************"
