#/******************************************************************************
#*
#* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
#*
#* Permission is hereby granted, free of charge, to any person obtaining a copy
#* of this software and associated documentation files (the "Software"), to deal
#* in the Software without restriction, including without limitation the rights
#* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#* copies of the Software, and to permit persons to whom the Software is
#* furnished to do so, subject to the following conditions:
#*
#* The above copyright notice and this permission notice shall be included in
#* all copies or substantial portions of the Software.
#*
#* Use of the Software is limited solely to applications:
#* (a) running on a Xilinx device, or
#* (b) that interact with a Xilinx device through a bus or interconnect.
#*
#* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
#* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
#* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#* SOFTWARE.
#*
#* Except as contained in this notice, the name of the Xilinx shall not be used
#* in advertising or otherwise to promote the sale, use or other dealings in
#* this Software without prior written authorization from Xilinx.
#*
#******************************************************************************/

proc swapp_get_name {} {
    return "OpenAMP Echo Demo for uC/OS"
}

proc swapp_get_description {} {
    return "OpenAMP Echo Application for uC/OS"
}

proc check_oamp_supported_os {} {
    set oslist [hsi::get_os]

    if { [llength $oslist] != 1 } {
        return 0
    }
    set os [lindex $oslist 0]

    if {  $os != "ucos" } {
        error "This application is supported only on the uC/OS Board Support Packages"
    }
}

proc get_stdout {} {
    set os [hsi::get_os]
    if { $os == "" } {
        error "No Operating System specified in the Board Support Package.";
    }
    set stdout [common::get_property CONFIG.STDOUT $os];
    return $stdout;
}

proc check_stdout_hw {} {
        # check processor type
	set proc_instance [hsi::get_sw_processor];
	set hw_processor [common::get_property HW_INSTANCE $proc_instance]

	set slaves [common::get_property SLAVES [hsi::get_cells -hier [hsi::get_sw_processor]]]
	foreach slave $slaves {
		set slave_type [common::get_property IP_NAME [hsi::get_cells -hier $slave]];
		# Check for MDM-Uart peripheral. The MDM would be listed as a peripheral
		# only if it has a UART interface. So no further check is required
		if { $slave_type == "psu_uart" || $slave_type == "axi_uartlite" ||
			 $slave_type == "axi_uart16550" || $slave_type == "iomodule" ||
			 $slave_type == "mdm" } {
			return;
		}
	}

	error "This application requires a Uart IP in the hardware."
}

proc check_stdout_sw {} {
    set stdout [get_stdout];
    if { $stdout == "none" } {
        error "The STDOUT parameter is not set on the OS. Hello World requires stdout to be set."
    }
}
proc swapp_is_supported_sw {} {
    # make sure we are using a supported OS
    check_oamp_supported_os

    # make sure openamp and metal libs are available
    set librarylist_1 [hsi::get_libs -filter "NAME==ucos_openamp"]
    set librarylist_2 [hsi::get_libs -filter "NAME==ucos_libmetal"]

    if { ([llength $librarylist_1] == 0) || ([llength $librarylist_2] == 0) } {
        error "This application requires OpenAMP and Libmetal libraries in the Board Support Package."
    } elseif { [llength $librarylist_1] > 1 } {
        error "Multiple OpenAMP  libraries present in the Board Support Package."
    } elseif { [llength $librarylist_2] > 1 } {
        error "Multiple Libmetal libraries present in the Board Support Package."
    }
}

proc swapp_is_supported_hw {} {
    # check processor type
    set proc_instance [hsi::get_sw_processor]
    set hw_processor [common::get_property HW_INSTANCE $proc_instance]
    set proc_type [common::get_property IP_NAME [hsi::get_cells -hier $hw_processor]]

    if { $proc_type != "psu_cortexr5" } {
        error "This application is supported only for Cortex-R5 processors."
    }

    check_stdout_hw
    return 1
}

proc generate_stdout_config { fid } {
    set stdout [get_stdout];
    set stdout [hsi::get_cells -hier $stdout]

    # if stdout is uartlite, we don't have to generate anything
    set stdout_type [common::get_property IP_NAME $stdout];

    if { [regexp -nocase "uartlite" $stdout_type] || [string match -nocase "mdm" $stdout_type] } {
        return;
    } elseif { [regexp -nocase "uart16550" $stdout_type] } {
	# mention that we have a 16550
        puts $fid "#define STDOUT_IS_16550";

        # and note down its base address
	set prefix "XPAR_";
	set postfix "_BASEADDR";
	set stdout_baseaddr_macro $prefix$stdout$postfix;
	set stdout_baseaddr_macro [string toupper $stdout_baseaddr_macro];
	puts $fid "#define STDOUT_BASEADDR $stdout_baseaddr_macro";
    } elseif { [regexp -nocase "psu_uart" $stdout_type] } {
	# mention that we have a psu_uart
        puts $fid "#define STDOUT_IS_PSU_UART";
        # and get it device id
        set p8_uarts [lsort [hsi::get_cells -filter { ip_name == "psu_uart"} ]];
        set id 0
        foreach uart $p8_uarts {
            if {[string compare -nocase $uart $stdout] == 0} {
		puts $fid "#define UART_DEVICE_ID $id"
		break;
	    }
	    incr id
	}
    }
}

proc swapp_generate {} {
    set oslist [get_os]
    if { [llength $oslist] != 1 } {
        return 0
    }
    set os [lindex $oslist 0]

    set proc_instance [hsi::get_sw_processor]
    set hw_processor [common::get_property HW_INSTANCE $proc_instance]
    set proc_type [common::get_property IP_NAME [hsi::get_cells -hier $hw_processor]]

    # cleanup this file for writing
    set fid [open "platform_config.h" "w+"];
    puts $fid "#ifndef __PLATFORM_CONFIG_H_";
    puts $fid "#define __PLATFORM_CONFIG_H_\n";

    # if we have a uart16550/ps7_uart as stdout, then generate some config for that
    generate_stdout_config $fid;

    puts $fid "#endif";
    close $fid;

    return 1
}

proc swapp_get_linker_constraints {} {
    # don't generate a linker script, we provide one
    return "lscript no"
}

proc swapp_get_supported_processors {} {
    return "psu_cortexr5"
}

proc swapp_get_supported_os {} {
    return "ucos"
}
