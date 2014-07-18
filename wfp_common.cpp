//----------------------------------------------------------------------------
// Hone common Windows Filtering Platform (WFP) structures
//
// Copyright (c) 2014 Battelle Memorial Institute
// Licensed under a modification of the 3-clause BSD license
// See License.txt for the full text of the license and additional disclaimers
//
// Authors
//   Richard L. Griswold <richard.griswold@pnnl.gov>
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------------

#ifdef KERNEL
#include <ntddk.h>
#include <fwpmk.h>
#else
#include <Windows.h>
#include <fwpmu.h>
#endif

#include "wfp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------
// Defines
//--------------------------------------------------------------------------

// Short names for the layers
#define LAC4   FWPM_LAYER_ALE_AUTH_CONNECT_V4
#define LAC6   FWPM_LAYER_ALE_AUTH_CONNECT_V6
#define LARA4  FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V4
#define LARA6  FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V6
#define LEC4   FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V4
#define LEC6   FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V6
#define LRA4   FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4
#define LRA6   FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6
#define LRR4   FWPM_LAYER_ALE_RESOURCE_RELEASE_V4
#define LRR6   FWPM_LAYER_ALE_RESOURCE_RELEASE_V6
#define LIT4   FWPM_LAYER_INBOUND_TRANSPORT_V4
#define LIT6   FWPM_LAYER_INBOUND_TRANSPORT_V6
#define LOT4   FWPM_LAYER_OUTBOUND_TRANSPORT_V4
#define LOT6   FWPM_LAYER_OUTBOUND_TRANSPORT_V6

#ifndef ARRAY_SIZEOF
#define ARRAY_SIZEOF(a) (sizeof(a) / sizeof(a[0]))
#endif

//--------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------

// Callout keys
DEFINE_GUID(AC4CK,  0x8507ecaf, 0xed50, 0x46b9, 0x9e, 0xdb, 0x08, 0x24, 0x90, 0x94, 0xc1, 0x0a);
DEFINE_GUID(AC6CK,  0xc719d65d, 0x5e63, 0x48fd, 0xa0, 0xbe, 0xc8, 0x6c, 0xdf, 0xb3, 0x7b, 0x1b);
DEFINE_GUID(ARA4CK, 0xcf23b1ef, 0xb44a, 0x48aa, 0x94, 0xef, 0x61, 0xca, 0x32, 0x22, 0x19, 0xd5);
DEFINE_GUID(ARA6CK, 0x3f2a1fa1, 0x0efd, 0x433e, 0xa5, 0x6e, 0xc6, 0x7d, 0xac, 0x35, 0x5b, 0xb1);
DEFINE_GUID(EC4CK,  0x84825fc4, 0xc9ca, 0x4bc8, 0x9d, 0x94, 0xa8, 0xd9, 0x82, 0x2b, 0xde, 0xaa);
DEFINE_GUID(EC6CK,  0xb47be296, 0x44ac, 0x443d, 0x8a, 0x03, 0x48, 0xab, 0x23, 0x1b, 0xd9, 0x41);
DEFINE_GUID(RA4CK,  0xd62594e5, 0xedbc, 0x4966, 0xbb, 0x22, 0xb7, 0x6d, 0xb9, 0x2f, 0xbc, 0xaa);
DEFINE_GUID(RA6CK,  0xb46a099b, 0x3ffa, 0x40a3, 0x9c, 0xb1, 0x45, 0xfd, 0x5b, 0xb8, 0xcb, 0xaf);
DEFINE_GUID(RR4CK,  0x8b3adb50, 0x9e0e, 0x4b0f, 0xb1, 0x46, 0xa7, 0xe0, 0x55, 0xc4, 0xc4, 0x73);
DEFINE_GUID(RR6CK,  0x57c15b25, 0x271c, 0x4e7a, 0xb5, 0x40, 0x0b, 0x93, 0xa2, 0x2a, 0x03, 0xe2);
DEFINE_GUID(IT4CK,  0x9edbd5c2, 0x7132, 0x4955, 0x82, 0xdc, 0x13, 0x79, 0x4c, 0x08, 0xd5, 0x82);
DEFINE_GUID(IT6CK,  0x58a9655f, 0xcc73, 0x4706, 0xab, 0x97, 0x01, 0x00, 0x15, 0x4c, 0x9e, 0xd3);
DEFINE_GUID(OT4CK,  0x0d562566, 0xb097, 0x4a29, 0xad, 0xfa, 0xff, 0x6a, 0x54, 0xe3, 0xbe, 0xd6);
DEFINE_GUID(OT6CK,  0x678243c9, 0x1dc3, 0x4416, 0x93, 0xc9, 0x56, 0x95, 0xca, 0x8f, 0x23, 0x25);

// Filter keys
DEFINE_GUID(AC4FK,  0xf579c330, 0x3383, 0x4187, 0x99, 0x8e, 0xfb, 0x7d, 0xd4, 0xe1, 0xfd, 0x5f);
DEFINE_GUID(AC6FK,  0x23f394e5, 0x6328, 0x4096, 0xaa, 0xdd, 0x35, 0x39, 0x24, 0x28, 0x0c, 0x7f);
DEFINE_GUID(ARA4FK, 0xb6b1aa81, 0x088e, 0x4d78, 0xbe, 0x3f, 0xcd, 0xea, 0xa0, 0x32, 0xe1, 0x9e);
DEFINE_GUID(ARA6FK, 0x24eeaf13, 0x6e9b, 0x4e31, 0x98, 0x02, 0x0b, 0x36, 0xf6, 0x35, 0x17, 0x60);
DEFINE_GUID(EC4FK,  0x31f23fbc, 0xdf76, 0x4f0e, 0x92, 0x81, 0x43, 0x74, 0xed, 0xcf, 0xa0, 0x2d);
DEFINE_GUID(EC6FK,  0xa1955625, 0xd2ab, 0x4ddc, 0x88, 0x5d, 0xdd, 0x77, 0x81, 0x7f, 0x3f, 0xec);
DEFINE_GUID(RA4FK,  0x2db9f0ab, 0xcdbf, 0x486b, 0xbd, 0x5b, 0x72, 0xb2, 0x1f, 0xb4, 0x76, 0x9e);
DEFINE_GUID(RA6FK,  0xb5e06998, 0xae9e, 0x4107, 0xab, 0xd6, 0xab, 0x80, 0x99, 0xdf, 0x52, 0x1d);
DEFINE_GUID(RR4FK,  0x9fbb7e6a, 0xfda1, 0x4bee, 0x83, 0x19, 0x7b, 0x2e, 0x39, 0x28, 0x55, 0xad);
DEFINE_GUID(RR6FK,  0x8d4753ed, 0xd5b4, 0x4509, 0xa0, 0xb7, 0xf8, 0xb9, 0x30, 0x19, 0x2b, 0x6f);
DEFINE_GUID(IT4FK,  0x3ade95df, 0x7a85, 0x4f9b, 0xaa, 0xae, 0x5d, 0xbc, 0xdf, 0x85, 0xb8, 0xa5);
DEFINE_GUID(IT6FK,  0x5aeb7cf6, 0x5cca, 0x427c, 0xb1, 0x9e, 0x58, 0x6a, 0xda, 0xfb, 0xac, 0xb5);
DEFINE_GUID(OT4FK,  0xcd3e2a92, 0x37bc, 0x4be2, 0xa1, 0x2d, 0xd5, 0x5a, 0x2a, 0x00, 0x59, 0xc8);
DEFINE_GUID(OT6FK,  0x80d6c352, 0x1830, 0x4cef, 0xb6, 0x9a, 0x95, 0xe4, 0x6f, 0x92, 0x32, 0xc1);

// Boot-time filter keys
DEFINE_GUID(AC4BFK,  0x9d5997b4, 0x2a91, 0x4268, 0xb0, 0xa8, 0x40, 0x05, 0xd4, 0xd7, 0x82, 0x91);
DEFINE_GUID(AC6BFK,  0xabb2a4c7, 0xb37f, 0x49d5, 0xbe, 0x73, 0xa1, 0x9c, 0x1a, 0xcb, 0x85, 0x77);
DEFINE_GUID(ARA4BFK, 0x0a168a3a, 0xecf8, 0x41fd, 0xb1, 0x8b, 0x04, 0xc5, 0x7f, 0x8f, 0x25, 0x41);
DEFINE_GUID(ARA6BFK, 0xd70c0916, 0xba16, 0x48dd, 0x9c, 0xf1, 0xb2, 0x6a, 0xa9, 0x5d, 0x42, 0x00);
DEFINE_GUID(EC4BFK,  0x302732c6, 0x3c71, 0x4b38, 0x98, 0x60, 0x51, 0x07, 0xc7, 0x5b, 0x0a, 0x74);
DEFINE_GUID(EC6BFK,  0x2ebee506, 0x3365, 0x4f6e, 0x8d, 0xb9, 0x3a, 0x3a, 0x98, 0xfc, 0xdc, 0xe1);
DEFINE_GUID(RA4BFK,  0x34e51734, 0x2765, 0x4916, 0x9a, 0x0f, 0x9d, 0x60, 0xdd, 0xcb, 0x1c, 0x8f);
DEFINE_GUID(RA6BFK,  0xd67c3179, 0x680c, 0x4a5a, 0x9a, 0x76, 0x64, 0xbf, 0xf5, 0x63, 0x45, 0x1d);
DEFINE_GUID(RR4BFK,  0xd6730b9a, 0xa955, 0x4296, 0x91, 0xf6, 0x72, 0x92, 0xc8, 0x28, 0xb4, 0xf4);
DEFINE_GUID(RR6BFK,  0x5e2f9411, 0x0ed0, 0x4402, 0x86, 0xd8, 0x41, 0x9e, 0x60, 0xdd, 0x54, 0x45);
DEFINE_GUID(IT4BFK,  0x572feb46, 0xcc9b, 0x4e82, 0x8b, 0x0e, 0x85, 0xae, 0x8b, 0x4f, 0xf8, 0xc8);
DEFINE_GUID(IT6BFK,  0x3d5daaee, 0x1727, 0x474f, 0x86, 0xeb, 0x61, 0x94, 0x00, 0x85, 0x29, 0x54);
DEFINE_GUID(OT4BFK,  0x2d0193ce, 0xe811, 0x42fd, 0x85, 0x63, 0x7e, 0x26, 0x8f, 0x1f, 0x24, 0xbd);
DEFINE_GUID(OT6BFK,  0x6f97d45a, 0x359b, 0x4c78, 0x97, 0xba, 0x3c, 0xf9, 0xf8, 0x4b, 0x18, 0x18);

// Information for all of the filters we register
static struct LAYER_INFO gLayers[] = {
	{"Connect V4",             &LAC4,  &AC4BFK,  &AC4FK,  &AC4CK,  CtConnection},
	{"Connect V6",             &LAC6,  &AC6BFK,  &AC6FK,  &AC6CK,  CtConnection},
	{"Receive Accept V4",      &LARA4, &ARA4BFK, &ARA4FK, &ARA4CK, CtConnection},
	{"Receive Accept V6",      &LARA6, &ARA6BFK, &ARA6FK, &ARA6CK, CtConnection},
	{"Endpoint Closure V4",    &LEC4,  &EC4BFK,  &EC4FK,  &EC4CK,  CtConnection},
	{"Endpoint Closure V6",    &LEC6,  &EC6BFK,  &EC6FK,  &EC6CK,  CtConnection},
	{"Resource Assignment V4", &LRA4,  &RA4BFK,  &RA4FK,  &RA4CK,  CtConnection},
	{"Resource Assignment V6", &LRA6,  &RA6BFK,  &RA6FK,  &RA6CK,  CtConnection},
	{"Resource Release V4",    &LRR4,  &RR4BFK,  &RR4FK,  &RR4CK,  CtConnection},
	{"Resource Release V6",    &LRR6,  &RR6BFK,  &RR6FK,  &RR6CK,  CtConnection},
	{"Inbound Transport V4",   &LIT4,  &IT4BFK,  &IT4FK,  &IT4CK,  CtPacketInbound},
	{"Inbound Transport V6",   &LIT6,  &IT6BFK,  &IT6FK,  &IT6CK,  CtPacketInbound},
	{"Outbound Transport V4",  &LOT4,  &OT4BFK,  &OT4FK,  &OT4CK,  CtPacketOutbound},
	{"Outbound Transport V6",  &LOT6,  &OT6BFK,  &OT6FK,  &OT6CK,  CtPacketOutbound},
};

//----------------------------------------------------------------------------
const LAYER_INFO* HoneLayerInfo(const int index)
{
	return (index < ARRAY_SIZEOF(gLayers)) ? &gLayers[index] : NULL;
}

//--------------------------------------------------------------------------
int HoneNumLayers(void)
{
	return ARRAY_SIZEOF(gLayers);
}

#ifdef __cplusplus
} // extern "C"
#endif