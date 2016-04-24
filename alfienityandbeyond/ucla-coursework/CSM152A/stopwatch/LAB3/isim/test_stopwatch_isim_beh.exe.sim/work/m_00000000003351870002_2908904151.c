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
static const char *ng0 = "C:/Users/152/Desktop/Alfred_Maya_Lab3/LAB3/stopwatch.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {9U, 0U};
static unsigned int ng4[] = {5U, 0U};
static int ng5[] = {4, 0};
static int ng6[] = {2, 0};
static int ng7[] = {3, 0};



static void Initial_47_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(47, ng0);

LAB2:    xsi_set_current_line(48, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3528);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 4);
    xsi_set_current_line(49, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3688);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 4);
    xsi_set_current_line(50, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3848);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 4);
    xsi_set_current_line(51, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 4008);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 4);
    xsi_set_current_line(52, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 4168);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(53, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 4328);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(54, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 4488);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB1:    return;
}

static void Always_95_1(char *t0)
{
    char t13[8];
    char t17[8];
    char t22[8];
    char t38[8];
    char t46[8];
    char t88[8];
    char t99[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t37;
    char *t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t45;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    char *t50;
    char *t51;
    char *t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    char *t60;
    char *t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    int t70;
    int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;
    char *t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    char *t95;
    char *t96;
    char *t97;
    char *t98;
    char *t100;

LAB0:    t1 = (t0 + 5656U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(95, ng0);
    t2 = (t0 + 5976);
    *((int *)t2) = 1;
    t3 = (t0 + 5688);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(96, ng0);

LAB5:    xsi_set_current_line(97, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:
LAB8:    xsi_set_current_line(104, ng0);
    t2 = (t0 + 2008U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t3 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t3);
    t9 = (t8 & t7);
    t10 = (t9 & 1U);
    if (t10 != 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t2) != 0)
        goto LAB12;

LAB13:    t5 = (t13 + 4);
    t14 = *((unsigned int *)t13);
    t15 = *((unsigned int *)t5);
    t16 = (t14 || t15);
    if (t16 > 0)
        goto LAB14;

LAB15:    memcpy(t46, t13, 8);

LAB16:    t78 = (t46 + 4);
    t79 = *((unsigned int *)t78);
    t80 = (~(t79));
    t81 = *((unsigned int *)t46);
    t82 = (t81 & t80);
    t83 = (t82 != 0);
    if (t83 > 0)
        goto LAB28;

LAB29:
LAB30:    xsi_set_current_line(131, ng0);
    t2 = (t0 + 2168U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t3);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB68;

LAB69:
LAB70:    xsi_set_current_line(163, ng0);
    t2 = (t0 + 2648U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t3);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB89;

LAB90:
LAB91:    goto LAB2;

LAB6:    xsi_set_current_line(98, ng0);

LAB9:    xsi_set_current_line(99, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 4, 0LL);
    xsi_set_current_line(100, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 3688);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 4, 0LL);
    xsi_set_current_line(101, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 3848);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 4, 0LL);
    xsi_set_current_line(102, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 4008);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 4, 0LL);
    goto LAB8;

LAB10:    *((unsigned int *)t13) = 1;
    goto LAB13;

LAB12:    t4 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t4) = 1;
    goto LAB13;

LAB14:    t11 = (t0 + 1528U);
    t12 = *((char **)t11);
    t11 = (t0 + 1488U);
    t18 = (t11 + 72U);
    t19 = *((char **)t18);
    t20 = ((char*)((ng1)));
    xsi_vlog_generic_get_index_select_value(t17, 32, t12, t19, 2, t20, 32, 1);
    t21 = ((char*)((ng1)));
    memset(t22, 0, 8);
    t23 = (t17 + 4);
    t24 = (t21 + 4);
    t25 = *((unsigned int *)t17);
    t26 = *((unsigned int *)t21);
    t27 = (t25 ^ t26);
    t28 = *((unsigned int *)t23);
    t29 = *((unsigned int *)t24);
    t30 = (t28 ^ t29);
    t31 = (t27 | t30);
    t32 = *((unsigned int *)t23);
    t33 = *((unsigned int *)t24);
    t34 = (t32 | t33);
    t35 = (~(t34));
    t36 = (t31 & t35);
    if (t36 != 0)
        goto LAB20;

LAB17:    if (t34 != 0)
        goto LAB19;

LAB18:    *((unsigned int *)t22) = 1;

LAB20:    memset(t38, 0, 8);
    t39 = (t22 + 4);
    t40 = *((unsigned int *)t39);
    t41 = (~(t40));
    t42 = *((unsigned int *)t22);
    t43 = (t42 & t41);
    t44 = (t43 & 1U);
    if (t44 != 0)
        goto LAB21;

LAB22:    if (*((unsigned int *)t39) != 0)
        goto LAB23;

LAB24:    t47 = *((unsigned int *)t13);
    t48 = *((unsigned int *)t38);
    t49 = (t47 & t48);
    *((unsigned int *)t46) = t49;
    t50 = (t13 + 4);
    t51 = (t38 + 4);
    t52 = (t46 + 4);
    t53 = *((unsigned int *)t50);
    t54 = *((unsigned int *)t51);
    t55 = (t53 | t54);
    *((unsigned int *)t52) = t55;
    t56 = *((unsigned int *)t52);
    t57 = (t56 != 0);
    if (t57 == 1)
        goto LAB25;

LAB26:
LAB27:    goto LAB16;

LAB19:    t37 = (t22 + 4);
    *((unsigned int *)t22) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB20;

LAB21:    *((unsigned int *)t38) = 1;
    goto LAB24;

LAB23:    t45 = (t38 + 4);
    *((unsigned int *)t38) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB24;

LAB25:    t58 = *((unsigned int *)t46);
    t59 = *((unsigned int *)t52);
    *((unsigned int *)t46) = (t58 | t59);
    t60 = (t13 + 4);
    t61 = (t38 + 4);
    t62 = *((unsigned int *)t13);
    t63 = (~(t62));
    t64 = *((unsigned int *)t60);
    t65 = (~(t64));
    t66 = *((unsigned int *)t38);
    t67 = (~(t66));
    t68 = *((unsigned int *)t61);
    t69 = (~(t68));
    t70 = (t63 & t65);
    t71 = (t67 & t69);
    t72 = (~(t70));
    t73 = (~(t71));
    t74 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t74 & t72);
    t75 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t75 & t73);
    t76 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t76 & t72);
    t77 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t77 & t73);
    goto LAB27;

LAB28:    xsi_set_current_line(105, ng0);

LAB31:    xsi_set_current_line(106, ng0);
    t84 = (t0 + 4488);
    t85 = (t84 + 56U);
    t86 = *((char **)t85);
    t87 = ((char*)((ng1)));
    memset(t88, 0, 8);
    xsi_vlog_signed_equal(t88, 32, t86, 32, t87, 32);
    t89 = (t88 + 4);
    t90 = *((unsigned int *)t89);
    t91 = (~(t90));
    t92 = *((unsigned int *)t88);
    t93 = (t92 & t91);
    t94 = (t93 != 0);
    if (t94 > 0)
        goto LAB32;

LAB33:
LAB34:    goto LAB30;

LAB32:    xsi_set_current_line(107, ng0);

LAB35:    xsi_set_current_line(108, ng0);
    t95 = (t0 + 3528);
    t96 = (t95 + 56U);
    t97 = *((char **)t96);
    t98 = ((char*)((ng2)));
    memset(t99, 0, 8);
    xsi_vlog_unsigned_add(t99, 32, t97, 4, t98, 32);
    t100 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t100, t99, 0, 0, 4, 0LL);
    xsi_set_current_line(109, ng0);
    t2 = (t0 + 3528);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    t12 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t11);
    t10 = *((unsigned int *)t12);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t11);
    t25 = *((unsigned int *)t12);
    t26 = (t16 | t25);
    t27 = (~(t26));
    t28 = (t15 & t27);
    if (t28 != 0)
        goto LAB39;

LAB36:    if (t26 != 0)
        goto LAB38;

LAB37:    *((unsigned int *)t13) = 1;

LAB39:    t19 = (t13 + 4);
    t29 = *((unsigned int *)t19);
    t30 = (~(t29));
    t31 = *((unsigned int *)t13);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB40;

LAB41:
LAB42:    goto LAB34;

LAB38:    t18 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t18) = 1;
    goto LAB39;

LAB40:    xsi_set_current_line(110, ng0);

LAB43:    xsi_set_current_line(111, ng0);
    t20 = ((char*)((ng1)));
    t21 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 4, 0LL);
    xsi_set_current_line(112, ng0);
    t2 = (t0 + 3688);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 4, t5, 32);
    t11 = (t0 + 3688);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 4, 0LL);
    xsi_set_current_line(113, ng0);
    t2 = (t0 + 3688);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    t12 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t11);
    t10 = *((unsigned int *)t12);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t11);
    t25 = *((unsigned int *)t12);
    t26 = (t16 | t25);
    t27 = (~(t26));
    t28 = (t15 & t27);
    if (t28 != 0)
        goto LAB47;

LAB44:    if (t26 != 0)
        goto LAB46;

LAB45:    *((unsigned int *)t13) = 1;

LAB47:    t19 = (t13 + 4);
    t29 = *((unsigned int *)t19);
    t30 = (~(t29));
    t31 = *((unsigned int *)t13);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB48;

LAB49:
LAB50:    goto LAB42;

LAB46:    t18 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t18) = 1;
    goto LAB47;

LAB48:    xsi_set_current_line(114, ng0);

LAB51:    xsi_set_current_line(115, ng0);
    t20 = ((char*)((ng1)));
    t21 = (t0 + 3688);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 4, 0LL);
    xsi_set_current_line(116, ng0);
    t2 = (t0 + 3848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 4, t5, 32);
    t11 = (t0 + 3848);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 4, 0LL);
    xsi_set_current_line(117, ng0);
    t2 = (t0 + 3848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    t12 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t11);
    t10 = *((unsigned int *)t12);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t11);
    t25 = *((unsigned int *)t12);
    t26 = (t16 | t25);
    t27 = (~(t26));
    t28 = (t15 & t27);
    if (t28 != 0)
        goto LAB55;

LAB52:    if (t26 != 0)
        goto LAB54;

LAB53:    *((unsigned int *)t13) = 1;

LAB55:    t19 = (t13 + 4);
    t29 = *((unsigned int *)t19);
    t30 = (~(t29));
    t31 = *((unsigned int *)t13);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB56;

LAB57:
LAB58:    goto LAB50;

LAB54:    t18 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t18) = 1;
    goto LAB55;

LAB56:    xsi_set_current_line(118, ng0);

LAB59:    xsi_set_current_line(119, ng0);
    t20 = ((char*)((ng1)));
    t21 = (t0 + 3848);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 4, 0LL);
    xsi_set_current_line(120, ng0);
    t2 = (t0 + 4008);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 32, t4, 4, t5, 32);
    t11 = (t0 + 4008);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 4, 0LL);
    xsi_set_current_line(121, ng0);
    t2 = (t0 + 4008);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    t12 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = *((unsigned int *)t5);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t11);
    t10 = *((unsigned int *)t12);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t11);
    t25 = *((unsigned int *)t12);
    t26 = (t16 | t25);
    t27 = (~(t26));
    t28 = (t15 & t27);
    if (t28 != 0)
        goto LAB63;

LAB60:    if (t26 != 0)
        goto LAB62;

LAB61:    *((unsigned int *)t13) = 1;

LAB63:    t19 = (t13 + 4);
    t29 = *((unsigned int *)t19);
    t30 = (~(t29));
    t31 = *((unsigned int *)t13);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB64;

LAB65:
LAB66:    goto LAB58;

LAB62:    t18 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t18) = 1;
    goto LAB63;

LAB64:    xsi_set_current_line(122, ng0);

LAB67:    xsi_set_current_line(123, ng0);
    t20 = ((char*)((ng1)));
    t21 = (t0 + 4008);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 4, 0LL);
    goto LAB66;

LAB68:    xsi_set_current_line(132, ng0);

LAB71:    xsi_set_current_line(133, ng0);
    t4 = (t0 + 4168);
    t5 = (t4 + 56U);
    t11 = *((char **)t5);
    t12 = ((char*)((ng5)));
    memset(t13, 0, 8);
    xsi_vlog_signed_mod(t13, 32, t11, 32, t12, 32);
    t18 = (t0 + 4328);
    xsi_vlogvar_wait_assign_value(t18, t13, 0, 0, 32, 0LL);
    xsi_set_current_line(134, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);

LAB72:    t5 = ((char*)((ng1)));
    t70 = xsi_vlog_signed_case_compare(t4, 32, t5, 32);
    if (t70 == 1)
        goto LAB73;

LAB74:    t2 = ((char*)((ng2)));
    t70 = xsi_vlog_signed_case_compare(t4, 32, t2, 32);
    if (t70 == 1)
        goto LAB75;

LAB76:    t2 = ((char*)((ng6)));
    t70 = xsi_vlog_signed_case_compare(t4, 32, t2, 32);
    if (t70 == 1)
        goto LAB77;

LAB78:    t2 = ((char*)((ng7)));
    t70 = xsi_vlog_signed_case_compare(t4, 32, t2, 32);
    if (t70 == 1)
        goto LAB79;

LAB80:
LAB82:
LAB81:    xsi_set_current_line(156, ng0);

LAB88:    xsi_set_current_line(157, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 4, 0LL);
    xsi_set_current_line(158, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);

LAB83:    xsi_set_current_line(161, ng0);
    t2 = (t0 + 4168);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t11 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t5, 32, t11, 32);
    t12 = (t0 + 4168);
    xsi_vlogvar_wait_assign_value(t12, t13, 0, 0, 32, 0LL);
    goto LAB70;

LAB73:    xsi_set_current_line(136, ng0);

LAB84:    xsi_set_current_line(137, ng0);
    t11 = (t0 + 4008);
    t12 = (t11 + 56U);
    t18 = *((char **)t12);
    t19 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t19, t18, 0, 0, 4, 0LL);
    xsi_set_current_line(138, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t11 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t11, t5, 0, 0, 2, 0LL);
    goto LAB83;

LAB75:    xsi_set_current_line(141, ng0);

LAB85:    xsi_set_current_line(142, ng0);
    t3 = (t0 + 3848);
    t5 = (t3 + 56U);
    t11 = *((char **)t5);
    t12 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 4, 0LL);
    xsi_set_current_line(143, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t11 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t11, t5, 0, 0, 2, 0LL);
    goto LAB83;

LAB77:    xsi_set_current_line(146, ng0);

LAB86:    xsi_set_current_line(147, ng0);
    t3 = (t0 + 3688);
    t5 = (t3 + 56U);
    t11 = *((char **)t5);
    t12 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 4, 0LL);
    xsi_set_current_line(148, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t11 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t11, t5, 0, 0, 2, 0LL);
    goto LAB83;

LAB79:    xsi_set_current_line(151, ng0);

LAB87:    xsi_set_current_line(152, ng0);
    t3 = (t0 + 3528);
    t5 = (t3 + 56U);
    t11 = *((char **)t5);
    t12 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 4, 0LL);
    xsi_set_current_line(153, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t11 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t11, t5, 0, 0, 2, 0LL);
    goto LAB83;

LAB89:    xsi_set_current_line(164, ng0);

LAB92:    xsi_set_current_line(165, ng0);
    t5 = (t0 + 1368U);
    t11 = *((char **)t5);
    memset(t13, 0, 8);
    t5 = (t11 + 4);
    t14 = *((unsigned int *)t5);
    t15 = (~(t14));
    t16 = *((unsigned int *)t11);
    t25 = (t16 & t15);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB93;

LAB94:    if (*((unsigned int *)t5) != 0)
        goto LAB95;

LAB96:    t18 = (t13 + 4);
    t27 = *((unsigned int *)t13);
    t28 = *((unsigned int *)t18);
    t29 = (t27 || t28);
    if (t29 > 0)
        goto LAB97;

LAB98:    memcpy(t38, t13, 8);

LAB99:    t60 = (t38 + 4);
    t69 = *((unsigned int *)t60);
    t72 = (~(t69));
    t73 = *((unsigned int *)t38);
    t74 = (t73 & t72);
    t75 = (t74 != 0);
    if (t75 > 0)
        goto LAB107;

LAB108:    xsi_set_current_line(168, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t5 = (t3 + 4);
    t11 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t11);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t5);
    t25 = *((unsigned int *)t11);
    t26 = (t16 | t25);
    t27 = (~(t26));
    t28 = (t15 & t27);
    if (t28 != 0)
        goto LAB114;

LAB111:    if (t26 != 0)
        goto LAB113;

LAB112:    *((unsigned int *)t13) = 1;

LAB114:    memset(t17, 0, 8);
    t18 = (t13 + 4);
    t29 = *((unsigned int *)t18);
    t30 = (~(t29));
    t31 = *((unsigned int *)t13);
    t32 = (t31 & t30);
    t33 = (t32 & 1U);
    if (t33 != 0)
        goto LAB115;

LAB116:    if (*((unsigned int *)t18) != 0)
        goto LAB117;

LAB118:    t20 = (t17 + 4);
    t34 = *((unsigned int *)t17);
    t35 = *((unsigned int *)t20);
    t36 = (t34 || t35);
    if (t36 > 0)
        goto LAB119;

LAB120:    memcpy(t46, t17, 8);

LAB121:    t78 = (t46 + 4);
    t79 = *((unsigned int *)t78);
    t80 = (~(t79));
    t81 = *((unsigned int *)t46);
    t82 = (t81 & t80);
    t83 = (t82 != 0);
    if (t83 > 0)
        goto LAB129;

LAB130:
LAB131:
LAB109:    goto LAB91;

LAB93:    *((unsigned int *)t13) = 1;
    goto LAB96;

LAB95:    t12 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB96;

LAB97:    t19 = (t0 + 4488);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    t23 = ((char*)((ng1)));
    memset(t17, 0, 8);
    xsi_vlog_signed_equal(t17, 32, t21, 32, t23, 32);
    memset(t22, 0, 8);
    t24 = (t17 + 4);
    t30 = *((unsigned int *)t24);
    t31 = (~(t30));
    t32 = *((unsigned int *)t17);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB100;

LAB101:    if (*((unsigned int *)t24) != 0)
        goto LAB102;

LAB103:    t35 = *((unsigned int *)t13);
    t36 = *((unsigned int *)t22);
    t40 = (t35 & t36);
    *((unsigned int *)t38) = t40;
    t39 = (t13 + 4);
    t45 = (t22 + 4);
    t50 = (t38 + 4);
    t41 = *((unsigned int *)t39);
    t42 = *((unsigned int *)t45);
    t43 = (t41 | t42);
    *((unsigned int *)t50) = t43;
    t44 = *((unsigned int *)t50);
    t47 = (t44 != 0);
    if (t47 == 1)
        goto LAB104;

LAB105:
LAB106:    goto LAB99;

LAB100:    *((unsigned int *)t22) = 1;
    goto LAB103;

LAB102:    t37 = (t22 + 4);
    *((unsigned int *)t22) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB103;

LAB104:    t48 = *((unsigned int *)t38);
    t49 = *((unsigned int *)t50);
    *((unsigned int *)t38) = (t48 | t49);
    t51 = (t13 + 4);
    t52 = (t22 + 4);
    t53 = *((unsigned int *)t13);
    t54 = (~(t53));
    t55 = *((unsigned int *)t51);
    t56 = (~(t55));
    t57 = *((unsigned int *)t22);
    t58 = (~(t57));
    t59 = *((unsigned int *)t52);
    t62 = (~(t59));
    t70 = (t54 & t56);
    t71 = (t58 & t62);
    t63 = (~(t70));
    t64 = (~(t71));
    t65 = *((unsigned int *)t50);
    *((unsigned int *)t50) = (t65 & t63);
    t66 = *((unsigned int *)t50);
    *((unsigned int *)t50) = (t66 & t64);
    t67 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t67 & t63);
    t68 = *((unsigned int *)t38);
    *((unsigned int *)t38) = (t68 & t64);
    goto LAB106;

LAB107:    xsi_set_current_line(165, ng0);

LAB110:    xsi_set_current_line(166, ng0);
    t61 = ((char*)((ng2)));
    t78 = (t0 + 4488);
    xsi_vlogvar_wait_assign_value(t78, t61, 0, 0, 32, 0LL);
    goto LAB109;

LAB113:    t12 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB114;

LAB115:    *((unsigned int *)t17) = 1;
    goto LAB118;

LAB117:    t19 = (t17 + 4);
    *((unsigned int *)t17) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB118;

LAB119:    t21 = (t0 + 4488);
    t23 = (t21 + 56U);
    t24 = *((char **)t23);
    t37 = ((char*)((ng2)));
    memset(t22, 0, 8);
    xsi_vlog_signed_equal(t22, 32, t24, 32, t37, 32);
    memset(t38, 0, 8);
    t39 = (t22 + 4);
    t40 = *((unsigned int *)t39);
    t41 = (~(t40));
    t42 = *((unsigned int *)t22);
    t43 = (t42 & t41);
    t44 = (t43 & 1U);
    if (t44 != 0)
        goto LAB122;

LAB123:    if (*((unsigned int *)t39) != 0)
        goto LAB124;

LAB125:    t47 = *((unsigned int *)t17);
    t48 = *((unsigned int *)t38);
    t49 = (t47 & t48);
    *((unsigned int *)t46) = t49;
    t50 = (t17 + 4);
    t51 = (t38 + 4);
    t52 = (t46 + 4);
    t53 = *((unsigned int *)t50);
    t54 = *((unsigned int *)t51);
    t55 = (t53 | t54);
    *((unsigned int *)t52) = t55;
    t56 = *((unsigned int *)t52);
    t57 = (t56 != 0);
    if (t57 == 1)
        goto LAB126;

LAB127:
LAB128:    goto LAB121;

LAB122:    *((unsigned int *)t38) = 1;
    goto LAB125;

LAB124:    t45 = (t38 + 4);
    *((unsigned int *)t38) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB125;

LAB126:    t58 = *((unsigned int *)t46);
    t59 = *((unsigned int *)t52);
    *((unsigned int *)t46) = (t58 | t59);
    t60 = (t17 + 4);
    t61 = (t38 + 4);
    t62 = *((unsigned int *)t17);
    t63 = (~(t62));
    t64 = *((unsigned int *)t60);
    t65 = (~(t64));
    t66 = *((unsigned int *)t38);
    t67 = (~(t66));
    t68 = *((unsigned int *)t61);
    t69 = (~(t68));
    t70 = (t63 & t65);
    t71 = (t67 & t69);
    t72 = (~(t70));
    t73 = (~(t71));
    t74 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t74 & t72);
    t75 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t75 & t73);
    t76 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t76 & t72);
    t77 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t77 & t73);
    goto LAB128;

LAB129:    xsi_set_current_line(169, ng0);
    t84 = ((char*)((ng1)));
    t85 = (t0 + 4488);
    xsi_vlogvar_wait_assign_value(t85, t84, 0, 0, 32, 0LL);
    goto LAB131;

}


extern void work_m_00000000003351870002_2908904151_init()
{
	static char *pe[] = {(void *)Initial_47_0,(void *)Always_95_1};
	xsi_register_didat("work_m_00000000003351870002_2908904151", "isim/test_stopwatch_isim_beh.exe.sim/work/m_00000000003351870002_2908904151.didat");
	xsi_register_executes(pe);
}
