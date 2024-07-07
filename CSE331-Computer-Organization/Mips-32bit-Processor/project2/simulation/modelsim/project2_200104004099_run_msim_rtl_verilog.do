transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/adder1.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/adder4_cla.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/adder4_g_p_G_P_signals.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/addSubBlock.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/inverter32.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/mod_dp.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/onebit_mux_two_one.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/fourbit_mux_two_one.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/thirtytwobit_mux_two_one.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/mod_cu.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/mod.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/alu.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/and4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/and32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/or4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/or32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/xor4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/xor32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/nor4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/nor32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/sign_extend.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/shift_left_2.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/control_unit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/alu_control.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/mips.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/fivebit_mux_two_one.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/instruction_block.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/register_block.v}
vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/memory_block.v}

vlog -vlog01compat -work work +incdir+C:/Users/Emre/Documents/quartus_lab/project2 {C:/Users/Emre/Documents/quartus_lab/project2/mips_tb.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  mips_tb

add wave *
view structure
view signals
run -all
