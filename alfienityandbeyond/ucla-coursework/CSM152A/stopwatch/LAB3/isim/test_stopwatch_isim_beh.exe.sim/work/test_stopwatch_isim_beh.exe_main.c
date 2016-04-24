/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003055665757_2370313535_init();
    work_m_00000000000279465966_4194365165_init();
    work_m_00000000003580368461_4165357748_init();
    work_m_00000000002920345709_3723373849_init();
    work_m_00000000003739584497_2585087929_init();
    work_m_00000000001717965083_2477501822_init();
    work_m_00000000003351870002_2908904151_init();
    work_m_00000000003258198225_2138391471_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000003258198225_2138391471");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
