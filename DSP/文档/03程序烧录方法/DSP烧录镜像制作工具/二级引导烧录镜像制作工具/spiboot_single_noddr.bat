copy D:\pxqwork\project\5G-DSP\5G_SBL\Release\5G_SBL.out D:\pxqwork\project\git_Pro\C_Programe\DSP\文档\03程序烧录方法\DSP烧录镜像制作工具\二级引导烧录镜像制作工具\simple.out
hex6x simple.rmd
b2i2c simple.btbl simple.btbl.i2c
b2ccs simple.btbl.i2c simple.i2c.ccs
romparse nysh.spi.map
modify i2crom.ccs spirom_le.dat
copy spirom_le.dat C:\ti\pdk\6678\pdk_c667x_2_0_13\packages\ti\boot\writer\nor\evmc6678l\bin