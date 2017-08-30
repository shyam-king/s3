@echo off
copy /Y s3* ..\
copy /y GOALDATA.DAT ..\
copy /y additionalToolsSource\writegoals.cpp ..\
copy /y s3goalma.h ..\
copy /y additionalToolsSource\PLAYER.CPP ..\
copy /y additionalToolsSource\playread.CPP ..\
pause
