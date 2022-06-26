#ifndef __iop_fifo_out_defs_asm_h
#define __iop_fifo_out_defs_asm_h

/*
 * This file is autogenerated from
 *   file:           ../../inst/io_proc/rtl/iop_fifo_out.r
 *     id:           <not found>
 *     last modfied: Mon Apr 11 16:10:09 2005
 *
 *   by /n/asic/design/tools/rdesc/src/rdes2c -asm --outfile asm/iop_fifo_out_defs_asm.h ../../inst/io_proc/rtl/iop_fifo_out.r
 *      id: $Id: //WIFI_SOC/MP/SDK_4_2_0_0/RT288x_SDK/source/linux-2.6.36.x/arch/cris/include/arch-v32/arch/hwregs/iop/asm/iop_fifo_out_defs_asm.h#1 $
 * Any changes here will be lost.
 *
 * -*- buffer-read-only: t -*-
 */

#ifndef REG_FIELD
#define REG_FIELD( scope, reg, field, value ) \
  REG_FIELD_X_( value, reg_##scope##_##reg##___##field##___lsb )
#define REG_FIELD_X_( value, shift ) ((value) << shift)
#endif

#ifndef REG_STATE
#define REG_STATE( scope, reg, field, symbolic_value ) \
  REG_STATE_X_( regk_##scope##_##symbolic_value, reg_##scope##_##reg##___##field##___lsb )
#define REG_STATE_X_( k, shift ) (k << shift)
#endif

#ifndef REG_MASK
#define REG_MASK( scope, reg, field ) \
  REG_MASK_X_( reg_##scope##_##reg##___##field##___width, reg_##scope##_##reg##___##field##___lsb )
#define REG_MASK_X_( width, lsb ) (((1 << width)-1) << lsb)
#endif

#ifndef REG_LSB
#define REG_LSB( scope, reg, field ) reg_##scope##_##reg##___##field##___lsb
#endif

#ifndef REG_BIT
#define REG_BIT( scope, reg, field ) reg_##scope##_##reg##___##field##___bit
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) REG_ADDR_X_(inst, reg_##scope##_##reg##_offset)
#define REG_ADDR_X_( inst, offs ) ((inst) + offs)
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
         REG_ADDR_VECT_X_(inst, reg_##scope##_##reg##_offset, index, \
			 STRIDE_##scope##_##reg )
#define REG_ADDR_VECT_X_( inst, offs, index, stride ) \
                          ((inst) + offs + (index) * stride)
#endif

/* Register rw_cfg, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_cfg___free_lim___lsb 0
#define reg_iop_fifo_out_rw_cfg___free_lim___width 3
#define reg_iop_fifo_out_rw_cfg___byte_order___lsb 3
#define reg_iop_fifo_out_rw_cfg___byte_order___width 2
#define reg_iop_fifo_out_rw_cfg___trig___lsb 5
#define reg_iop_fifo_out_rw_cfg___trig___width 2
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_in___lsb 7
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_in___width 1
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_in___bit 7
#define reg_iop_fifo_out_rw_cfg___mode___lsb 8
#define reg_iop_fifo_out_rw_cfg___mode___width 2
#define reg_iop_fifo_out_rw_cfg___delay_out_last___lsb 10
#define reg_iop_fifo_out_rw_cfg___delay_out_last___width 1
#define reg_iop_fifo_out_rw_cfg___delay_out_last___bit 10
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_out___lsb 11
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_out___width 1
#define reg_iop_fifo_out_rw_cfg___last_dis_dif_out___bit 11
#define reg_iop_fifo_out_rw_cfg_offset 0

/* Register rw_ctrl, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_ctrl___dif_in_en___lsb 0
#define reg_iop_fifo_out_rw_ctrl___dif_in_en___width 1
#define reg_iop_fifo_out_rw_ctrl___dif_in_en___bit 0
#define reg_iop_fifo_out_rw_ctrl___dif_out_en___lsb 1
#define reg_iop_fifo_out_rw_ctrl___dif_out_en___width 1
#define reg_iop_fifo_out_rw_ctrl___dif_out_en___bit 1
#define reg_iop_fifo_out_rw_ctrl_offset 4

/* Register r_stat, scope iop_fifo_out, type r */
#define reg_iop_fifo_out_r_stat___avail_bytes___lsb 0
#define reg_iop_fifo_out_r_stat___avail_bytes___width 4
#define reg_iop_fifo_out_r_stat___last___lsb 4
#define reg_iop_fifo_out_r_stat___last___width 8
#define reg_iop_fifo_out_r_stat___dif_in_en___lsb 12
#define reg_iop_fifo_out_r_stat___dif_in_en___width 1
#define reg_iop_fifo_out_r_stat___dif_in_en___bit 12
#define reg_iop_fifo_out_r_stat___dif_out_en___lsb 13
#define reg_iop_fifo_out_r_stat___dif_out_en___width 1
#define reg_iop_fifo_out_r_stat___dif_out_en___bit 13
#define reg_iop_fifo_out_r_stat___zero_data_last___lsb 14
#define reg_iop_fifo_out_r_stat___zero_data_last___width 1
#define reg_iop_fifo_out_r_stat___zero_data_last___bit 14
#define reg_iop_fifo_out_r_stat_offset 8

/* Register rw_wr1byte, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr1byte___data___lsb 0
#define reg_iop_fifo_out_rw_wr1byte___data___width 8
#define reg_iop_fifo_out_rw_wr1byte_offset 12

/* Register rw_wr2byte, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr2byte___data___lsb 0
#define reg_iop_fifo_out_rw_wr2byte___data___width 16
#define reg_iop_fifo_out_rw_wr2byte_offset 16

/* Register rw_wr3byte, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr3byte___data___lsb 0
#define reg_iop_fifo_out_rw_wr3byte___data___width 24
#define reg_iop_fifo_out_rw_wr3byte_offset 20

/* Register rw_wr4byte, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr4byte___data___lsb 0
#define reg_iop_fifo_out_rw_wr4byte___data___width 32
#define reg_iop_fifo_out_rw_wr4byte_offset 24

/* Register rw_wr1byte_last, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr1byte_last___data___lsb 0
#define reg_iop_fifo_out_rw_wr1byte_last___data___width 8
#define reg_iop_fifo_out_rw_wr1byte_last_offset 28

/* Register rw_wr2byte_last, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr2byte_last___data___lsb 0
#define reg_iop_fifo_out_rw_wr2byte_last___data___width 16
#define reg_iop_fifo_out_rw_wr2byte_last_offset 32

/* Register rw_wr3byte_last, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr3byte_last___data___lsb 0
#define reg_iop_fifo_out_rw_wr3byte_last___data___width 24
#define reg_iop_fifo_out_rw_wr3byte_last_offset 36

/* Register rw_wr4byte_last, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_wr4byte_last___data___lsb 0
#define reg_iop_fifo_out_rw_wr4byte_last___data___width 32
#define reg_iop_fifo_out_rw_wr4byte_last_offset 40

/* Register rw_set_last, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_set_last_offset 44

/* Register rs_rd_data, scope iop_fifo_out, type rs */
#define reg_iop_fifo_out_rs_rd_data_offset 48

/* Register r_rd_data, scope iop_fifo_out, type r */
#define reg_iop_fifo_out_r_rd_data_offset 52

/* Register rw_strb_dif_out, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_strb_dif_out_offset 56

/* Register rw_intr_mask, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_intr_mask___urun___lsb 0
#define reg_iop_fifo_out_rw_intr_mask___urun___width 1
#define reg_iop_fifo_out_rw_intr_mask___urun___bit 0
#define reg_iop_fifo_out_rw_intr_mask___last_data___lsb 1
#define reg_iop_fifo_out_rw_intr_mask___last_data___width 1
#define reg_iop_fifo_out_rw_intr_mask___last_data___bit 1
#define reg_iop_fifo_out_rw_intr_mask___dav___lsb 2
#define reg_iop_fifo_out_rw_intr_mask___dav___width 1
#define reg_iop_fifo_out_rw_intr_mask___dav___bit 2
#define reg_iop_fifo_out_rw_intr_mask___free___lsb 3
#define reg_iop_fifo_out_rw_intr_mask___free___width 1
#define reg_iop_fifo_out_rw_intr_mask___free___bit 3
#define reg_iop_fifo_out_rw_intr_mask___orun___lsb 4
#define reg_iop_fifo_out_rw_intr_mask___orun___width 1
#define reg_iop_fifo_out_rw_intr_mask___orun___bit 4
#define reg_iop_fifo_out_rw_intr_mask_offset 60

/* Register rw_ack_intr, scope iop_fifo_out, type rw */
#define reg_iop_fifo_out_rw_ack_intr___urun___lsb 0
#define reg_iop_fifo_out_rw_ack_intr___urun___width 1
#define reg_iop_fifo_out_rw_ack_intr___urun___bit 0
#define reg_iop_fifo_out_rw_ack_intr___last_data___lsb 1
#define reg_iop_fifo_out_rw_ack_intr___last_data___width 1
#define reg_iop_fifo_out_rw_ack_intr___last_data___bit 1
#define reg_iop_fifo_out_rw_ack_intr___dav___lsb 2
#define reg_iop_fifo_out_rw_ack_intr___dav___width 1
#define reg_iop_fifo_out_rw_ack_intr___dav___bit 2
#define reg_iop_fifo_out_rw_ack_intr___free___lsb 3
#define reg_iop_fifo_out_rw_ack_intr___free___width 1
#define reg_iop_fifo_out_rw_ack_intr___free___bit 3
#define reg_iop_fifo_out_rw_ack_intr___orun___lsb 4
#define reg_iop_fifo_out_rw_ack_intr___orun___width 1
#define reg_iop_fifo_out_rw_ack_intr___orun___bit 4
#define reg_iop_fifo_out_rw_ack_intr_offset 64

/* Register r_intr, scope iop_fifo_out, type r */
#define reg_iop_fifo_out_r_intr___urun___lsb 0
#define reg_iop_fifo_out_r_intr___urun___width 1
#define reg_iop_fifo_out_r_intr___urun___bit 0
#define reg_iop_fifo_out_r_intr___last_data___lsb 1
#define reg_iop_fifo_out_r_intr___last_data___width 1
#define reg_iop_fifo_out_r_intr___last_data___bit 1
#define reg_iop_fifo_out_r_intr___dav___lsb 2
#define reg_iop_fifo_out_r_intr___dav___width 1
#define reg_iop_fifo_out_r_intr___dav___bit 2
#define reg_iop_fifo_out_r_intr___free___lsb 3
#define reg_iop_fifo_out_r_intr___free___width 1
#define reg_iop_fifo_out_r_intr___free___bit 3
#define reg_iop_fifo_out_r_intr___orun___lsb 4
#define reg_iop_fifo_out_r_intr___orun___width 1
#define reg_iop_fifo_out_r_intr___orun___bit 4
#define reg_iop_fifo_out_r_intr_offset 68

/* Register r_masked_intr, scope iop_fifo_out, type r */
#define reg_iop_fifo_out_r_masked_intr___urun___lsb 0
#define reg_iop_fifo_out_r_masked_intr___urun___width 1
#define reg_iop_fifo_out_r_masked_intr___urun___bit 0
#define reg_iop_fifo_out_r_masked_intr___last_data___lsb 1
#define reg_iop_fifo_out_r_masked_intr___last_data___width 1
#define reg_iop_fifo_out_r_masked_intr___last_data___bit 1
#define reg_iop_fifo_out_r_masked_intr___dav___lsb 2
#define reg_iop_fifo_out_r_masked_intr___dav___width 1
#define reg_iop_fifo_out_r_masked_intr___dav___bit 2
#define reg_iop_fifo_out_r_masked_intr___free___lsb 3
#define reg_iop_fifo_out_r_masked_intr___free___width 1
#define reg_iop_fifo_out_r_masked_intr___free___bit 3
#define reg_iop_fifo_out_r_masked_intr___orun___lsb 4
#define reg_iop_fifo_out_r_masked_intr___orun___width 1
#define reg_iop_fifo_out_r_masked_intr___orun___bit 4
#define reg_iop_fifo_out_r_masked_intr_offset 72


/* Constants */
#define regk_iop_fifo_out_hi                      0x00000000
#define regk_iop_fifo_out_neg                     0x00000002
#define regk_iop_fifo_out_no                      0x00000000
#define regk_iop_fifo_out_order16                 0x00000001
#define regk_iop_fifo_out_order24                 0x00000002
#define regk_iop_fifo_out_order32                 0x00000003
#define regk_iop_fifo_out_order8                  0x00000000
#define regk_iop_fifo_out_pos                     0x00000001
#define regk_iop_fifo_out_pos_neg                 0x00000003
#define regk_iop_fifo_out_rw_cfg_default          0x00000024
#define regk_iop_fifo_out_rw_ctrl_default         0x00000000
#define regk_iop_fifo_out_rw_intr_mask_default    0x00000000
#define regk_iop_fifo_out_rw_set_last_default     0x00000000
#define regk_iop_fifo_out_rw_strb_dif_out_default  0x00000000
#define regk_iop_fifo_out_rw_wr1byte_default      0x00000000
#define regk_iop_fifo_out_rw_wr1byte_last_default  0x00000000
#define regk_iop_fifo_out_rw_wr2byte_default      0x00000000
#define regk_iop_fifo_out_rw_wr2byte_last_default  0x00000000
#define regk_iop_fifo_out_rw_wr3byte_default      0x00000000
#define regk_iop_fifo_out_rw_wr3byte_last_default  0x00000000
#define regk_iop_fifo_out_rw_wr4byte_default      0x00000000
#define regk_iop_fifo_out_rw_wr4byte_last_default  0x00000000
#define regk_iop_fifo_out_size16                  0x00000002
#define regk_iop_fifo_out_size24                  0x00000001
#define regk_iop_fifo_out_size32                  0x00000000
#define regk_iop_fifo_out_size8                   0x00000003
#define regk_iop_fifo_out_yes                     0x00000001
#endif /* __iop_fifo_out_defs_asm_h */
