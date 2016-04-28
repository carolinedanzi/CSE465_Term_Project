set SCHEMEDIR=\Program Files (x86)\MIT-GNU Scheme
set SCHEMEBIN="%SCHEMEDIR%\bin\mit-scheme.exe"
set SCHEMELIBDIR=%SCHEMEDIR%\lib
%SCHEMEBIN% -band "%SCHEMELIBDIR%\all.com" -library "%SCHEMELIBDIR%"