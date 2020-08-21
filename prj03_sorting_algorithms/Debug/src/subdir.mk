################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prj03_sorting_algorithms.cpp \
../src/sortingalgorythms.cpp 

OBJS += \
./src/prj03_sorting_algorithms.o \
./src/sortingalgorythms.o 

CPP_DEPS += \
./src/prj03_sorting_algorithms.d \
./src/sortingalgorythms.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


