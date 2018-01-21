/*
   Project: SC4Fix Patches for SimCity 4
   File: PropPoxVaccine.cpp

   Copyright (c) 2018 Nelson Gomez (simmaster07)

   Licensed under the MIT License. A copy of the License is available in
   LICENSE or at:

       http://opensource.org/licenses/MIT

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <assert.h>
#include <EASTL/internal/red_black_tree.h>
#include <stdio.h>
#include <vector>
#include "patcher.h"
#include "PropPoxVaccine.h"

const uint32_t kModeRead = 1;
const uint32_t kModeWrite = 2;
const uint32_t kCOMSerializedGID = 0x299b2d1b;
const uint32_t kMaxCRCDataLength = 250000;

class cIGZUnknown
{
public:
    virtual bool QueryInterface(uint32_t riid, void** ppvObj) = 0;
    virtual uint32_t AddRef(void) = 0;
    virtual uint32_t Release(void) = 0;
};

class cIGZString : public cIGZUnknown
{
public:
    virtual uint32_t FromChar(char const* pszSource) = 0;
    virtual uint32_t FromChar(char const* pszSource, uint32_t dwLength) = 0;
    virtual char const* ToChar(void) const = 0;
    virtual char const* Data(void) const = 0;
    
    virtual uint32_t Strlen(void) const = 0;
    virtual bool IsEqual(cIGZString const* szOther, bool bCaseSensitive) const = 0;
    virtual bool IsEqual(cIGZString const& szOther, bool bCaseSensitive) const = 0;
    virtual bool IsEqual(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const = 0;
    
    virtual int32_t CompareTo(cIGZString const& szOther, bool bCaseSensitive) const = 0;
    virtual int32_t CompareTo(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const = 0;
    
    virtual cIGZString& operator=(cIGZString const& szOther) = 0;
    
    virtual int32_t Copy(cIGZString const& szOther) = 0;
    virtual int32_t Resize(uint32_t dwNewSize) = 0;
    
    virtual cIGZString* Append(char const* pszOther, uint32_t dwLength) = 0;
    virtual cIGZString* Append(cIGZString const& szOther) = 0;
    virtual cIGZString* Insert(uint32_t dwPos, char const* pszOther, uint32_t dwLength) = 0;
    virtual cIGZString* Insert(uint32_t dwPos, cIGZString const& szOther) = 0;
    virtual cIGZString* Replace(uint32_t dwStartPos, char const* pszOther, uint32_t dwLength) = 0;
    virtual cIGZString* Replace(uint32_t dwStartPos, cIGZString const& szOther) = 0;
    virtual cIGZString* Erase(uint32_t dwStartPos, uint32_t dwEndPos) = 0;
    
    virtual int32_t Find(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
    virtual int32_t Find(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
    
    virtual int32_t RFind(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
    virtual int32_t RFind(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
    
    virtual cIGZString* Sprintf(char const* pszFormat, ...) = 0;
};

class cIGZIStream;
class cIGZPersistDBRecord;
class cIGZPersistDBSegment;
class cIGZSerializable;
class cIGZVariant;
class cISC4COMSerializer;
class cISC4DBSegment;
class cISC4DBSegmentIStream : public cIGZUnknown { };

struct cGZPersistResourceKey {
    uint32_t tid;
    uint32_t gid;
    uint32_t iid;
};

class cRZUnknown
{
public:
    virtual bool QueryInterface(uint32_t riid, void** ppvObj) = 0;
    virtual uint32_t AddRef(void) = 0;
    virtual uint32_t Release(void) = 0;
    
    virtual ~cRZUnknown();
    
    virtual uint32_t RemoveRef(void) = 0;
    virtual uint32_t RefCount(void) = 0;
    
protected:
    uint32_t mnRefCount;
};

#define GET_FIELD(x, y) virtual bool GetField ## x(y&) = 0; \
                        virtual bool GetField ## x(y*, uint32_t dwRepCount) = 0;

#define SET_FIELD(x, y) virtual bool SetField ## x(y&) = 0; \
                        virtual bool SetField ## x(y*, uint32_t dwRepCount) = 0;

#define GET_INT(x) GET_FIELD(Uint ## x, uint ## x ## _t); \
                   GET_FIELD(Sint ## x, int ## x ## _t);

#define SET_INT(x) SET_FIELD(Uint ## x, uint ## x ## _t); \
                   SET_FIELD(Sint ## x, int ## x ## _t);

class cIGZPersistDBSerialRecord : public cIGZUnknown
{
public:
    virtual cIGZPersistDBRecord* AsIGZPersistDBRecord(void) = 0;
    
    GET_INT(8)
    GET_INT(16)
    GET_INT(32)
    GET_INT(64)
    
    GET_FIELD(Float32, float)
    GET_FIELD(Float64, double)
    
    virtual bool GetFieldString(cIGZString&) = 0;
    virtual bool GetFieldResKey(cGZPersistResourceKey&) = 0;
    virtual bool GetFieldVariant(cIGZVariant**) = 0;
    virtual bool GetFieldVoid(void*, uint32_t) = 0;
    
    SET_INT(8)
    SET_INT(16)
    SET_INT(32)
    SET_INT(64)
    
    SET_FIELD(Float32, float)
    SET_FIELD(Float64, double)
    
    virtual bool SetFieldString(cIGZString const&) = 0;
    virtual bool SetFieldResKey(cGZPersistResourceKey const&) = 0;
    virtual bool SetFieldVariant(cIGZVariant const*) = 0;
    virtual bool SetFieldVoid(void const* uint32_t) = 0;
    
    virtual uint32_t GetSize(void) = 0;
    virtual bool SetSize(uint32_t) = 0;
    
    virtual uint32_t GetPosition(void) = 0;
    virtual bool SeekAbsolute(uint32_t) = 0;
    virtual bool SeekRelative(int32_t) = 0;
    
    virtual ~cIGZPersistDBSerialRecord();
};

class cIGZOStream : public cIGZUnknown
{
public:
    virtual void Flush(void) = 0;
    
    virtual bool SetSint8(int8_t cValue) = 0;
    virtual bool SetUint8(uint8_t ucValue) = 0;
    virtual bool SetSint16(int16_t sValue) = 0;
    virtual bool SetUint16(uint16_t usValue) = 0;
    virtual bool SetSint32(int32_t lValue) = 0;
    virtual bool SetUint32(uint32_t ulValue) = 0;
    virtual bool SetSint64(int64_t llValue) = 0;
    virtual bool SetUint64(uint64_t ullValue) = 0;
    virtual bool SetFloat32(float fValue) = 0;
    virtual bool SetFloat64(double dValue) = 0;
    virtual bool SetRZCharStr(char const* pszData) = 0;
    virtual bool SetGZStr(cIGZString const& szData) = 0;
    virtual bool SetGZSerializable(cIGZSerializable const& sData) = 0;
    virtual bool SetVoid(void const* pData, uint32_t dwSize) = 0;
    
    virtual int32_t GetError(void) = 0;
    virtual int32_t SetUserData(cIGZVariant* pData) = 0;
    virtual int32_t GetUserData(void) = 0;
};

class cISC4DBSegmentOStream : public cIGZOStream
{
public:
    virtual bool Open(cISC4DBSegment* pSegment, cGZPersistResourceKey const& key, bool bContinueFromEnd) = 0;
    virtual bool Close(void) = 0;
    virtual bool IsOpen(void) = 0;
    
    virtual cIGZPersistDBSerialRecord* GetRecord(void) = 0;
    virtual cISC4DBSegment* GetSegment(void) = 0;
    
    virtual bool WriteGZSerializable(cIGZSerializable const* pSerializable) = 0;
    virtual bool WriteResKey(cGZPersistResourceKey const& key) = 0;
    virtual bool WriteVariant(cIGZVariant const& variant) = 0;
};

class cISC4DBSegment : public cIGZUnknown
{
public:
    virtual cIGZPersistDBSegment* AsIGZPersistDBSegment(void) = 0;
    virtual cISC4COMSerializer* GetCOMSerializer(void) = 0;
    
    virtual bool OpenIStream(cGZPersistResourceKey const& key, cISC4DBSegmentIStream** ppStreamOut) = 0;
    virtual bool CloseIStream(cISC4DBSegmentIStream* pStream) = 0;
    
    virtual bool LoadClassObjects(void) = 0;
    
    virtual bool OpenOStream(cGZPersistResourceKey const& key, cISC4DBSegmentOStream** ppStreamOut, bool bContinueFromEnd) = 0;
    virtual bool CloseOStream(cISC4DBSegmentOStream* pStream) = 0;
    
    virtual bool SaveClassObjects(void) = 0;
    
    virtual uint32_t GetLastError(void) = 0;
    
    virtual float GetPercentageCompletion(void) = 0;
    virtual bool SetPercentageCompletion(float fCompletion) = 0;
};

class cISC4COMSerializer : public cIGZUnknown
{
public:
    virtual bool Open(cISC4DBSegment* pSegment, int32_t nMode) = 0;
    virtual bool Close(void) = 0;
    
    virtual int32_t GetMode(void) = 0;
    
    virtual bool LoadClassObjects(void) = 0;
    virtual bool SaveClassObjects(void) = 0;
    
    virtual bool WriteGZSerializable(cIGZOStream& out, cIGZSerializable const* pData) = 0;
    virtual bool ReadGZSerializable(cIGZIStream& in, cIGZSerializable** ppOutArray, bool bSingleObject) = 0;
};

class cIGZSerializable : public cIGZUnknown
{
public:
    virtual bool Write(cIGZOStream& gzOut) = 0;
    virtual bool Read(cIGZIStream& gzIn) = 0;
    virtual int32_t GetGZCLSID(void) = 0;
};

void* pRealFree;
void* pRealMapOperatorEq;

void __declspec(naked) __fastcall FreeMap(void* pUnknown) {
	_asm push ebp
	_asm mov ebp, esp

	_asm push ecx
	_asm call pRealFree
	_asm add esp, 4h
	
	_asm mov esp, ebp
	_asm pop ebp
	_asm retn
}

void __declspec(naked) __fastcall MapOperatorEq(void* left, void* right) {
	_asm push ebp
	_asm mov ebp, esp

	_asm push edx
	_asm call pRealMapOperatorEq

	_asm mov esp, ebp
	_asm pop ebp
	_asm retn
}

template<typename Key, typename Value>
struct SC4Win32Map
{
public:
	typedef eastl::pair<Key, Value> pair_type;
	typedef eastl::rbtree_node<pair_type> node_type;
	typedef eastl::rbtree_iterator<pair_type, pair_type*, pair_type&> iterator;
	typedef eastl::rbtree_iterator<pair_type, const pair_type*, const pair_type&> const_iterator;
	typedef SC4Win32Map<Key, Value> this_type;

	eastl::rbtree_node_base* mpAnchor;
	size_t mnSize;
	uint32_t dwUnknown; // mAllocator?

	iterator begin() noexcept {
		return iterator(static_cast<node_type*>(mpAnchor->mpNodeLeft));
	}

	iterator end() noexcept {
		return iterator(static_cast<node_type*>(mpAnchor));
	}

	iterator erase(const_iterator position) {
		const iterator iErase(position.mpNode);
		--mnSize; // Interleave this between the two references to itNext. We expect no exceptions to occur during the code below.
		++position;
		RBTreeErase(iErase.mpNode, mpAnchor);
		DoFreeNode(iErase.mpNode);
		return iterator(position.mpNode);
	}

	bool empty() noexcept {
		return mnSize == 0;
	}

	const size_t size() const noexcept {
		return mnSize;
	}

	this_type& operator=(const this_type& x);

protected:
	void DoFreeNode(node_type* pNode) {
		pNode->~node_type();

		// TODO: put this in an allocator
		cIGZUnknown* pUnknown = (cIGZUnknown*)pNode->mValue.second.pSerializable;
		if (pUnknown)
			pUnknown->Release();

		FreeMap(pNode);
	}
};

class cSC4COMSerializer : public cISC4COMSerializer
{
public:
    virtual bool Open(cISC4DBSegment* pSegment, int32_t nMode);
    virtual bool Close(void);
    
    virtual int32_t GetMode(void);
    
    virtual bool LoadClassObjects(void);
    virtual bool SaveClassObjects(void);
    
    virtual bool WriteGZSerializable(cIGZOStream& out, cIGZSerializable const* pData);
    virtual bool ReadGZSerializable(cIGZIStream& in, cIGZSerializable** ppOutArray, bool bSingleObject);
    
public:
	bool __thiscall SaveClassObjectsImpl(void);

public:
    struct cIDInfo
    {
        cIGZSerializable *pSerializable;
    };
    
    struct cClassInfo
    {
        uint32_t dwUnknown1;
        uint32_t dwUnknown2;
		SC4Win32Map<uint32_t, cIDInfo> dataPendingWrite;
    };
    
    int8_t byteUnknown1; // 4-5
    
    int8_t __align_1[3]; // 5-8
	SC4Win32Map<uint32_t, cClassInfo> tempClassMap; // 8-20
	SC4Win32Map<uint32_t, cClassInfo> realClassMap; // 20-32
    uint32_t dwMode; // 32-36
    uint32_t dwTotalObjects; // 36-40
    uint8_t byteAlreadyRead; // 40-41
    uint8_t byteAlreadyWritten; // 41-42
    uint8_t __align_2[2]; // 42-44
    cISC4DBSegment* pOpenSegment; // 44-48
};

static const unsigned int crc32_table[] =
{
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
    0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
    0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
    0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
    0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
    0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
    0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
    0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
    0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
    0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
    0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
    0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
    0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
    0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
    0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
    0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
    0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
    0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
    0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
    0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
    0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
    0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
    0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
    0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
    0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
    0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
    0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
    0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
    0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
    0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
    0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
    0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
    0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
    0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
    0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
    0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
    0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
    0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
    0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
    0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
    0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
    0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
    0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
    0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
    0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
    0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
    0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
    0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
    0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
    0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
    0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
    0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
    0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
    0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

unsigned int xcrc32 (const unsigned char *buf, int len)
{
    unsigned int crc = 0xFFFFFFFF;
    while (len--)
    {
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *buf) & 255];
        buf++;
    }
    return crc;
}

//#define DEBUG
#ifdef DEBUG
void PRINTDBG(const char* pszFormat, ...) {
	static FILE* fp = NULL;
	errno_t fopen_res;

	if (!fp) {
		fopen_res = fopen_s(&fp, "serialize.log", "w");
		if (fopen_res != 0)
			MessageBoxA(NULL, "Failed to PRINTDBG to serialization log", NULL, NULL);
	}

	va_list args;
	va_start(args, pszFormat);
	vfprintf_s(fp, pszFormat, args);
	va_end(args);
}
#else
#define PRINTDBG(...)
#endif

bool __thiscall cSC4COMSerializer::SaveClassObjectsImpl()
{
    if (this->dwMode != kModeWrite || this->byteAlreadyWritten || (!this->byteAlreadyRead && this->realClassMap.empty())) {
        //PRINTDBG("[COMSerialize] Write deemed unnecessary, bailing\n\n");
        return true;
    }

	PRINTDBG("\n[COMSerialize] Inside our serialization override\n");
	PRINTDBG("[COMSerialize] dwMode: %u, byteAlreadyWritten: %u\n", this->dwMode, this->byteAlreadyWritten);
	PRINTDBG("[COMSerialize] byteAlreadyRead: %u, realClassMap.empty(): %u\n", this->byteAlreadyRead, this->realClassMap.empty());
    PRINTDBG("[COMSerialize] Write mode confirmed\n");

    this->byteUnknown1 = 1;
    //this->tempClassMap = this->realClassMap;
	MapOperatorEq(&this->tempClassMap, &this->realClassMap);
    
    cISC4DBSegmentOStream* pOutStream = NULL;
    
    uint32_t dwNumWritten = 0;
    uint32_t dwNumTotal = 0;
    
    PRINTDBG("[COMSerialize] Preparing to write %u objects\n", this->dwTotalObjects);
    
    while (dwNumTotal != this->dwTotalObjects) {
        PRINTDBG("[COMSerialize] In loop reentrance point\n");
        
        auto it = this->tempClassMap.begin();
        while (it != this->tempClassMap.end()) {
            cSC4COMSerializer::cClassInfo& info = it->second;
            cGZPersistResourceKey key;
            
            key.tid = it->first;
            key.gid = kCOMSerializedGID;
            key.iid = 0;
            
            if (!info.dataPendingWrite.empty()) {
                PRINTDBG("[COMSerialize]    |-- Serializing t=0x%x, g=0x%x, i=0x%x\n", key.tid, key.gid, key.iid);
                PRINTDBG("[COMSerialize]    |-- First CID: 0x%x\n", info.dataPendingWrite.begin()->first);
                
                if (pOutStream) {
                    PRINTDBG("[COMSerialize]        |-- Releasing existing output stream\n");
                    pOutStream->Release();
                    pOutStream = NULL;
                }
                
                if (!this->pOpenSegment->OpenOStream(key, &pOutStream, false)) {
                    PRINTDBG("[COMSerialize]        |-- Failed to open output stream\n");
                    goto fail;
                }
                
                cIGZPersistDBSerialRecord* pRecord = pOutStream->GetRecord();
                auto it2 = info.dataPendingWrite.begin();
				uint32_t erased = 0;
				uint32_t size = info.dataPendingWrite.size();
                
                while (it2 != info.dataPendingWrite.end()) {
                    uint32_t dwPosition = pRecord->GetPosition();
                    
                    PRINTDBG("[COMSerialize]        |-- Writing CID 0x%x\n", it2->first);
                    PRINTDBG("[COMSerialize]            |-- Current position: 0x%x\n", dwPosition);
                    
                    pOutStream->SetUint32(0); // Will write size later
                    pOutStream->SetUint32(0); // Will write CRC32 later
                    pOutStream->SetUint32(it2->first);
                    
                    if (it2->second.pSerializable->Write(*pOutStream)) {
                        uint32_t dwNewPosition = pRecord->GetPosition();
                        uint32_t dwSize = dwNewPosition - dwPosition;
                        
                        PRINTDBG("[COMSerialize]            |-- New position: 0x%x (size: 0x%x)\n", dwNewPosition, dwSize);
                        
                        pRecord->SeekAbsolute(dwPosition);
                        pOutStream->SetUint32(dwSize);
                        
                        pRecord->SeekAbsolute(dwPosition + 8);
                        
                        uint32_t dwCRCSize = dwSize - 8;
                        if (dwCRCSize > kMaxCRCDataLength)
                            dwCRCSize = kMaxCRCDataLength;
                        
                        uint32_t dwCRC32 = 0;
                        std::vector<uint8_t> crcBytes;
                        
                        crcBytes.resize(dwCRCSize + 1);
                        
                        if (pRecord->GetFieldVoid(&crcBytes[0], dwCRCSize))
                            dwCRC32 = xcrc32(&crcBytes[0], dwCRCSize);

                        pRecord->SeekAbsolute(dwPosition + 4);
                        pOutStream->SetUint32(dwCRC32);
                        
                        pRecord->SeekAbsolute(dwNewPosition);
                        ++dwNumWritten;
                        
                        fprintf(stderr,
                                "[COMSerialize]            |-- Finished rewriting CRC (0x%x) and size, new position: 0x%x\n",
                                dwCRC32, pRecord->GetPosition());
                    }
                    else {
                        PRINTDBG("[COMSerialize]            |-- Failed to write this entry\n");
                        pRecord->SeekAbsolute(dwPosition);
                    }
                    
                    ++dwNumTotal;
                    it2 = info.dataPendingWrite.erase(it2);
					++erased;
                    
                    PRINTDBG("[COMSerialize]        |-- Serialization progress: %u / %u\n", dwNumTotal, this->dwTotalObjects);
                    
                    if (pOutStream->GetError()) {
                        PRINTDBG("[COMSerialize] Write error %x encountered, bailing\n", pOutStream->GetError());
                        this->pOpenSegment->CloseOStream(pOutStream);
                        goto fail;
                    }
                    
                }
                
                if (!this->pOpenSegment->CloseOStream(pOutStream)) {
                    PRINTDBG("[COMSerialize] Failed to close output stream, bailing\n");
                    goto fail;
                }
            }
            else
                PRINTDBG("[COMSerialize] SKIPPING t=0x%x, g=0x%x, i=0x%x with no data available to write\n", key.tid, key.gid, key.iid);
            
            ++it;
        }
        
        this->pOpenSegment->SetPercentageCompletion(((float)dwNumWritten * 100.0f) / ((float)this->dwTotalObjects));
    }
    
    this->byteUnknown1 = 0;
    
    cGZPersistResourceKey key;
    key.tid = 0x499b23fe;
    key.gid = kCOMSerializedGID;
    key.iid = 0;
    
    if (pOutStream) {
        pOutStream->Release();
        pOutStream = NULL;
    }
    
    if (!this->pOpenSegment->OpenOStream(key, &pOutStream, true))
        goto end;
    
    pOutStream->SetUint32(1);
    pOutStream->SetUint32((uint32_t)this->realClassMap.size());
    pOutStream->SetSint32(dwNumWritten);
    
    for (auto it = this->realClassMap.begin(); it != this->realClassMap.end(); ++it) {
        pOutStream->SetUint32(it->first);
        pOutStream->SetUint32((uint32_t)it->second.dwUnknown2);
    }
    
    if (this->pOpenSegment->CloseOStream(pOutStream) && !pOutStream->GetError()) {
    end:
        this->byteAlreadyWritten = 1;
        if (pOutStream)
            pOutStream->Release();
        
        PRINTDBG("[COMSerialize] Exiting successfully\n\n");
        return true;
    }
    
fail:
    if (pOutStream)
        pOutStream->Release();

    PRINTDBG("[COMSerialize] Exiting with error status\n\n");
    return false;
}

//--- PATCH THE SC4COMSERIALIZER ---------------------------
// Points SC4COMSerializer::SaveClassObjects to our
// reimplementation instead of the standard implementation
// which seems to have issues seeking when redefined Maxis
// TGIs are present
//----------------------------------------------------------
static union hook_shim_t {
	bool (cSC4COMSerializer::*pfnSave)(void) = &cSC4COMSerializer::SaveClassObjectsImpl;
	void (*pfnVoid)(void);
} hook_shim;

static_assert(sizeof(hook_shim_t::pfnSave) == sizeof(hook_shim_t::pfnVoid),
	"sizeof(pfnSave) != sizeof(pfnVoid), is cSC4COMSerializer using multiple inheritance?");

void PropPoxVaccine::InstallPatch(void) {
	switch (GetGameVersion()) {
	case 640:
		CPatcher::InstallHook(0x5D3B60, hook_shim.pfnVoid);
		pRealFree = (void*)0x90D009;
		pRealMapOperatorEq = (void*)0x5D3050;
		break;

	case 641:
		CPatcher::InstallHook(0x5D3DE0, hook_shim.pfnVoid);
		pRealFree = (void*)0x90CF63;
		pRealMapOperatorEq = (void*)0x5D32D0;
		break;

	default:
		break;
	}
}