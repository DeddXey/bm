#ifndef BM_W5500_H
#define BM_W5500_H

#include <cstdint>

struct CommonRegs
{
  uint8_t  mode;
  uint8_t  gatewayAddr[4]; // Net
  uint8_t  subnetMaskAddr[4];
  uint8_t  srcHwAddr[6];
  uint8_t  srcIpAddr[4];
  uint16_t interruptLlTimer;
  uint8_t  interrupt;
  uint8_t  interruptMask;
  uint8_t  socketInterrupt;
  uint8_t  socketInterruptMask;
  uint16_t retryTime;
  uint8_t  retryCount;
  uint8_t  pppLcpRequestTimer;
  uint8_t  pppLcpMagicNumber;
  uint8_t  pppDestinationMacAddr[6];
  uint16_t pppSessionIdentificator;
  uint16_t pppMaximumSegmentSize;
  uint8_t  unreachableIpAddr[4];
  uint16_t unreachablePort;
  uint8_t  phyConfiguration;
  uint8_t  reserved[10];
  uint8_t  chipVersion;
};

struct CommonRegsMode
{
  constexpr static uint8_t FARP[]{ 1, 1 };
  constexpr static uint8_t PPPoE[]{ 3, 1 };
  constexpr static uint8_t PB[]{ 4, 1 };
  constexpr static uint8_t WOL[]{ 5, 1 };
  constexpr static uint8_t RST[]{ 7, 1 };
};

struct CommonRegsInterrupt
{
  constexpr static uint8_t MP[]{ 4, 1 };
  constexpr static uint8_t PPPoE[]{ 5, 1 };
  constexpr static uint8_t UNREACH[]{ 6, 1 };
  constexpr static uint8_t CONFLICT[]{ 7, 1 };
};

struct CommonRegsInterruptMask
{
  constexpr static uint8_t MP[]{ 4, 1 };
  constexpr static uint8_t PPPoE[]{ 5, 1 };
  constexpr static uint8_t UNREACH[]{ 6, 1 };
  constexpr static uint8_t CONFLICT[]{ 7, 1 };
};

struct CommonRegsPhyConfiguration
{
  constexpr static uint8_t LNK[]{ 0, 1 };
  constexpr static uint8_t SPD[]{ 1, 1 };
  constexpr static uint8_t DPX[]{ 2, 1 };
  constexpr static uint8_t OPMDC[]{ 3, 3 };
  constexpr static uint8_t OPMD[]{ 6, 1 };
  constexpr static uint8_t RST[]{ 7, 1 };
};

struct SocketRegs
{
  uint8_t mode;
  uint8_t command;
  uint8_t interrupt;
  uint8_t status;

  uint16_t srcPort; //
  uint8_t  dstHwAddr[6];
  uint8_t  dstIpAddr[4];
  uint16_t dstPort;
  uint16_t maxSegmentSize;
  uint8_t  reserved;
  uint8_t  ipTos;
  uint8_t  ipTtl;
  uint8_t  reserved2[7];
  uint8_t  rxBufSize;
  uint8_t  txBufSize;

  uint16_t txFreeSize;
  uint16_t txReadPointer;
  uint16_t txWritePointer;

  uint16_t rxReceivedSize;
  uint16_t rxReadPointer;
  uint16_t rxWritePointer;
  uint8_t  interruptMask;
  uitn16_t fragmentOffset;
  uint8_t  keepAliveTimer;
};

struct SocketRegsMode
{
  constexpr static uint8_t PROTOCOL[]{ 0, 4 };
  constexpr static uint8_t UCASTB_MIP6B[]{ 4, 1 };
  constexpr static uint8_t ND_MC_MMB[]{ 5, 1 };
  constexpr static uint8_t BCASTB[]{ 6, 1 };
  constexpr static uint8_t MULTI_MFEN[]{ 7, 1 };
};

class enum SocketRegsCommand : uint8_t
{
  open     = 0x01,
  listen   = 0x02,
  connect  = 0x04,
  discon   = 0x08,
  close    = 0x10,
  send     = 0x20,
  sendMac  = 0x21,
  sendKeep = 0x22,
  recv     = 0x40
};

struct SocketRegsInterrupt
{
  constexpr static uint8_t CON[]{ 0, 1 };
  constexpr static uint8_t DISCON[]{ 1, 1 };
  constexpr static uint8_t RECV[]{ 2, 1 };
  constexpr static uint8_t TIMEOUT[]{ 3, 1 };
  constexpr static uint8_t SEND_OK[]{ 4, 1 };
};

struct SocketRegsInterruptMask
{
  constexpr static uint8_t CON[]{ 0, 1 };
  constexpr static uint8_t DISCON[]{ 1, 1 };
  constexpr static uint8_t RECV[]{ 2, 1 };
  constexpr static uint8_t TIMEOUT[]{ 3, 1 };
  constexpr static uint8_t SEND_OK[]{ 4, 1 };
};

class enum SocketRegsStatus : uint8_t
{
  closed       = 0x00,
  init         = 0x13,
  listen       = 0x14,
  estabilished = 0x17,
  closeWait    = 0x1c,
  udp          = 0x22,
  macraw       = 0x42,

  synSent  = 0x015,
  synRecv = 0x16,
  finWait     = 0x18,
  closing = 0x1a,
  timeWait = 0x1b,
  lastAck = 0x1d,

};

#endif // BM_W5500_H
