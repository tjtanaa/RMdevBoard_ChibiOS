/**
 * Beck Pang, 20180331
 * Mixing the command from joystick, keyboard, and computer vision
 */

#include <main.h>
#include "ch.h"
#include "dbus.h"
#include "math_misc.h"
#include "command_mixer_task.h"
#include "gimbal.h"
#include "string.h"

// create a new thread for this
static THD_WORKING_AREA(command_mixer_wa, 512);
static GimbalCommandStruct gimbal_cmd;

GimbalCommandStruct* gimbal_cmd_get(void)
{
    return &gimbal_cmd;
}

/**
 * gimbal mixer
 * @input: RC_Ctl_t, computer vision command
 * @ouput: target gimbal attitude, target gimbal angular velocity
 */
static THD_FUNCTION(command_mixer, ptr)
{
    (void)ptr;
    chRegSetThreadName("command_mixer");
    RC_Ctl_t* pRC = RC_get();
    GimbalStruct* pGimbal = gimbal_get();

    while (!chThdShouldTerminateX())
    {
        // handle joystick
        gimbal_cmd.yaw_vel_cmd = mapInput(pRC->rc.channel3, RC_CH_VALUE_MIN, RC_CH_VALUE_MAX, (float)M_PI/2000, (float)-M_PI/2000);
        gimbal_cmd.pitch_vel_cmd = mapInput(pRC->rc.channel2, RC_CH_VALUE_MIN, RC_CH_VALUE_MAX, (float)M_PI/700, (float)-M_PI/700);
        gimbal_cmd.yaw_atti_cmd += gimbal_cmd.yaw_vel_cmd;
        gimbal_cmd.pitch_atti_cmd += gimbal_cmd.pitch_vel_cmd;

        // TODO: understand Edward's code

        bound(&gimbal_cmd.pitch_atti_cmd, (float)M_PI/8);
        bound(&gimbal_cmd.yaw_atti_cmd, (float)M_PI); // change to M_PI/3 if gear ratio changed
//        pGimbal->yaw_atti_cmd = gimbal_cmd.yaw_atti_cmd;
//        pGimbal->pitch_atti_cmd = gimbal_cmd.pitch_atti_cmd;
        chThdSleepMilliseconds(1);
    }
}

/**
 * @Dependent   Requires RC_init() and MAVLink_init() to be run first
 */
void command_mixer_init(void)
{
    memset(&gimbal_cmd, 0, sizeof(GimbalCommandStruct));

    gimbal_cmd.yaw_atti_cmd = 0;
    gimbal_cmd.yaw_vel_cmd = 0;
    gimbal_cmd.pitch_atti_cmd = 0;
    gimbal_cmd.pitch_vel_cmd = 0;

    chThdCreateStatic(command_mixer_wa, sizeof(command_mixer_wa),
                        NORMALPRIO - 4, command_mixer, NULL);
}