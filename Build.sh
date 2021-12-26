#You can run this Build Script with RFI or bash/zsh#
##|INIT|(@^+++*+@V;)
##|Compile|(
##%>
g++ -std=c++17 SRC/main.cpp -o RFI 2>Log 1>Log
##%$;
##)
##|Install|([>]%>
./RFI --install
##%$;)
##|ERROR_CHECKING|(
##<'=}_[S%<NO ERROR!%[<.]^.V%<Install% =< ;]%>Log%&>S[?.]:S%<ERROR!%[<.]^.V;
##)
## %>INIT% =>
## %>Compile% =>
##>%>ERROR_CHECKING% =>