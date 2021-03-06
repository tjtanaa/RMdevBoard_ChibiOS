# stable internal files basic hardware functions
DEV_PATH = $(CHIBIOS)/dev

DEVSRC =    \
            $(DEV_PATH)/shellcfg.c \
            $(DEV_PATH)/dbus.c \
            $(DEV_PATH)/exti.c \
            $(DEV_PATH)/flash.c \
            $(DEV_PATH)/imu_temp.c \
            $(DEV_PATH)/params.c \
            $(DEV_PATH)/shoot_pwm.c \
            $(DEV_PATH)/pwm_test.c \
            $(DEV_PATH)/can_bus.c \
            $(DEV_PATH)/usbcfg.c
            # $(DEV_PATH)/shooter_rm3508.c \

# general configuration and headers
DEVINC =    $(DEV_PATH)/inc \
            $(DEV_PATH)/conf