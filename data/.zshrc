echo "Welcome to the Fibonacci Race Against Time!"
echo "Remember you've only got 2 minutes until automatic logout."
TMOUT=30
readonly TMOUT
setopt PROMPT_SUBST
PROMPT="fibonacci>"