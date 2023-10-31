#!/bin/sh

#xrdb merge ~/.Xresources 
xbacklight -set 4 
#xset r rate 200 50 &

function run {
    if ! pgrep -x "$1" > /dev/null; then
        "$@" &
    fi
}
#run "dex $HOME/.config/autostart/artolinux-welcome-app.desktop"
#run xrandr --output Virtual1 --primary --mode 2560x1600 --pos 0x0 --rotate normal --output Virtual2 --off --output Virtual3 --off --output Virtual4 --off --output Virtual5 --off --output Virtual6 --off --output Virtual7 --off --output Virtual8 --off
#run "xrandr --output VGA-1 --primary --mode 1360x768 --pos 0x0 --rotate normal"
#run "xrandr --output HDMI2 --mode 1920x1080 --pos 1920x0 --rotate normal --output HDMI1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output VIRTUAL1 --off"
#run xrandr --output eDP-1 --primary --mode 1368x768 --pos 0x0 --rotate normal --output DP-1 --off --output HDMI-1 --off --output DP-2 --off --output HDMI-2 --off
#run xrandr --output LVDS1 --mode 1366x768 --output DP3 --mode 1920x1080 --right-of LVDS1
#run xrandr --output DVI-I-0 --right-of HDMI-0 --auto
#run xrandr --output DVI-1 --right-of DVI-0 --auto
#run xrandr --output DVI-D-1 --right-of DVI-I-1 --auto
#run xrandr --output HDMI2 --right-of HDMI1 --auto
#autorandr horizontal

run nm-applet
run variety
run "blueberry-tray"
run "dunst"
run "lxpolkit"
picom -b  --config ~/.config/arto-chadwm/picom/picom.conf &
run "numlockx on"
run "volumeicon"
emacs --daemon
run "flameshot"
#run "nitrogen --restore"
#run "conky -c $HOME/.config/arto-chadwm/conky/system-overview"
#you can set wallpapers in themes as well
feh --bg-fill /usr/share/backgrounds/wallpaper.jpg &
#feh --bg-fill /usr/share/backgrounds/artolinux/arto-wallpaper.jpg &
#feh --randomize --bg-fill /home/erik/Insync/Apps/Wallhaven/*
#feh --bg-fill ~/.config/arto-chadwm/wallpaper/chadwm.jpg &

#nitrogen --set-zoom-fill --random /home/erik/Insync/Apps/Desktoppr/ --head=0
#nitrogen --set-zoom-fill --random /home/erik/Insync/Apps/Desktoppr/ --head=1

#wallpaper for other Arch based systems
#feh --bg-fill /usr/share/archlinux-tweak-tool/data/wallpaper/wallpaper.png &
#run applications from startup

#run "insync start"
#run "spotify"
#run "ckb-next -b"
#run "discord"
#run "telegram-desktop"
#run "dropbox"

pkill bar.sh
~/.config/arto-chadwm/scripts/bar.sh &
while type chadwm >/dev/null; do chadwm && continue || break; done
