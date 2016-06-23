
################################################################
# This is a generated script based on design: mb_sub
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.4
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source mb_sub_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7k325tffg900-2

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name mb_sub

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   puts "INFO: Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set m_apb [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:apb_rtl:1.0 m_apb ]
  set sys_clk [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 sys_clk ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {25000000} \
 ] $sys_clk
  set uart0 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 uart0 ]
  set uart1 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 uart1 ]
  set uart2 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 uart2 ]

  # Create ports
  set clk_100m [ create_bd_port -dir O -type clk clk_100m ]
  set clk_200m [ create_bd_port -dir O -type clk clk_200m ]
  set clk_50m [ create_bd_port -dir O -type clk clk_50m ]
  set clk_75m [ create_bd_port -dir O -type clk clk_75m ]
  set mb_intr [ create_bd_port -dir I -from 31 -to 0 -type intr mb_intr ]
  set_property -dict [ list \
CONFIG.PortWidth {32} \
CONFIG.SENSITIVITY {EDGE_RISING:NULL:NULL} \
 ] $mb_intr
  set rstn [ create_bd_port -dir O -from 0 -to 0 -type rst rstn ]
  set sys_clk_locked [ create_bd_port -dir O sys_clk_locked ]
  set sys_rst_n [ create_bd_port -dir I -type rst sys_rst_n ]
  set_property -dict [ list \
CONFIG.POLARITY {ACTIVE_LOW} \
 ] $sys_rst_n
  set uart0_irpt [ create_bd_port -dir O -type intr uart0_irpt ]
  set uart1_irpt [ create_bd_port -dir O -type intr uart1_irpt ]
  set uart2_irpt [ create_bd_port -dir O -type intr uart2_irpt ]

  # Create instance: axi_apb_bridge_0, and set properties
  set axi_apb_bridge_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_apb_bridge:3.0 axi_apb_bridge_0 ]
  set_property -dict [ list \
CONFIG.C_APB_NUM_SLAVES {1} \
CONFIG.C_DPHASE_TIMEOUT {0} \
 ] $axi_apb_bridge_0

  # Create instance: axi_intc_0, and set properties
  set axi_intc_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_intc:4.1 axi_intc_0 ]
  set_property -dict [ list \
CONFIG.C_ASYNC_INTR {0xFFFFFFF8} \
CONFIG.C_HAS_FAST {1} \
CONFIG.C_KIND_OF_INTR {0xFFFF0000} \
CONFIG.C_NUM_SW_INTR {0} \
CONFIG.C_PROCESSOR_CLK_FREQ_MHZ {75} \
 ] $axi_intc_0

  # Create instance: axi_interconnect_0, and set properties
  set axi_interconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0 ]
  set_property -dict [ list \
CONFIG.ENABLE_ADVANCED_OPTIONS {1} \
CONFIG.ENABLE_PROTOCOL_CHECKERS {0} \
CONFIG.NUM_MI {5} \
CONFIG.NUM_SI {1} \
CONFIG.STRATEGY {2} \
CONFIG.XBAR_DATA_WIDTH {64} \
 ] $axi_interconnect_0

  # Create instance: axi_uartlite_0, and set properties
  set axi_uartlite_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_0 ]
  set_property -dict [ list \
CONFIG.C_BAUDRATE {921600} \
CONFIG.C_S_AXI_ACLK_FREQ_HZ {75000000} \
 ] $axi_uartlite_0

  # Create instance: axi_uartlite_1, and set properties
  set axi_uartlite_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_1 ]
  set_property -dict [ list \
CONFIG.C_BAUDRATE {115200} \
CONFIG.C_S_AXI_ACLK_FREQ_HZ {75000000} \
 ] $axi_uartlite_1

  # Create instance: axi_uartlite_2, and set properties
  set axi_uartlite_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_2 ]
  set_property -dict [ list \
CONFIG.C_BAUDRATE {115200} \
CONFIG.C_S_AXI_ACLK_FREQ_HZ {75000000} \
 ] $axi_uartlite_2

  # Create instance: blk_mem_gen_0, and set properties
  set blk_mem_gen_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.3 blk_mem_gen_0 ]

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.2 clk_wiz_0 ]
  set_property -dict [ list \
CONFIG.CLKIN1_JITTER_PS {400.0} \
CONFIG.CLKOUT1_JITTER {207.962} \
CONFIG.CLKOUT1_PHASE_ERROR {222.305} \
CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50} \
CONFIG.CLKOUT2_JITTER {190.518} \
CONFIG.CLKOUT2_PHASE_ERROR {222.305} \
CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {100} \
CONFIG.CLKOUT2_USED {true} \
CONFIG.CLKOUT3_JITTER {197.510} \
CONFIG.CLKOUT3_PHASE_ERROR {222.305} \
CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {75} \
CONFIG.CLKOUT3_USED {true} \
CONFIG.CLKOUT4_JITTER {175.029} \
CONFIG.CLKOUT4_PHASE_ERROR {222.305} \
CONFIG.CLKOUT4_REQUESTED_OUT_FREQ {200} \
CONFIG.CLKOUT4_USED {true} \
CONFIG.DIFF_CLK_IN2_BOARD_INTERFACE {Custom} \
CONFIG.MMCM_CLKFBOUT_MULT_F {48} \
CONFIG.MMCM_CLKIN1_PERIOD {40.0} \
CONFIG.MMCM_CLKOUT0_DIVIDE_F {24} \
CONFIG.MMCM_CLKOUT1_DIVIDE {12} \
CONFIG.MMCM_CLKOUT2_DIVIDE {16} \
CONFIG.MMCM_CLKOUT3_DIVIDE {6} \
CONFIG.MMCM_DIVCLK_DIVIDE {1} \
CONFIG.NUM_OUT_CLKS {4} \
CONFIG.OVERRIDE_MMCM {false} \
CONFIG.PRIMITIVE {PLL} \
CONFIG.PRIM_IN_FREQ {25} \
CONFIG.PRIM_SOURCE {Differential_clock_capable_pin} \
CONFIG.RESET_PORT {resetn} \
CONFIG.RESET_TYPE {ACTIVE_LOW} \
 ] $clk_wiz_0

  # Create instance: lmb_bram_if_cntlr_0, and set properties
  set lmb_bram_if_cntlr_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_bram_if_cntlr:4.0 lmb_bram_if_cntlr_0 ]
  set_property -dict [ list \
CONFIG.C_MASK {0xd0000000} \
CONFIG.C_MASK1 {0x00000000} \
CONFIG.C_NUM_LMB {2} \
 ] $lmb_bram_if_cntlr_0

  # Create instance: mdm_0, and set properties
  set mdm_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mdm:3.2 mdm_0 ]

  # Create instance: microblaze_0, and set properties
  set microblaze_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:microblaze:9.5 microblaze_0 ]
  set_property -dict [ list \
CONFIG.C_D_AXI {1} \
CONFIG.C_D_LMB {1} \
CONFIG.C_FREQ {75000000} \
CONFIG.C_I_AXI {0} \
CONFIG.C_I_LMB {1} \
CONFIG.C_M_AXI_DC_USER_SIGNALS {0} \
CONFIG.C_M_AXI_D_BUS_EXCEPTION {1} \
CONFIG.C_M_AXI_IC_USER_SIGNALS {0} \
CONFIG.C_NUMBER_OF_PC_BRK {2} \
CONFIG.C_USE_BARREL {1} \
CONFIG.C_USE_DCACHE {0} \
CONFIG.C_USE_EXT_BRK {0} \
CONFIG.C_USE_EXT_NM_BRK {0} \
CONFIG.C_USE_HW_MUL {1} \
CONFIG.C_USE_ICACHE {0} \
CONFIG.C_USE_INTERRUPT {1} \
CONFIG.C_USE_MSR_INSTR {1} \
CONFIG.C_USE_PCMP_INSTR {1} \
CONFIG.G_TEMPLATE_LIST {6} \
CONFIG.G_USE_EXCEPTIONS {0} \
 ] $microblaze_0

  # Create instance: proc_sys_reset_0, and set properties
  set proc_sys_reset_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_0 ]
  set_property -dict [ list \
CONFIG.C_AUX_RESET_HIGH {0} \
 ] $proc_sys_reset_0

  # Create interface connections
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_pins axi_interconnect_0/S00_AXI] [get_bd_intf_pins microblaze_0/M_AXI_DP]
  connect_bd_intf_net -intf_net axi_apb_bridge_0_APB_M [get_bd_intf_ports m_apb] [get_bd_intf_pins axi_apb_bridge_0/APB_M]
  connect_bd_intf_net -intf_net axi_intc_0_interrupt [get_bd_intf_pins axi_intc_0/interrupt] [get_bd_intf_pins microblaze_0/INTERRUPT]
  connect_bd_intf_net -intf_net axi_interconnect_0_M00_AXI [get_bd_intf_pins axi_apb_bridge_0/AXI4_LITE] [get_bd_intf_pins axi_interconnect_0/M00_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M01_AXI [get_bd_intf_pins axi_interconnect_0/M01_AXI] [get_bd_intf_pins axi_uartlite_0/S_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M02_AXI [get_bd_intf_pins axi_intc_0/s_axi] [get_bd_intf_pins axi_interconnect_0/M02_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M03_AXI [get_bd_intf_pins axi_interconnect_0/M03_AXI] [get_bd_intf_pins axi_uartlite_2/S_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_0_M04_AXI [get_bd_intf_pins axi_interconnect_0/M04_AXI] [get_bd_intf_pins axi_uartlite_1/S_AXI]
  connect_bd_intf_net -intf_net axi_uartlite_0_UART [get_bd_intf_ports uart0] [get_bd_intf_pins axi_uartlite_0/UART]
  connect_bd_intf_net -intf_net axi_uartlite_1_UART [get_bd_intf_ports uart1] [get_bd_intf_pins axi_uartlite_1/UART]
  connect_bd_intf_net -intf_net axi_uartlite_2_UART [get_bd_intf_ports uart2] [get_bd_intf_pins axi_uartlite_2/UART]
  connect_bd_intf_net -intf_net lmb_bram_if_cntlr_0_BRAM_PORT [get_bd_intf_pins blk_mem_gen_0/BRAM_PORTA] [get_bd_intf_pins lmb_bram_if_cntlr_0/BRAM_PORT]
  connect_bd_intf_net -intf_net mdm_0_MBDEBUG_0 [get_bd_intf_pins mdm_0/MBDEBUG_0] [get_bd_intf_pins microblaze_0/DEBUG]
  connect_bd_intf_net -intf_net microblaze_0_DLMB [get_bd_intf_pins lmb_bram_if_cntlr_0/SLMB] [get_bd_intf_pins microblaze_0/DLMB]
  connect_bd_intf_net -intf_net microblaze_0_ILMB [get_bd_intf_pins lmb_bram_if_cntlr_0/SLMB1] [get_bd_intf_pins microblaze_0/ILMB]
  connect_bd_intf_net -intf_net sys_clk_1 [get_bd_intf_ports sys_clk] [get_bd_intf_pins clk_wiz_0/CLK_IN1_D]

  # Create port connections
  connect_bd_net -net axi_uartlite_0_interrupt [get_bd_ports uart0_irpt] [get_bd_pins axi_uartlite_0/interrupt]
  connect_bd_net -net axi_uartlite_1_interrupt [get_bd_ports uart1_irpt] [get_bd_pins axi_uartlite_1/interrupt]
  connect_bd_net -net axi_uartlite_2_interrupt [get_bd_ports uart2_irpt] [get_bd_pins axi_uartlite_2/interrupt]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_ports clk_50m] [get_bd_pins clk_wiz_0/clk_out1]
  connect_bd_net -net clk_wiz_0_clk_out2 [get_bd_ports clk_75m] [get_bd_pins axi_apb_bridge_0/s_axi_aclk] [get_bd_pins axi_intc_0/processor_clk] [get_bd_pins axi_intc_0/s_axi_aclk] [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK] [get_bd_pins axi_interconnect_0/M01_ACLK] [get_bd_pins axi_interconnect_0/M02_ACLK] [get_bd_pins axi_interconnect_0/M03_ACLK] [get_bd_pins axi_interconnect_0/M04_ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins axi_uartlite_0/s_axi_aclk] [get_bd_pins axi_uartlite_1/s_axi_aclk] [get_bd_pins axi_uartlite_2/s_axi_aclk] [get_bd_pins clk_wiz_0/clk_out3] [get_bd_pins lmb_bram_if_cntlr_0/LMB_Clk] [get_bd_pins microblaze_0/Clk] [get_bd_pins proc_sys_reset_0/slowest_sync_clk]
  connect_bd_net -net clk_wiz_0_clk_out3 [get_bd_ports clk_100m] [get_bd_pins clk_wiz_0/clk_out2]
  connect_bd_net -net clk_wiz_0_clk_out4 [get_bd_ports clk_200m] [get_bd_pins clk_wiz_0/clk_out4]
  connect_bd_net -net clk_wiz_0_locked [get_bd_ports sys_clk_locked] [get_bd_pins clk_wiz_0/locked] [get_bd_pins proc_sys_reset_0/dcm_locked]
  connect_bd_net -net intr_1 [get_bd_ports mb_intr] [get_bd_pins axi_intc_0/intr]
  connect_bd_net -net mdm_0_Debug_SYS_Rst [get_bd_pins mdm_0/Debug_SYS_Rst] [get_bd_pins proc_sys_reset_0/mb_debug_sys_rst]
  connect_bd_net -net proc_sys_reset_0_mb_reset [get_bd_pins axi_intc_0/processor_rst] [get_bd_pins lmb_bram_if_cntlr_0/LMB_Rst] [get_bd_pins microblaze_0/Reset] [get_bd_pins proc_sys_reset_0/mb_reset]
  connect_bd_net -net proc_sys_reset_0_peripheral_aresetn [get_bd_ports rstn] [get_bd_pins axi_apb_bridge_0/s_axi_aresetn] [get_bd_pins axi_intc_0/s_axi_aresetn] [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/M01_ARESETN] [get_bd_pins axi_interconnect_0/M02_ARESETN] [get_bd_pins axi_interconnect_0/M03_ARESETN] [get_bd_pins axi_interconnect_0/M04_ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_uartlite_0/s_axi_aresetn] [get_bd_pins axi_uartlite_1/s_axi_aresetn] [get_bd_pins axi_uartlite_2/s_axi_aresetn] [get_bd_pins proc_sys_reset_0/peripheral_aresetn]
  connect_bd_net -net sys_rst_1 [get_bd_ports sys_rst_n] [get_bd_pins clk_wiz_0/resetn] [get_bd_pins proc_sys_reset_0/ext_reset_in]

  # Create address segments
  create_bd_addr_seg -range 0x8000 -offset 0x11000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_intc_0/s_axi/Reg] SEG_axi_intc_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x40600000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_uartlite_0/S_AXI/Reg] SEG_axi_uartlite_0_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x40610000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_uartlite_1/S_AXI/Reg] SEG_axi_uartlite_1_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x40620000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs axi_uartlite_2/S_AXI/Reg] SEG_axi_uartlite_2_Reg
  create_bd_addr_seg -range 0x10000 -offset 0x0 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs lmb_bram_if_cntlr_0/SLMB/Mem] SEG_lmb_bram_if_cntlr_0_Mem
  create_bd_addr_seg -range 0x10000 -offset 0x0 [get_bd_addr_spaces microblaze_0/Instruction] [get_bd_addr_segs lmb_bram_if_cntlr_0/SLMB1/Mem] SEG_lmb_bram_if_cntlr_0_Mem
  create_bd_addr_seg -range 0x10000 -offset 0x20000000 [get_bd_addr_spaces microblaze_0/Data] [get_bd_addr_segs m_apb/Reg] SEG_mb_sub_Reg

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.5.5  2015-06-26 bk=1.3371 VDI=38 GEI=35 GUI=JA:1.6
#  -string -flagsOSRD
preplace port uart1_irpt -pg 1 -y 720 -defaultsOSRD
preplace port clk_200m -pg 1 -y 170 -defaultsOSRD
preplace port uart0_irpt -pg 1 -y 480 -defaultsOSRD
preplace port m_apb -pg 1 -y 590 -defaultsOSRD
preplace port sys_clk -pg 1 -y 140 -defaultsOSRD
preplace port uart0 -pg 1 -y 460 -defaultsOSRD
preplace port uart1 -pg 1 -y 700 -defaultsOSRD
preplace port uart2_irpt -pg 1 -y 1100 -defaultsOSRD
preplace port clk_100m -pg 1 -y 130 -defaultsOSRD
preplace port uart2 -pg 1 -y 1080 -defaultsOSRD
preplace port sys_rst_n -pg 1 -y 160 -defaultsOSRD
preplace port clk_50m -pg 1 -y 110 -defaultsOSRD
preplace port sys_clk_locked -pg 1 -y 190 -defaultsOSRD
preplace port clk_75m -pg 1 -y 780 -defaultsOSRD
preplace portBus rstn -pg 1 -y 800 -defaultsOSRD
preplace portBus mb_intr -pg 1 -y 960 -defaultsOSRD
preplace inst axi_intc_0 -pg 1 -lvl 1 -y 950 -defaultsOSRD
preplace inst proc_sys_reset_0 -pg 1 -lvl 3 -y 340 -defaultsOSRD
preplace inst mdm_0 -pg 1 -lvl 1 -y 770 -defaultsOSRD
preplace inst blk_mem_gen_0 -pg 1 -lvl 4 -y 940 -defaultsOSRD
preplace inst microblaze_0 -pg 1 -lvl 2 -y 910 -defaultsOSRD
preplace inst axi_uartlite_0 -pg 1 -lvl 4 -y 470 -defaultsOSRD
preplace inst axi_interconnect_0 -pg 1 -lvl 3 -y 610 -defaultsOSRD
preplace inst axi_apb_bridge_0 -pg 1 -lvl 4 -y 590 -defaultsOSRD
preplace inst axi_uartlite_1 -pg 1 -lvl 4 -y 710 -defaultsOSRD
preplace inst lmb_bram_if_cntlr_0 -pg 1 -lvl 3 -y 930 -defaultsOSRD
preplace inst clk_wiz_0 -pg 1 -lvl 3 -y 150 -defaultsOSRD
preplace inst axi_uartlite_2 -pg 1 -lvl 4 -y 1090 -defaultsOSRD
preplace netloc axi_intc_0_interrupt 1 1 1 270
preplace netloc axi_uartlite_2_interrupt 1 4 1 NJ
preplace netloc sys_rst_1 1 0 3 NJ 160 NJ 160 730
preplace netloc axi_uartlite_1_interrupt 1 4 1 NJ
preplace netloc clk_wiz_0_locked 1 2 3 740 240 1070 190 NJ
preplace netloc axi_apb_bridge_0_APB_M 1 4 1 NJ
preplace netloc axi_uartlite_0_interrupt 1 4 1 NJ
preplace netloc mdm_0_Debug_SYS_Rst 1 1 2 NJ 360 N
preplace netloc axi_uartlite_1_UART 1 4 1 NJ
preplace netloc microblaze_0_ILMB 1 2 1 710
preplace netloc sys_clk_1 1 0 3 NJ 140 NJ 140 NJ
preplace netloc axi_interconnect_0_M02_AXI 1 0 4 0 830 NJ 830 NJ 830 1060
preplace netloc proc_sys_reset_0_mb_reset 1 0 4 30 1060 290 1000 740 1010 1070
preplace netloc axi_uartlite_2_UART 1 4 1 NJ
preplace netloc intr_1 1 0 1 NJ
preplace netloc axi_interconnect_0_M04_AXI 1 3 1 1110
preplace netloc lmb_bram_if_cntlr_0_BRAM_PORT 1 3 1 NJ
preplace netloc S00_AXI_1 1 2 1 730
preplace netloc clk_wiz_0_clk_out1 1 3 2 NJ 110 NJ
preplace netloc axi_uartlite_0_UART 1 4 1 NJ
preplace netloc axi_interconnect_0_M00_AXI 1 3 1 N
preplace netloc proc_sys_reset_0_peripheral_aresetn 1 0 5 10 840 NJ 810 740 810 1090 800 NJ
preplace netloc clk_wiz_0_clk_out2 1 0 5 20 1050 280 990 720 250 1120 780 NJ
preplace netloc axi_interconnect_0_M01_AXI 1 3 1 1060
preplace netloc mdm_0_MBDEBUG_0 1 1 1 260
preplace netloc clk_wiz_0_clk_out3 1 3 2 N 130 NJ
preplace netloc clk_wiz_0_clk_out4 1 3 2 NJ 170 NJ
preplace netloc axi_interconnect_0_M03_AXI 1 3 1 1100
preplace netloc microblaze_0_DLMB 1 2 1 740
levelinfo -pg 1 -20 140 500 900 1230 1360 -top 50 -bot 1160
",
}

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


