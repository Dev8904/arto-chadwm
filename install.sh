#!/bin/bash
#set -e

##################################################################################################################
#Author  : Jonathan Marshall
#Github  : https://github.com/Dev8904
###########################################################################################################################

#Declaring our installed directory
installed_dir=$(dirname "$(readlink -f "$(basename "$(pwd)")")")

#hard coding home
if [[ $EUID -eq 0 ]]; then
    # The script is running as root (e.g., via sudo)
    if [[ -n $SUDO_USER ]]; then
        # Get the home directory of the user who invoked sudo
        USER_HOME=$(eval echo ~$SUDO_USER)
    else
        # Fall back to /scriptdump if we can't determine a sudo invoker
        echo "Please run the script as sudo."
    fi
else
    # The script is not running as root
    USER_HOME="$HOME"
fi

##################################################################################################################
CNT="[\e[1;36mNOTE\e[0m]"
COK="[\e[1;32mOK\e[0m]"
CER="[\e[1;31mERROR\e[0m]"
CAT="[\e[1;37mATTENTION\e[0m]"
CWR="[\e[1;35mWARNING\e[0m]"
CAC="[\e[1;33mACTION\e[0m]"
INSTLOG="install.log"

#Move function
move_files() 
{
    local dest="$1"
    shift  # Remove the destination from the arguments

    # Check if destination directory exists; create it if not
    if [[ ! -d "$dest" ]]; then
        mkdir -p "$dest"
    fi

    # Remaining arguments are the source files/directories
    for src in "$@"; do
        # Determine whether to use sudo based on the destination path
        if [[ "$dest" == "$HOME"* ]]; then
            # Move the source to the destination
            mv -v "$src" "$dest" >> "$INSTLOG" 2> /dev/null &
        else
            # Move the source to the destination using sudo
            sudo mv -v "$src" "$dest" >> "$INSTLOG" 2> /dev/null &
        fi
    done
}

# Define source and destination directories
dwm_config=(
  "$installed_dir/root/usr/bin/" "/usr/bin/"
  "$installed_dir/root/usr/local/bin/" "/usr/local/bin/"
  "$installed_dir/root/usr/share/backgrounds/" "/usr/share/backgrounds/"
  "$installed_dir/root/usr/share/xsessions/" "/usr/share/xsessions/"
  "$installed_dir/root/etc/skel/.config/arto-chadwm/" "$USER_HOME/.config/arto-chadwm/"
)

echo "Moving files..."
for (( i=0; i<${#dwm_config[@]}; i+=2 )); do
    src_dir="${dwm_config[$i]}"
    dest_dir="${dwm_config[$i+1]}"
    for src_file in "$src_dir"*; do
        move_files "$dest_dir" "$src_file"
    done
done

sleep 5
echo "Done. Installing..."

cd "$USER_HOME/.config/arto-chadwm/chadwm/"
sudo make install

echo "Dwm Install finished."


