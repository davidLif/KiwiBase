################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PendingPuts/PutPendingItem.cpp 

OBJS += \
./PendingPuts/PutPendingItem.o 

CPP_DEPS += \
./PendingPuts/PutPendingItem.d 


# Each subdirectory must supply rules for building sources it contributes
PendingPuts/%.o: ../PendingPuts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


