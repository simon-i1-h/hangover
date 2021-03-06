/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <usp10.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_GetEnhMetaFileA
{
    struct qemu_syscall super;
    uint64_t lpszMetaFile;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI GetEnhMetaFileA(LPCSTR lpszMetaFile)
{
    struct qemu_GetEnhMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEA);
    call.lpszMetaFile = (ULONG_PTR)lpszMetaFile;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetEnhMetaFileA(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileA *c = (struct qemu_GetEnhMetaFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GetEnhMetaFileA(QEMU_G2H(c->lpszMetaFile));
}

#endif

struct qemu_GetEnhMetaFileW
{
    struct qemu_syscall super;
    uint64_t lpszMetaFile;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI GetEnhMetaFileW(LPCWSTR lpszMetaFile)
{
    struct qemu_GetEnhMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEW);
    call.lpszMetaFile = (ULONG_PTR)lpszMetaFile;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetEnhMetaFileW(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileW *c = (struct qemu_GetEnhMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GetEnhMetaFileW(QEMU_G2H(c->lpszMetaFile));
}

#endif

struct qemu_GetEnhMetaFileHeader
{
    struct qemu_syscall super;
    uint64_t hmf;
    uint64_t bufsize;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetEnhMetaFileHeader(HENHMETAFILE hmf, UINT bufsize, LPENHMETAHEADER buf)
{
    struct qemu_GetEnhMetaFileHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEHEADER);
    call.hmf = (ULONG_PTR)hmf;
    call.bufsize = (ULONG_PTR)bufsize;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnhMetaFileHeader(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileHeader *c = (struct qemu_GetEnhMetaFileHeader *)call;
    WINE_TRACE("\n");
    c->super.iret = GetEnhMetaFileHeader(QEMU_G2H(c->hmf), c->bufsize, QEMU_G2H(c->buf));
}

#endif

struct qemu_GetEnhMetaFileDescriptionA
{
    struct qemu_syscall super;
    uint64_t hmf;
    uint64_t size;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetEnhMetaFileDescriptionA(HENHMETAFILE hmf, UINT size, LPSTR buf)
{
    struct qemu_GetEnhMetaFileDescriptionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEDESCRIPTIONA);
    call.hmf = (ULONG_PTR)hmf;
    call.size = (ULONG_PTR)size;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnhMetaFileDescriptionA(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileDescriptionA *c = (struct qemu_GetEnhMetaFileDescriptionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEnhMetaFileDescriptionA(QEMU_G2H(c->hmf), c->size, QEMU_G2H(c->buf));
}

#endif

struct qemu_GetEnhMetaFileDescriptionW
{
    struct qemu_syscall super;
    uint64_t hmf;
    uint64_t size;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetEnhMetaFileDescriptionW(HENHMETAFILE hmf, UINT size, LPWSTR buf)
{
    struct qemu_GetEnhMetaFileDescriptionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEDESCRIPTIONW);
    call.hmf = (ULONG_PTR)hmf;
    call.size = (ULONG_PTR)size;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnhMetaFileDescriptionW(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileDescriptionW *c = (struct qemu_GetEnhMetaFileDescriptionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEnhMetaFileDescriptionW(QEMU_G2H(c->hmf), c->size, QEMU_G2H(c->buf));
}

#endif

struct qemu_SetEnhMetaFileBits
{
    struct qemu_syscall super;
    uint64_t bufsize;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI SetEnhMetaFileBits(UINT bufsize, const BYTE *buf)
{
    struct qemu_SetEnhMetaFileBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENHMETAFILEBITS);
    call.bufsize = (ULONG_PTR)bufsize;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetEnhMetaFileBits(struct qemu_syscall *call)
{
    struct qemu_SetEnhMetaFileBits *c = (struct qemu_SetEnhMetaFileBits *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)SetEnhMetaFileBits(c->bufsize, QEMU_G2H(c->buf));
}

#endif

struct qemu_GetEnhMetaFileBits
{
    struct qemu_syscall super;
    uint64_t hmf;
    uint64_t bufsize;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetEnhMetaFileBits(HENHMETAFILE hmf, UINT bufsize, LPBYTE buf)
{
    struct qemu_GetEnhMetaFileBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEBITS);
    call.hmf = (ULONG_PTR)hmf;
    call.bufsize = (ULONG_PTR)bufsize;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnhMetaFileBits(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFileBits *c = (struct qemu_GetEnhMetaFileBits *)call;
    WINE_TRACE("\n");
    c->super.iret = GetEnhMetaFileBits(QEMU_G2H(c->hmf), c->bufsize, QEMU_G2H(c->buf));
}

#endif

struct qemu_PlayEnhMetaFileRecord
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t handletable;
    uint64_t mr;
    uint64_t handles;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PlayEnhMetaFileRecord(HDC hdc, LPHANDLETABLE handletable, const ENHMETARECORD *mr, UINT handles)
{
    struct qemu_PlayEnhMetaFileRecord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYENHMETAFILERECORD);
    call.hdc = (ULONG_PTR)hdc;
    call.handletable = (ULONG_PTR)handletable;
    call.mr = (ULONG_PTR)mr;
    call.handles = (ULONG_PTR)handles;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlayEnhMetaFileRecord(struct qemu_syscall *call)
{
    struct qemu_PlayEnhMetaFileRecord *c = (struct qemu_PlayEnhMetaFileRecord *)call;
    WINE_TRACE("\n");
    c->super.iret = PlayEnhMetaFileRecord(QEMU_G2H(c->hdc), QEMU_G2H(c->handletable), QEMU_G2H(c->mr), c->handles);
}

#endif

struct qemu_EnumEnhMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hmf;
    uint64_t callback;
    uint64_t data;
    uint64_t lpRect;
    uint64_t wrapper;
};

struct qemu_EnumEnhMetaFile_cb
{
    uint64_t proc;
    uint64_t dc;
    uint64_t handle_table;
    uint64_t emr;
    uint64_t n_objs;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumEnhMetaFile_guest_cb(struct qemu_EnumEnhMetaFile_cb *data)
{
    ENHMFENUMPROC proc = (ENHMFENUMPROC)(ULONG_PTR)data->proc;
    return proc((HDC)(ULONG_PTR)data->dc, (HANDLETABLE *)(ULONG_PTR)data->handle_table, (const ENHMETARECORD *)(ULONG_PTR)data->emr, data->n_objs, data->param);
}

WINGDIAPI BOOL WINAPI EnumEnhMetaFile(HDC hdc, HENHMETAFILE hmf, ENHMFENUMPROC callback, LPVOID data, const RECT *lpRect)
{
    struct qemu_EnumEnhMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMENHMETAFILE);
    call.hdc = (ULONG_PTR)hdc;
    call.hmf = (ULONG_PTR)hmf;
    call.callback = (ULONG_PTR)callback;
    call.data = (ULONG_PTR)data;
    call.lpRect = (ULONG_PTR)lpRect;
    call.wrapper = (ULONG_PTR)EnumEnhMetaFile_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumEnhMetaFile_host_data
{
    uint64_t wrapper, guest_func;
    uint64_t guest_data;
};

static int CALLBACK qemu_EnumEnhMetaFile_host_cb(HDC hdc, HANDLETABLE *handle_table,
        const ENHMETARECORD *emr, int n_objs, LPARAM param)
{
    struct qemu_EnumEnhMetaFile_host_data *data = (struct qemu_EnumEnhMetaFile_host_data *)param;
    struct qemu_EnumEnhMetaFile_cb call;
    int ret;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %p, %d, 0x%lx).\n", (unsigned long)data->guest_func,
            hdc, handle_table, emr, n_objs, (unsigned long)data->guest_data);
    call.proc = data->guest_func;
    call.dc = (ULONG_PTR)hdc;
    call.handle_table = QEMU_H2G(handle_table);
    call.emr = QEMU_H2G(emr);
    call.n_objs = n_objs;
    call.param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %d.\n", ret);
    return ret;
}

void qemu_EnumEnhMetaFile(struct qemu_syscall *call)
{
    struct qemu_EnumEnhMetaFile *c = (struct qemu_EnumEnhMetaFile *)call;
    struct qemu_EnumEnhMetaFile_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->callback;
    data.guest_data = c->data;

    c->super.iret = EnumEnhMetaFile((HDC)c->hdc, QEMU_G2H(c->hmf),
            c->callback ? qemu_EnumEnhMetaFile_host_cb : NULL, &data, QEMU_G2H(c->lpRect));
}

#endif

struct qemu_PlayEnhMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hmf;
    uint64_t lpRect;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PlayEnhMetaFile(HDC hdc, HENHMETAFILE hmf, const RECT *lpRect)
{
    struct qemu_PlayEnhMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYENHMETAFILE);
    call.hdc = (ULONG_PTR)hdc;
    call.hmf = (ULONG_PTR)hmf;
    call.lpRect = (ULONG_PTR)lpRect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlayEnhMetaFile(struct qemu_syscall *call)
{
    struct qemu_PlayEnhMetaFile *c = (struct qemu_PlayEnhMetaFile *)call;
    WINE_TRACE("\n");
    c->super.iret = PlayEnhMetaFile(QEMU_G2H(c->hdc), QEMU_G2H(c->hmf), QEMU_G2H(c->lpRect));
}

#endif

struct qemu_DeleteEnhMetaFile
{
    struct qemu_syscall super;
    uint64_t hmf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DeleteEnhMetaFile(HENHMETAFILE hmf)
{
    struct qemu_DeleteEnhMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEENHMETAFILE);
    call.hmf = (ULONG_PTR)hmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteEnhMetaFile(struct qemu_syscall *call)
{
    struct qemu_DeleteEnhMetaFile *c = (struct qemu_DeleteEnhMetaFile *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteEnhMetaFile(QEMU_G2H(c->hmf));
}

#endif

struct qemu_CopyEnhMetaFileA
{
    struct qemu_syscall super;
    uint64_t hmfSrc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI CopyEnhMetaFileA(HENHMETAFILE hmfSrc, LPCSTR file)
{
    struct qemu_CopyEnhMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYENHMETAFILEA);
    call.hmfSrc = (ULONG_PTR)hmfSrc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CopyEnhMetaFileA(struct qemu_syscall *call)
{
    struct qemu_CopyEnhMetaFileA *c = (struct qemu_CopyEnhMetaFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CopyEnhMetaFileA(QEMU_G2H(c->hmfSrc), QEMU_G2H(c->file));
}

#endif

struct qemu_CopyEnhMetaFileW
{
    struct qemu_syscall super;
    uint64_t hmfSrc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI CopyEnhMetaFileW(HENHMETAFILE hmfSrc, LPCWSTR file)
{
    struct qemu_CopyEnhMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYENHMETAFILEW);
    call.hmfSrc = (ULONG_PTR)hmfSrc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CopyEnhMetaFileW(struct qemu_syscall *call)
{
    struct qemu_CopyEnhMetaFileW *c = (struct qemu_CopyEnhMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CopyEnhMetaFileW(QEMU_G2H(c->hmfSrc), QEMU_G2H(c->file));
}

#endif

struct qemu_GetEnhMetaFilePaletteEntries
{
    struct qemu_syscall super;
    uint64_t hEmf;
    uint64_t cEntries;
    uint64_t lpPe;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetEnhMetaFilePaletteEntries(HENHMETAFILE hEmf, UINT cEntries, LPPALETTEENTRY lpPe)
{
    struct qemu_GetEnhMetaFilePaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENHMETAFILEPALETTEENTRIES);
    call.hEmf = (ULONG_PTR)hEmf;
    call.cEntries = (ULONG_PTR)cEntries;
    call.lpPe = (ULONG_PTR)lpPe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnhMetaFilePaletteEntries(struct qemu_syscall *call)
{
    struct qemu_GetEnhMetaFilePaletteEntries *c = (struct qemu_GetEnhMetaFilePaletteEntries *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEnhMetaFilePaletteEntries(QEMU_G2H(c->hEmf), c->cEntries, QEMU_G2H(c->lpPe));
}

#endif

struct qemu_SetWinMetaFileBits
{
    struct qemu_syscall super;
    uint64_t cbBuffer;
    uint64_t lpbBuffer;
    uint64_t hdcRef;
    uint64_t lpmfp;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HENHMETAFILE WINAPI SetWinMetaFileBits(UINT cbBuffer, const BYTE *lpbBuffer, HDC hdcRef, const METAFILEPICT *lpmfp)
{
    struct qemu_SetWinMetaFileBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINMETAFILEBITS);
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.lpbBuffer = (ULONG_PTR)lpbBuffer;
    call.hdcRef = (ULONG_PTR)hdcRef;
    call.lpmfp = (ULONG_PTR)lpmfp;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetWinMetaFileBits(struct qemu_syscall *call)
{
    struct qemu_SetWinMetaFileBits *c = (struct qemu_SetWinMetaFileBits *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)SetWinMetaFileBits(c->cbBuffer, QEMU_G2H(c->lpbBuffer), QEMU_G2H(c->hdcRef), QEMU_G2H(c->lpmfp));
}

#endif

