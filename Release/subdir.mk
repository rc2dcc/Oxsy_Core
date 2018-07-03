################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../OxsyBasicCommands.cpp \
../OxsyClassPointers.cpp \
../OxsyClock.cpp \
../OxsyCommandsList.cpp \
../OxsyInfo.cpp \
../OxsyLogger.cpp \
../OxsyMain.cpp \
../OxsyParameters.cpp \
../OxsyPlay.cpp \
../OxsyPlayMode.cpp \
../OxsyPlayer.cpp \
../OxsyScanInfo.cpp \
../OxsyScoreInfo.cpp \
../OxsySensorInfo.cpp \
../OxsySocket.cpp \
../OxsySocketCommands.cpp \
../OxsyStatics.cpp \
../OxsyTime.cpp \
../OxsyUtility.cpp 

OBJS += \
./OxsyBasicCommands.o \
./OxsyClassPointers.o \
./OxsyClock.o \
./OxsyCommandsList.o \
./OxsyInfo.o \
./OxsyLogger.o \
./OxsyMain.o \
./OxsyParameters.o \
./OxsyPlay.o \
./OxsyPlayMode.o \
./OxsyPlayer.o \
./OxsyScanInfo.o \
./OxsyScoreInfo.o \
./OxsySensorInfo.o \
./OxsySocket.o \
./OxsySocketCommands.o \
./OxsyStatics.o \
./OxsyTime.o \
./OxsyUtility.o 

CPP_DEPS += \
./OxsyBasicCommands.d \
./OxsyClassPointers.d \
./OxsyClock.d \
./OxsyCommandsList.d \
./OxsyInfo.d \
./OxsyLogger.d \
./OxsyMain.d \
./OxsyParameters.d \
./OxsyPlay.d \
./OxsyPlayMode.d \
./OxsyPlayer.d \
./OxsyScanInfo.d \
./OxsyScoreInfo.d \
./OxsySensorInfo.d \
./OxsySocket.d \
./OxsySocketCommands.d \
./OxsyStatics.d \
./OxsyTime.d \
./OxsyUtility.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


