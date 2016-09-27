#ifdef APIEXDLL_EXPORTS
#define APIEXDLL_API __declspec(dllexport)
#else
#define APIEXDLL_API __declspec(dllimport)
#endif


#ifndef __APIEX_H__
#define __APIEX_H__


/*
 *    Interface Routines
*/
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ISR_ROUTINE)();
typedef void (*BOARD_FAILURE_ROUTINE)();
typedef void (*DMA_FINISH_ROUTINE)();
APIEXDLL_API bool Startup();
APIEXDLL_API void Cleanup();


APIEXDLL_API bool PortReadByte(unsigned short address, unsigned char *pdata);
APIEXDLL_API bool PortWriteByte(unsigned short address, unsigned char data);

APIEXDLL_API bool MemReadByte(unsigned short address, unsigned char *pdata);
APIEXDLL_API bool MemWriteByte(unsigned short address, unsigned char data);

APIEXDLL_API bool EnableIntr();
APIEXDLL_API bool DisableIntr();
APIEXDLL_API bool RegisterLocalISR(ISR_ROUTINE);

APIEXDLL_API bool RegisterBoardFailureRoutine(BOARD_FAILURE_ROUTINE);

APIEXDLL_API bool RegisterDmaFinishNotifyRoutine(DMA_FINISH_ROUTINE);

APIEXDLL_API bool ProgMemReadByte(unsigned short address, unsigned char* pdata);
APIEXDLL_API bool ProgMemWriteByte(unsigned short address, unsigned char data);

APIEXDLL_API bool PramWrite(unsigned short address, unsigned char data[], int len, bool bWrite);
APIEXDLL_API int DmaRead(unsigned char buffer[], unsigned long nBytesToRead);
APIEXDLL_API int DmaWrite(unsigned char buffer[], unsigned long nBytesToWrite);
//APIEXDLL_API int BulkRead(BYTE buffer[], DWORD nBytesToWrite);
//APIEXDLL_API int BulkWrite(BYTE buffer[], DWORD nBytesToWrite);
APIEXDLL_API bool Read8237(unsigned short address, unsigned char* pdata);
APIEXDLL_API bool Write8237(unsigned short address, unsigned char data);
APIEXDLL_API int DmaTransferHostToLocal(unsigned char data[], unsigned short wBytes);

// +++++++++++++++++++++++++++++++++ //
APIEXDLL_API bool PortWriteEx(unsigned short address, unsigned char data[], unsigned char nBytesToWrite, unsigned char nDelay);
APIEXDLL_API bool PortReadEx(unsigned short address, unsigned char buffer[], unsigned char nBytesToRead, unsigned char nDelay);
APIEXDLL_API bool Read0809(unsigned short address, unsigned char buffer[], unsigned char nBytesToRead, unsigned char nDelay);
// +++++++++++++++++++++++++++++++++ //

#ifdef __cplusplus
}
#endif
#endif
