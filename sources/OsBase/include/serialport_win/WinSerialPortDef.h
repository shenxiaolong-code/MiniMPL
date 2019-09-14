#ifndef WINSERIALPORTDEF_H__
#define WINSERIALPORTDEF_H__
/************************************************************************************
author  :	Shen.Xiaolong(2009-2016), xlshen@126.com  xlshen2002@hotmail.com
purpose :	common structure definition for CSerialPort
*************************************************************************************/

namespace OS_Win32
{
    enum EBaundRate
    {
        EBaund_110      = CBR_110,  
        EBaund_300      = CBR_300,  
        EBaund_600      = CBR_600,  
        EBaund_1200     = CBR_1200,  
        EBaund_2400     = CBR_2400,  
        EBaund_4800     = CBR_4800,  
        EBaund_9600     = CBR_9600,  
        EBaund_14400    = CBR_14400,  
        EBaund_19200    = CBR_19200,  
        EBaund_38400    = CBR_38400,  
        EBaund_56000    = CBR_56000,  
        EBaund_57600    = CBR_57600,  
        EBaund_115200   = CBR_115200,  
        EBaund_128000   = CBR_128000,  
        EBaund_256000   = CBR_256000 
    };

    // Data bits (5-8)
    enum EDataBits
    {
        EDataBits_Unknown = -1,    // Unknown
        EDataBits_5       =  5,    // 5 bits per byte
        EDataBits_6       =  6,    // 6 bits per byte
        EDataBits_7       =  7,    // 7 bits per byte
        EDataBits_8       =  8     // 8 bits per byte (default)
    };

    // Parity scheme
    enum EParity
    {
        EParity_Unknown   = -1,           // Unknown
        EParity_None      = NOPARITY,     // No parity (default)
        EParity_Odd       = ODDPARITY,    // Odd parity
        EParity_Even      = EVENPARITY,   // Even parity
        EParity_Mark      = MARKPARITY,   // Mark parity
        EParity_Space     = SPACEPARITY   // Space parity
    };

    // Stop bits
    enum EStopBits
    {
        EStopBits_Unknown  = -1,           // Unknown
        EStopBits_1        = ONESTOPBIT,   // 1 stopbit (default)
        EStopBits_1_5      = ONE5STOPBITS, // 1.5 stopbit
        EStopBits_2        = TWOSTOPBITS   // 2 stopbits
    };

    // Handshaking
    enum EHandshake
    {
        EHandshakeUnknown     = -1,   // Unknown
        EHandshakeOff         =  0,   // No handshaking
        EHandshakeHardware    =  1,   // Hardware handshaking (RTS/CTS)
        EHandshakeSoftware    =  2    // Software handshaking (XON/XOFF)
    };

    enum ESerialPortEvent
    {
        EEvent_RXCHAR   =  EV_RXCHAR ,      // Any Character received
        EEvent_RXFLAG   =  EV_RXFLAG ,      // Received certain character
        EEvent_TXEMPTY  =  EV_TXEMPTY ,     // Transmitt Queue Empty
        EEvent_CTS      =  EV_CTS ,         // CTS changed state
        EEvent_DSR      =  EV_DSR ,         // DSR changed state
        EEvent_RLSD     =  EV_RLSD ,        // RLSD changed state
        EEvent_BREAK    =  EV_BREAK ,       // BREAK received
        EEvent_ERR      =  EV_ERR ,         // Line status error occurred
        EEvent_RING     =  EV_RING ,        // Ring signal detected
        EEvent_PERR     =  EV_PERR ,        // Printer error occured
        EEvent_RX80FULL =  EV_RX80FULL ,    // Receive buffer is 80 percent full
        EEvent_EVENT1   =  EV_EVENT1 ,      // Provider specific event 1
        EEvent_EVENT2   =  EV_EVENT2        // Provider specific event 2
    };

    enum EOpenError
    {
        EOpenError_BADID    = IE_BADID ,    // Invalid or unsupported id
        EOpenError_OPEN     = IE_OPEN ,     // Device Already Open
        EOpenError_NOPEN    = IE_NOPEN ,    // Device Not Open
        EOpenError_MEMORY   = IE_MEMORY ,   // Unable to allocate queues
        EOpenError_DEFAULT  = IE_DEFAULT ,  // Error in default parameters
        EOpenError_HARDWARE = IE_HARDWARE , // Hardware Not Present
        EOpenError_BYTESIZE = IE_BYTESIZE , // Illegal Byte Size
        EOpenError_BAUDRATE = IE_BAUDRATE   // Unsupported BaudRate
    };
}

#endif // WINSERIALPORTDEF_H__
