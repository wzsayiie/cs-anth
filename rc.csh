# shell configuration.
set __ANTH_DN = `dirname $0`
set ANTH_HOME = `cd $__ANTH_DN && pwd`
set prompt    = "%{\e[32m%}%~ %{\e[37m%}"\$"%{\e[0m%} "

# environment:
set PATH = $ANTH_HOME/bin:$PATH

set CPATH             = $ANTH_HOME/libextend:$ANTH_HOME/libhost
set LIBRARY_PATH      = $ANTH_HOME/lib
set DYLD_LIBRARY_PATH = $ANTH_HOME/lib
set LD_LIBRARY_PATH   = $ANTH_HOME/lib

# commands.
alias cls clear

# user rc.
if ( -e $ANTH_HOME/urc.csh ) then
    source $ANTH_HOME/urc.csh
endif
