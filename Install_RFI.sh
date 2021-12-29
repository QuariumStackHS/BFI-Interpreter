#Link#
#You can run this Build Script with RFI or bash/zsh#
##|PRE_INIT|(@^+++*+@V;)
##|Compile|(%>
g++ -std=c++17 SRC/main.cpp -o RFI 2>Log 1>Log
##%$;)
##|Install|([>]%>
./RFI --install
##%$@V%>rm Log ; rm RFI%$@^;)|ERROR_CHECKING|(<'=}_{[S%<NO ERROR!%[<.]^.V%<Install% =< ;]%>Log%&>S[?.]:S%<ERROR!%[<.]^.V;)
##%>PRE_INIT% =>
## %>Compile% =>
##>%>ERROR_CHECKING% =>