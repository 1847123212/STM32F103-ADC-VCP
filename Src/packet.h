/**
 ******************************************************************************
 * File Name          : packet_buffer.h
 * Description        : This file provides header for managing a packet buffer
 * Project            : Project Lab Embedded Systems - SS2015 - TU Chemnitz
 *
 *
 *
 * Author             : Saeid Yazdani [saeid@embedonix.com]
 * Date               : 11-6-2015
 ******************************************************************************
 *
 * COPYRIGHT(c) 2015 EMBEDONIX GmbH
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

#ifndef __PACKET_H
#define __PACKET_H

#include "stdint.h"
#include "usart.h"

#define CM_START_BYTE              				126
#define CM_STOP_BYTE		                    127

//#define CM_PACKET_SIZE							22

#define CM_VALUE_0              0x00
#define CM_VALUE_1              0x01
#define CM_VALUE_2              0x02
#define CM_VALUE_3              0x03

typedef enum cm_delayratio {
	CM_DELAY_100 	= 1,
	CM_DELAY_200 	= 2,
	CM_DELAY_300 	= 3,
	CM_DELAY_400 	= 4,
	CM_DELAY_500 	= 5,
	CM_DELAY_600 	= 6,
	CM_DELAY_700 	= 7,
	CM_DELAY_800 	= 8,
	CM_DELAY_900 	= 9,
	CM_DELAY_1000 	= 10,
	CM_DELAY_2000 	= 11,
	CM_DELAY_3000 	= 12,
	CM_DELAY_4000 	= 13,
	CM_DELAY_5000 	= 14
} CM_DelayRatio;

typedef struct cm_packet {
	uint8_t StartByte;      //start of packet
	uint8_t	Dummy1;         //always 0
	uint8_t DelayRatio;     //ratio of transfer delay (* 100)
	uint8_t DeviceId;       //ID of attached device

	uint32_t Value0;        //ADC10 Value
	uint32_t Value1;        //ADC11 Value
	uint32_t Value2;        //ADC12 Value
	uint32_t Value3;        //ADC13 Value

	uint8_t CRC_0;          //first byte of CRC
	uint8_t CRC_1;          //second byte of CRC
	uint8_t Dummy2;         //Always 0
	uint8_t StopByte;       //end (stop) of the packet       

} CM_Packet;

#define CM_PACKET_SIZE sizeof(CM_Packet);

/***************        CRC16 TABLE     ***************/
static const uint16_t CM_CRC16_TABLE[256] = { 0x0000, 0x1189, 0x2312, 0x329B,
		0x4624, 0x57AD, 0x6536, 0x74BF, 0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C,
		0xDBE5, 0xE97E, 0xF8F7, 0x0919, 0x1890, 0x2A0B, 0x3B82, 0x4F3D, 0x5EB4,
		0x6C2F, 0x7DA6, 0x8551, 0x94D8, 0xA643, 0xB7CA, 0xC375, 0xD2FC, 0xE067,
		0xF1EE, 0x1232, 0x03BB, 0x3120, 0x20A9, 0x5416, 0x459F, 0x7704, 0x668D,
		0x9E7A, 0x8FF3, 0xBD68, 0xACE1, 0xD85E, 0xC9D7, 0xFB4C, 0xEAC5, 0x1B2B,
		0x0AA2, 0x3839, 0x29B0, 0x5D0F, 0x4C86, 0x7E1D, 0x6F94, 0x9763, 0x86EA,
		0xB471, 0xA5F8, 0xD147, 0xC0CE, 0xF255, 0xE3DC, 0x2464, 0x35ED, 0x0776,
		0x16FF, 0x6240, 0x73C9, 0x4152, 0x50DB, 0xA82C, 0xB9A5, 0x8B3E, 0x9AB7,
		0xEE08, 0xFF81, 0xCD1A, 0xDC93, 0x2D7D, 0x3CF4, 0x0E6F, 0x1FE6, 0x6B59,
		0x7AD0, 0x484B, 0x59C2, 0xA135, 0xB0BC, 0x8227, 0x93AE, 0xE711, 0xF698,
		0xC403, 0xD58A, 0x3656, 0x27DF, 0x1544, 0x04CD, 0x7072, 0x61FB, 0x5360,
		0x42E9, 0xBA1E, 0xAB97, 0x990C, 0x8885, 0xFC3A, 0xEDB3, 0xDF28, 0xCEA1,
		0x3F4F, 0x2EC6, 0x1C5D, 0x0DD4, 0x796B, 0x68E2, 0x5A79, 0x4BF0, 0xB307,
		0xA28E, 0x9015, 0x819C, 0xF523, 0xE4AA, 0xD631, 0xC7B8, 0x48C8, 0x5941,
		0x6BDA, 0x7A53, 0x0EEC, 0x1F65, 0x2DFE, 0x3C77, 0xC480, 0xD509, 0xE792,
		0xF61B, 0x82A4, 0x932D, 0xA1B6, 0xB03F, 0x41D1, 0x5058, 0x62C3, 0x734A,
		0x07F5, 0x167C, 0x24E7, 0x356E, 0xCD99, 0xDC10, 0xEE8B, 0xFF02, 0x8BBD,
		0x9A34, 0xA8AF, 0xB926, 0x5AFA, 0x4B73, 0x79E8, 0x6861, 0x1CDE, 0x0D57,
		0x3FCC, 0x2E45, 0xD6B2, 0xC73B, 0xF5A0, 0xE429, 0x9096, 0x811F, 0xB384,
		0xA20D, 0x53E3, 0x426A, 0x70F1, 0x6178, 0x15C7, 0x044E, 0x36D5, 0x275C,
		0xDFAB, 0xCE22, 0xFCB9, 0xED30, 0x998F, 0x8806, 0xBA9D, 0xAB14, 0x6CAC,
		0x7D25, 0x4FBE, 0x5E37, 0x2A88, 0x3B01, 0x099A, 0x1813, 0xE0E4, 0xF16D,
		0xC3F6, 0xD27F, 0xA6C0, 0xB749, 0x85D2, 0x945B, 0x65B5, 0x743C, 0x46A7,
		0x572E, 0x2391, 0x3218, 0x0083, 0x110A, 0xE9FD, 0xF874, 0xCAEF, 0xDB66,
		0xAFD9, 0xBE50, 0x8CCB, 0x9D42, 0x7E9E, 0x6F17, 0x5D8C, 0x4C05, 0x38BA,
		0x2933, 0x1BA8, 0x0A21, 0xF2D6, 0xE35F, 0xD1C4, 0xC04D, 0xB4F2, 0xA57B,
		0x97E0, 0x8669, 0x7787, 0x660E, 0x5495, 0x451C, 0x31A3, 0x202A, 0x12B1,
		0x0338, 0xFBCF, 0xEA46, 0xD8DD, 0xC954, 0xBDEB, 0xAC62, 0x9EF9, 0x8F70 };

extern CM_Packet cmHandler;
void CM_Init(CM_Packet *handler);

void CM_AppendData(CM_Packet *handler, uint8_t identifier, uint32_t data);

uint16_t CalculateCRC16(uint16_t crc, const void *c_ptr, uint32_t len);

#endif
