#! /bin/bash

echo "Checking \$SHELL environment"

case $SHELL in
*/zsh)
    configfile=~/.zshrc
    ;;
*/bash)
    # assume Bash
    configfile=~/.bashrc
    ;;
*)
    echo "Unsupported \$SHELL!"
    echo "Please use bash or zsh to execute script."
    exit 1
    ;;
esac

echo "System Environment Variables will be written to:"

printf 'SHELL PATH:\t%s\n' "$configfile"

echo "Updating Repository Packages..."
sudo apt update
sudo apt upgrade -y

echo "Downloading Pre-requisite packages..."

sudo apt-get install gcc git wget make libncurses-dev -y 
sudo apt-get install flex bison gperf python3 python3-serial cmake -y

echo "Creating link for python"

sudo ln -s /usr/bin/python3 /usr/bin/python

echo "Creating Development Folder 'esp' located at: ~/esp "

mkdir -p "$HOME"/esp
# cd "$HOME/esp" || exit 1

printf "\nDownloading Compiler..."

wget https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz -P ~/esp/ 

printf "\nDownloading ESP8266_RTOS_SDK..."

git clone https://github.com/espressif/ESP8266_RTOS_SDK.git ~/esp/

export IDF_PATH="\$HOME/esp/ESP8266_RTOS_SDK"

echo "Extracting compiler..."

tar -xzvf ~/esp/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz "$HOME"/esp/

rm ~/esp/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz

echo "Setting up PATHS..."
{
    printf "\n# ESP8266-RTOS-SDK Environment Paths" 
    echo "export IDF_PATH=\"\$HOME/esp/ESP8266_RTOS_SDK\""
    echo "export PATH=\"\$PATH:\$HOME/esp/xtensa-lx106-elf/bin\"" 
} >> "$configfile"

printf "\nInstalling Required Packages for ESP8266-RTOS-SDK..."

python -m pip install -r "$IDF_PATH"/requirements.txt

printf "\nExecute the following script before beginning to code your ESP8266 Project!"
echo "esp-toolchain.sh"
printf "\nFor USB Driver Issues, please use the following link:"
echo "https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/linux-setup.html"
