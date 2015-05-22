SET PATH=E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40;C:\ProgramData\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\Microsoft\Web Platform Installer\;C:\Program Files (x86)\Microsoft ASP.NET\ASP.NET Web Pages\v1.0\;C:\Program Files (x86)\Microsoft SQL Server\100\Tools\Binn\;C:\Program Files\Microsoft SQL Server\100\Tools\Binn\;C:\Program Files\Microsoft SQL Server\100\DTS\Binn\;d:\MATLAB\R2013a\runtime\win64;d:\MATLAB\R2013a\bin;E:\Program Files (x86)\QuickTime\QTSystem\;D:\Python\Python27;D:\Python\Python27\Scripts;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\TekVISA\BIN;C:\Program Files\IVI Foundation\VISA\Win64\Bin\
SET ARMCC41INC=E:\Program Files (x86)\Keil\Keil 4.54\ARM\RV31\Inc
SET ARMCC41LIB=E:\Program Files (x86)\Keil\Keil 4.54\ARM\RV31\Lib
SET CPU_TYPE=STM32F103VC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_it.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\system_stm32f10x.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\timer.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\led.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\key.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\spi.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\a7139.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\a7139_config.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\interrupt.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\flash.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\delay.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\sys.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\usart.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_exti.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\core_cm3.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmAsm" --Via "..\obj\startup_stm32f10x_hd._ia"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\misc.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_fsmc.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_gpio.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_rcc.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_tim.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_usart.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\stm32f10x_spi.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\main.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\beacon.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\processevent.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\join.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\device.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmCC" --Via "..\obj\tdma.__i"
"E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\ArmLink" --Via "..\OBJ\SPI.lnp"
E:\Program Files (x86)\Keil\Keil 4.54\ARM\BIN40\fromelf.exe "..\OBJ\SPI.axf" --i32combined --output "..\OBJ\SPI.hex"
fromelf.exe --bin -o ../obj/SPI.bin ../obj/SPI.axf
