copy D:\pxqwork\project\5G-DSP\5G_SBL\Release\5G_SBL.out D:\pxqwork\project\git_Pro\C_Programe\DSP\�ĵ�\03������¼����\DSP��¼������������\����������¼������������\simple.out
hex6x simple.rmd
b2i2c simple.btbl simple.btbl.i2c
b2ccs simple.btbl.i2c simple.i2c.ccs
romparse nysh.spi.map
modify i2crom.ccs spirom_le.dat
copy spirom_le.dat C:\ti\pdk\6678\pdk_c667x_2_0_13\packages\ti\boot\writer\nor\evmc6678l\bin