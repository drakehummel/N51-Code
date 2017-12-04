################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Client

dependents:
	-cd /root/workspace/Utils/Debug && $(MAKE) clean all

# Tool invocations
Client: $(OBJS) $(USER_OBJS) /root/workspace/Utils/Debug/libUtils.a
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/root/workspace/Utils/Debug" -o "Client" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Client
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/root/workspace/Utils/Debug/libUtils.a:

-include ../makefile.targets
