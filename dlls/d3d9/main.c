/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#define COBJMACROS
#include <windows.h>
#include <stdio.h>
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

struct qemu_d3d9_set_callbacks
{
    struct qemu_syscall super;
    uint64_t buffer_destroyed;
    uint64_t texture_destroyed;
    uint64_t subresource_destroyed;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_d3d9_set_callbacks call;
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SET_CALLBACKS);
            call.buffer_destroyed = (ULONG_PTR)qemu_d3d9_buffer_destroyed;
            call.texture_destroyed = (ULONG_PTR)qemu_d3d9_texture_destroyed;
            call.subresource_destroyed = (ULONG_PTR)qemu_d3d9_buffer_destroyed;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);

uint64_t qemu_d3d9_buffer_destroyed;
uint64_t qemu_d3d9_texture_destroyed;
uint64_t qemu_d3d9_subresource_destroyed;

static void qemu_d3d9_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_d3d9_set_callbacks *c = (struct qemu_d3d9_set_callbacks *)call;
    qemu_d3d9_buffer_destroyed = c->buffer_destroyed;
    qemu_d3d9_texture_destroyed = c->texture_destroyed;
    qemu_d3d9_subresource_destroyed = c->subresource_destroyed;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_d3d9_AddRef,
    qemu_d3d9_CheckDepthStencilMatch,
    qemu_d3d9_CheckDeviceFormat,
    qemu_d3d9_CheckDeviceFormatConversion,
    qemu_d3d9_CheckDeviceMultiSampleType,
    qemu_d3d9_CheckDeviceType,
    qemu_d3d9_CreateDevice,
    qemu_d3d9_CreateDeviceEx,
    qemu_d3d9_device_AddRef,
    qemu_d3d9_device_BeginScene,
    qemu_d3d9_device_BeginStateBlock,
    qemu_d3d9_device_CheckDeviceState,
    qemu_d3d9_device_CheckResourceResidency,
    qemu_d3d9_device_Clear,
    qemu_d3d9_device_ColorFill,
    qemu_d3d9_device_ComposeRects,
    qemu_d3d9_device_CreateAdditionalSwapChain,
    qemu_d3d9_device_CreateCubeTexture,
    qemu_d3d9_device_CreateDepthStencilSurface,
    qemu_d3d9_device_CreateDepthStencilSurfaceEx,
    qemu_d3d9_device_CreateIndexBuffer,
    qemu_d3d9_device_CreateOffscreenPlainSurface,
    qemu_d3d9_device_CreateOffscreenPlainSurfaceEx,
    qemu_d3d9_device_CreatePixelShader,
    qemu_d3d9_device_CreateQuery,
    qemu_d3d9_device_CreateRenderTarget,
    qemu_d3d9_device_CreateRenderTargetEx,
    qemu_d3d9_device_CreateStateBlock,
    qemu_d3d9_device_CreateTexture,
    qemu_d3d9_device_CreateVertexBuffer,
    qemu_d3d9_device_CreateVertexDeclaration,
    qemu_d3d9_device_CreateVertexShader,
    qemu_d3d9_device_CreateVolumeTexture,
    qemu_d3d9_device_DeletePatch,
    qemu_d3d9_device_DrawIndexedPrimitive,
    qemu_d3d9_device_DrawIndexedPrimitiveUP,
    qemu_d3d9_device_DrawPrimitive,
    qemu_d3d9_device_DrawPrimitiveUP,
    qemu_d3d9_device_DrawRectPatch,
    qemu_d3d9_device_DrawTriPatch,
    qemu_d3d9_device_EndScene,
    qemu_d3d9_device_EndStateBlock,
    qemu_d3d9_device_EvictManagedResources,
    qemu_d3d9_device_GetAvailableTextureMem,
    qemu_d3d9_device_GetBackBuffer,
    qemu_d3d9_device_GetClipPlane,
    qemu_d3d9_device_GetClipStatus,
    qemu_d3d9_device_GetCreationParameters,
    qemu_d3d9_device_GetCurrentTexturePalette,
    qemu_d3d9_device_GetDepthStencilSurface,
    qemu_d3d9_device_GetDeviceCaps,
    qemu_d3d9_device_GetDirect3D,
    qemu_d3d9_device_GetDisplayMode,
    qemu_d3d9_device_GetDisplayModeEx,
    qemu_d3d9_device_GetFrontBufferData,
    qemu_d3d9_device_GetFVF,
    qemu_d3d9_device_GetGammaRamp,
    qemu_d3d9_device_GetGPUThreadPriority,
    qemu_d3d9_device_GetIndices,
    qemu_d3d9_device_GetLight,
    qemu_d3d9_device_GetLightEnable,
    qemu_d3d9_device_GetMaterial,
    qemu_d3d9_device_GetMaximumFrameLatency,
    qemu_d3d9_device_GetNPatchMode,
    qemu_d3d9_device_GetNumberOfSwapChains,
    qemu_d3d9_device_GetPaletteEntries,
    qemu_d3d9_device_GetPixelShader,
    qemu_d3d9_device_GetPixelShaderConstantB,
    qemu_d3d9_device_GetPixelShaderConstantF,
    qemu_d3d9_device_GetPixelShaderConstantI,
    qemu_d3d9_device_GetRasterStatus,
    qemu_d3d9_device_GetRenderState,
    qemu_d3d9_device_GetRenderTarget,
    qemu_d3d9_device_GetRenderTargetData,
    qemu_d3d9_device_GetSamplerState,
    qemu_d3d9_device_GetScissorRect,
    qemu_d3d9_device_GetSoftwareVertexProcessing,
    qemu_d3d9_device_GetStreamSource,
    qemu_d3d9_device_GetStreamSourceFreq,
    qemu_d3d9_device_GetSwapChain,
    qemu_d3d9_device_GetTexture,
    qemu_d3d9_device_GetTextureStageState,
    qemu_d3d9_device_GetTransform,
    qemu_d3d9_device_GetVertexDeclaration,
    qemu_d3d9_device_GetVertexShader,
    qemu_d3d9_device_GetVertexShaderConstantB,
    qemu_d3d9_device_GetVertexShaderConstantF,
    qemu_d3d9_device_GetVertexShaderConstantI,
    qemu_d3d9_device_GetViewport,
    qemu_d3d9_device_LightEnable,
    qemu_d3d9_device_MultiplyTransform,
    qemu_d3d9_device_Present,
    qemu_d3d9_device_PresentEx,
    qemu_d3d9_device_ProcessVertices,
    qemu_d3d9_device_QueryInterface,
    qemu_d3d9_device_Release,
    qemu_d3d9_device_Reset,
    qemu_d3d9_device_ResetEx,
    qemu_d3d9_device_SetClipPlane,
    qemu_d3d9_device_SetClipStatus,
    qemu_d3d9_device_SetConvolutionMonoKernel,
    qemu_d3d9_device_SetCurrentTexturePalette,
    qemu_d3d9_device_SetCursorPosition,
    qemu_d3d9_device_SetCursorProperties,
    qemu_d3d9_device_SetDepthStencilSurface,
    qemu_d3d9_device_SetDialogBoxMode,
    qemu_d3d9_device_SetFVF,
    qemu_d3d9_device_SetGammaRamp,
    qemu_d3d9_device_SetGPUThreadPriority,
    qemu_d3d9_device_SetIndices,
    qemu_d3d9_device_SetLight,
    qemu_d3d9_device_SetMaterial,
    qemu_d3d9_device_SetMaximumFrameLatency,
    qemu_d3d9_device_SetNPatchMode,
    qemu_d3d9_device_SetPaletteEntries,
    qemu_d3d9_device_SetPixelShader,
    qemu_d3d9_device_SetPixelShaderConstantB,
    qemu_d3d9_device_SetPixelShaderConstantF,
    qemu_d3d9_device_SetPixelShaderConstantI,
    qemu_d3d9_device_SetRenderState,
    qemu_d3d9_device_SetRenderTarget,
    qemu_d3d9_device_SetSamplerState,
    qemu_d3d9_device_SetScissorRect,
    qemu_d3d9_device_SetSoftwareVertexProcessing,
    qemu_d3d9_device_SetStreamSource,
    qemu_d3d9_device_SetStreamSourceFreq,
    qemu_d3d9_device_SetTexture,
    qemu_d3d9_device_SetTextureStageState,
    qemu_d3d9_device_SetTransform,
    qemu_d3d9_device_SetVertexDeclaration,
    qemu_d3d9_device_SetVertexShader,
    qemu_d3d9_device_SetVertexShaderConstantB,
    qemu_d3d9_device_SetVertexShaderConstantF,
    qemu_d3d9_device_SetVertexShaderConstantI,
    qemu_d3d9_device_SetViewport,
    qemu_d3d9_device_ShowCursor,
    qemu_d3d9_device_StretchRect,
    qemu_d3d9_device_TestCooperativeLevel,
    qemu_d3d9_device_UpdateSurface,
    qemu_d3d9_device_UpdateTexture,
    qemu_d3d9_device_ValidateDevice,
    qemu_d3d9_device_WaitForVBlank,
    qemu_d3d9_EnumAdapterModes,
    qemu_d3d9_EnumAdapterModesEx,
    qemu_d3d9_GetAdapterCount,
    qemu_d3d9_GetAdapterDisplayMode,
    qemu_d3d9_GetAdapterDisplayModeEx,
    qemu_d3d9_GetAdapterIdentifier,
    qemu_d3d9_GetAdapterLUID,
    qemu_d3d9_GetAdapterModeCount,
    qemu_d3d9_GetAdapterModeCountEx,
    qemu_d3d9_GetAdapterMonitor,
    qemu_d3d9_GetDeviceCaps,
    qemu_d3d9_indexbuffer_AddRef,
    qemu_d3d9_indexbuffer_FreePrivateData,
    qemu_d3d9_indexbuffer_GetDesc,
    qemu_d3d9_indexbuffer_GetDevice,
    qemu_d3d9_indexbuffer_GetPriority,
    qemu_d3d9_indexbuffer_GetPrivateData,
    qemu_d3d9_indexbuffer_GetType,
    qemu_d3d9_indexbuffer_Lock,
    qemu_d3d9_indexbuffer_PreLoad,
    qemu_d3d9_indexbuffer_QueryInterface,
    qemu_d3d9_indexbuffer_Release,
    qemu_d3d9_indexbuffer_SetPriority,
    qemu_d3d9_indexbuffer_SetPrivateData,
    qemu_d3d9_indexbuffer_Unlock,
    qemu_d3d9_pixelshader_AddRef,
    qemu_d3d9_pixelshader_GetDevice,
    qemu_d3d9_pixelshader_GetFunction,
    qemu_d3d9_pixelshader_QueryInterface,
    qemu_d3d9_pixelshader_Release,
    qemu_d3d9_query_AddRef,
    qemu_d3d9_query_GetData,
    qemu_d3d9_query_GetDataSize,
    qemu_d3d9_query_GetDevice,
    qemu_d3d9_query_GetType,
    qemu_d3d9_query_Issue,
    qemu_d3d9_query_QueryInterface,
    qemu_d3d9_query_Release,
    qemu_d3d9_QueryInterface,
    qemu_d3d9_RegisterSoftwareDevice,
    qemu_d3d9_Release,
    qemu_d3d9_set_callbacks,
    qemu_d3d9_stateblock_AddRef,
    qemu_d3d9_stateblock_Apply,
    qemu_d3d9_stateblock_Capture,
    qemu_d3d9_stateblock_GetDevice,
    qemu_d3d9_stateblock_QueryInterface,
    qemu_d3d9_stateblock_Release,
    qemu_d3d9_surface_AddRef,
    qemu_d3d9_surface_FreePrivateData,
    qemu_d3d9_surface_GetContainer,
    qemu_d3d9_surface_GetDC,
    qemu_d3d9_surface_GetDesc,
    qemu_d3d9_surface_GetDevice,
    qemu_d3d9_surface_GetPriority,
    qemu_d3d9_surface_GetPrivateData,
    qemu_d3d9_surface_GetType,
    qemu_d3d9_surface_LockRect,
    qemu_d3d9_surface_PreLoad,
    qemu_d3d9_surface_QueryInterface,
    qemu_d3d9_surface_Release,
    qemu_d3d9_surface_ReleaseDC,
    qemu_d3d9_surface_SetPriority,
    qemu_d3d9_surface_SetPrivateData,
    qemu_d3d9_surface_UnlockRect,
    qemu_d3d9_swapchain_AddRef,
    qemu_d3d9_swapchain_GetBackBuffer,
    qemu_d3d9_swapchain_GetDevice,
    qemu_d3d9_swapchain_GetDisplayMode,
    qemu_d3d9_swapchain_GetDisplayModeEx,
    qemu_d3d9_swapchain_GetFrontBufferData,
    qemu_d3d9_swapchain_GetLastPresentCount,
    qemu_d3d9_swapchain_GetPresentParameters,
    qemu_d3d9_swapchain_GetPresentStatistics,
    qemu_d3d9_swapchain_GetRasterStatus,
    qemu_d3d9_swapchain_Present,
    qemu_d3d9_swapchain_QueryInterface,
    qemu_d3d9_swapchain_Release,
    qemu_d3d9_texture_2d_AddDirtyRect,
    qemu_d3d9_texture_2d_AddRef,
    qemu_d3d9_texture_2d_FreePrivateData,
    qemu_d3d9_texture_2d_GenerateMipSubLevels,
    qemu_d3d9_texture_2d_GetAutoGenFilterType,
    qemu_d3d9_texture_2d_GetDevice,
    qemu_d3d9_texture_2d_GetLevelCount,
    qemu_d3d9_texture_2d_GetLevelDesc,
    qemu_d3d9_texture_2d_GetLOD,
    qemu_d3d9_texture_2d_GetPriority,
    qemu_d3d9_texture_2d_GetPrivateData,
    qemu_d3d9_texture_2d_GetSurfaceLevel,
    qemu_d3d9_texture_2d_GetType,
    qemu_d3d9_texture_2d_LockRect,
    qemu_d3d9_texture_2d_PreLoad,
    qemu_d3d9_texture_2d_QueryInterface,
    qemu_d3d9_texture_2d_Release,
    qemu_d3d9_texture_2d_SetAutoGenFilterType,
    qemu_d3d9_texture_2d_SetLOD,
    qemu_d3d9_texture_2d_SetPriority,
    qemu_d3d9_texture_2d_SetPrivateData,
    qemu_d3d9_texture_2d_UnlockRect,
    qemu_d3d9_texture_3d_AddDirtyBox,
    qemu_d3d9_texture_3d_AddRef,
    qemu_d3d9_texture_3d_FreePrivateData,
    qemu_d3d9_texture_3d_GenerateMipSubLevels,
    qemu_d3d9_texture_3d_GetAutoGenFilterType,
    qemu_d3d9_texture_3d_GetDevice,
    qemu_d3d9_texture_3d_GetLevelCount,
    qemu_d3d9_texture_3d_GetLevelDesc,
    qemu_d3d9_texture_3d_GetLOD,
    qemu_d3d9_texture_3d_GetPriority,
    qemu_d3d9_texture_3d_GetPrivateData,
    qemu_d3d9_texture_3d_GetType,
    qemu_d3d9_texture_3d_GetVolumeLevel,
    qemu_d3d9_texture_3d_LockBox,
    qemu_d3d9_texture_3d_PreLoad,
    qemu_d3d9_texture_3d_QueryInterface,
    qemu_d3d9_texture_3d_Release,
    qemu_d3d9_texture_3d_SetAutoGenFilterType,
    qemu_d3d9_texture_3d_SetLOD,
    qemu_d3d9_texture_3d_SetPriority,
    qemu_d3d9_texture_3d_SetPrivateData,
    qemu_d3d9_texture_3d_UnlockBox,
    qemu_d3d9_texture_cube_AddDirtyRect,
    qemu_d3d9_texture_cube_AddRef,
    qemu_d3d9_texture_cube_FreePrivateData,
    qemu_d3d9_texture_cube_GenerateMipSubLevels,
    qemu_d3d9_texture_cube_GetAutoGenFilterType,
    qemu_d3d9_texture_cube_GetCubeMapSurface,
    qemu_d3d9_texture_cube_GetDevice,
    qemu_d3d9_texture_cube_GetLevelCount,
    qemu_d3d9_texture_cube_GetLevelDesc,
    qemu_d3d9_texture_cube_GetLOD,
    qemu_d3d9_texture_cube_GetPriority,
    qemu_d3d9_texture_cube_GetPrivateData,
    qemu_d3d9_texture_cube_GetType,
    qemu_d3d9_texture_cube_LockRect,
    qemu_d3d9_texture_cube_PreLoad,
    qemu_d3d9_texture_cube_QueryInterface,
    qemu_d3d9_texture_cube_Release,
    qemu_d3d9_texture_cube_SetAutoGenFilterType,
    qemu_d3d9_texture_cube_SetLOD,
    qemu_d3d9_texture_cube_SetPriority,
    qemu_d3d9_texture_cube_SetPrivateData,
    qemu_d3d9_texture_cube_UnlockRect,
    qemu_d3d9_vertex_declaration_AddRef,
    qemu_d3d9_vertex_declaration_GetDeclaration,
    qemu_d3d9_vertex_declaration_GetDevice,
    qemu_d3d9_vertex_declaration_QueryInterface,
    qemu_d3d9_vertex_declaration_Release,
    qemu_d3d9_vertexbuffer_AddRef,
    qemu_d3d9_vertexbuffer_FreePrivateData,
    qemu_d3d9_vertexbuffer_GetDesc,
    qemu_d3d9_vertexbuffer_GetDevice,
    qemu_d3d9_vertexbuffer_GetPriority,
    qemu_d3d9_vertexbuffer_GetPrivateData,
    qemu_d3d9_vertexbuffer_GetType,
    qemu_d3d9_vertexbuffer_Lock,
    qemu_d3d9_vertexbuffer_PreLoad,
    qemu_d3d9_vertexbuffer_QueryInterface,
    qemu_d3d9_vertexbuffer_Release,
    qemu_d3d9_vertexbuffer_SetPriority,
    qemu_d3d9_vertexbuffer_SetPrivateData,
    qemu_d3d9_vertexbuffer_Unlock,
    qemu_d3d9_vertexshader_AddRef,
    qemu_d3d9_vertexshader_GetDevice,
    qemu_d3d9_vertexshader_GetFunction,
    qemu_d3d9_vertexshader_QueryInterface,
    qemu_d3d9_vertexshader_Release,
    qemu_d3d9_volume_AddRef,
    qemu_d3d9_volume_FreePrivateData,
    qemu_d3d9_volume_GetContainer,
    qemu_d3d9_volume_GetDesc,
    qemu_d3d9_volume_GetDevice,
    qemu_d3d9_volume_GetPrivateData,
    qemu_d3d9_volume_LockBox,
    qemu_d3d9_volume_QueryInterface,
    qemu_d3d9_volume_Release,
    qemu_d3d9_volume_SetPrivateData,
    qemu_d3d9_volume_UnlockBox,
    qemu_D3DPERF_BeginEvent,
    qemu_D3DPERF_EndEvent,
    qemu_D3DPERF_GetStatus,
    qemu_D3DPERF_QueryRepeatFrame,
    qemu_D3DPERF_SetMarker,
    qemu_D3DPERF_SetOptions,
    qemu_D3DPERF_SetRegion,
    qemu_DebugSetMute,
    qemu_Direct3DCreate9,
    qemu_Direct3DCreate9Ex,
    qemu_Direct3DShaderValidatorCreate9,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3d9 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

const GUID qemu_d3d9_swapchain_guid =
{
    0xe7a14042,
    0xc71a,
    0x8f5f,
    {0x8f,0x4f,0xfd,0xd5,0x19,0xe9,0x07,0x9c}
};

const GUID qemu_d3d9_surface_guid =
{
    0xb06032d0,
    0xb720,
    0x4191,
    {0xa9,0x08,0x32,0x97,0x48,0x88,0xfe,0xf6}
};

const GUID qemu_d3d9_texture_guid =
{
    0x3b3b2a76,
    0x16e1,
    0x4ac8,
    {0xa1,0xa5,0x12,0xf7,0x7e,0xa6,0x0a,0xdd}
};

const GUID qemu_d3d9_buffer_guid =
{
    0x1ed2dd61,
    0x55c4,
    0x4453,
    {0xa7,0xc0,0x14,0x98,0x03,0xda,0x74,0x6e}
};

const GUID qemu_d3d9_standalone_surface_guid =
{
    0x110ef0a8,
    0x7a35,
    0x4818,
    {0xad,0xea,0x6d,0x63,0x23,0xcf,0x0c,0xf6}
};

const GUID qemu_d3d9_volume_guid =
{
    0x83ba67e2,
    0x89ed,
    0x4db5,
    {0xb4,0x63,0xf4,0x7d,0xa5,0x3c,0x3c,0x24}
};

#endif
