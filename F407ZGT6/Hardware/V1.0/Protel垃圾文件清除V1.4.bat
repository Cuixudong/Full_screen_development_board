::PROTEL垃圾文件删除器 
::版本 V1.4  20120914更新
::正点原子制作
::论坛:www.openedv.com 

del *.SchDocPreview /s
del *.PcbDocPreview /s 
del *.pcbPreview /s 
del *.PrjPCBStructure /s 
del *.drc /s
del *.LOG /s 
del *.OutJob /s 
for /r /d %%b in (History) do rd "%%b" /s /q 
::删除当前目录下的所有History文件夹
for /r /d %%b in (Project?Logs?for*) do rd "%%b" /s /q 
::删除当前目录下的所有带字符串Project Logs for的文件夹
for /r /d %%b in (Project?Outputs?for*) do rd "%%b" /s /q   
::删除当前目录下的所有带字符串Project Outputs for的文件夹
exit
