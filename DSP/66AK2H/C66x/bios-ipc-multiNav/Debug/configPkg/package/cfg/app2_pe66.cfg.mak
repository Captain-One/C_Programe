# invoke SourceDir generated makefile for app2.pe66
app2.pe66: .libraries,app2.pe66
.libraries,app2.pe66: package/cfg/app2_pe66.xdl
	$(MAKE) -f D:\pxqwork\project\app-n\bios-ipc-multiNav/src/makefile.libs

clean::
	$(MAKE) -f D:\pxqwork\project\app-n\bios-ipc-multiNav/src/makefile.libs clean

