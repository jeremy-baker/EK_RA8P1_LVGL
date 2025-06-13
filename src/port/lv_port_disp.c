/**
 * @file lv_port_disp_templ.c
 *
 */


/*********************
 *      INCLUDES
 *********************/
#include "new_thread0.h"
#include "lv_port_disp.h"
#include "../../lvgl/src/drivers/display/renesas_glcdc/lv_renesas_glcdc.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/

    /* Shared RESET between the GT911 touch controller and the LCD, only reset once, here */
    disp_init();

    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    fsp_err_t err;
    err = RM_LVGL_PORT_Open(&g_lvgl_port_ctrl, &g_lvgl_port_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    /* Enable Backlight */
    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_BLEN, BSP_IO_LEVEL_HIGH);
}

static void disp_init(void)
{

    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_RESET, BSP_IO_LEVEL_HIGH);

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_RESET, BSP_IO_LEVEL_LOW);

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, LCD_RESET, BSP_IO_LEVEL_HIGH);

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
}
