# shell configuration:
set ANTH_HOME (cd (dirname (status --current-file)); pwd)

function fish_prompt
    printf "%s%s %s>%s " \
        (set_color) (pwd) (set_color white) (set_color normal)
end

# environment:
set PATH $ANTH_HOME/bin:$PATH

set CPATH             $ANTH_HOME/libextend:$ANTH_HOME/libhost
set LIBRARY_PATH      $ANTH_HOME/lib
set DYLD_LIBRARY_PATH $ANTH_HOME/lib
set LD_LIBRARY_PATH   $ANTH_HOME/lib

# commands.
alias cls="clear"

# user rc.
if test -e $ANTH_HOME/urc.fish
    source $ANTH_HOME/urc.fish
end
