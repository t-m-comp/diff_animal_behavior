################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Diff_main.cpp \
../source/bat_den_progross.cpp \
../source/k_means++.cpp \
../source/main.cpp \
../source/mem_useag.cpp \
../source/read_txt.cpp \
../source/sax.cpp \
../source/sort.cpp \
../source/spectral_clustering.cpp \
../source/useful.cpp 

OBJS += \
./source/Diff_main.o \
./source/bat_den_progross.o \
./source/k_means++.o \
./source/main.o \
./source/mem_useag.o \
./source/read_txt.o \
./source/sax.o \
./source/sort.o \
./source/spectral_clustering.o \
./source/useful.o 

CPP_DEPS += \
./source/Diff_main.d \
./source/bat_den_progross.d \
./source/k_means++.d \
./source/main.d \
./source/mem_useag.d \
./source/read_txt.d \
./source/sax.d \
./source/sort.d \
./source/spectral_clustering.d \
./source/useful.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/april/workspace/cluster_method/head" -O1 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


