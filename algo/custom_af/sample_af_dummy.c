/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2021. All rights reserved.
 *
 * File Name: sample_af_dummy.c
 * Description: Dummy implementation of the AF ISP MPI wrappers
 *              (CVI_ISP_GetAFAttr / CVI_ISP_SetAFAttr).
 *              The open-source custom_af libaf.so lacks these symbols,
 *              which left UND references inside libcvi_ispd2.so and broke
 *              strict executable linking in downstream projects.
 *              The AF tuning RPC path only needs the symbols to exist;
 *              the dummy stores the attribute so Get/Set remain consistent.
 */

/**************************************************************************
 *                        H E A D E R   F I L E S
 **************************************************************************/
#include <string.h>

#include "cvi_base.h"
#include "cvi_comm_isp.h"
#include "cvi_comm_3a.h"
#include "cvi_af.h"
#include "cvi_isp.h"

#include "sample_af.h"

/**************************************************************************
 *                              M A C R O S
 **************************************************************************/
/**************************************************************************
 *                          D A T A   T Y P E S
 **************************************************************************/
/**************************************************************************
 *                  E X T E R N A L   R E F E R E N C E
 **************************************************************************/
/**************************************************************************
 *              F U N C T I O N   D E C L A R A T I O N S
 **************************************************************************/
/**************************************************************************
 *                        G L O B A L   D A T A
 **************************************************************************/

/* Single static storage; zero-initialized, no real AF hardware involved */
static ISP_FOCUS_ATTR_S stAfMpiAttr;

/**
 * @brief Get the AF (focus) control attributes.
 *
 * Dummy implementation that returns the cached attribute set by
 * CVI_ISP_SetAFAttr (zero-initialized if never set).
 *
 * @param[in] ViPipe pipe id (unused in dummy)
 * @param[out] pstFocusAttr pointer to receive the AF attributes
 * @return CVI_SUCCESS always
 */
CVI_S32 CVI_ISP_GetAFAttr(VI_PIPE ViPipe, ISP_FOCUS_ATTR_S *pstFocusAttr)
{
	UNUSED(ViPipe);

	*pstFocusAttr = stAfMpiAttr;
	return CVI_SUCCESS;
}

/**
 * @brief Set the AF (focus) control attributes.
 *
 * Dummy implementation that only caches the attribute; no motor or
 * AF algorithm is driven.
 *
 * @param[in] ViPipe pipe id (unused in dummy)
 * @param[in] pstFocusAttr pointer to the AF attributes to store
 * @return CVI_SUCCESS always
 */
CVI_S32 CVI_ISP_SetAFAttr(VI_PIPE ViPipe, const ISP_FOCUS_ATTR_S *pstFocusAttr)
{
	UNUSED(ViPipe);

	stAfMpiAttr = *pstFocusAttr;
	return CVI_SUCCESS;
}
