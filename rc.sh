# shell configuration.
if [ "$0" = "bash" ]; then
    export ANTH_HOME=$(cd $(dirname $BASH_SOURCE) && pwd)
    export PS1="\033[32m\w \033[37m\$\033[0m "

elif [ "$0" = "dash" ]; then
    if [ "$ANTH_HOME" = "" ] || [ ! -e "$ANTH_HOME/rc.sh" ]; then
        # can not get the directory of running script.
        # need user to set ANTH_HOME manually.
        echo "need to configure ANTH_HOME manually"
        return
    fi
    export PS1="$(echo "\033[32m$PWD \033[37m\$\033[0m ")"

elif [ "$0" = "ksh" ]; then
    export ANTH_HOME=$(cd $(dirname ${.sh.file}) && pwd)
    export PS1="$PWD \$ "

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
