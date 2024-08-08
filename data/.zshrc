#!/usr/bin/zsh

max_sessions=4
user_sessions=$(ps "$$USER" | grep -e "zsh" | wc -l)
if (( $user_sessions > $max_sessions )); then
  print -r "Es ist bereits eine Sitzung von '$USER' aktiv. Mehrfachanmeldungen sind nicht erlaubt."
  logout
fi

print "Welcome to the Fibonacci Race Against Time!"
print "Remember you've only got 2 minutes until automatic logout."
TMOUT=120
readonly TMOUT
setopt PROMPT_SUBST
PROMPT="fibonacci>"
