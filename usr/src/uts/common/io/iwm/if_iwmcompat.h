#ifndef _IF_IWMCOMPAT_H
#define	_IF_IWMCOMPAT_H

#define IEEE80211_NO_HT

/*
 * QoS  definitions
 */

#define	AC_NUM		(4)	/* the number of access category */

/*
 * index of every AC in firmware
 */
#define	QOS_AC_BK	(0)
#define	QOS_AC_BE	(1)
#define	QOS_AC_VI	(2)
#define	QOS_AC_VO	(3)
#define	QOS_AC_INVALID	(-1)

#define	QOS_CW_RANGE_MIN	(0)	/* exponential of 2 */
#define	QOS_CW_RANGE_MAX	(15)	/* exponential of 2 */
#define	QOS_TXOP_MIN		(0)	/* unit of 32 microsecond */
#define	QOS_TXOP_MAX		(255)	/* unit of 32 microsecond */
#define	QOS_AIFSN_MIN		(2)
#define	QOS_AIFSN_MAX		(15)	/* undefined */

/*
 * masks for flags of QoS parameter command
 */
#define	QOS_PARAM_FLG_UPDATE_EDCA	(0x01)
#define	QOS_PARAM_FLG_TGN		(0x02)

/*
 * index of TX queue for every AC
 */
#define	QOS_AC_BK_TO_TXQ	(3)
#define	QOS_AC_BE_TO_TXQ	(2)
#define	QOS_AC_VI_TO_TXQ	(1)
#define	QOS_AC_VO_TO_TXQ	(0)
#define	TXQ_FOR_AC_MIN		(0)
#define	TXQ_FOR_AC_MAX		(3)
#define	TXQ_FOR_AC_INVALID	(-1)
#define	NON_QOS_TXQ		QOS_AC_BE_TO_TXQ
#define	QOS_TXQ_FOR_MGT		QOS_AC_VO_TO_TXQ

#define	WME_TID_MIN	(0)
#define	WME_TID_MAX	(7)
#define	WME_TID_INVALID	((uint8_t)-1)

/*
 * One Time Unit (TU) is 1Kus = 1024 microseconds.
 */
#define	IEEE80211_DUR_TU		1024

#define	PCI_VENDOR_INTEL	0x8086		/* Intel */

#define	PCI_PRODUCT_INTEL_WIFI_LINK_7260_1	0x08b1		/* Dual Band Wireless AC 7260 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_7260_2	0x08b2		/* Dual Band Wireless AC 7260 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_3160_1	0x08b3		/* Dual Band Wireless AC 3160 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_3160_2	0x08b4		/* Dual Band Wireless AC 3160 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_7265_1	0x095a		/* Dual Band Wireless AC 7265 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_7265_2	0x095b		/* Dual Band Wireless AC 7265 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_8260_1	0x24f3		/* Dual Band Wireless AC 8260 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_8260_2	0x24f4		/* Dual Band Wireless AC 8260 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_4165_1	0x24f5		/* Dual Band Wireless AC 4165 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_4165_2	0x24f6		/* Dual Band Wireless AC 4165 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_3168	0x24fb		/* Dual Band Wireless AC 3168 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_8265	0x24fd		/* Dual Band Wireless AC 8265 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_3165_1	0x3165		/* Dual Band Wireless AC 3165 */
#define	PCI_PRODUCT_INTEL_WIFI_LINK_3165_2	0x3166		/* Dual Band Wireless AC 3165 */

#define	__BIT(n)	(1 << (n))
#define ETHER_ADDR_LEN 6

#define	__inline	inline
#define	__arraycount(x)	ARRAY_SIZE(x)
#define	abs(x)		ABS(x)

#define	le16toh(x) LE_16(x)
#define	htole16(x) LE_16(x)
#define	le32toh(x) LE_32(x)
#define	htole32(x) LE_32(x)
#define	le64toh(x) LE_64(x)
#define	htole64(x) LE_64(x)

#define	IWM_SUCCESS		0
#define	IWM_FAIL		EIO

#endif /* _IF_IWNCOMPAT_H */
