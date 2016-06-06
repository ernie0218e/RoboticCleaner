#define RC_RF24_CE_PIN 7
#define RC_RF24_CSN_PIN 8
#define RC_RF24_ROLL_PIN 3

#define RC_RF24_INT_NUM 3

//#define RC_RF24_PIPE_ADDR 0xE8E8F0F0E1LL // Black
//#define RC_RF24_PIPE_ADDR 0x98E8F0F0E1LL // Yellow
//#define RC_RF24_PIPE_ADDR 0x58E8F0F0E1LL // Blue
#define RC_RF24_PIPE_ADDR 0x38E8F0F0E1LL // Green
#define RC_RF24_BTN_LEFT 0
#define RC_RF24_BTN_RIGHT 1


//#define RC_PKT_ARM_PATTERN {0xDEAD, 0xBEEF}
#define RC_PKT_GUIDE_PATTERN 0xABBA

// The various roles supported by this sketch
typedef enum { role_sender = 1, role_receiver } role_e;

//#define RC_PKT_CRC 

typedef enum {
  E_RC_CMD_GET_STATUS = 0,
  E_RC_CMD_SEND_RC_DATA,
  E_RC_CMD_HEART_BEAT,
  E_RC_CMD_HANDSHAKE,
  E_RC_CMD_ACK,
  E_RC_CMD_ERROR,
  E_RC_CMD_MAX
} enumRcPktCmd_t;

typedef struct {
  uint16_t guidePattern;
  enumRcPktCmd_t cmd;
} stRcPktHeader_t;

typedef struct {
  uint16_t batteryLevel;
} stRcPktPayloadStatus_t;

typedef struct {
  uint16_t axis_left_x;
  uint16_t axis_left_y;
  uint16_t axis_right_x;
  uint16_t axis_right_y;
  uint8_t button;
} stRcPktPlayloadData_t;

typedef struct {
  uint32_t timeStamp;
} stRcPktPlayloadHeartBeat_t;

typedef struct {
  union {
    stRcPktPayloadStatus_t targetStatus;
    stRcPktPlayloadData_t data;
    stRcPktPlayloadHeartBeat_t heartBeat;
  };
} stRcPktPayload_t;

#ifdef RC_PKT_CRC
typedef struct {
  
} stRcPktCRC_t;
#endif

typedef struct {
  stRcPktHeader_t header;
  stRcPktPayload_t payLoad;
#ifdef RC_PKT_CRC
  stRcPktCRC_t crc;
#endif
} stRcPkt_t;

typedef enum {
  E_RC_CH_X,
  E_RC_CH_Y,
//  E_RC_BTN,
//  E_RC_LED,
  E_RC_CHANS
} E_RC_CHANNEL_t;

void setup_rc(role_e rcRole);
void update_rc(uint16_t left_x, uint16_t left_y, uint16_t right_x, uint16_t right_y, uint8_t button, uint8_t led);
void send_rc(uint8_t len, uint8_t* pData);
#ifdef RC_PKT_CRC
bool calculateCRC(stRcPkt_t pkt);
#endif

