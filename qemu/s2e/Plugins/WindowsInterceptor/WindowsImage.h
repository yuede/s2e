/**
 *  Defines structures and utility classes to parse
 *  windows PE images.
 */

#ifndef _WINDOWS_IMAGE_H_

#define _WINDOWS_IMAGE_H_

#include <inttypes.h>
#include <map>
#include <string>

namespace s2e {
namespace windows {

#define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
#define IMAGE_NT_SIGNATURE                  0x00004550  // PE00

typedef struct IMAGE_DOS_HEADER {      // DOS .EXE header
    uint16_t   e_magic;                     // Magic number
    uint16_t   e_cblp;                      // Bytes on last page of file
    uint16_t   e_cp;                        // Pages in file
    uint16_t   e_crlc;                      // Relocations
    uint16_t   e_cparhdr;                   // Size of header in paragraphs
    uint16_t   e_minalloc;                  // Minimum extra paragraphs needed
    uint16_t   e_maxalloc;                  // Maximum extra paragraphs needed
    uint16_t   e_ss;                        // Initial (relative) SS value
    uint16_t   e_sp;                        // Initial SP value
    uint16_t   e_csum;                      // Checksum
    uint16_t   e_ip;                        // Initial IP value
    uint16_t   e_cs;                        // Initial (relative) CS value
    uint16_t   e_lfarlc;                    // File address of relocation table
    uint16_t   e_ovno;                      // Overlay number
    uint16_t   e_res[4];                    // Reserved uint16_ts
    uint16_t   e_oemid;                     // OEM identifier (for e_oeminfo)
    uint16_t   e_oeminfo;                   // OEM information; e_oemid specific
    uint16_t   e_res2[10];                  // Reserved uint16_ts
    int32_t    e_lfanew;                    // File address of new exe header
  }__attribute__ ((packed)) IMAGE_DOS_HEADER;

typedef struct IMAGE_FILE_HEADER {	//20 bytes
    uint16_t    Machine;
    uint16_t    NumberOfSections;
    uint32_t   TimeDateStamp;
    uint32_t   PointerToSymbolTable;
    uint32_t   NumberOfSymbols;
    uint16_t    SizeOfOptionalHeader;
    uint16_t    Characteristics;
} __attribute__ ((packed)) IMAGE_FILE_HEADER;

#define IMAGE_SIZEOF_FILE_HEADER             20


#if 0
#define IMAGE_FILE_RELOCS_STRIPPED           0x0001  // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE          0x0002  // File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED        0x0004  // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED       0x0008  // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM         0x0010  // Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE       0x0020  // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO         0x0080  // Bytes of machine uint16_t are reversed.
#define IMAGE_FILE_32BIT_MACHINE             0x0100  // 32 bit uint16_t machine.
#define IMAGE_FILE_DEBUG_STRIPPED            0x0200  // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   0x0400  // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP         0x0800  // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM                    0x1000  // System File.
#define IMAGE_FILE_DLL                       0x2000  // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY            0x4000  // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI         0x8000  // Bytes of machine uint16_t are reversed.

#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
#endif
//
// Directory format.
//

typedef struct IMAGE_DATA_DIRECTORY {
    uint32_t   VirtualAddress;
    uint32_t   Size;
} __attribute__ ((packed)) IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

//
// Optional header format.
//

typedef struct IMAGE_OPTIONAL_HEADER {			//96 + ... bytes
    //
    // Standard fields.
    //

    uint16_t    Magic;
    uint8_t    MajorLinkerVersion;
    uint8_t    MinorLinkerVersion;
    uint32_t   SizeOfCode;
    uint32_t   SizeOfInitializedData;
    uint32_t   SizeOfUninitializedData;
    uint32_t   AddressOfEntryPoint;			//+16 bytes
    uint32_t   BaseOfCode;
    uint32_t   BaseOfData;

    //
    // NT additional fields.
    //

    uint32_t   ImageBase;
    uint32_t   SectionAlignment;
    uint32_t   FileAlignment;
    uint16_t    MajorOperatingSystemVersion;
    uint16_t    MinorOperatingSystemVersion;
    uint16_t    MajorImageVersion;
    uint16_t    MinorImageVersion;
    uint16_t    MajorSubsystemVersion;
    uint16_t    MinorSubsystemVersion;
    uint32_t   Win32VersionValue;
    uint32_t   SizeOfImage;
    uint32_t   SizeOfHeaders;
    uint32_t   CheckSum;
    uint16_t    Subsystem;
    uint16_t    DllCharacteristics;
    uint32_t   SizeOfStackReserve;
    uint32_t   SizeOfStackCommit;
    uint32_t   SizeOfHeapReserve;
    uint32_t   SizeOfHeapCommit;
    uint32_t   LoaderFlags;
    uint32_t   NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} __attribute__ ((packed)) IMAGE_OPTIONAL_HEADER;


typedef struct IMAGE_NT_HEADERS {				//
    uint32_t Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
} __attribute__ ((packed)) IMAGE_NT_HEADERS;

typedef struct IMAGE_ROM_OPTIONAL_HEADER {
    uint16_t   Magic;
    uint8_t   MajorLinkerVersion;
    uint8_t   MinorLinkerVersion;
    uint32_t  SizeOfCode;
    uint32_t  SizeOfInitializedData;
    uint32_t  SizeOfUninitializedData;
    uint32_t  AddressOfEntryPoint;
    uint32_t  BaseOfCode;
    uint32_t  BaseOfData;
    uint32_t  BaseOfBss;
    uint32_t  GprMask;
    uint32_t  CprMask[4];
    uint32_t  GpValue;
} __attribute__ ((packed)) IMAGE_ROM_OPTIONAL_HEADER;


#define IMAGE_SIZEOF_ROM_OPTIONAL_HEADER      56
#define IMAGE_SIZEOF_STD_OPTIONAL_HEADER      28
#define IMAGE_SIZEOF_NT_OPTIONAL32_HEADER    224
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER    240

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b
#define IMAGE_ROM_OPTIONAL_HDR_MAGIC       0x107


#define IMAGE_SIZEOF_SHORT_NAME              8

typedef struct IMAGE_SECTION_HEADER {
    uint8_t    Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
            uint32_t   PhysicalAddress;
            uint32_t   VirtualSize;
    } Misc;
    uint32_t   VirtualAddress;
    uint32_t   SizeOfRawData;
    uint32_t   PointerToRawData;
    uint32_t   PointerToRelocations;
    uint32_t   PointerToLinenumbers;
    uint16_t    NumberOfRelocations;
    uint16_t    NumberOfLinenumbers;
    uint32_t   Characteristics;
}  __attribute__ ((packed)) IMAGE_SECTION_HEADER;

#define IMAGE_SIZEOF_SECTION_HEADER          40

// Directory Entries

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor


//
// DLL support.
//

//
// Export Format
//

typedef struct IMAGE_EXPORT_DIRECTORY {
    uint32_t   Characteristics;
    uint32_t   TimeDateStamp;
    uint16_t    MajorVersion;
    uint16_t    MinorVersion;
    uint32_t   Name;
    uint32_t   Base;
    uint32_t   NumberOfFunctions;
    uint32_t   NumberOfNames;
    uint32_t   AddressOfFunctions;     // RVA from base of image
    uint32_t   AddressOfNames;         // RVA from base of image
    uint32_t   AddressOfNameOrdinals;  // RVA from base of image
} __attribute__ ((packed)) IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

//
// Import Format
//

typedef struct IMAGE_IMPORT_BY_NAME {
    uint16_t    Hint;
    uint8_t    Name[1];
} __attribute__ ((packed)) IMAGE_IMPORT_BY_NAME;

#ifndef IMAGE_ORDINAL_FLAG
#define IMAGE_ORDINAL_FLAG  0x80000000
#endif

typedef struct IMAGE_THUNK_DATA {
    union {
        uint32_t ForwarderString; //PBYTE
        uint32_t Function; //Puint32_t
        uint32_t Ordinal;
        uint32_t AddressOfData; //IMAGE_IMPORT_BY_NAME  *
    } u1;
} __attribute__ ((packed)) IMAGE_THUNK_DATA, *PIMAGE_THUNK_DATA, IMAGE_THUNK_DATA32, *PIMAGE_THUNK_DATA32;

typedef IMAGE_THUNK_DATA * PIMAGE_THUNK_DATA;

typedef struct IMAGE_IMPORT_DESCRIPTOR {
    union {
        uint32_t   Characteristics;            // 0 for terminating null import descriptor
        uint32_t   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    };
    uint32_t   TimeDateStamp;                  // 0 if not bound,
                                            // -1 if bound, and real date\time stamp
                                            //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                            // O.W. date/time stamp of DLL bound to (Old BIND)

    uint32_t   ForwarderChain;                 // -1 if no forwarders
    uint32_t   Name;
    uint32_t   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} __attribute__ ((packed))IMAGE_IMPORT_DESCRIPTOR, *PIMAGE_IMPORT_DESCRIPTOR;


//
// Based relocation format.
//

typedef struct IMAGE_BASE_RELOCATION {
    uint32_t   VirtualAddress;
    uint32_t   SizeOfBlock;
//  uint16_t    TypeOffset[1];
} __attribute__ ((packed)) IMAGE_BASE_RELOCATION;

typedef IMAGE_BASE_RELOCATION * PIMAGE_BASE_RELOCATION;

#define IMAGE_SIZEOF_BASE_RELOCATION         8

//
// Based relocation types.
//

#define IMAGE_REL_BASED_ABSOLUTE              0
#define IMAGE_REL_BASED_HIGH                  1
#define IMAGE_REL_BASED_LOW                   2
#define IMAGE_REL_BASED_HIGHLOW               3
#define IMAGE_REL_BASED_HIGHADJ               4
#define IMAGE_REL_BASED_MIPS_JMPADDR          5
#define IMAGE_REL_BASED_SECTION               6
#define IMAGE_REL_BASED_REL32                 7

#define IMAGE_REL_BASED_MIPS_JMPADDR16        9
#define IMAGE_REL_BASED_IA64_IMM64            9
#define IMAGE_REL_BASED_DIR64                 10
#define IMAGE_REL_BASED_HIGH3ADJ              11

typedef struct IMAGE_RELOC_TYPE
{
	unsigned offset:12;
	unsigned type:4;


}__attribute__((packed))IMAGE_RELOC_TYPE;

/****************************************************************/
/****************************************************************/
/****************************************************************/

/*typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR  Buffer;
}UNICODE_STRING, *PUNICODE_STRING;*/

typedef struct _UNICODE_STRING32 {
  uint16_t Length;
  uint16_t MaximumLength;
  uint32_t  Buffer;
}UNICODE_STRING32, *PUNICODE_STRING32;

typedef struct _LIST_ENTRY32 {
    uint32_t Flink;
    uint32_t Blink;
}LIST_ENTRY32, *PLIST_ENTRY32;

#define CONTAINING_RECORD32(address, type, field) ((uint32_t)( \
                                                  (uint32_t)(address) - \
                                                  (uint32_t)(uint64_t)(&((type *)0)->field)))

typedef int32_t NTSTATUS; //MUST BE SIGNED

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define NT_INFORMATION(Status) ((ULONG)(Status) >> 30 == 1)
#define NT_WARNING(Status) ((ULONG)(Status) >> 30 == 2)
#define NT_ERROR(Status) ((ULONG)(Status) >> 30 == 3)

typedef struct _MODULE_ENTRY32
{
	LIST_ENTRY32 le_mod;
	uint32_t  unknown[4];
	uint32_t  base;
	uint32_t  driver_start;
	uint32_t  unk1;
	UNICODE_STRING32 driver_Path;
	UNICODE_STRING32 driver_Name;
} MODULE_ENTRY32, *PMODULE_ENTRY32;

typedef struct _DRIVER_OBJECT32
{
  uint16_t Type;
  uint16_t Size;

  uint32_t DeviceObject; //PVOID
  uint32_t Flags;

  uint32_t DriverStart; //PVOID
  uint32_t DriverSize; //PVOID
  uint32_t DriverSection; //PVOID
  UNICODE_STRING32 DriverName;
}DRIVER_OBJECT32, *PDRIVER_OBJECT32;

#define KPCR_OFFSET 0xFFDFF000
#define KD_VERSION_BLOCK (KPCR_OFFSET + 0x34)
#define PS_LOADED_MODULE_LIST_OFFSET 0x70 //Inside the kd version block
#define KPRCB_OFFSET 0xFFDFF120
#define IRQL_OFFSET 0xFFDFF124
#define PEB_OFFSET 0x7FFDF000
typedef uint32_t KAFFINITY;

typedef struct _LDR_DATA_TABLE_ENTRY32
{
     LIST_ENTRY32 InLoadOrderLinks;
     LIST_ENTRY32 InMemoryOrderLinks;
     LIST_ENTRY32 InInitializationOrderLinks;
     uint32_t DllBase;
     uint32_t EntryPoint;
     uint32_t SizeOfImage;
     UNICODE_STRING32 FullDllName;
     UNICODE_STRING32 BaseDllName;
     uint32_t Flags;
     uint16_t LoadCount;
     uint16_t TlsIndex;
     union
     {
          LIST_ENTRY32 HashLinks;
          struct
          {
               uint32_t SectionPointer;
               uint32_t CheckSum;
          };
     };
     union
     {
          uint32_t TimeDateStamp;
          uint32_t LoadedImports;
     };
     uint32_t EntryPointActivationContext;
     uint32_t PatchInformation;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;


typedef struct _PEB_LDR_DATA32
{
  uint32_t Length;
  uint32_t Initialized;
  uint32_t SsHandle;
  LIST_ENTRY32 InLoadOrderModuleList;
  LIST_ENTRY32 InMemoryOrderModuleList;
  uint32_t EntryInProgress;
}PEB_LDR_DATA32;

typedef struct _PEB32 {
  uint8_t Unk1[0x8];
  uint32_t ImageBaseAddress;
  uint32_t Ldr; /* PEB_LDR_DATA */
}PEB32;


typedef struct _KPROCESS32 {
  uint8_t Unk1[0x18];
  uint32_t DirectoryTableBase;
  uint8_t Unk2[0x50];
}KPROCESS32;

typedef struct _EPROCESS32 {
  KPROCESS32 Pcb;
  uint8_t Unk1[0x1C];
  LIST_ENTRY32 ActiveProcessLinks;
  uint8_t Unk2[0xE4];
  uint8_t ImageFileName[16]; //offset 0x174
}EPROCESS32;

typedef struct _KAPC_STATE32 {
  LIST_ENTRY32 ApcListHead[2];
  uint32_t Process;  /* Ptr to (E)KPROCESS */
  uint8_t KernelApcInProgress;
  uint8_t KernelApcPending;
  uint8_t UserApcPending;
}KAPC_STATE32;

typedef struct _KTHREAD32
{
  uint8_t Unk1[0x18];
  uint32_t InitialStack;
  uint32_t StackLimit;
  uint8_t Unk2[0x14];
  KAPC_STATE32 ApcState;

}KTHREAD32;

typedef struct _KPRCB32 {
    uint16_t MinorVersion;
    uint16_t MajorVersion;
    uint32_t CurrentThread;
    uint32_t NextThread;
    uint32_t IdleThread;
/*    CCHAR Number;
    CCHAR WakeIdle;
    USHORT BuildType;
    KAFFINITY SetMember;
    DWORD32  RestartBlock;
    ULONG_PTR PcrPage;
    ULONG Spare0[4];

    ULONG     ProcessorModel;
    ULONG     ProcessorRevision;
    ULONG     ProcessorFamily;
    ULONG     ProcessorArchRev;
    ULONGLONG ProcessorSerialNumber;
    ULONGLONG ProcessorFeatureBits;
    UCHAR     ProcessorVendorString[16];

    ULONGLONG SystemReserved[8];

    ULONGLONG HalReserved[16]; */

} KPRCB32;




} //namespace windows
} //namespace s2e

/****************************************************************/
/****************************************************************/
/****************************************************************/

#include <s2e/Plugins/ExecutableImage.h>
#include <s2e/Plugins/ModuleDescriptor.h>

namespace s2e
{
namespace plugins
{

class WindowsImage:IExecutableImage
{

private:
  s2e::windows::IMAGE_DOS_HEADER DosHeader;
  s2e::windows::IMAGE_NT_HEADERS NtHeader;
  
  uint64_t m_Base;
  uint64_t m_ImageBase;
  uint64_t m_EntryPoint;
  unsigned m_ImageSize;

  /* Stores the relative addresses of all exported functions */
  Exports m_Exports;
  bool m_ExportsInited;
  
  /* We assume for now that there are no name collisions between
   * function with the same name in different libraries */
  Imports m_Imports;
  bool m_ImportsInited;

  int InitImports();
  int InitExports();

  static bool IsValidString(const char *str);
public:
  WindowsImage(uint64_t Base);

  virtual uint64_t GetBase() const { 
    return m_Base;
  }

  virtual uint64_t GetImageBase() const {
    return m_ImageBase;
  }

  virtual uint64_t GetImageSize() const {
    return m_ImageSize;
  }

  virtual uint64_t GetEntryPoint() const {
    return m_EntryPoint;
  }

  virtual uint64_t GetRoundedImageSize() const {
    if (m_ImageSize & 0xFFF)
      return (m_ImageSize & ~0xFFF) + 0x1000;
    else
      return m_ImageSize;
  }


  virtual const Exports& GetExports() {
      if (!m_ExportsInited) {
          InitExports();
          m_ExportsInited = true;
      }
      return m_Exports; 
  }

  virtual const Imports& GetImports() {
      if (!m_ImportsInited) {
        InitImports();
        m_ImportsInited = true;
      }
      return m_Imports;
  }
  
  virtual void DumpInfo(std::iostream &os) const;

  
};

}

}
#endif
