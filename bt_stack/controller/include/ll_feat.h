/*
 * Copyright (c) 2016-2020 Nordic Semiconductor ASA
 * Copyright (c) 2016 Vinayak Kariappa Chettimada
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_BT_CTLR_LE_ENC)
#define LL_FEAT_BIT_ENC BIT64(BT_LE_FEAT_BIT_ENC)
#else /* !CONFIG_BT_CTLR_LE_ENC */
#define LL_FEAT_BIT_ENC 0
#endif /* !CONFIG_BT_CTLR_LE_ENC */

#if defined(CONFIG_BT_CTLR_CONN_PARAM_REQ)
#define LL_FEAT_BIT_CONN_PARAM_REQ BIT64(BT_LE_FEAT_BIT_CONN_PARAM_REQ)
#else /* !CONFIG_BT_CTLR_CONN_PARAM_REQ */
#define LL_FEAT_BIT_CONN_PARAM_REQ 0
#endif /* !CONFIG_BT_CTLR_CONN_PARAM_REQ */

#if defined(CONFIG_BT_CTLR_EXT_REJ_IND)
#define LL_FEAT_BIT_EXT_REJ_IND BIT64(BT_LE_FEAT_BIT_EXT_REJ_IND)
#else /* !CONFIG_BT_CTLR_EXT_REJ_IND */
#define LL_FEAT_BIT_EXT_REJ_IND 0
#endif /* !CONFIG_BT_CTLR_EXT_REJ_IND */

#if defined(CONFIG_BT_CTLR_SLAVE_FEAT_REQ)
#define LL_FEAT_BIT_SLAVE_FEAT_REQ BIT64(BT_LE_FEAT_BIT_SLAVE_FEAT_REQ)
#else /* !CONFIG_BT_CTLR_SLAVE_FEAT_REQ */
#define LL_FEAT_BIT_SLAVE_FEAT_REQ 0
#endif /* !CONFIG_BT_CTLR_SLAVE_FEAT_REQ */

#if defined(CONFIG_BT_CTLR_LE_PING)
#define LL_FEAT_BIT_PING BIT64(BT_LE_FEAT_BIT_PING)
#else /* !CONFIG_BT_CTLR_LE_PING */
#define LL_FEAT_BIT_PING 0
#endif /* !CONFIG_BT_CTLR_LE_PING */

#if defined(CONFIG_BT_CTLR_DATA_LENGTH_MAX)
#define LL_FEAT_BIT_DLE         BIT64(BT_LE_FEAT_BIT_DLE)
#define LL_LENGTH_OCTETS_RX_MAX CONFIG_BT_CTLR_DATA_LENGTH_MAX
#else
#define LL_FEAT_BIT_DLE         0
#define LL_LENGTH_OCTETS_RX_MAX 27
#endif /* CONFIG_BT_CTLR_DATA_LENGTH_MAX */

#if defined(CONFIG_BT_CTLR_PRIVACY)
#define LL_FEAT_BIT_PRIVACY BIT64(BT_LE_FEAT_BIT_PRIVACY)
#else /* !CONFIG_BT_CTLR_PRIVACY */
#define LL_FEAT_BIT_PRIVACY 0
#endif /* !CONFIG_BT_CTLR_PRIVACY */

#if defined(CONFIG_BT_CTLR_EXT_SCAN_FP)
#define LL_FEAT_BIT_EXT_SCAN BIT64(BT_LE_FEAT_BIT_EXT_SCAN)
#else /* !CONFIG_BT_CTLR_EXT_SCAN_FP */
#define LL_FEAT_BIT_EXT_SCAN 0
#endif /* !CONFIG_BT_CTLR_EXT_SCAN_FP */

#if defined(CONFIG_BT_CTLR_CHAN_SEL_2)
#define LL_FEAT_BIT_CHAN_SEL_2 BIT64(BT_LE_FEAT_BIT_CHAN_SEL_ALGO_2)
#else /* !CONFIG_BT_CTLR_CHAN_SEL_2 */
#define LL_FEAT_BIT_CHAN_SEL_2 0
#endif /* !CONFIG_BT_CTLR_CHAN_SEL_2 */

#if defined(CONFIG_BT_CTLR_MIN_USED_CHAN)
#define LL_FEAT_BIT_MIN_USED_CHAN \
    BIT64(BT_LE_FEAT_BIT_MIN_USED_CHAN_PROC)
#else /* !CONFIG_BT_CTLR_MIN_USED_CHAN */
#define LL_FEAT_BIT_MIN_USED_CHAN 0
#endif /* !CONFIG_BT_CTLR_MIN_USED_CHAN */

#if defined(CONFIG_BT_CTLR_PHY_2M)
#define LL_FEAT_BIT_PHY_2M BIT64(BT_LE_FEAT_BIT_PHY_2M)
#else /* !CONFIG_BT_CTLR_PHY_2M */
#define LL_FEAT_BIT_PHY_2M 0
#endif /* !CONFIG_BT_CTLR_PHY_2M */

#if defined(CONFIG_BT_CTLR_SMI_TX)
#if defined(CONFIG_BT_CTLR_SMI_TX_SETTING)
#define LL_FEAT_BIT_SMI_TX (ll_settings_smi_tx() ?             \
                                BIT64(BT_LE_FEAT_BIT_SMI_TX) : \
                                0)
#else /* !CONFIG_BT_CTLR_SMI_TX_SETTING */
#define LL_FEAT_BIT_SMI_TX BIT64(BT_LE_FEAT_BIT_SMI_TX)
#endif /* !CONFIG_BT_CTLR_SMI_TX_SETTING */
#else  /* !CONFIG_BT_CTLR_SMI_TX */
#define LL_FEAT_BIT_SMI_TX 0
#endif /* !CONFIG_BT_CTLR_SMI_TX */

#if defined(CONFIG_BT_CTLR_SMI_RX)
#define LL_FEAT_BIT_SMI_RX BIT64(BT_LE_FEAT_BIT_SMI_RX)
#else /* !CONFIG_BT_CTLR_SMI_RX */
#define LL_FEAT_BIT_SMI_RX 0
#endif /* !CONFIG_BT_CTLR_SMI_RX */

#if defined(CONFIG_BT_CTLR_PHY_CODED)
#define LL_FEAT_BIT_PHY_CODED BIT64(BT_LE_FEAT_BIT_PHY_CODED)
#else /* !CONFIG_BT_CTLR_PHY_CODED */
#define LL_FEAT_BIT_PHY_CODED 0
#endif /* !CONFIG_BT_CTLR_PHY_CODED */

#if defined(CONFIG_BT_CTLR_ADV_EXT)
#define LL_FEAT_BIT_EXT_ADV BIT64(BT_LE_FEAT_BIT_EXT_ADV)
#else /* !CONFIG_BT_CTLR_ADV_EXT */
#define LL_FEAT_BIT_EXT_ADV 0
#endif /* !CONFIG_BT_CTLR_ADV_EXT */

#if defined(CONFIG_BT_CTLR_ADV_PERIODIC) || \
    defined(CONFIG_BT_CTLR_SYNC_PERIODIC)
#define LL_FEAT_BIT_PER_ADV BIT64(BT_LE_FEAT_BIT_PER_ADV)
#else /* !CONFIG_BT_CTLR_ADV_PERIODIC && !CONFIG_BT_CTLR_SYNC_PERIODIC */
#define LL_FEAT_BIT_PER_ADV 0
#endif /* !CONFIG_BT_CTLR_ADV_PERIODIC && !CONFIG_BT_CTLR_SYNC_PERIODIC */

#define LL_FEAT_BIT_MASK       0x1FFFF
#define LL_FEAT_BIT_MASK_VALID 0x1CF2F
#define LL_FEAT_FILTER_OCTET0  0x1FF00
#define LL_FEAT                (LL_FEAT_BIT_ENC | \
                 LL_FEAT_BIT_CONN_PARAM_REQ |     \
                 LL_FEAT_BIT_EXT_REJ_IND |        \
                 LL_FEAT_BIT_SLAVE_FEAT_REQ |     \
                 LL_FEAT_BIT_PING |               \
                 LL_FEAT_BIT_DLE |                \
                 LL_FEAT_BIT_PRIVACY |            \
                 LL_FEAT_BIT_EXT_SCAN |           \
                 LL_FEAT_BIT_PHY_2M |             \
                 LL_FEAT_BIT_SMI_TX |             \
                 LL_FEAT_BIT_SMI_RX |             \
                 LL_FEAT_BIT_PHY_CODED |          \
                 LL_FEAT_BIT_EXT_ADV |            \
                 LL_FEAT_BIT_PER_ADV |            \
                 LL_FEAT_BIT_CHAN_SEL_2 |         \
                 LL_FEAT_BIT_MIN_USED_CHAN)
