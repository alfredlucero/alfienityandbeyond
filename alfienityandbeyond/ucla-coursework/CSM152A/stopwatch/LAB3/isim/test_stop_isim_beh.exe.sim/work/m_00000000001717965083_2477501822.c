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

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/display7.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {192U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {249U, 0U};
static unsigned int ng5[] = {2U, 0U};
static unsigned int ng6[] = {164U, 0U};
static unsigned int ng7[] = {3U, 0U};
static unsigned int ng8[] = {176U, 0U};
static unsigned int ng9[] = {4U, 0U};
static unsigned int ng10[] = {153U, 0U};
static unsigned int ng11[] = {5U, 0U};
static unsigned int ng12[] = {146U, 0U};
static unsigned int ng13[] = {6U, 0U};
static unsigned int ng14[] = {130U, 0U};
static unsigned int ng15[] = {7U, 0U};
static unsigned int ng16[] = {248U, 0U};
static unsigned int ng17[] = {8U, 0U};
static unsigned int ng18[] = {128U, 0U};
static unsigned int ng19[] = {9U, 0U};
static unsigned int ng20[] = {144U, 0U};
static unsigned int ng21[] = {11U, 0U};
static int ng22[] = {0, 0};
static unsigned int ng23[] = {13U, 0U};
static unsigned int ng24[] = {14U, 0U};



static void Always_31_0(char *t0)
{
    char t9[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t13;

LAB0:    t1 = (t0 + 3328U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 3648);
    *((int *)t2) = 1;
    t3 = (t0 + 3360);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(32, ng0);

LAB5:    xsi_set_current_line(33, ng0);
    t4 = (t0 + 1688U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t4, 4);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng13)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng15)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng17)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng19)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB25;

LAB26:
LAB28:
LAB27:    xsi_set_current_line(44, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);

LAB29:    xsi_set_current_line(46, ng0);
    t2 = (t0 + 1848U);
    t3 = *((char **)t2);

LAB30:    t2 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t6 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t6 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t6 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t6 == 1)
        goto LAB37;

LAB38:
LAB40:
LAB39:    xsi_set_current_line(55, ng0);
    t2 = ((char*)((ng1)));
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t2, 0, 0, 4);

LAB41:    goto LAB2;

LAB7:    xsi_set_current_line(34, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t0 + 2248);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 8);
    goto LAB29;

LAB9:    xsi_set_current_line(35, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB11:    xsi_set_current_line(36, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB13:    xsi_set_current_line(37, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB15:    xsi_set_current_line(38, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB17:    xsi_set_current_line(39, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB19:    xsi_set_current_line(40, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB21:    xsi_set_current_line(41, ng0);
    t3 = ((char*)((ng16)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB23:    xsi_set_current_line(42, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB25:    xsi_set_current_line(43, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 8);
    goto LAB29;

LAB31:    xsi_set_current_line(47, ng0);
    t4 = ((char*)((ng15)));
    t7 = (t0 + 2408);
    xsi_vlogvar_assign_value(t7, t4, 0, 0, 4);
    goto LAB41;

LAB33:    xsi_set_current_line(49, ng0);

LAB42:    xsi_set_current_line(50, ng0);
    t4 = ((char*)((ng21)));
    t7 = (t0 + 2408);
    xsi_vlogvar_assign_value(t7, t4, 0, 0, 4);
    xsi_set_current_line(51, ng0);
    t2 = ((char*)((ng22)));
    t4 = (t0 + 2248);
    t7 = (t0 + 2248);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = ((char*)((ng22)));
    xsi_vlog_generic_convert_bit_index(t9, t10, 2, t11, 32, 1);
    t12 = (t9 + 4);
    t13 = *((unsigned int *)t12);
    t6 = (!(t13));
    if (t6 == 1)
        goto LAB43;

LAB44:    goto LAB41;

LAB35:    xsi_set_current_line(53, ng0);
    t4 = ((char*)((ng23)));
    t7 = (t0 + 2408);
    xsi_vlogvar_assign_value(t7, t4, 0, 0, 4);
    goto LAB41;

LAB37:    xsi_set_current_line(54, ng0);
    t4 = ((char*)((ng24)));
    t7 = (t0 + 2408);
    xsi_vlogvar_assign_value(t7, t4, 0, 0, 4);
    goto LAB41;

LAB43:    xsi_vlogvar_assign_value(t4, t2, 0, *((unsigned int *)t9), 1);
    goto LAB44;

}


extern void work_m_00000000001717965083_2477501822_init()
{
	static char *pe[] = {(void *)Always_31_0};
	xsi_register_didat("work_m_00000000001717965083_2477501822", "isim/test_stop_isim_beh.exe.sim/work/m_00000000001717965083_2477501822.didat");
	xsi_register_executes(pe);
}
