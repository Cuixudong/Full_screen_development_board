::PROTEL�����ļ�ɾ���� 
::�汾 V1.4  20120914����
::����ԭ������
::��̳:www.openedv.com 

del *.SchDocPreview /s
del *.PcbDocPreview /s 
del *.pcbPreview /s 
del *.PrjPCBStructure /s 
del *.drc /s
del *.LOG /s 
del *.OutJob /s 
for /r /d %%b in (History) do rd "%%b" /s /q 
::ɾ����ǰĿ¼�µ�����History�ļ���
for /r /d %%b in (Project?Logs?for*) do rd "%%b" /s /q 
::ɾ����ǰĿ¼�µ����д��ַ���Project Logs for���ļ���
for /r /d %%b in (Project?Outputs?for*) do rd "%%b" /s /q   
::ɾ����ǰĿ¼�µ����д��ַ���Project Outputs for���ļ���
exit
