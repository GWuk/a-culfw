/* 
 * Copyright by B.Hempel
 * License: GPL v2
 */

#ifndef _RF_RECEIVE_OREGON3_H
#define _RF_RECEIVE_OREGON3_H

#include <stdio.h>
#include "board.h"
#include "rf_receive_bucket.h"
#include "fband.h"

#ifdef HAS_OREGON3
#define STATE_OREGON3 10
#define TYPE_OREGON3  'o'

/*
 * Analyse Oregon 3 packet.
 * Parameter:
 *  b        = the received bucket
 *  datatype = the datatype
 *  obuf     = the object buffer
 *  oby      = the oby count
 * The datatype are set to TYPE_IT, if packet is correct.
 */
void analyze_oregon3(bucket_t *b, uint8_t *datatype, uint8_t *obuf, uint8_t *oby);

/*
 * Sync the IT received packet
 * return 1 if rf_receive routine must be restarted
 * return 0 if routine must not be restarted or it is no it
 */
//uint8_t sync_intertechno(bucket_t *b, pulse_t *hightime, pulse_t *lowtime);

/*
 * Check if received packat is a Intertechno packet
 * hightime the received hightime
 * lowtime the received lowtime
 * return 1 (true) if packet ist OK
 * return 0 (false) if packet is not Intertechno 
 */
//uint8_t is_intertechno(bucket_t *b, pulse_t *hightime, pulse_t *lowtime);

/*
 * Add the the bit to the bucket if it is a Intertechno bit.
 * hightime the received hightime
 * lowtime the received lowtime
 */
//void addbit_intertechno_v3(bucket_t *b, pulse_t *hightime, pulse_t *lowtime);

#endif
#endif
