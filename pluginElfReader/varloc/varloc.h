/**
 ******************************************************************************
 * @file    varloc.h
 * @author  kasper
 * @date    2023-Jul-13
 * @brief   Description
 ******************************************************************************
 */
#ifndef INC_VARLOC_H_
#define INC_VARLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported includes ---------------------------------------------------------*/
#include <stdint.h>
#include "varcommon.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

// parse elf file for static variables and return root node
varloc_node_t*  varloc_open_elf(char* file);

#ifdef __cplusplus
}
#endif

#endif /* INC_VARLOC_H_ */