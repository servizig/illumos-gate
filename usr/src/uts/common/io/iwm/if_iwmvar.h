/*	$NetBSD: if_iwmvar.h,v 1.20 2020/05/22 20:27:16 thorpej Exp $	*/
/*	OpenBSD: if_iwmvar.h,v 1.24 2016/09/21 13:53:18 stsp Exp 	*/

/*
 * Copyright (c) 2014 genua mbh <info@genua.de>
 * Copyright (c) 2014 Fixup Software Ltd.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*-
 * Based on BSD-licensed source modules in the Linux iwlwifi driver,
 * which were used as the reference documentation for this implementation.
 *
 * Driver version we are currently based off of is
 * Linux 3.14.3 (tag id a2df521e42b1d9a23f620ac79dbfe8655a8391dd)
 *
 ***********************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may do so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2007 - 2013 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called COPYING.
 *
 * Contact Information:
 *  Intel Linux Wireless <ilw@linux.intel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *
 * BSD LICENSE
 *
 * Copyright(c) 2005 - 2013 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * Copyright (c) 2007-2010 Damien Bergamini <damien.bergamini@free.fr>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _IF_IWMVAR_H
#define	_IF_IWMVAR_H

#include <sys/net80211.h>
#include <sys/queue.h>

#define IWM_UCODE_SECT_MAX 16
#define IWM_FWDMASEGSZ (192*1024)
#define IWM_FWDMASEGSZ_8000 (320*1024)

/*
 * fw_status is used to determine if we've already parsed the firmware file
 *
 * In addition to the following, status < 0 ==> -error
 */
#define IWM_FW_STATUS_NONE		0
#define IWM_FW_STATUS_INPROGRESS	1
#define IWM_FW_STATUS_DONE		2

enum iwm_ucode_type {
	IWM_UCODE_TYPE_REGULAR,
	IWM_UCODE_TYPE_INIT,
	IWM_UCODE_TYPE_WOW,
	IWM_UCODE_TYPE_REGULAR_USNIFFER,
	IWM_UCODE_TYPE_MAX
};

struct iwm_fw_info {
	void *fw_rawdata;
	size_t fw_rawsize;
	int fw_status;

	struct iwm_fw_sects {
		struct iwm_fw_onesect {
			void *fws_data;
			uint32_t fws_len;
			uint32_t fws_devoff;

			void *fws_alloc;
			size_t fws_allocsize;
		} fw_sect[IWM_UCODE_SECT_MAX];
		size_t fw_totlen;
		int fw_count;
		int is_dual_cpus;
		uint32_t paging_mem_size;
	} fw_sects[IWM_UCODE_TYPE_MAX];
};

struct iwm_nvm_data {
	int n_hw_addrs;
	uint8_t hw_addr[ETHER_ADDR_LEN];

	uint8_t calib_version;
	uint16_t calib_voltage;

	uint16_t raw_temperature;
	uint16_t kelvin_temperature;
	uint16_t kelvin_voltage;
	uint16_t xtal_calib[2];

	int sku_cap_band_24GHz_enable;
	int sku_cap_band_52GHz_enable;
	int sku_cap_11n_enable;
	int sku_cap_amt_enable;
	int sku_cap_ipan_enable;
	int sku_cap_mimo_disable;

	uint8_t radio_cfg_type;
	uint8_t radio_cfg_step;
	uint8_t radio_cfg_dash;
	uint8_t radio_cfg_pnum;
	uint8_t valid_tx_ant, valid_rx_ant;

	uint16_t nvm_version;
	uint8_t max_tx_pwr_half_dbm;

	boolean_t lar_enabled;
};

/* max bufs per tfd the driver will use */
#define IWM_MAX_CMD_TBS_PER_TFD 2

struct iwm_rx_packet;
struct iwm_host_cmd {
	const void *data[IWM_MAX_CMD_TBS_PER_TFD];
	struct iwm_rx_packet *resp_pkt;
	unsigned long _rx_page_addr;
	uint32_t _rx_page_order;
	int handler_status;

	uint32_t flags;
	uint16_t len[IWM_MAX_CMD_TBS_PER_TFD];
	uint8_t dataflags[IWM_MAX_CMD_TBS_PER_TFD];
	uint32_t id;
};

/*
 * DMA glue is from iwm
 */

struct iwm_dma_info {
	ddi_dma_handle_t	dma_hdl;
	ddi_acc_handle_t	acc_hdl;
	ddi_dma_cookie_t	cookie;
	uint_t			ncookies;
	uintptr_t		paddr;
	caddr_t			vaddr;
	size_t			size;
	size_t			length;
};

/**
 * struct iwm_fw_paging
 * @fw_paging_block: dma memory info
 * @fw_paging_size: page size
 */
struct iwm_fw_paging {
	struct iwm_dma_info fw_paging_block;
	uint32_t fw_paging_size;
};

#define IWM_TX_RING_COUNT	256
#define IWM_TX_RING_LOMARK	192
#define IWM_TX_RING_HIMARK	224

struct iwm_tx_data {
	struct iwm_dma_info	dma_data;
	uintptr_t		cmd_paddr;
	uintptr_t		scratch_paddr;
	struct iwm_dma_info	cmd_dma;
	struct iwm_node		*in;
	int done;
};

struct iwm_tx_ring {
	struct iwm_dma_info	desc_dma;
	struct iwm_dma_info	cmd_dma;
	struct iwm_tfd		*desc;
	struct iwm_device_cmd	*cmd;
	struct iwm_tx_data	data[IWM_TX_RING_COUNT];
	int			qid;
	int			queued;
	int			cur;
};

#define IWM_RX_RING_COUNT	256
#define IWM_RBUF_COUNT		(IWM_RX_RING_COUNT + 32)
/* Linux driver optionally uses 8k buffer */
#define IWM_RBUF_SIZE		4096

struct iwm_rx_data {
	struct iwm_dma_info	dma_data;
};

struct iwm_rx_ring {
	struct iwm_dma_info	desc_dma;
	struct iwm_dma_info	stat_dma;
	uint32_t		*desc;
	struct iwm_rb_status	*stat;
	struct iwm_rx_data	data[IWM_RX_RING_COUNT];
	int			cur;
};

#define IWM_FLAG_USE_ICT	__BIT(0)
#define IWM_FLAG_HW_INITED	__BIT(1)
#define IWM_FLAG_STOPPED	__BIT(2)
#define IWM_FLAG_RFKILL		__BIT(3)
#define IWM_FLAG_SCANNING	__BIT(4)
#define IWM_FLAG_ATTACHED	__BIT(5)
#define IWM_FLAG_FW_LOADED	__BIT(6)
/* From iwp.c */
#define	IWM_FLAG_CMD_DONE	(1 << 12)
#define	IWM_FLAG_FW_ALIVE	(1 << 13)
#define	IWM_FLAG_HW_ERR_RECOVER	(1 << 14)
#define	IWM_FLAG_RATE_AUTO_CTL	(1 << 15)
#define	IWM_FLAG_RUNNING	(1 << 16)
#define	IWM_FLAG_SUSPEND	(1 << 17)
#define	IWM_FLAG_RADIO_OFF	(1 << 18)
#define	IWM_FLAG_STATISTICS	(1 << 19)
#define	IWM_FLAG_READY		(1 << 20)
#define	IWM_FLAG_PUT_SEG	(1 << 21)
#define	IWM_FLAG_QUIESCED	(1 << 22)
#define	IWM_FLAG_LAZY_RESUME	(1 << 23)
#define	IWM_FLAG_STOP_CALIB_TO	(1 << 24)

struct iwm_ucode_status {
	uint32_t uc_error_event_table;
	uint32_t uc_umac_error_event_table;
	uint32_t uc_log_event_table;

	int uc_ok;
	int uc_intr;
};

/* sc_wantresp */
#define IWM_CMD_RESP_IDLE	-1

#define IWM_CMD_RESP_MAX 0x1000 /* NetBSD: PAGE_SIZE */

/* lower blocks contain EEPROM image and calibration data */
#define IWM_OTP_LOW_IMAGE_SIZE_FAMILY_7000 	16384
#define IWM_OTP_LOW_IMAGE_SIZE_FAMILY_8000	32768

#define IWM_TE_SESSION_PROTECTION_MAX_TIME_MS 1000
#define IWM_TE_SESSION_PROTECTION_MIN_TIME_MS 400

enum IWM_CMD_MODE {
	IWM_CMD_ASYNC		= (1 << 0),
	IWM_CMD_WANT_SKB	= (1 << 1),
	IWM_CMD_SEND_IN_RFKILL	= (1 << 2),
};
enum iwm_hcmd_dataflag {
	IWM_HCMD_DFL_NOCOPY     = (1 << 0),
	IWM_HCMD_DFL_DUP        = (1 << 1),
};

#define IWM_NUM_PAPD_CH_GROUPS	9
#define IWM_NUM_TXP_CH_GROUPS	9

struct iwm_phy_db_entry {
	uint16_t size;
	uint8_t *data;
};

struct iwm_phy_db {
	struct iwm_phy_db_entry	cfg;
	struct iwm_phy_db_entry	calib_nch;
	struct iwm_phy_db_entry	calib_ch_group_papd[IWM_NUM_PAPD_CH_GROUPS];
	struct iwm_phy_db_entry	calib_ch_group_txp[IWM_NUM_TXP_CH_GROUPS];
};

struct iwm_phy_ctxt {
	uint16_t id;
	uint16_t color;
	uint32_t ref;
	struct ieee80211_channel *channel;
};

struct iwm_bf_data {
	int bf_enabled;		/* filtering	*/
	int ba_enabled;		/* abort	*/
	int ave_beacon_signal;
	int last_cqm_event;
};

struct iwm_softc {
	struct ieee80211com sc_ic;
	dev_info_t *sc_dip;

	int (*sc_newstate)(struct ieee80211com *, enum ieee80211_state, int);

	enum ieee80211_state sc_ostate;

	clock_t sc_clk;
	struct ieee80211_amrr sc_amrr;

	ddi_periodic_t		sc_periodic;
	timeout_id_t sc_calib_to;
	timeout_id_t sc_led_blink_to;

	uint16_t sc_devid;
	caddr_t sc_base;

	ddi_acc_handle_t sc_regh;
	void *sc_ih;
	ddi_acc_handle_t sc_pcih;
	uint_t sc_intr_pri;
	int sc_intr_cap;
	int sc_intr_count;
	size_t sc_intr_size;
	ddi_intr_handle_t *sc_intr_htable;

	void *sc_soft_ih;

	/* TX scheduler rings. */
	struct iwm_dma_info		sched_dma;
	uint16_t			*sched;
	uint32_t			sched_base;

	/* TX/RX rings. */
	struct iwm_tx_ring txq[IWM_MAX_QUEUES];
	struct iwm_rx_ring rxq;
	int qfullmsk;

	int sc_sf_state;

	/* ICT table. */
	struct iwm_dma_info	ict_dma;
	uint32_t		*ict;
	int			ict_cur;

	int sc_hw_rev;
#define IWM_SILICON_A_STEP	0
#define IWM_SILICON_B_STEP	1
#define IWM_SILICON_C_STEP	2
#define IWM_SILICON_D_STEP	3
	int sc_hw_id;
	int sc_device_family;
#define IWM_DEVICE_FAMILY_7000	1
#define IWM_DEVICE_FAMILY_8000	2

	struct iwm_dma_info kw_dma;
	struct iwm_dma_info fw_dma;

	int sc_fw_chunk_done;
	int sc_init_complete;

	struct iwm_ucode_status sc_uc;
	enum iwm_ucode_type sc_uc_current;
	char sc_fwver[32];

	int sc_capaflags;
	int sc_capa_max_probe_len;
	int sc_capa_n_scan_channels;
	uint8_t sc_ucode_api[howmany(IWM_NUM_UCODE_TLV_API, NBBY)];
	uint8_t sc_enabled_capa[howmany(IWM_NUM_UCODE_TLV_CAPA, NBBY)];
	char sc_fw_mcc[3];

	int sc_intmask;
	int sc_flags;

	/*
	 * So why do we need a separate stopped flag and a generation?
	 * the former protects the device from issueing commands when it's
	 * stopped (duh).  The latter protects against race from a very
	 * fast stop/unstop cycle where threads waiting for responses do
	 * not have a chance to run in between.  Notably: we want to stop
	 * the device from interrupt context when it craps out, so we
	 * don't have the luxury of waiting for quiescense.
	 */
	int sc_generation;

	int sc_cap_off; /* PCIe caps */

	const char *sc_fwname;
	size_t sc_fwdmasegsz;
	struct iwm_fw_info sc_fw;
	int sc_fw_phy_config;
	struct iwm_tlv_calib_ctrl sc_default_calib[IWM_UCODE_TYPE_MAX];

	struct iwm_nvm_data sc_nvm;
	struct iwm_phy_db sc_phy_db;

	struct iwm_bf_data sc_bf;

	int sc_tx_timer;
	int sc_rx_ba_sessions;

	int sc_scan_last_antenna;
	int sc_mgmt_last_antenna;

	int sc_fixed_ridx;

	int sc_staid;
	int sc_nodecolor;

	uint8_t sc_cmd_resp[IWM_CMD_RESP_MAX];
	int sc_wantresp;

	ddi_taskq_t *sc_nstq;

	struct iwm_rx_phy_info sc_last_phy_info;
	int sc_ampdu_ref;

	/* phy contexts.  we only use the first one */
	struct iwm_phy_ctxt sc_phyctxt[IWM_NUM_PHY_CTX];

	struct iwm_notif_statistics sc_stats;
	int sc_noise;

	int sc_cmd_hold_nic_awake;

	/* device needs host interrupt operation mode set */
	int host_interrupt_operation_mode;
	/* should the MAC access REQ be asserted when a command is in flight.
	 * This is due to a HW bug in 7260, 3160 and 7265. */
	int apmg_wake_up_wa;

	/*
	 * Paging parameters - All of the parameters should be set by the
	 * opmode when paging is enabled
	 */
	struct iwm_fw_paging fw_paging_db[IWM_NUM_OF_FW_PAGING_BLOCKS];
	uint16_t num_of_paging_blk;
	uint16_t num_of_pages_in_last_blk;

	struct sysctllog *sc_clog;

	kmutex_t sc_mtx;		/* mutex for init/stop */
	kmutex_t sc_tx_mtx;
	kmutex_t sc_mt_mtx;

	kmutex_t	sc_media_mtx;	/* XXX */

	kcondvar_t		sc_wantresp_cv;
	kcondvar_t		sc_init_complete_cv;
	kcondvar_t		sc_fw_cv;
	kcondvar_t		sc_cmd_cv;
	kcondvar_t		sc_scan_cv;
	kcondvar_t		sc_fhdma_cv;
	kcondvar_t		sc_alive_cv;
	kcondvar_t		sc_calib_cv;
	kcondvar_t		sc_mt_cv;

	volatile uint32_t	sc_cmd_flag;
	volatile uint32_t	sc_cmd_accum;
#define	SC_CMD_FLG_NONE		(0)
#define	SC_CMD_FLG_PENDING	(1)
#define	SC_CMD_FLG_DONE		(2)

	/* kstats */
	uint32_t		sc_tx_nobuf;
	uint32_t		sc_rx_nobuf;
	uint32_t		sc_tx_err;
	uint32_t		sc_rx_err;
	uint32_t		sc_tx_retries;

	kstat_t			*sc_ks_misc;
	struct iwm_ks_misc	*sc_misc;
	kstat_t			*sc_ks_ant;
	struct iwm_ks_ant	*sc_ant;
	kstat_t			*sc_ks_sens;
	struct iwm_ks_sens	*sc_sens;
	kstat_t			*sc_ks_timing;
	struct iwm_ks_timing	*sc_timing;
	kstat_t			*sc_ks_edca;
	struct iwm_ks_edca	*sc_edca;
	kstat_t			*sc_ks_txpower;
	struct iwm_ks_txpower	*sc_txpower;
	kstat_t			*sc_ks_toff;
};

struct iwm_ks_misc {
	kstat_named_t		temp;
	kstat_named_t		crit_temp;
	kstat_named_t		pslevel;
	kstat_named_t		noise;
};

struct iwm_ks_ant {
	kstat_named_t		tx_ant;
	kstat_named_t		rx_ant;
	kstat_named_t		conn_ant;
	kstat_named_t		gain[3];
};

struct iwm_ks_sens {
	kstat_named_t		ofdm_x1;
	kstat_named_t		ofdm_mrc_x1;
	kstat_named_t		ofdm_x4;
	kstat_named_t		ofdm_mrc_x4;
	kstat_named_t		cck_x4;
	kstat_named_t		cck_mrc_x4;
	kstat_named_t		energy_cck;
};

struct iwm_ks_timing {
	kstat_named_t		bintval;
	kstat_named_t		tstamp;
	kstat_named_t		init;
};

struct iwm_ks_edca {
	struct {
		kstat_named_t		cwmin;
		kstat_named_t		cwmax;
		kstat_named_t		aifsn;
		kstat_named_t		txop;
	} ac[4];
};

struct iwm_ks_txpower {
	kstat_named_t		vdiff;
	kstat_named_t		chan;
	kstat_named_t		group;
	kstat_named_t		subband;
	struct {
		kstat_named_t	power;
		kstat_named_t	gain;
		kstat_named_t	temp;
		kstat_named_t	tcomp;
	} txchain[2];
};

struct iwm_node {
	struct ieee80211_node in_ni;
	struct iwm_phy_ctxt *in_phyctxt;

	uint16_t in_id;
	uint16_t in_color;

	struct iwm_lq_cmd in_lq;
	struct ieee80211_amrr_node in_amn;
};
#define IWM_STATION_ID 0
#define IWM_AUX_STA_ID 1

#define IWM_ICT_SIZE		4096
#define IWM_ICT_COUNT		(IWM_ICT_SIZE / sizeof (uint32_t))
#define IWM_ICT_PADDR_SHIFT	12


#define	IWM_CHK_FAST_RECOVER(sc) \
	(sc->sc_ic.ic_state == IEEE80211_S_RUN && \
	sc->sc_ic.ic_opmode == IEEE80211_M_STA)

#endif	/* _IF_IWMVAR_H */
