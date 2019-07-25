################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./LCD_Files/hal_LCD.obj" \
"./MSP430FR2xx_4xx/adc.obj" \
"./MSP430FR2xx_4xx/crc.obj" \
"./MSP430FR2xx_4xx/cs.obj" \
"./MSP430FR2xx_4xx/ecomp.obj" \
"./MSP430FR2xx_4xx/eusci_a_spi.obj" \
"./MSP430FR2xx_4xx/eusci_a_uart.obj" \
"./MSP430FR2xx_4xx/eusci_b_i2c.obj" \
"./MSP430FR2xx_4xx/eusci_b_spi.obj" \
"./MSP430FR2xx_4xx/framctl.obj" \
"./MSP430FR2xx_4xx/gpio.obj" \
"./MSP430FR2xx_4xx/icc.obj" \
"./MSP430FR2xx_4xx/lcd_e.obj" \
"./MSP430FR2xx_4xx/mpy32.obj" \
"./MSP430FR2xx_4xx/pmm.obj" \
"./MSP430FR2xx_4xx/rtc.obj" \
"./MSP430FR2xx_4xx/sac.obj" \
"./MSP430FR2xx_4xx/sfr.obj" \
"./MSP430FR2xx_4xx/sysctl.obj" \
"./MSP430FR2xx_4xx/tia.obj" \
"./MSP430FR2xx_4xx/timer_a.obj" \
"./MSP430FR2xx_4xx/timer_b.obj" \
"./MSP430FR2xx_4xx/tlv.obj" \
"./MSP430FR2xx_4xx/wdt_a.obj" \
"../lnk_msp430fr4133.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include LCD_Files/subdir_vars.mk
-include MSP430FR2xx_4xx/subdir_vars.mk
-include subdir_rules.mk
-include LCD_Files/subdir_rules.mk
-include MSP430FR2xx_4xx/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
GreenHouse_Control.out \

EXE_OUTPUTS__QUOTED += \
"GreenHouse_Control.out" \

BIN_OUTPUTS += \
GreenHouse_Control.hex \

BIN_OUTPUTS__QUOTED += \
"GreenHouse_Control.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "GreenHouse_Control.out"

# Tool invocations
GreenHouse_Control.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmspx --use_hw_mpy=none --advice:power=all --advice:hw_config=all --define=__MSP430FR4133__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"GreenHouse_Control.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"/Applications/ti/ccsv8/ccs_base/msp430/include" -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/lib" -i"/Applications/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="GreenHouse_Control_linkInfo.xml" --use_hw_mpy=none --rom_model -o "GreenHouse_Control.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

GreenHouse_Control.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "GreenHouse_Control.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "LCD_Files/hal_LCD.obj" "MSP430FR2xx_4xx/adc.obj" "MSP430FR2xx_4xx/crc.obj" "MSP430FR2xx_4xx/cs.obj" "MSP430FR2xx_4xx/ecomp.obj" "MSP430FR2xx_4xx/eusci_a_spi.obj" "MSP430FR2xx_4xx/eusci_a_uart.obj" "MSP430FR2xx_4xx/eusci_b_i2c.obj" "MSP430FR2xx_4xx/eusci_b_spi.obj" "MSP430FR2xx_4xx/framctl.obj" "MSP430FR2xx_4xx/gpio.obj" "MSP430FR2xx_4xx/icc.obj" "MSP430FR2xx_4xx/lcd_e.obj" "MSP430FR2xx_4xx/mpy32.obj" "MSP430FR2xx_4xx/pmm.obj" "MSP430FR2xx_4xx/rtc.obj" "MSP430FR2xx_4xx/sac.obj" "MSP430FR2xx_4xx/sfr.obj" "MSP430FR2xx_4xx/sysctl.obj" "MSP430FR2xx_4xx/tia.obj" "MSP430FR2xx_4xx/timer_a.obj" "MSP430FR2xx_4xx/timer_b.obj" "MSP430FR2xx_4xx/tlv.obj" "MSP430FR2xx_4xx/wdt_a.obj" 
	-$(RM) "main.d" "LCD_Files/hal_LCD.d" "MSP430FR2xx_4xx/adc.d" "MSP430FR2xx_4xx/crc.d" "MSP430FR2xx_4xx/cs.d" "MSP430FR2xx_4xx/ecomp.d" "MSP430FR2xx_4xx/eusci_a_spi.d" "MSP430FR2xx_4xx/eusci_a_uart.d" "MSP430FR2xx_4xx/eusci_b_i2c.d" "MSP430FR2xx_4xx/eusci_b_spi.d" "MSP430FR2xx_4xx/framctl.d" "MSP430FR2xx_4xx/gpio.d" "MSP430FR2xx_4xx/icc.d" "MSP430FR2xx_4xx/lcd_e.d" "MSP430FR2xx_4xx/mpy32.d" "MSP430FR2xx_4xx/pmm.d" "MSP430FR2xx_4xx/rtc.d" "MSP430FR2xx_4xx/sac.d" "MSP430FR2xx_4xx/sfr.d" "MSP430FR2xx_4xx/sysctl.d" "MSP430FR2xx_4xx/tia.d" "MSP430FR2xx_4xx/timer_a.d" "MSP430FR2xx_4xx/timer_b.d" "MSP430FR2xx_4xx/tlv.d" "MSP430FR2xx_4xx/wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

