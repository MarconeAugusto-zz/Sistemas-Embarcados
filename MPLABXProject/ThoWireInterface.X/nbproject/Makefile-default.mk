#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=TWIMaster.cpp TWISlave.cpp GPIO.cpp GPIO_Port.cpp UART.cpp mainMASTER.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/TWIMaster.o ${OBJECTDIR}/TWISlave.o ${OBJECTDIR}/GPIO.o ${OBJECTDIR}/GPIO_Port.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/mainMASTER.o
POSSIBLE_DEPFILES=${OBJECTDIR}/TWIMaster.o.d ${OBJECTDIR}/TWISlave.o.d ${OBJECTDIR}/GPIO.o.d ${OBJECTDIR}/GPIO_Port.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/mainMASTER.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/TWIMaster.o ${OBJECTDIR}/TWISlave.o ${OBJECTDIR}/GPIO.o ${OBJECTDIR}/GPIO_Port.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/mainMASTER.o

# Source Files
SOURCEFILES=TWIMaster.cpp TWISlave.cpp GPIO.cpp GPIO_Port.cpp UART.cpp mainMASTER.cpp


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=ATmega2560
ProjectDir=/home/guilherme/MPLABXProjects/Sistemas-Embarcados/MPLABXProject/ThoWireInterface.X
ConfName=default
ImagePath=dist/default/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ImageDir=dist/default/${IMAGE_TYPE}
ImageName=ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [avrdude -c avrispmkII -P /dev/ttyACM0 -D -p ${Device} -U flash:w:${ImagePath}:i]"
	@avrdude -c avrispmkII -P /dev/ttyACM0 -D -p ${Device} -U flash:w:${ImagePath}:i
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATmega2560
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/TWIMaster.o: TWIMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWIMaster.o.d 
	@${RM} ${OBJECTDIR}/TWIMaster.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/TWIMaster.o.d" -MT "${OBJECTDIR}/TWIMaster.o.d" -MT ${OBJECTDIR}/TWIMaster.o  -o ${OBJECTDIR}/TWIMaster.o TWIMaster.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TWISlave.o: TWISlave.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWISlave.o.d 
	@${RM} ${OBJECTDIR}/TWISlave.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/TWISlave.o.d" -MT "${OBJECTDIR}/TWISlave.o.d" -MT ${OBJECTDIR}/TWISlave.o  -o ${OBJECTDIR}/TWISlave.o TWISlave.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GPIO.o: GPIO.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO.o.d 
	@${RM} ${OBJECTDIR}/GPIO.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/GPIO.o.d" -MT "${OBJECTDIR}/GPIO.o.d" -MT ${OBJECTDIR}/GPIO.o  -o ${OBJECTDIR}/GPIO.o GPIO.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GPIO_Port.o: GPIO_Port.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Port.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Port.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/GPIO_Port.o.d" -MT "${OBJECTDIR}/GPIO_Port.o.d" -MT ${OBJECTDIR}/GPIO_Port.o  -o ${OBJECTDIR}/GPIO_Port.o GPIO_Port.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/UART.o: UART.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o  -o ${OBJECTDIR}/UART.o UART.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mainMASTER.o: mainMASTER.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mainMASTER.o.d 
	@${RM} ${OBJECTDIR}/mainMASTER.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560" -g -DDEBUG  -gdwarf-2  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/mainMASTER.o.d" -MT "${OBJECTDIR}/mainMASTER.o.d" -MT ${OBJECTDIR}/mainMASTER.o  -o ${OBJECTDIR}/mainMASTER.o mainMASTER.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/TWIMaster.o: TWIMaster.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWIMaster.o.d 
	@${RM} ${OBJECTDIR}/TWIMaster.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/TWIMaster.o.d" -MT "${OBJECTDIR}/TWIMaster.o.d" -MT ${OBJECTDIR}/TWIMaster.o  -o ${OBJECTDIR}/TWIMaster.o TWIMaster.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TWISlave.o: TWISlave.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWISlave.o.d 
	@${RM} ${OBJECTDIR}/TWISlave.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/TWISlave.o.d" -MT "${OBJECTDIR}/TWISlave.o.d" -MT ${OBJECTDIR}/TWISlave.o  -o ${OBJECTDIR}/TWISlave.o TWISlave.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GPIO.o: GPIO.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO.o.d 
	@${RM} ${OBJECTDIR}/GPIO.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/GPIO.o.d" -MT "${OBJECTDIR}/GPIO.o.d" -MT ${OBJECTDIR}/GPIO.o  -o ${OBJECTDIR}/GPIO.o GPIO.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/GPIO_Port.o: GPIO_Port.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Port.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Port.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/GPIO_Port.o.d" -MT "${OBJECTDIR}/GPIO_Port.o.d" -MT ${OBJECTDIR}/GPIO_Port.o  -o ${OBJECTDIR}/GPIO_Port.o GPIO_Port.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/UART.o: UART.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o  -o ${OBJECTDIR}/UART.o UART.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mainMASTER.o: mainMASTER.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mainMASTER.o.d 
	@${RM} ${OBJECTDIR}/mainMASTER.o 
	 ${MP_CPPC} $(MP_EXTRA_CC_PRE) -mmcu=atmega2560  -I "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/include"  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -x c++ -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/mainMASTER.o.d" -MT "${OBJECTDIR}/mainMASTER.o.d" -MT ${OBJECTDIR}/mainMASTER.o  -o ${OBJECTDIR}/mainMASTER.o mainMASTER.cpp  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=atmega2560  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -mmcu=atmega2560  -B "/opt/microchip/mplabx/v5.20/packs/Microchip/ATmega_DFP/2.0.12/gcc/dev/atmega2560"  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/ThoWireInterface.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
