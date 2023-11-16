#!/bin/dash

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
. ~/.config/arto-chadwm/scripts/bar_themes/starlight

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c$white^ ^b$black^ CPU"
  printf "^c$white^ ^b$black^ $cpu_val"
}

battery() {
  get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
  printf "^c$blue^   $get_capacity"
}

brightness() {
  printf "^c$red^   "
  printf "^c$red^%.0f\n" $(cat /sys/class/backlight/*/brightness)
}

mem() {
  printf "^c$blue^^b$black^  "
  printf "^c$blue^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$black^ ^b$blue^ 󰤨 ^d^%s" " ^c$blue^Connected" ;;
	down) printf "^c$black^ ^b$blue^ 󰤭 ^d^%s" " ^c$blue^Disconnected" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^  "
	printf "^c$black^^b$blue^ $(date '+%d/%m/%y %H:%M')  "
}


dwm_audio () {
  STATUS=$(amixer sget Master | tail -n1 | sed -r "s/.*\[(.*)\]/\1/")
  VOL=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
  if [ "$STATUS" = "off" ]; then
    printf "🔇"
  else
    #removed this line becuase it may get confusing
    if [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
      printf "🔈 %s%%" "$VOL"
    elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
      printf "🔉 %s%%" "$VOL"
    else
      printf "🔊 %s%%" "$VOL"
    fi
  fi
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && 
  interval=$((interval + 1))

  sleep 2 && xsetroot -name "$(dwm_audio) $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
done
