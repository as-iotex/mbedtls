/**
 * \file mbedtls_ripemd160.h
 *
 * \brief RIPE MD-160 message digest
 *
 *  Copyright (C) 2014-2014, ARM Limited, All Rights Reserved
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef MBEDTLS_RIPEMD160_H
#define MBEDTLS_RIPEMD160_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(_MSC_VER) && !defined(EFIX64) && !defined(EFI32)
#include <basetsd.h>
typedef UINT32 uint32_t;
#else
#include <inttypes.h>
#endif

#define MBEDTLS_ERR_RIPEMD160_FILE_IO_ERROR              -0x007E  /**< Read/write error in file. */

#if !defined(MBEDTLS_RIPEMD160_ALT)
// Regular implementation
//

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          RIPEMD-160 context structure
 */
typedef struct
{
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[5];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
}
mbedtls_ripemd160_context;

/**
 * \brief          Initialize RIPEMD-160 context
 *
 * \param ctx      RIPEMD-160 context to be initialized
 */
void mbedtls_ripemd160_init( mbedtls_ripemd160_context *ctx );

/**
 * \brief          Clear RIPEMD-160 context
 *
 * \param ctx      RIPEMD-160 context to be cleared
 */
void mbedtls_ripemd160_free( mbedtls_ripemd160_context *ctx );

/**
 * \brief          RIPEMD-160 context setup
 *
 * \param ctx      context to be initialized
 */
void mbedtls_ripemd160_starts( mbedtls_ripemd160_context *ctx );

/**
 * \brief          RIPEMD-160 process buffer
 *
 * \param ctx      RIPEMD-160 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void mbedtls_ripemd160_update( mbedtls_ripemd160_context *ctx,
                       const unsigned char *input, size_t ilen );

/**
 * \brief          RIPEMD-160 final digest
 *
 * \param ctx      RIPEMD-160 context
 * \param output   RIPEMD-160 checksum result
 */
void mbedtls_ripemd160_finish( mbedtls_ripemd160_context *ctx, unsigned char output[20] );

/* Internal use */
void mbedtls_ripemd160_process( mbedtls_ripemd160_context *ctx, const unsigned char data[64] );

#ifdef __cplusplus
}
#endif

#else  /* MBEDTLS_RIPEMD160_ALT */
#include "ripemd160.h"
#endif /* MBEDTLS_RIPEMD160_ALT */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Output = RIPEMD-160( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   RIPEMD-160 checksum result
 */
void mbedtls_ripemd160( const unsigned char *input, size_t ilen,
                unsigned char output[20] );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief          Output = RIPEMD-160( file contents )
 *
 * \param path     input file name
 * \param output   RIPEMD-160 checksum result
 *
 * \return         0 if successful, or MBEDTLS_ERR_RIPEMD160_FILE_IO_ERROR
 */
int mbedtls_ripemd160_file( const char *path, unsigned char output[20] );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int mbedtls_ripemd160_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_ripemd160.h */
