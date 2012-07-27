/*
 * Enumeration of all SSL-specific error codes.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/* $Id: sslerr.h,v 1.24 2012/05/08 00:10:56 wtc%google.com Exp $ */
#ifndef __SSL_ERR_H_
#define __SSL_ERR_H_


#define SSL_ERROR_BASE				(-0x3000)
#define SSL_ERROR_LIMIT				(SSL_ERROR_BASE + 1000)

#define IS_SSL_ERROR(code) \
    (((code) >= SSL_ERROR_BASE) && ((code) < SSL_ERROR_LIMIT))

#ifndef NO_SECURITY_ERROR_ENUM
typedef enum {
SSL_ERROR_EXPORT_ONLY_SERVER 		= (SSL_ERROR_BASE +  0),
SSL_ERROR_US_ONLY_SERVER 		= (SSL_ERROR_BASE +  1),
SSL_ERROR_NO_CYPHER_OVERLAP 		= (SSL_ERROR_BASE +  2),
/* 
 * Received an alert reporting what we did wrong.  (more alerts below)
 */
SSL_ERROR_NO_CERTIFICATE /*_ALERT */	= (SSL_ERROR_BASE +  3),
SSL_ERROR_BAD_CERTIFICATE            	= (SSL_ERROR_BASE +  4),
SSL_ERROR_UNUSED_5			= (SSL_ERROR_BASE +  5),
					/* error 5 is obsolete */
SSL_ERROR_BAD_CLIENT 			= (SSL_ERROR_BASE +  6),
SSL_ERROR_BAD_SERVER 			= (SSL_ERROR_BASE +  7),
SSL_ERROR_UNSUPPORTED_CERTIFICATE_TYPE	= (SSL_ERROR_BASE +  8),
SSL_ERROR_UNSUPPORTED_VERSION 		= (SSL_ERROR_BASE +  9),
SSL_ERROR_UNUSED_10			= (SSL_ERROR_BASE + 10),
					/* error 10 is obsolete */
SSL_ERROR_WRONG_CERTIFICATE		= (SSL_ERROR_BASE + 11),
SSL_ERROR_BAD_CERT_DOMAIN 		= (SSL_ERROR_BASE + 12),
SSL_ERROR_POST_WARNING 			= (SSL_ERROR_BASE + 13),
SSL_ERROR_SSL2_DISABLED 		= (SSL_ERROR_BASE + 14),
SSL_ERROR_BAD_MAC_READ 			= (SSL_ERROR_BASE + 15),
/* 
 * Received an alert reporting what we did wrong.
 * (two more alerts above, and many more below)
 */
SSL_ERROR_BAD_MAC_ALERT 		= (SSL_ERROR_BASE + 16),
SSL_ERROR_BAD_CERT_ALERT                = (SSL_ERROR_BASE + 17),
SSL_ERROR_REVOKED_CERT_ALERT 		= (SSL_ERROR_BASE + 18),
SSL_ERROR_EXPIRED_CERT_ALERT 		= (SSL_ERROR_BASE + 19),

SSL_ERROR_SSL_DISABLED 			= (SSL_ERROR_BASE + 20),
SSL_ERROR_FORTEZZA_PQG 			= (SSL_ERROR_BASE + 21),
SSL_ERROR_UNKNOWN_CIPHER_SUITE		= (SSL_ERROR_BASE + 22),
SSL_ERROR_NO_CIPHERS_SUPPORTED		= (SSL_ERROR_BASE + 23),
SSL_ERROR_BAD_BLOCK_PADDING		= (SSL_ERROR_BASE + 24),
SSL_ERROR_RX_RECORD_TOO_LONG		= (SSL_ERROR_BASE + 25),
SSL_ERROR_TX_RECORD_TOO_LONG		= (SSL_ERROR_BASE + 26),
/* 
 * Received a malformed (too long or short) SSL handshake.
 */
SSL_ERROR_RX_MALFORMED_HELLO_REQUEST	= (SSL_ERROR_BASE + 27),
SSL_ERROR_RX_MALFORMED_CLIENT_HELLO	= (SSL_ERROR_BASE + 28),
SSL_ERROR_RX_MALFORMED_SERVER_HELLO	= (SSL_ERROR_BASE + 29),
SSL_ERROR_RX_MALFORMED_CERTIFICATE	= (SSL_ERROR_BASE + 30),
SSL_ERROR_RX_MALFORMED_SERVER_KEY_EXCH	= (SSL_ERROR_BASE + 31),
SSL_ERROR_RX_MALFORMED_CERT_REQUEST	= (SSL_ERROR_BASE + 32),
SSL_ERROR_RX_MALFORMED_HELLO_DONE	= (SSL_ERROR_BASE + 33),
SSL_ERROR_RX_MALFORMED_CERT_VERIFY	= (SSL_ERROR_BASE + 34),
SSL_ERROR_RX_MALFORMED_CLIENT_KEY_EXCH	= (SSL_ERROR_BASE + 35),
SSL_ERROR_RX_MALFORMED_FINISHED 	= (SSL_ERROR_BASE + 36),
/* 
 * Received a malformed (too long or short) SSL record.
 */
SSL_ERROR_RX_MALFORMED_CHANGE_CIPHER 	= (SSL_ERROR_BASE + 37),
SSL_ERROR_RX_MALFORMED_ALERT	 	= (SSL_ERROR_BASE + 38),
SSL_ERROR_RX_MALFORMED_HANDSHAKE 	= (SSL_ERROR_BASE + 39),
SSL_ERROR_RX_MALFORMED_APPLICATION_DATA	= (SSL_ERROR_BASE + 40),
/*
 * Received an SSL handshake that was inappropriate for the state we're in.
 * E.g. Server received message from server, or wrong state in state machine.
 */
SSL_ERROR_RX_UNEXPECTED_HELLO_REQUEST	= (SSL_ERROR_BASE + 41),
SSL_ERROR_RX_UNEXPECTED_CLIENT_HELLO	= (SSL_ERROR_BASE + 42),
SSL_ERROR_RX_UNEXPECTED_SERVER_HELLO	= (SSL_ERROR_BASE + 43),
SSL_ERROR_RX_UNEXPECTED_CERTIFICATE	= (SSL_ERROR_BASE + 44),
SSL_ERROR_RX_UNEXPECTED_SERVER_KEY_EXCH	= (SSL_ERROR_BASE + 45),
SSL_ERROR_RX_UNEXPECTED_CERT_REQUEST	= (SSL_ERROR_BASE + 46),
SSL_ERROR_RX_UNEXPECTED_HELLO_DONE	= (SSL_ERROR_BASE + 47),
SSL_ERROR_RX_UNEXPECTED_CERT_VERIFY	= (SSL_ERROR_BASE + 48),
SSL_ERROR_RX_UNEXPECTED_CLIENT_KEY_EXCH	= (SSL_ERROR_BASE + 49),
SSL_ERROR_RX_UNEXPECTED_FINISHED 	= (SSL_ERROR_BASE + 50),
/*
 * Received an SSL record that was inappropriate for the state we're in.
 */
SSL_ERROR_RX_UNEXPECTED_CHANGE_CIPHER 	= (SSL_ERROR_BASE + 51),
SSL_ERROR_RX_UNEXPECTED_ALERT	 	= (SSL_ERROR_BASE + 52),
SSL_ERROR_RX_UNEXPECTED_HANDSHAKE 	= (SSL_ERROR_BASE + 53),
SSL_ERROR_RX_UNEXPECTED_APPLICATION_DATA= (SSL_ERROR_BASE + 54),
/*
 * Received record/message with unknown discriminant.
 */
SSL_ERROR_RX_UNKNOWN_RECORD_TYPE	= (SSL_ERROR_BASE + 55),
SSL_ERROR_RX_UNKNOWN_HANDSHAKE 		= (SSL_ERROR_BASE + 56),
SSL_ERROR_RX_UNKNOWN_ALERT 		= (SSL_ERROR_BASE + 57),
/* 
 * Received an alert reporting what we did wrong.  (more alerts above)
 */
SSL_ERROR_CLOSE_NOTIFY_ALERT 		= (SSL_ERROR_BASE + 58),
SSL_ERROR_HANDSHAKE_UNEXPECTED_ALERT 	= (SSL_ERROR_BASE + 59),
SSL_ERROR_DECOMPRESSION_FAILURE_ALERT 	= (SSL_ERROR_BASE + 60),
SSL_ERROR_HANDSHAKE_FAILURE_ALERT 	= (SSL_ERROR_BASE + 61),
SSL_ERROR_ILLEGAL_PARAMETER_ALERT 	= (SSL_ERROR_BASE + 62),
SSL_ERROR_UNSUPPORTED_CERT_ALERT 	= (SSL_ERROR_BASE + 63),
SSL_ERROR_CERTIFICATE_UNKNOWN_ALERT 	= (SSL_ERROR_BASE + 64),

SSL_ERROR_GENERATE_RANDOM_FAILURE	= (SSL_ERROR_BASE + 65),
SSL_ERROR_SIGN_HASHES_FAILURE		= (SSL_ERROR_BASE + 66),
SSL_ERROR_EXTRACT_PUBLIC_KEY_FAILURE	= (SSL_ERROR_BASE + 67),
SSL_ERROR_SERVER_KEY_EXCHANGE_FAILURE	= (SSL_ERROR_BASE + 68),
SSL_ERROR_CLIENT_KEY_EXCHANGE_FAILURE	= (SSL_ERROR_BASE + 69),

SSL_ERROR_ENCRYPTION_FAILURE		= (SSL_ERROR_BASE + 70),
SSL_ERROR_DECRYPTION_FAILURE		= (SSL_ERROR_BASE + 71), /* don't use */
SSL_ERROR_SOCKET_WRITE_FAILURE		= (SSL_ERROR_BASE + 72),

SSL_ERROR_MD5_DIGEST_FAILURE		= (SSL_ERROR_BASE + 73),
SSL_ERROR_SHA_DIGEST_FAILURE		= (SSL_ERROR_BASE + 74),
SSL_ERROR_MAC_COMPUTATION_FAILURE	= (SSL_ERROR_BASE + 75),
SSL_ERROR_SYM_KEY_CONTEXT_FAILURE	= (SSL_ERROR_BASE + 76),
SSL_ERROR_SYM_KEY_UNWRAP_FAILURE	= (SSL_ERROR_BASE + 77),
SSL_ERROR_PUB_KEY_SIZE_LIMIT_EXCEEDED	= (SSL_ERROR_BASE + 78),
SSL_ERROR_IV_PARAM_FAILURE		= (SSL_ERROR_BASE + 79),
SSL_ERROR_INIT_CIPHER_SUITE_FAILURE	= (SSL_ERROR_BASE + 80),
SSL_ERROR_SESSION_KEY_GEN_FAILURE	= (SSL_ERROR_BASE + 81),
SSL_ERROR_NO_SERVER_KEY_FOR_ALG		= (SSL_ERROR_BASE + 82),
SSL_ERROR_TOKEN_INSERTION_REMOVAL	= (SSL_ERROR_BASE + 83),
SSL_ERROR_TOKEN_SLOT_NOT_FOUND		= (SSL_ERROR_BASE + 84),
SSL_ERROR_NO_COMPRESSION_OVERLAP	= (SSL_ERROR_BASE + 85),
SSL_ERROR_HANDSHAKE_NOT_COMPLETED	= (SSL_ERROR_BASE + 86),
SSL_ERROR_BAD_HANDSHAKE_HASH_VALUE	= (SSL_ERROR_BASE + 87),
SSL_ERROR_CERT_KEA_MISMATCH		= (SSL_ERROR_BASE + 88),
/* SSL_ERROR_NO_TRUSTED_SSL_CLIENT_CA became obsolete in NSS 3.14. */
SSL_ERROR_NO_TRUSTED_SSL_CLIENT_CA	= (SSL_ERROR_BASE + 89),
SSL_ERROR_SESSION_NOT_FOUND		= (SSL_ERROR_BASE + 90),

SSL_ERROR_DECRYPTION_FAILED_ALERT	= (SSL_ERROR_BASE + 91),
SSL_ERROR_RECORD_OVERFLOW_ALERT		= (SSL_ERROR_BASE + 92),
SSL_ERROR_UNKNOWN_CA_ALERT		= (SSL_ERROR_BASE + 93),
SSL_ERROR_ACCESS_DENIED_ALERT		= (SSL_ERROR_BASE + 94),
SSL_ERROR_DECODE_ERROR_ALERT		= (SSL_ERROR_BASE + 95),
SSL_ERROR_DECRYPT_ERROR_ALERT		= (SSL_ERROR_BASE + 96),
SSL_ERROR_EXPORT_RESTRICTION_ALERT	= (SSL_ERROR_BASE + 97),
SSL_ERROR_PROTOCOL_VERSION_ALERT	= (SSL_ERROR_BASE + 98),
SSL_ERROR_INSUFFICIENT_SECURITY_ALERT	= (SSL_ERROR_BASE + 99),
SSL_ERROR_INTERNAL_ERROR_ALERT		= (SSL_ERROR_BASE + 100),
SSL_ERROR_USER_CANCELED_ALERT		= (SSL_ERROR_BASE + 101),
SSL_ERROR_NO_RENEGOTIATION_ALERT	= (SSL_ERROR_BASE + 102),

SSL_ERROR_SERVER_CACHE_NOT_CONFIGURED	= (SSL_ERROR_BASE + 103),

SSL_ERROR_UNSUPPORTED_EXTENSION_ALERT		= (SSL_ERROR_BASE + 104),
SSL_ERROR_CERTIFICATE_UNOBTAINABLE_ALERT	= (SSL_ERROR_BASE + 105),
SSL_ERROR_UNRECOGNIZED_NAME_ALERT		= (SSL_ERROR_BASE + 106),
SSL_ERROR_BAD_CERT_STATUS_RESPONSE_ALERT	= (SSL_ERROR_BASE + 107),
SSL_ERROR_BAD_CERT_HASH_VALUE_ALERT		= (SSL_ERROR_BASE + 108),

SSL_ERROR_RX_UNEXPECTED_NEW_SESSION_TICKET = (SSL_ERROR_BASE + 109),
SSL_ERROR_RX_MALFORMED_NEW_SESSION_TICKET  = (SSL_ERROR_BASE + 110),

SSL_ERROR_DECOMPRESSION_FAILURE		= (SSL_ERROR_BASE + 111),
SSL_ERROR_RENEGOTIATION_NOT_ALLOWED     = (SSL_ERROR_BASE + 112),
SSL_ERROR_UNSAFE_NEGOTIATION            = (SSL_ERROR_BASE + 113),

SSL_ERROR_RX_UNEXPECTED_UNCOMPRESSED_RECORD	= (SSL_ERROR_BASE + 114),

SSL_ERROR_WEAK_SERVER_EPHEMERAL_DH_KEY  = (SSL_ERROR_BASE + 115),

SSL_ERROR_NEXT_PROTOCOL_DATA_INVALID	= (SSL_ERROR_BASE + 116),

SSL_ERROR_FEATURE_NOT_SUPPORTED_FOR_SSL2 = (SSL_ERROR_BASE + 117),
SSL_ERROR_FEATURE_NOT_SUPPORTED_FOR_SERVERS = (SSL_ERROR_BASE + 118),
SSL_ERROR_FEATURE_NOT_SUPPORTED_FOR_CLIENTS = (SSL_ERROR_BASE + 119),

SSL_ERROR_INVALID_VERSION_RANGE		= (SSL_ERROR_BASE + 120),
SSL_ERROR_CIPHER_DISALLOWED_FOR_VERSION	= (SSL_ERROR_BASE + 121),

SSL_ERROR_RX_MALFORMED_HELLO_VERIFY_REQUEST = (SSL_ERROR_BASE + 122),
SSL_ERROR_RX_UNEXPECTED_HELLO_VERIFY_REQUEST = (SSL_ERROR_BASE + 123),

SSL_ERROR_END_OF_LIST	/* let the c compiler determine the value of this. */
} SSLErrorCodes;
#endif /* NO_SECURITY_ERROR_ENUM */

#endif /* __SSL_ERR_H_ */
