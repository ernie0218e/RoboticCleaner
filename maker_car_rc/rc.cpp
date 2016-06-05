/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example of using interrupts
 *
 * This is an example of how to user interrupts to interact with the radio.
 * It builds on the pingpair_pl example, and uses ack payloads.
 */
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "rc.h"


//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(RC_RF24_CE_PIN,RC_RF24_CSN_PIN);

// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const short role_pin = RC_RF24_CSN_PIN;

//
// Topology
//

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = RC_RF24_PIPE_ADDR;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Sender", "Receiver"};

// The role of the current running sketch
role_e role;

// Packet
stRcPkt_t rcPacket;

// Interrupt handler, check the radio because we got an IRQ
void check_radio(void);

void parseRC(void* pIncomingPkt);

void setup_rc(role_e rcRole)
{
  // global variable initialize
  //memset(rcData, 0, sizeof(rcData));
  memset(&rcPacket, 0, sizeof(rcPacket));
  rcPacket.header.guidePattern = RC_PKT_GUIDE_PATTERN;
  rcPacket.header.cmd = E_RC_CMD_MAX;
  
  //
  // Role
  //
  role = rcRole;


  //
  // Setup and configure rf radio
  //

  radio.begin();

  // We will be using the Ack Payload feature, so please enable it
  radio.enableAckPayload();

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens a single pipe for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.

  if ( role == role_sender )
  {
    radio.openWritingPipe(pipe);
  }
  else
  {
    radio.openReadingPipe(1,pipe);
  }

  //
  // Start listening
  //

  if ( role == role_receiver )
    radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();

  //
  // Attach interrupt handler to interrupt #0 (using pin 2)
  // on BOTH the sender and receiver
  //

  attachInterrupt(digitalPinToInterrupt(RC_RF24_INT_NUM), check_radio, FALLING);
}

static uint32_t message_count = 0;


void send_rc(uint8_t len, uint8_t* pData)
{
  radio.startWrite( pData, len, false );
}


void check_radio(void)
{
  // What happened?
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);

  // Have we successfully transmitted?
  if ( tx )
  {
      //printf("Send:OK\n\r");
  }

  // Have we failed to transmit?
  if ( fail )
  {
      //printf("Send:Failed\n\r");
  }

  
  // Did we receive a message?
  if ( rx )
  {
    // If we're the sender, we've received an ack payload
    if ( role == role_sender )
    {
      radio.read(&message_count,sizeof(message_count));
    }

    // If we're the receiver, we've received a time message
    if ( role == role_receiver )
    {
      // Get this payload and dump it
      radio.read( &rcPacket, sizeof(rcPacket) );
      parseRC((void*)&rcPacket);    

      // Add an ack packet for the next time around.  This is a simple
      // packet counter
      radio.writeAckPayload( 1, &message_count, sizeof(message_count) );
      ++message_count;
    }
  }
}

void update_rc(uint16_t left_x, uint16_t left_y, uint16_t right_x, uint16_t right_y, uint8_t button)
{
  
  rcPacket.header.cmd = E_RC_CMD_SEND_RC_DATA;
  
  rcPacket.payLoad.data.axis_left_x = left_x;
  rcPacket.payLoad.data.axis_left_y = left_y;
  rcPacket.payLoad.data.axis_right_x = right_x;
  rcPacket.payLoad.data.axis_right_y = right_y;
  rcPacket.payLoad.data.button = button;

  send_rc(sizeof(rcPacket), (uint8_t*)&rcPacket);
}

void parseRC(void* pIncomingPkt) {
  stRcPkt_t* pPkt = (stRcPkt_t*)pIncomingPkt;
  
  // check packet header
  if(pPkt->header.guidePattern != RC_PKT_GUIDE_PATTERN) {
    return;
  }
  
  switch(pPkt->header.cmd) {
    case E_RC_CMD_GET_STATUS:
      //printf("batteryLevel: %d", pPkt->payLoad.targetStatus.batteryLevel);
      break;
    case E_RC_CMD_SEND_RC_DATA:
      break;
    case E_RC_CMD_HEART_BEAT:
      break;
    case E_RC_CMD_HANDSHAKE:
      break;
    case E_RC_CMD_ACK:
      break;
    case E_RC_CMD_ERROR:
      break;
    default:
      break;
  }
}
