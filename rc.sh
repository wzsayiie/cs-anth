# shell configuration.
if [ "$0" = "bash" ]; then
    export ANTH_HOME=$(cd $(dirname $BASH_SOURCE) && pwd)
    export PS1="\e[32m\w \e[37m\$\e[0m "

else # zsh.
    export ANTH_HOME=$0:a:h
    export PS1="%F{green}%~ %F{white}%#%f "
fi

# environment:
export PATH=$ANTH_HOME/bin:$PATH

export             CPATH=$ANTH_HOME/libextend:$ANTH_HOME/libhost
export      LIBRARY_PATH=$ANTH_HOME/lib
export DYLD_LIBRARY_PATH=$ANTH_HOME/lib
export   LD_LIBRARY_PATH=$ANTH_HOME/lib

# commands.
alias cls="clear"

# preferences:

# mac ls color setting for 11 different file types.
#..............=1.2.3.4.5.6.7.8.9.a.b.
export LSCOLORS=exaxaxaxaxaxaxaxaxaxax
export CLICOLOR=1

# user rc.
if [ -e $ANTH_HOME/urc.sh ]; then
    . $ANTH_HOME/urc.sh
fi
