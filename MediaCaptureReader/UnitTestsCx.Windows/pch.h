#pragma once

#include "targetver.h"

#include "CppUnitTest.h"

#include <collection.h>
#include <ppltasks.h>
#include <algorithm>

#include <robuffer.h>

#include "Await.h"

//
// Error handling
//

// Exception-based error handling
#define CHK(statement)  {HRESULT _hr = (statement); if (FAILED(_hr)) { throw ref new Platform::COMException(_hr); };}
#define CHKNULL(p)  {if ((p) == nullptr) { throw ref new Platform::NullReferenceException(L#p); };}
#define CHKOOM(p)  {if ((p) == nullptr) { throw ref new Platform::OutOfMemoryException(L#p); };}

//
// IBuffer data access
//

inline unsigned char* GetData(Windows::Storage::Streams::IBuffer^ buffer)
{
    unsigned char* bytes = nullptr;
    Microsoft::WRL::ComPtr<::Windows::Storage::Streams::IBufferByteAccess> bufferAccess;
    CHK(((IUnknown*)buffer)->QueryInterface(IID_PPV_ARGS(&bufferAccess)));
    CHK(bufferAccess->Buffer(&bytes));
    return bytes;
}

namespace WSS = ::Windows::Storage::Streams;