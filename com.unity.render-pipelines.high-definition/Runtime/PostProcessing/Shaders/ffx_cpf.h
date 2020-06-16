// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
// INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD ONLY PREVIEW - INTERNAL AMD 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//
//                                           [CPF] CINEMATIC POST FILTER v0.20200217
//
//
//------------------------------------------------------------------------------------------------------------------------------
// ABOUT
// =====
// FidelityFX Cinematic Post Filter (CPF) is a temporal post processing package.
// The aim of this package is to provide a more believable real-life image reconstruction of 2xTSSAA.
// CPF is provided in a simple, fast, and highly portable package.
// It is NOT the goal of this package to make the sharpest synthetic reconstruction.
// Features. 
//  (.) HDR Support - Handles 15 stops over the {0 to 1} LDR range.
//  (.) 2xTSSAA - 2 samples/pixel temporally across 2 frames.
//  (.) PSL Support - Programmable Sample Location without MSAA (Navi-only), increases 2x to 4x AA quality.
//  (.) Smooth Wide Kernel Resolve - This focuses on a filmic look and feel to hide typical artficts of raster graphics.
//  (.) Directional Contrast Adaptive Sharpening (CAS) - CAS is used conservatively on local gradients.
//  (.) Motion Blur - Wide shutter approximation, uses 2 frames to have leading and trailing backgrounds.
//  (.) Still Frame Stability - The dual frame composite is temporally stable on still views.
//  (.) Micro Diffusion - Hot pixels have a pixel-sized bloom to support the perception of brightness.
//  (.) Diffusion - Energy preserving diffusion filter (aka bloom) with very wide clean fall off.
//  (.) Noise Suppression - Configurable filter to reduce the contrast of hot pixels.
//  (.) Micro Depth of Field - Maximum circle of confusion is tiny (1.5 pixel radius maximum).
//  (.) Auto Exposure - (PLANNED) Feedback to enable game to easily manage exposure level automatically.
//  (.) Distortion - (PLANNED) Typically used for heat shimmer, water, etc.
//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------------------------
// INTEGRATION
// ===========
// CPF is packaged into 2 headers: ffx_a.ush (portability) and ffx_cpf.ush (this file, the algorithm).
// With defines which control usage between C code and high-level shading language code.
// -----------
// Including CPF in GLSL/HLSL,
//  (0.) Setup the defines for the portability header and include. Example for Vulkan with 16-bit support,
//        #define A_GLSL 1
//        #define A_GPU 1
//        #define A_HALF 1
//        #define A_LONG 1
//        #define A_WAVE 1
//        #include "ffx_a.h"
//  (1.) Setup defines for CPF and include the header. Example (see "DEVELOPER CONTROL KNOBS" below for meaning of defines),
//        #define CPF_DFU 1
//        #define CPF_NOZ 0
//        #define CPF_PSL 1
//        #define CPF_TAP 12
//        #define CPF_16BIT 1
//        #define CPF_32BIT 1
//        // Place callbacks before including 'ffx_cpf.h'.
//        ...
//        #include "ffx_cpf.h"
// -----------
// Including CPF in C code. Example (less defines are needed for the C code),
//  #define A_CPU 1
//  #include "ffx_a.ush"
//  // Place callbacks before including 'ffx_cpf.ush'.
//  . . .
//  #include "ffx_cpf.ush"
// -----------
// Image list (make sure to round up when dividing for width and height).
// The noise reduction images are only required if CPF_NOZ is defined.
// The diffusion images are only required if CPF_DFU is defined.
//  width height format  frame   usage
//  ===== ====== ======= ======= =====
//  x     y      RG16F   new     {luma prior, luma prior prior} feedback for noise reduction
//  x     y      RG16F   prior   {luma prior, luma prior prior} feedback for noise reduction
//  x     y      R16UI   even    {motion} packed compressed vector
//  x     y      R16UI   odd     {motion} packed compressed vector
//  x     y      RGBA8   even    {rgb,coc} packed compressed data
//  x     y      RGBA8   odd     {rgb,coc} packed compressed data
//  x     y      RGBA16F         {rgb,blur} input to cleaner pass
//  x/4   y/4    RGBA16F         {rgb,weight} diffusion down 4x4
//  x/8   y/8    RGBA16F new     {rgb,weight} diffusion down 8x8
//  x/8   y/8    RGBA16F prior   {rgb,weight} diffusion down 8x8
//  x/16  y/16   RGBA16F new     {rgb,weight} diffusion down 16x16
//  x/16  y/16   RGBA16F prior   {rgb,weight} diffusion down 16x16
//  x/32  y/32   RGBA16F new     {rgb,weight} diffusion down 32x32
//  x/32  y/32   RGBA16F prior   {rgb,weight} diffusion down 32x32
//  x/64  y/64   RGBA16F new     {rgb,weight} diffusion down 64x64
//  x/64  y/64   RGBA16F prior   {rgb,weight} diffusion down 64x64
//  x/128 y/128  RGBA16F new     {rgb,weight} diffusion down 128x128
//  x/128 y/128  RGBA16F prior   {rgb,weight} diffusion down 128x128
//  x/4   y/4    RGBA16F new     {rgb,weight} diffusion up 4x4
//  x/4   y/4    RGBA16F prior   {rgb,weight} diffusion up 4x4
//  x/8   y/8    RGBA16F new     {rgb,weight} diffusion up 8x8
//  x/8   y/8    RGBA16F prior   {rgb,weight} diffusion up 8x8
//  x/4   y/16   RGBA16F new     {rgb,weight} diffusion up 16x16
//  x/4   y/16   RGBA16F prior   {rgb,weight} diffusion up 16x16
//  x/4   y/32   RGBA16F new     {rgb,weight} diffusion up 32x32
//  x/4   y/32   RGBA16F prior   {rgb,weight} diffusion up 32x32
//  x/4   y/64   RGBA16F new     {rgb,weight} diffusion up 64x64
//  x/4   y/64   RGBA16F prior   {rgb,weight} diffusion up 64x64
// -----------
// Callbacks used by CPF, there are a lot. Below is an example for Vulkan,
//  ...
//  // Structure used for CPF constant block.
//  struct CpfT{AU4 cpf[32];};
//  ...
//  // Samplers.
//  layout(set=0,binding=2)uniform sampler sam[3]; // {nearest,linear,linear-black-border} sampling.
//  ... 
//  // Example for GPU generated double buffered constants.
//  // Normally this would be merged with other constants to avoid using extra descriptors.
//  layout(set=0,binding=3,std430) /* readonly */ buffer ssbo1_ {CpfT cpfR;};
//  layout(set=0,binding=4,std430)writeonly coherent buffer ssbo2_ {CpfT cpfW;};
//  ...
//  // Example on how it is possible to setup multiple formats in the same texture arrays.
//  // Defines specific to this example,
//  // Count of single or double buffered images.
//  #define GFX_IMG_S 5
//  #define GFX_IMG_D 13
//  // Single buffered images (set even/odd access, or just single image).
//  #define IMG_COL0 0
//  #define IMG_COL1 1
//  #define IMG_MOV0 2
//  #define IMG_MOV1 3
//  #define IMG_CLN 4
//  // Double buffered images.
//  #define IMG_NOZ 0
//  #define IMG_DFU_DWN0 2
//  #define IMG_DFU_DWN1 3
//  #define IMG_DFU_DWN2 4
//  #define IMG_DFU_DWN3 5
//  #define IMG_DFU_DWN4 6
//  #define IMG_DFU_DWN5 7
//  #define IMG_DFU_UP0 8
//  #define IMG_DFU_UP1 9
//  #define IMG_DFU_UP2 10
//  #define IMG_DFU_UP3 11
//  #define IMG_DFU_UP4 12
//  // Single buffered image access - as image.
//  layout(set=0,binding=6,rgba16f)uniform image2D imgS_2D_RGBA16F[GFX_IMG_S];
//  layout(set=0,binding=6,r16ui)uniform uimage2D imgS_2D_R16UI[GFX_IMG_S];
//  layout(set=0,binding=6,rgba8)uniform image2D imgS_2D_RGBA8[GFX_IMG_S];
//  // Double buffered current image access - as image.
//  layout(set=0,binding=7,rg16f)uniform image2D imgC_2D_RG16F[GFX_IMG_D];
//  layout(set=0,binding=7,rgba16f)uniform image2D imgC_2D_RGBA16F[GFX_IMG_D];
//  // Double buffered prior image access - as image.
//  layout(set=0,binding=8,rg16f)uniform image2D imgP_2D_RG16F[GFX_IMG_D];
//  layout(set=0,binding=8,rgba16f)uniform image2D imgP_2D_RGBA16F[GFX_IMG_D];
//  // Aliased resources as textures (unfortunately Vulkan requires a different binding point).
//  // Single buffered.
//  layout(set=0,binding=9)uniform texture2D texS_2D[GFX_IMG_S];
//  layout(set=0,binding=9)uniform utexture2D texS_2D_U[GFX_IMG_S];
//  // Double buffered current.
//  layout(set=0,binding=10)uniform texture2D texC_2D[GFX_IMG_D];
//  // Double buffered prior.
//  layout(set=0,binding=11)uniform texture2D texP_2D[GFX_IMG_D];
//  ...
//  // Now all the callbacks.
//  ...
//  // Control block: RGBA32UI[32].
//  A_STATIC void CpfPut(AU1 i,AU4 v){cpfW.cpf[i]=v;}
//  A_STATIC AU4 CpfGet(AU1 i){return cpfR.cpf[i];}
//  ...
//  // Cleaner input: {width,height} RGBA16F.
//  #ifdef CPF_32BIT
//   AF4 CpfClnLd(AU2 p){return imageLoad(imgS_2D_RGBA16F[IMG_CLN],ASU2(p));}
//   void CpfClnSt(AU2 p,AF4 v){imageStore(imgS_2D_RGBA16F[IMG_CLN],ASU2(p),v);}
//  #endif
//  #ifdef CPF_16BIT
//   AH4 CpfClnLdH(AW2 p){return AH4(imageLoad(imgS_2D_RGBA16F[IMG_CLN],ASU2(p)));}
//   void CpfClnStH(AW2 p,AH4 v){imageStore(imgS_2D_RGBA16F[IMG_CLN],ASU2(p),AF4(v));}
//  #endif
//  ...
//  // Noise reduction: {width,height} RG16F.
//  #ifdef CPF_32BIT
//   AF2 CpfNozLd(AU2 p){return imageLoad(imgP_2D_RG16F[IMG_NOZ],ASU2(p)).xy;}
//   void CpfNozSt(AU2 p,AF2 v){imageStore(imgC_2D_RG16F[IMG_NOZ],ASU2(p),AF4(v.x,v.y,0,0));}
//   // This requires a bilinear sampler.
//   AF2 CpfNozSm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,0.0).xy;}
//   AF4 CpfNoz4R(AF2 p){return textureGather(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,0);}
//   AF4 CpfNoz4G(AF2 p){return textureGather(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,1);}
//  #endif
//  #ifdef CPF_16BIT
//   // This uses 32-bit for float position for sampling as FP16 does not have enough precion for large resolutions.
//   AH2 CpfNozLd(AW2 p){return AH2(imageLoad(imgP_2D_RG16F[IMG_NOZ],ASU2(p)).xy);}
//   void CpfNozStH(AW2 p,AH2 v){imageStore(imgC_2D_RG16F[IMG_NOZ],ASU2(p),AF4(AH4(v.x,v.y,0,0)));}
//   // This requires a bilinear sampler.
//   AH2 CpfNozSmH(AF2 p){return AH2(textureLod(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,0.0).xy);}
//   AH4 CpfNoz4RH(AF2 p){return AH4(textureGather(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,0));}
//   AH4 CpfNoz4GH(AF2 p){return AH4(textureGather(sampler2D(texP_2D[IMG_NOZ],sam[1]),p,1));}
//  #endif
//  ...
//  // Motion vector: {width,height} R16UI.
//  #ifdef CPF_32BIT
//   AU1 CpfMovLd(AU1 b,AU2 p){return imageLoad(imgS_2D_R16UI[IMG_MOV0+b],ASU2(p)).x;}
//   void CpfMovSt(AU1 b,AU2 p,AU1 v){imageStore(imgS_2D_R16UI[IMG_MOV0+b],ASU2(p),AU4(v,0,0,0));}
//   // This is setup with a bilinear sampler.
//   AU4 CpfMov4R(AU1 b,AF2 p){return textureGather(usampler2D(texS_2D_U[IMG_MOV0+b],sam[1]),p,0);}
//  #endif
//  #ifdef CPF_16BIT
//   void CpfMovStH(AU1 b,AW2 p,AW1 v){imageStore(imgS_2D_R16UI[IMG_MOV0+b],ASU2(p),AU4(v,0,0,0));}
//  #endif
//  ...
//  // Color: {width,height} RGBA8
//  #ifdef CPF_32BIT
//   AF4 CpfColLd(AU1 b,AU2 p){return imageLoad(imgS_2D_RGBA8[IMG_COL0+b],ASU2(p));}
//   void CpfColSt(AU1 b,AU2 p,AF4 v){imageStore(imgS_2D_RGBA8[IMG_COL0+b],ASU2(p),v);}
//   // These are setup with a bilinear sampler.
//   AF4 CpfColSm(AU1 b,AF2 p){return textureLod(sampler2D(texS_2D[IMG_COL0+b],sam[1]),p,0.0);}
//   AF4 CpfCol4A(AU1 b,AF2 p){return textureGather(sampler2D(texS_2D[IMG_COL0+b],sam[1]),p,3);}
//  #endif
//  #ifdef CPF_16BIT
//   AH4 CpfColLdH(AU1 b,AW2 p){return AH4(imageLoad(imgS_2D_RGBA8[IMG_COL0+b],ASU2(p)));}
//   void CpfColStH(AU1 b,AW2 p,AH4 v){imageStore(imgS_2D_RGBA8[IMG_COL0+b],ASU2(p),AF4(v));}
//   // These use non-packed arguments due to the need for high precision positioning for larger render targets.
//   AH4 CpfColSmH(AU1 b,AF2 p){return AH4(textureLod(sampler2D(texS_2D[IMG_COL0+b],sam[1]),p,0.0));}
//   AH4 CpfCol4AH(AU1 b,AF2 p){return AH4(textureGather(sampler2D(texS_2D[IMG_COL0+b],sam[1]),p,3));}
//  #endif 
//  ...
//  // Diffusion is all RGBA16 (currently need the high precision).
//  // These all use bilinear samplers with black edges (different than other images), with one noted execption.
//  #ifdef CPF_32BIT
//   // Current frame down-sampling series.
//   // {width/4,height/4}
//   // Special since new drops into current instead of previous frame.
//   void CpfDfuDwn0St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN0],ASU2(p),v);}
//   AF4 CpfDfuDwn0Sm(AF2 p){return textureLod(sampler2D(texC_2D[IMG_DFU_DWN0],sam[2]),p,0.0);}
//   AF4 CpfDfuDwn0Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN0],ASU2(p));}
//   // {width/8,height/8}
//   void CpfDfuDwn1St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN1],ASU2(p),v);}
//   AF4 CpfDfuDwn1Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN1],ASU2(p));}
//   // {width/16,height/16}
//   void CpfDfuDwn2St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN2],ASU2(p),v);}
//   AF4 CpfDfuDwn2Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN2],ASU2(p));}
//   // {width/32,height/32}
//   void CpfDfuDwn3St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN3],ASU2(p),v);}
//   AF4 CpfDfuDwn3Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN3],ASU2(p));}
//   // {width/64,height/64}
//   void CpfDfuDwn4St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN4],ASU2(p),v);}
//   AF4 CpfDfuDwn4Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN4],ASU2(p));}
//   // {width/128,height/128}
//   void CpfDfuDwn5St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN5],ASU2(p),v);}
//   AF4 CpfDfuDwn5Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN5],ASU2(p));}
//   // These are the prior frame down-sampling series.
//   // The w/4 x h/4 image is not needed as it is replaced in the current frame series. 
//   // {width/8,height/8}
//   AF4 CpfDfuDwn1Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_DWN1],sam[2]),p,0.0);}
//   // {width/16,height/16}
//   AF4 CpfDfuDwn2Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_DWN2],sam[2]),p,0.0);}
//   // {width/32,height/32}
//   AF4 CpfDfuDwn3Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_DWN3],sam[2]),p,0.0);}
//   // {width/64,height/64}
//   AF4 CpfDfuDwn4Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_DWN4],sam[2]),p,0.0);}
//   // {width/128,height/128}
//   AF4 CpfDfuDwn5Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_DWN5],sam[2]),p,0.0);}
//   // Current frame up-sampling series.
//   // {width/4,height/4}
//   // Exception: This is bilinear without the black edge.
//   void CpfDfuUp0St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP0],ASU2(p),v);}
//   AF4 CpfDfuUp0Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_UP0],ASU2(p));}
//   AF4 CpfDfuOutSm(AF2 p){return textureLod(sampler2D(texC_2D[IMG_DFU_UP0],sam[1]),p,0.0);}
//   // {width/8,height/8}
//   void CpfDfuUp1St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP1],ASU2(p),v);}
//   AF4 CpfDfuUp1Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_UP1],ASU2(p));}
//   // {width/16,height/16}
//   void CpfDfuUp2St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP2],ASU2(p),v);}
//   AF4 CpfDfuUp2Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_UP2],ASU2(p));}
//   // {width/32,height/32}
//   void CpfDfuUp3St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP3],ASU2(p),v);}
//   AF4 CpfDfuUp3Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_UP3],ASU2(p));}
//   // {width/64,height/64}
//   void CpfDfuUp4St(AU2 p,AF4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP4],ASU2(p),v);}
//   AF4 CpfDfuUp4Ld(AU2 p){return imageLoad(imgC_2D_RGBA16F[IMG_DFU_UP4],ASU2(p));}
//   // Prior frame up-sampling series.
//   // {width/4,height/4}
//   AF4 CpfDfuUp0Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_UP0],sam[2]),p,0.0);}
//   // {width/8,height/8}
//   AF4 CpfDfuUp1Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_UP1],sam[2]),p,0.0);}
//   // {width/16,height/16}
//   AF4 CpfDfuUp2Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_UP2],sam[2]),p,0.0);}
//   // {width/32,height/32}
//   AF4 CpfDfuUp3Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_UP3],sam[2]),p,0.0);}
//   // {width/64,height/64}
//   AF4 CpfDfuUp4Sm(AF2 p){return textureLod(sampler2D(texP_2D[IMG_DFU_UP4],sam[2]),p,0.0);}
//  #endif
//  #ifdef CPF_16BIT
//   void CpfDfuDwn0StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN0],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn0LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN0],ASU2(p)));}
//   void CpfDfuDwn1StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN1],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn1LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN1],ASU2(p)));}
//   void CpfDfuDwn2StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN2],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn2LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN2],ASU2(p)));}
//   void CpfDfuDwn3StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN3],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn3LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN3],ASU2(p)));}
//   void CpfDfuDwn4StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN4],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn4LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN4],ASU2(p)));}
//   void CpfDfuDwn5StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_DWN5],ASU2(p),AF4(v));}
//   AH4 CpfDfuDwn5LdH(AW2 p){return AH4(imageLoad(imgC_2D_RGBA16F[IMG_DFU_DWN5],ASU2(p)));}
//   AH4 CpfDfuDwn0SmH(AF2 p){return AH4(textureLod(sampler2D(texC_2D[IMG_DFU_DWN0],sam[2]),p,0.0));}
//   AH4 CpfDfuDwn1SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_DWN1],sam[2]),p,0.0));}
//   AH4 CpfDfuDwn2SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_DWN2],sam[2]),p,0.0));}
//   AH4 CpfDfuDwn3SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_DWN3],sam[2]),p,0.0));}
//   AH4 CpfDfuDwn4SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_DWN4],sam[2]),p,0.0));}
//   AH4 CpfDfuDwn5SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_DWN5],sam[2]),p,0.0));}
//   void CpfDfuUp0StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP0],ASU2(p),AF4(v));}
//   AH4 CpfDfuOutSmH(AH2 p){return AH4(textureLod(sampler2D(texC_2D[IMG_DFU_UP0],sam[1]),AF2(p),0.0));}
//   void CpfDfuUp1StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP1],ASU2(p),AF4(v));}
//   void CpfDfuUp2StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP2],ASU2(p),AF4(v));}
//   void CpfDfuUp3StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP3],ASU2(p),AF4(v));}
//   void CpfDfuUp4StH(AW2 p,AH4 v){imageStore(imgC_2D_RGBA16F[IMG_DFU_UP4],ASU2(p),AF4(v));}
//   AH4 CpfDfuUp0SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_UP0],sam[2]),p,0.0));}
//   AH4 CpfDfuUp1SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_UP1],sam[2]),p,0.0));}
//   AH4 CpfDfuUp2SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_UP2],sam[2]),p,0.0));}
//   AH4 CpfDfuUp3SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_UP3],sam[2]),p,0.0));}
//   AH4 CpfDfuUp4SmH(AF2 p){return AH4(textureLod(sampler2D(texP_2D[IMG_DFU_UP4],sam[2]),p,0.0));}
//  #endif 
// -----------
// Integration points (note it is possible to mix and match 16-bit and 32-bit passes),
//  (0.) Setup callback functions after including 'ffx_a.ush' and before including 'ffx_cpf.ush'.
//       Callbacks are used in both C and high-level shader code.
//       However only the CpfPut() callback is used in C code.
//       See above section for details.
//  (1.) In C or shader code, generate the constants for CPF (this generates constants for both 32-bit and 16-bit paths).
//       These use the 'CpfPut()' callback to store the associated constants.
//       For for the CPU those stored constants will need to be uploaded to the GPU by some mechanism.
//       Example of generating the constant block,
//        AU1 frame=...; // Frame counter.
//        AF1 width=...; // Frame width in pixels.
//        AF1 height=...; // Frame height in pixels.
//        AF1 denoise=...; // Stops of denoise.
//        AF1 diffusion=...; // Stops of diffusion.
//        CpfBlk(frame,width,height,denoise,diffusion);
//  (2.) In the last pass before CPF is to be run (this will be the pass which stores color last).
//       Run the CPF preprocessor 'CpfPre()' inline in this pass.
//       This pass needs to be a {64,1,1} workgroup, and use the 'ARmpRed8x8()' function to reconfigure into an 8x8 block.
//       The 32-bit version of the code will work on 8x8 tiles.
//       The 16-bit version of the code will work on two 8x8 tiles in a 16x8 foot-print.
//       It is advised to do some extra number of tiles (via loop unrolling) to increase performance.
//       Profile to see what is best.
//       Example for Vulkan without loop unrolling,
//        layout(local_size_x=64)in;
//        void main(){
//         // Remapped local xy in workgroup.
//         AU2 lxy=ARmpRed8x8(gl_LocalInvocationID.x);
//         // Example for 32-bit.
//         #ifdef CPF_32BIT
//          // Global xy in kernel.
//          AU2 gxy=lxy+AU2(gl_WorkGroupID.x<<3u,gl_WorkGroupID.y<<3u);
//          // Color.
//          AF1 cR;AF1 cG;AF1 cB;
//          // Depth.
//          AF1 z;
//          // Motion vector.
//          AF1 mvX;AF1 mvY;
//          // Call the code for the pass before CPF to setup the above values for position 'gxy'.
//          PassBeforeCpf(cR,cG,cB,z,mvX,mvY,gxy);
//          // Convert depth to circle of confusion. Use the CpfCocIni() function to setup the 2 constants.
//          AF1 coc;
//          coc=CpfCoc(z,const0,const1);
//          // Call the CPF pre-pass function.
//          CpfPre(gxy,cR,cG,cB,coc,mvX,mvY);
//         #endif
//         // And for 16-bit.
//         #ifdef CPF_16BIT
//          AU2 gxy=lxy+AU2(gl_WorkGroupID.x<<4u,gl_WorkGroupID.y<<3u);
//          AH2 cR;AH2 cG;AH2 cB;
//          // Need 32-bit for depth.
//          AF2 z;
//          AH2 mvX;AH2 mvY;
//          // Will need to get 2 sets of values for the 16-bit version.
//          // This assumes the pass before CPF does not support packed 16-bit.
//          PassBeforeCpfH(cR.x,cG.x,cB.x,z.x,mvX.x,mvY.x,gxy);
//          PassBeforeCpfH(cR.y,cG.y,cB.y,z.y,mvX.y,mvY.y,gxy+AU2(8,0));
//          AH2 coc;
//          coc.x=AH1(CpfCoc(z.x,const0,const1));
//          coc.y=AH1(CpfCoc(z.y,const0,const1));
//          CpfPreH(gxy,cR,cG,cB,coc,mvX,mvY);
//         #endif
//  (2.) Next add the CPF pass.
//       Both the 16-bit and 32-bit version work on one 8x8 tile.
//       The packed 16-bit version works on prior and current image in hi/lo 16-bits instead of 2 tiles.
//       It is advised to do some extra number of tiles (via loop unrolling) to increase performance.
//       Profile to see what is best.
//       Example for Vulkan without loop unrolling,
//        layout(local_size_x=64)in;
//        void main(){
//         #ifdef CPF_32BIT
//          AU2 lxy=ARmpRed8x8(gl_LocalInvocationID.x);
//          AU2 gxy=lxy+AU2(gl_WorkGroupID.x<<3u,gl_WorkGroupID.y<<3u);
//          CpfRec(AU2(gl_WorkgroupID.xy),gxy);
//         #endif
//         #ifdef CPF_16BIT
//          AW2 lxy=ARmpRed8x8H(gl_LocalInvocationID.x);
//          AW2 gxy=lxy+AW2(gl_WorkGroupID.x<<3u,gl_WorkGroupID.y<<3u);
//          CpfRecH(AU2(gl_WorkGroupID.xy),gxy);
//         #endif
//  (3.) In the pass after CPF use the cleaner function to fetch the output color of CPF.
//       This pass needs to be a {64,1,1} workgroup, and use the 'ARmpRed8x8()' function to reconfigure into an 8x8 block.
//       The 32-bit version of the code will work on 8x8 tiles.
//       The 16-bit version of the code will work on two 8x8 tiles in a 16x8 foot-print.
//       It is advised to do some extra number of tiles (via loop unrolling) to increase performance.
//       Profile to see what is best.
//       Example for Vulkan without loop unrolling,
//        layout(local_size_x=64)in;
//        void main(){
//         // 32-bit version.
//         #ifdef CPF_32BIT
//          // Remapped local xy in workgroup.
//          AU2 lxy=ARmpRed8x8(gl_LocalInvocationID.x);
//          // Global xy in kernel.
//          AU2 gxy=lxy+AU2(gl_WorkGroupID.x<<3u,gl_WorkGroupID.y<<3u);
//          // Color.
//          AF1 cR,cG,cB;
//          // Run the cleaner.
//          CpfCln(cR,cG,cB,gxy);
//          // Optionally filter through the debug visualization tool (use the 'CPF_BUG' define to control).
//          CpfBug(cR,cG,cB,gxy);
//          // Do whatever processing is desired (composite in UI, tonemap, film grain, etc).
//          ...
//         #endif
//         // 16-bit version.
//         #ifdef CPF_16BIT
//          AW2 lxy=ARmpRed8x8H(gl_LocalInvocationID.x);
//          AW2 gxy=lxy+AW2(gl_WorkGroupID.x<<4u,gl_WorkGroupID.y<<3u);
//          // This version works on 2 8x8 tiles in a 16x8 foot-print.
//          AH2 cR,cG,cB;
//          CpfClnH(cR,cG,cB,gxy);
//          CpfBugH(cR,cG,cB,gxy);
//          // Do whatever processing is desired (composite in UI, tonemap, film grain, etc).
//          ...
//         #endif
// -----------
// Optimization checklist,
//  (0.) Check for double rate 16-bit support and run the associated shader permutations.
//       This is currently Vulkan only until DX gets the associated shader language support.
//       TODO: Correct way to check.
//  (1.) For 16-bit permutations, enable "VK_AMD_pipeline_compiler_control" ...
//       TODO: Correct way to do this.
//  (2.) Make sure {CpfPre*(),CpfCln*()} are merged inside existing passes.
//  (3.) Use semi-persistent wave loop unrolling ...
//       TODO: Details.
//  (4.) For Vulkan, remove the barriers between {CpfPre*(),CpfRec*(),CpfCln*()}, use Events only.
//  (5.) For Vulkan, descriptors used for stores and reads should have aliased layouts,
//       with "coherent" set for stores only, and make sure to NOT use "coherent" for reads.
//       This is not actually needed on AMD hardware as stores already have GLC=1 set.
//       TODO: Details.
//  (6.) For Vulkan, if running any of the passes in Async-Compute and use wave-limit tuning.
//       TODO: Details.
//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------------------------
// NOT SUPPORTED (TO BE REMOVED)
// =============================
//  - Scaling.
//     - Had a prototype working, didn't like the resampling artifacts.
//     - Make the reconstruction kernel really complex, esp with motion reconstruction.
//     - Could be possible, may come back to it someday.
//  - Non-micro depth of field.
//     - Reconstruction kernel got too complex to try to add larger DOF for now.
//  - Chromatic aberration.
//     - Cleaner's 3x3 kernel is already overloaded, it could be possible to add, but not interested for now.
//     - Might have to drop CA when the cleaner had already maxed out blur radius.
//  - Diffusion after motion blur.
//     - MDR to HDR transform is not stable enough to support diffusion after motion blur.
//  - Fast dithering functions?
//     - Accuracy is really needed for MDR 8-bit, so sticking with the ideal ones.
//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------------------------
// BUGS & TASKS LEFT PRIOR TO RELEASE (TO BE REMOVED)
// ==================================================
//  - Finish documentation, clean up documentation.
//  - Integration is complex, see if there are any ideas to simplify things.
//  - Add license and copyright blurb.
//  - Auto-exposure.
//  - Distortion.
//  - Resolve all remaining TODO items.
//  - Is motion vector dither now working in 16-bit? Or just banding at high speed?
//  - Alpha input to cleaner is bandy look into why.
//  - Diffusion noise weighting is maybe not working well.
//  - Noise reduction feedback for 16-bit has black in full HDR, fix that.
//  - Choose to remove or fully support 1/3 pixel jitter.
//  - Check to see if diffusion computation should be better spaced out across reconstruction pass.
//  - Decide if should limit taps for non-PSL and non-half version.
//  - Should micro-diffusion be adjusting resolve kernel (or just depend on cleaner)?
//  - Could be possible to extend foreground motion to get better edges?
//  - Does the CoC soft test need rework?
//  - What is the right amount of unrolling?
//  - Adjust diffusion feedback sampling by camera rotation?
//  - Optional application of diffusion to modulate dirt mask?
//  - Make the soft depth compare user adjustable?
//  - Get VK_AMD_pipeline_compiler_control and others into ffx_a.ush.
//  - Make sure diffusion multiplies by 1/N during sum instead of at end.
//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------------------------
// CHANGE LIST (TO BE REMOVED)
// ===========================
//  - 20200217
//     - Fixed compiler errors related to missing '_' for some macros.
//     - Corrected dof to AH1 in A_HALF version.
//  - 20200212
//     - Fixed NaN issues with diffusion in combination with noise reduction enabled.
//  - 20200128
//     - CpfMovXYH() added to optimize FP16 code better.
//     - ABsc01ToW2() code generation looks ok in isolated test case.
//     - Second pass on making CpfRec() not require A_HALF.
//     - Possible fix for CpfMovLim()??? TODO:Double check ranges going into the new saturates.
//     - TODO: Need to double check CPF_MOV_MAX usage everywhere (looks like a bug).
//     - TODO: CpfMovLimH() is totally broken (out of range, so fix that).
//==============================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                   DEVELOPER CONTROL KNOBS
//==============================================================================================================================
// These are for use when running CpfBug*() after CpfCln*().
// CPF_BUG define values and output,
//   0 - Off.
//  --
//   1 - Color dither pattern.
//   2 - Color dither pattern temporally.
//   3 - Diffusion upsample position dither pattern.
//   4 - Motion vector dither pattern.
//  --
//   5 - Color input to the cleaner (output from the reconstruction pass).
//   6 - Alpha input to the cleaner.
//  --
//   7 - Current frame color input to reconstruction (raw gamma 3.0 values so color is distorted and jittered).
//   8 - Current frame alpha input (Circle of Confusion) to reconstruction (raw).
//   9 - Current frame motion vector input to reconstruction (raw, high 8-bit in red, low 8-bit in blue).
//  --
//  10 - Noise reduction feedback (raw).
//  11 - Diffusion input (raw, not zoomed, should see shadow darkening on anything not temporally stable).
//  12 - Diffusion input alpha (raw, not zoomed, dark for temporally unstable).
//  -- 
//  13 - Absolute difference in frame color (raw, useful to check that jitter pattern is working on stills).
//  --
//  14 - Decoded motion vector with amplification (too see if dither is working right).
//  -- 
//  15 - Absolute difference in reprojected frame color (check if motion vectors are correct).
#ifndef CPF_BUG
 #define CPF_BUG 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// This adjust how much to zoom into the upper left corner of the view.
//  0 - 1:1 pixels.
//  1 - 1:2x2 pixels.
//  2 - 1:4x4 pixels and so on ... 
#ifndef CPF_BUG_ZOM
 #define CPF_BUG_ZOM 1
#endif
//==============================================================================================================================
// Control soft feather region of depth compare (see ascii art in the reconstruction pass docs).
// These are the 'x' in '1/x', increasing the value decreases the interval.
#ifndef CPF_COC_RAMP
 #define CPF_COC_RAMP 128.0
#endif
#ifndef CPF_COC_SAME
 #define CPF_COC_SAME 128.0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 1 to enable diffusion (aka bloom), default 0 is off.
#ifndef CPF_DFU
 #define CPF_DFU 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 0 to disable motion vector dither, default 1 is on.
#ifndef CPF_DMV 
 #define CPF_DMV 1
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 1 to enable micro depth of field, default 0 is off.
#ifndef CPF_MDF
 #define CPF_MDF 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// The {0 to 1} range is the "LDR target", the {1 to CPF_MDR} range is the peak HDR range supported for reconstruction.
// The reconstruction pass provides motion blur.
// Set this too high and the precision in the LDR range gets too small (screen grabs will show dithering).
// Set this too low and there won't be enough HDR range to support highlights.
// The default of 64.0 supports a compromise between some amount of dithering and maintaining color streaks in motion.
#ifndef CPF_MDR
 #define CPF_MDR 64.0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 1 to enable noise reduction, default 0 is off.
#ifndef CPF_NOZ
 #define CPF_NOZ 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 1 to enable programmable sample location based resolve (improves from 2x to 4x AA quality), default 0 is off.
#ifndef CPF_PSL
 #define CPF_PSL 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Set to 1 to use the smoother kernel (default 0 is sharper).
#ifndef CPF_SMOOTH
 #define CPF_SMOOTH 0
#endif
//------------------------------------------------------------------------------------------------------------------------------
// Choose the number of taps for the motion blur. Can only be {8,10, or 12}.
// TODO: What should the default actually be????????????????????????????????????????????????????????????????????????????????????
#ifndef CPF_TAP
 #define CPF_TAP 12
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                                            CODE
//
//==============================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                     SETTINGS WHICH ARE NOT INTENDED FOR DEVELOPER CONTROL
//==============================================================================================================================
// Contrast adaptive sharpening control knobs.
// Shift focus to micro details.
#define CDF_CAS_MIC 0
//------------------------------------------------------------------------------------------------------------------------------
// Shift focus to macro details.
#define CDF_CAS_MAC 0
//------------------------------------------------------------------------------------------------------------------------------
// The peak negative lobe for CAS.
// Go to far (too negative) and the screen will explode with noise, go to zero to turn off.
#define CDF_CAS_LOB (-1.0/3.0)
//==============================================================================================================================
 // Maximum number of samples used for any of the {DN,UN,FN}.
 #define CPF_DFU_N 32.0
//------------------------------------------------------------------------------------------------------------------------------
 // Diffusion control knobs.
 // Full-resolution sized pixels for down-sampling radius.
 #define CPF_DFU_DR 32.0
//------------------------------------------------------------------------------------------------------------------------------
 // Samples on circle.
 #define CPF_DFU_DN 32.0
//------------------------------------------------------------------------------------------------------------------------------
 // Similar values for up-sampling.
 #define CPF_DFU_UR 16.0
 #define CPF_DFU_UN 16.0
//------------------------------------------------------------------------------------------------------------------------------
 // Similar values for forward from down-sampling to up-sampling.
 #define CPF_DFU_FR 8.0
 #define CPF_DFU_FN 8.0
//------------------------------------------------------------------------------------------------------------------------------
 // Level blending base power.
 #define CPF_DFU_P 2.0
//==============================================================================================================================
// The {0 to 1} range is the "LDR target", the {1 to CPF_HDR} range is the peak HDR range supported.
// This is currently set to what is near the peak of FP16.
// TODO: This should likely not be configurable!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#ifndef CPF_HDR
 #define CPF_HDR 32768.0
#endif
//==============================================================================================================================
// Pixels of offset for 2x pattern.
// The 2xMSAA pattern is 1/4.
// However 1/4 looses all AA at 0.5 pixel phase of motion.
// Using 1/3 instead is a mid way compromise between motion and still quality.
#define CPF_JIT (1.0/4.0)
//==============================================================================================================================
// TODO: Perhaps make this user configurable since it can have a !/$ trade off (cache foot-print)???????????????????????????????
// Maximum number of pixels of motion for motion blur.
// This must be <= 127.0.
// Prior 56.0 seemed like a good trade off between max range and amount of dithering with HDR sources.
#define CPF_MOV_LIM 127.0
//------------------------------------------------------------------------------------------------------------------------------
// Need squared value divided by 128.0
#define CPF_MOV_MAX (CPF_MOV_LIM*CPF_MOV_LIM/128.0)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                     [CPF] [JIT] JITTER
//------------------------------------------------------------------------------------------------------------------------------
// Viewport jitter is a fixed 2x pattern.
//  1 .
//  . 0
//==============================================================================================================================
A_STATIC void CpfJit(outAF2 j,AU1 frame){j[0]=j[1]=AF1_AU1(AU1_AF1(AF1_(CPF_JIT))|(frame<<31));}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                        [CPF] [PSL] PROGRAMMABLE SAMPLE LOCATIONS
//------------------------------------------------------------------------------------------------------------------------------
// 8x pattern across 2x2 quad and 2 frames temporally: frame U={a,b,c,d} and frame V={E,F,G,H}.
// Pattern over 4x4 pixels shows the skewed grid pattern.
// Even frames are U.
// Odd  frames are V.
//  . . . . F : : : . . . . F : : :      . . . . : : : : . . . . : : : :      . . . . F : : : . . . . F : : :
//  . E . . : : : : . E . . : : : :      . . . . : : : : . . . . : : : :      . E . . : : : : . E . . : : : :
//  . . . . : : b : . . . . : : b :      . . . . : : b : . . . . : : b :      . . . . : : : : . . . . : : : :
//  . . . a : : : : . . . a : : : :      . . . a : : : : . . . a : : : :      . . . . : : : : . . . . : : : :
//  G : : : . . . . G : : : . . . .      : : : : . . . . : : : : . . . .      G : : : . . . . G : : : . . . .
//  : : : : . H . . : : : : . H . .      : : : : . . . . : : : : . . . .      : : : : . H . . : : : : . H . .
//  : : c : . . . . : : c : . . . .      : : c : . . . . : : c : . . . .      : : : : . . . . : : : : . . . .
//  : : : : . . . d : : : : . . . d      : : : : . . . d : : : : . . . d      : : : : . . . . : : : : . . . .
//  . . . . F : : : . . . . F : : :      . . . . : : : : . . . . : : : :      . . . . F : : : . . . . F : : :
//  . E . . : : : : . E . . : : : :      . . . . : : : : . . . . : : : :      . E . . : : : : . E . . : : : :
//  . . . . : : b : . . . . : : b :      . . . . : : b : . . . . : : b :      . . . . : : : : . . . . : : : :
//  . . . a : : : : . . . a : : : :      . . . a : : : : . . . a : : : :      . . . . : : : : . . . . : : : :
//  G : : : . . . . G : : : . . . .      : : : : . . . . : : : : . . . .      G : : : . . . . G : : : . . . .
//  : : : : . H . . : : : : . H . .      : : : : . . . . : : : : . . . .      : : : : . H . . : : : : . H . .
//  : : c : . . . . : : c : . . . .      : : c : . . . . : : c : . . . .      : : : : . . . . : : : : . . . .
//  : : : : . . . d : : : : . . . d      : : : : . . . d : : : : . . . d      : : : : . . . . : : : : . . . .
//  -------------------------------      -------------------------------      -------------------------------
//    Composite of 2 frames {U,V}             Positions for frame U                Positions for frame V
//------------------------------------------------------------------------------------------------------------------------------
// Pattern over 2x2 pixels, positions decomposed without jitter.
// Pixels {a,b,c,d} are centered on { 0.25, 0.25}.
// Pixels {E,F,G,H} are centered on {-0.25,-0.25}.
//  . . . . F : : :  -0.375
//  . E . . : : : :  -0.125
//  . . . . : : b :  +0.125
//  . . . a : : : :  +0.375
//  G : : : . . . .  -0.375
//  : : : : . H . .  -0.125
//  : : c : . . . .  +0.125
//  : : : : . . . d  +0.375
//  - - + + - - + +
//  0 0 0 0 0 0 0 0
//  . . . . . . . .
//  3 1 1 3 3 1 1 3
//  7 2 2 7 7 2 2 7
//  5 5 5 5 5 5 5 5
//------------------------------------------------------------------------------------------------------------------------------
// Offsets from center decomposed without jitter.
// Offsets are the same for {x,y} coordinates.
//  P   out X   out Y   x y f   x^y
//  -   -----   -----   - - -   ---
//  a   0.375   0.375   0 0 0   0
//  b   0.125   0.125   1 0 0   1
//  c   0.125   0.125   0 1 0   1
//  d   0.375   0.375   1 1 0   0
//  E  -0.125  -0.125   0 0 1
//  F  -0.375  -0.375   1 0 1
//  G  -0.375  -0.375   0 1 1
//  H  -0.125  -0.125   1 1 1
//------------------------------------------------------------------------------------------------------------------------------
// Offsets decomposed with fixed PSL positions and jitter.
//  P   out X   out Y   x y f   x^y   jit X   jit Y
//  -   -----   -----   - - -   ---   -----   -----
//  a   0.125   0.125   0 0 0   0     0.25    0.25
//  b  -0.125  -0.125   1 0 0   1     0.25    0.25
//  c  -0.125  -0.125   0 1 0   1     0.25    0.25
//  d   0.125   0.125   1 1 0   0     0.25    0.25
//  E   0.125   0.125   0 0 1        -0.25   -0.25
//  F  -0.125  -0.125   1 0 1        -0.25   -0.25
//  G  -0.125  -0.125   0 1 1        -0.25   -0.25
//  H   0.125   0.125   1 1 1        -0.25   -0.25
//==============================================================================================================================
// This first function is decomposed without jitter.
// Given pixel position p{x,y} on screen, and frame {f} count, this returns pixel offset from center of pixel.
// For a given frame pattern repeats every 2x2 pixels.
// The {x,y} offset is the same for each axis.
A_STATIC AF1 CpfPsl(inAU2 p,AU1 f){
 AF1 xy=AF1_((p[0]^p[1])&AU1_(1));
 AF1 i=AF1_(f&AU1_(1));
 return xy*AF1_(-0.25)+(AF1_(0.375)+i*AF1_(-0.5));}
//------------------------------------------------------------------------------------------------------------------------------
// This function is composed with FpfJit() jitter, so frame index does not matter, same pattern can be used for both frames.
A_STATIC AF1 CpfPslJ(inAU2 p){AF1 xy=AF1_((p[0]^p[1])&AU1_(1));return xy*AF1_(-0.25)+AF1_(0.125);}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                               [CPF] [BLK] CONSTANT BLOCK SETUP
//------------------------------------------------------------------------------------------------------------------------------
// Constants for all functions are computed and packed here into 128-byte "cacheline" optimal chunks. 
//==============================================================================================================================
#if defined(A_GPU) // Volkan : AU4 is not defined on CPU, excluding this to A_GPU
A_STATIC void CpfBlk(
AU1 frame, // Frame count.
AF1 width, // Render size in pixels.
AF1 height,
AF1 denoise, // Stops of denoise.
AF1 diffusion){ // Stops of diffusion.
//------------------------------------------------------------------------------------------------------------------------------
 // CpfPre*() constants.
 // Denoise constants.
 AU4 con;
 varAF2(jit0);
 varAF2(jit1);
 CpfJit(jit0,frame);
 CpfJit(jit1,frame-AU1_(1));
 varAF2(jit);
 jit[0]=jit0[0]-jit1[0];
 jit[1]=jit0[1]-jit1[1];
 // Scale.
 con[0]=AU1_AF1(ARcpF1(width));
 con[1]=AU1_AF1(ARcpF1(height));
 // Bias.
 con[2]=AU1_AF1(AF1_(0.5)*ARcpF1(width)+jit[0]*ARcpF1(width));
 con[3]=AU1_AF1(AF1_(0.5)*ARcpF1(height)+jit[1]*ARcpF1(height));
 // This is shared for 32-bit and 16-bit.
 #define CPF_C32_PRE0 0
 #define CPF_C16_PRE0 16
 CpfPut(CPF_C32_PRE0,con);
 CpfPut(CPF_C16_PRE0,con);
 // This is different for 32-bit and 16-bit.
 // Denoise amount.
 con[0]=AU1_AF1(exp2(-denoise));
 // Dither base in low bits and even/odd frame in high bits.
 con[1]=((frame&AU1_(1023))*AU1_(9))+((frame&AU1_(1))<<16);
 // Width and height.
 con[2]=AU1_AF1(width);
 con[3]=AU1_AF1(height);
 #define CPF_C32_PRE1 1
 CpfPut(CPF_C32_PRE1,con);
 // 16-bit is slightly different.
 // Tile shift.
 con[0]=AU1_AF1(AF1_(8.0)*ARcpF1(width));
 // Denoise amount in lower bits.
 varAF2(t);
 t[0]=exp2(-denoise);
 t[1]=AF1_(0);
 con[1]=AU1_AH2_AF2(t);
 // Index in the high bits.
 con[1]=(con[1]&AU1_(65535))+((frame&AU1_(1))<<16);
 // Dither base is packed for two tiles.
 con[2]=((frame&AU1_(1023))*AU1_(9));
 // The second tile needs an 8 pixel offset.
 con[2]=con[2]+((con[2]+AU1_(8))<<16);
 // Width and height is packed.
 t[0]=width;
 t[1]=height;
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_PRE1 17
 CpfPut(CPF_C16_PRE1,con);
//------------------------------------------------------------------------------------------------------------------------------
 // CpfRec*() and CpfDfu*() constants.
 // 32-bit.
 // Rcp frame size. 
 con[0]=AU1_AF1(ARcpF1(width));
 con[1]=AU1_AF1(ARcpF1(height));
 // Even/odd frame as -1/1.
 con[2]=AU1_AF1(((frame&AU1_(1))==AU1_(1))?AF1_(-1.0):AF1_(1.0));
 // Pack this right after CpfPre*() constants to share the same cacheline.
 #define CPF_C32_REC0 2
 CpfPut(CPF_C32_REC0,con);
 // Diffusion.
 // Limit per level.
 AU1 w=AU1(width);
 AU1 h=AU1(height);
 con[0]=(w+AU1_(63))>>(2+3);
 con[1]=(h+AU1_(63))>>(2+3);
 con[2]=(w+AU1_(127))>>(3+3);
 con[3]=(h+AU1_(127))>>(3+3);
 #define CPF_C32_DFU0 3
 CpfPut(CPF_C32_DFU0,con);
 con[0]=(w+AU1_(255))>>(4+3);
 con[1]=(h+AU1_(255))>>(4+3);
 con[2]=(w+AU1_(511))>>(5+3);
 con[3]=(h+AU1_(511))>>(5+3);
 #define CPF_C32_DFU1 4
 CpfPut(CPF_C32_DFU1,con);
 con[0]=(w+AU1_(1023))>>(6+3);
 con[1]=(h+AU1_(1023))>>(6+3);
 con[2]=(w+AU1_(2047))>>(7+3);
 con[3]=(h+AU1_(2047))>>(7+3);
 #define CPF_C32_DFU2 5
 CpfPut(CPF_C32_DFU2,con);
 // Scaling per level.
 AF1 rw=ARcpF1(width);
 AF1 rh=ARcpF1(height);
 con[0]=AU1_AF1(rw*AF1_(4.0));
 con[1]=AU1_AF1(rh*AF1_(4.0)); 
 con[2]=AU1_AF1(rw*AF1_(4.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(4.0*0.5)); 
 #define CPF_C32_DFU3 6
 CpfPut(CPF_C32_DFU3,con);
 con[0]=AU1_AF1(rw*AF1_(8.0));
 con[1]=AU1_AF1(rh*AF1_(8.0)); 
 con[2]=AU1_AF1(rw*AF1_(8.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(8.0*0.5)); 
 #define CPF_C32_DFU4 7
 CpfPut(CPF_C32_DFU4,con);
 con[0]=AU1_AF1(rw*AF1_(16.0));
 con[1]=AU1_AF1(rh*AF1_(16.0)); 
 con[2]=AU1_AF1(rw*AF1_(16.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(16.0*0.5)); 
 #define CPF_C32_DFU5 8
 CpfPut(CPF_C32_DFU5,con);
 con[0]=AU1_AF1(rw*AF1_(32.0));
 con[1]=AU1_AF1(rh*AF1_(32.0)); 
 con[2]=AU1_AF1(rw*AF1_(32.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(32.0*0.5)); 
 #define CPF_C32_DFU6 9
 CpfPut(CPF_C32_DFU6,con);
 con[0]=AU1_AF1(rw*AF1_(64.0));
 con[1]=AU1_AF1(rh*AF1_(64.0)); 
 con[2]=AU1_AF1(rw*AF1_(64.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(64.0*0.5)); 
 #define CPF_C32_DFU7 10
 CpfPut(CPF_C32_DFU7,con);
 con[0]=AU1_AF1(rw*AF1_(128.0));
 con[1]=AU1_AF1(rh*AF1_(128.0)); 
 con[2]=AU1_AF1(rw*AF1_(128.0*0.5));
 con[3]=AU1_AF1(rh*AF1_(128.0*0.5));
 #define CPF_C32_DFU8 11
 CpfPut(CPF_C32_DFU8,con); 
 // 16-bit.
 // Rcp frame size. 
 con[0]=AU1_AF1(ARcpF1(width));
 con[1]=AU1_AF1(ARcpF1(height));
 // Even/odd frame as -1/1.
 t[0]=((frame&AU1_(1))==AU1_(1))?AF1_(-1.0):AF1_(1.0);
 t[1]=0.0;
 con[2]=AU1_AH2_AF2(t);
 // Pack in 16-bit rcp frame size (for diffusion).
 t[0]=ARcpF1(width);
 t[1]=ARcpF1(height);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_REC0 18
 CpfPut(CPF_C16_REC0,con);
 // Diffusion.
 // Limit per level and scaling per level, this is done different than the 32-bit path.
 con[0]=(w+AU1_(63))>>(2+3);
 con[1]=(h+AU1_(63))>>(2+3);
 t[0]=rw*AF1_(4.0);
 t[1]=rh*AF1_(4.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(4.0*0.5);
 t[1]=rh*AF1_(4.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU0 19
 CpfPut(CPF_C16_DFU0,con);
 con[0]=(w+AU1_(127))>>(3+3);
 con[1]=(h+AU1_(127))>>(3+3);
 t[0]=rw*AF1_(8.0);
 t[1]=rh*AF1_(8.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(8.0*0.5);
 t[1]=rh*AF1_(8.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU1 20
 CpfPut(CPF_C16_DFU1,con);
 con[0]=(w+AU1_(255))>>(4+3);
 con[1]=(h+AU1_(255))>>(4+3);
 t[0]=rw*AF1_(16.0);
 t[1]=rh*AF1_(16.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(16.0*0.5);
 t[1]=rh*AF1_(16.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU2 21
 CpfPut(CPF_C16_DFU2,con);
 con[0]=(w+AU1_(511))>>(5+3);
 con[1]=(h+AU1_(511))>>(5+3);
 t[0]=rw*AF1_(32.0);
 t[1]=rh*AF1_(32.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(32.0*0.5);
 t[1]=rh*AF1_(32.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU3 22
 CpfPut(CPF_C16_DFU3,con);
 con[0]=(w+AU1_(1023))>>(6+3);
 con[1]=(h+AU1_(1023))>>(6+3);
 t[0]=rw*AF1_(64.0);
 t[1]=rh*AF1_(64.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(64.0*0.5);
 t[1]=rh*AF1_(64.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU4 23
 CpfPut(CPF_C16_DFU4,con);
 con[0]=(w+AU1_(2047))>>(7+3);
 con[1]=(h+AU1_(2047))>>(7+3);
 t[0]=rw*AF1_(128.0);
 t[1]=rh*AF1_(128.0);
 con[2]=AU1_AH2_AF2(t);
 t[0]=rw*AF1_(128.0*0.5);
 t[1]=rh*AF1_(128.0*0.5);
 con[3]=AU1_AH2_AF2(t);
 #define CPF_C16_DFU5 24
 CpfPut(CPF_C16_DFU5,con);
//------------------------------------------------------------------------------------------------------------------------------
 // CpfCln*() constants.
 // 32-bit.
 con[0]=AU1_AF1(ARcpF1(width));
 con[1]=AU1_AF1(ARcpF1(height));
 // This controls radius for dithered sampling of macro-difusion.
 AF1 k=AF1_(0.707*4.0);
 t[0]=k*ARcpF1(width*ARcpF1(AF1_(4.0)));
 t[1]=k*ARcpF1(height*ARcpF1(AF1_(4.0)));
 con[2]=AU1_AF1(t[0]);
 con[3]=AU1_AF1(t[1]);
 #define CPF_C32_CLN0 12
 CpfPut(CPF_C32_CLN0,con);
 // This is just the lerp and 1-lerp for diffusion.
 k=exp2(-diffusion);
 con[0]=AU1_AF1(k);
 k=AF1_(1.0)-k;
 con[1]=AU1_AF1(k);
 #define CPF_C32_CLN1 13
 CpfPut(CPF_C32_CLN1,con);
 // 16-bit is packed differently.
 t[0]=ARcpF1(width);
 t[1]=ARcpF1(height);
 con[0]=AU1_AH2_AF2(t);
 k=AF1_(0.707*4.0);
 t[0]=k*ARcpF1(width*ARcpF1(AF1_(4.0)));
 t[1]=k*ARcpF1(height*ARcpF1(AF1_(4.0)));
 con[1]=AU1_AH2_AF2(t); 
 t[0]=exp2(-diffusion);
 t[1]=AF1_(1.0)-t[0];
 con[2]=AU1_AH2_AF2(t); 
 #define CPF_C16_CLN0 25
 CpfPut(CPF_C16_CLN0,con);}
#endif // A_GPU
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                            [CPF] [COC] CIRCLE OF CONFUSION MODEL
//------------------------------------------------------------------------------------------------------------------------------
// Physically correct model is roughly: CoC=abs(1-focus/depth), where CoC at infinite depth is 1.0.
// A physically correct model suffers from some impossible constrains: infinte CoC for near field.
// If near CoC is clamped then the image looks substantially wrong as objects near the camera.
// If CoC is set at maximum practical size at near plane, peak CoC at infinite distance tends to be too small.
// So this module adopted a non-physically correct model with the following constraints,
//  - CoC at zero must be 1.0 (peak size)
//  - CoC at focus must be 0.0
//  - CoC at infinite depth must be 'm' where 'm<=1.0' (allows bokeh in distance to get smaller than peak size)
//  - Slope around focus must be matching on both sides
// FP16 precision not going to work here because input is rendered depth, and constants can get quite large.
//------------------------------------------------------------------------------------------------------------------------------
// MATHS
// =====
// Near ... -pow(focus,-s*m)   * pow(z, s*m) + 1
// Far ....  pow(focus, s  )*m * pow(z,-s  ) + (-m)
//          ^^^^^^^^^^^^^^^^^^         ^^^^    ^^^^
//          c0                         c1      c2
// Where
//  - Negative values are far field, and positive are near field, so abs(CoC) provides circle size
//  - The 'focus' is the focal plane
//  - The constant 's' controls how fast to get to out-of-focus: 0:=never, >0:=faster, 1:=physical far field
//  - The constant 'm' controls max size at infinite depth: 0:=off, 1:=maximum size
//  - There are two versions of the constants {c0,c1,c2} depending on near vs far.
//------------------------------------------------------------------------------------------------------------------------------
// TODO
// ====
//  - See how system handles changing focus and parameters live with temporal feedback.
// =============================================================================================================================
// Setup the constants for depth to CoC conversion.
A_STATIC void CpfCocIni(outAF4 k0,outAF3 k1,AF1 focus,AF1 s,AF1 m){
 k0[0]=-pow(focus,-s*m);k0[1]=pow(focus,s)*m;
 k0[2]=s*m;k0[3]=-s;
 k1[0]=1.0;k1[1]=-m;
 k1[2]=focus;} 
//------------------------------------------------------------------------------------------------------------------------------
#if defined(A_GPU)
 // Returned signed CoC from {1:near to 0:focus to -1:far}.
 AF1 CpfCoc(
 AF1 z, // Depth range from {0 to +inf}.
 AF4 k0,AF3 k1){ // Constants generated by CpfCocIni().
  AP1 near=z<k1.z;
  AF1 c0=near?k0.x:k0.y;
  AF1 c1=near?k0.z:k0.w;
  AF1 c2=near?k1.x:k1.y;
  return c0*pow(z,c1)+c2;}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                     [CPF] [DIT] DITHERING
//------------------------------------------------------------------------------------------------------------------------------
// Many kinds of dithering are used, some to dither position for loads, others to output values to fit in a low bit depth.
//==============================================================================================================================
#if defined(A_GPU)
 // Hand tuned integer position to dither value, with more values than simple checkerboard.
 // This is used to dither color.
 AF1 CpfDit(AU2 p,AU1 f){
  AF1 x=AF1_(p.x+f);
  AF1 y=AF1_(p.y);
  // The 1.61803 golden ratio.
  AF1 a=AF1_((1.0+sqrt(5.0))/2.0);
  // Number designed to provide a good visual pattern.
  AF1 b=AF1_(1.0/3.69);
  x=x*a+(y*b);
  return AFractF1(x);}
//------------------------------------------------------------------------------------------------------------------------------
 // TODO: Fix me like CpfDit3()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // This version is 7-bit gamma 2.0, with extra abs of input, and does not re-normalize at the end.
 // The 'c' input is {0 to 127*128}, pre-scaled so the sqrt() drops this into integer values in the output space.
 // Output is {0 to 127}.
 AF1 CpfDit2(AF1 c,AF1 dit){
  // TODO: Should faster approximations be used (as this is only for motion vector)?????????????????????????????????????????????
  c=abs(c);
  AF1 n=sqrt(c);
  #if (CPF_DMV==0)
   return n;
  #else
   n=floor(n);
   AF1 a=n*n;
   AF1 b=n+AF1_(1.0);b=b*b;
   // TODO: Will APrxLoRcpF1() work here????????????????????????????????????????????????????????????????????????????????????????
   AF1 r=(c-b)*APrxMedRcpF1(a-b);
   return n+AGtZeroF1(dit-r);
  #endif
 }
//------------------------------------------------------------------------------------------------------------------------------
 // Approximate energy conserving dither to 8-bit gamma 3.0 without dither overlap.
 // Where 'c' is the  linear color {0 to 1}, and 'dit' is a {0 to 1} dither value.
 // 27 op clk.
 AF1 CpfDit3(AF1 c,AF1 dit){
  // Convert to non-linear and scale (EXP2,MUL,LOG2).
  AF1 n=pow(c,AF1_(1.0/3.0));
  // Floor quantize to 8-bit precision (MUL,FLOOR,MUL).
  n=AF1_(1.0/255.0)*floor(n*AF1_(255.0));
  // Back to linear, first encoding option (MUL,MUL).
  AF1 a=n*n*n;
  // Build second encoding option (ADD,MUL,MUL).
  AF1 b=n+AF1_(1.0/255.0);b=b*b*b;
  // Ratio of 'a' to 'b' required to produce 'c' (ADD,ADD,MUL,IADD,FMA,MUL).
  // APrxLoRcpF1() won't work here (at least for very high CPF_MDR ranges).
  // APrxMedRcpF1() is an IADD,FMA,MUL.
  AF1 r=(c-b)*APrxMedRcpF1(a-b);
  // Use the ratio as a cutoff to choose 'a' or 'b' (ADD,MUL,ADD,MUL).
  // This scales back to {0 to 1} for images stores, also AGtZeroF1() is a MUL.
  return n+AF1_(1.0/255.0)*AGtZeroF1(dit-r);}
//------------------------------------------------------------------------------------------------------------------------------
 // Convert a {0 to 1} value into a vector on cicle of radius -1/4.
 void CpfDitC(out AF1 x,out AF1 y,AF1 v){v=v*AF1_(2.0)-AF1_(1.0);x=APCosF1(v);y=APSinF1(v);}
//------------------------------------------------------------------------------------------------------------------------------
 // Fixed dither used by diffusion upsample.
 // This is the same for both tiles in the 16-bit mode.
 // Convert a pixel position into a vector on cicle of radius -1/4.
 AF2 CpfDitD(AU2 p){return APSinCosF1(AF1((p.x+p.y+p.y)&AU1_(3))*AF1_(0.5)+AF1_(-0.75));}
//------------------------------------------------------------------------------------------------------------------------------
 // Fixed checker dither used by motion blur.
 // Motion needs a maximum dither output range of {-1 to 1}.
 // This returns -0.5*k or 0.5*k to stay centered in cells.
 // The 'k' input must be a compile time literal.
 AF1 CpfDitM(AU2 p,AF1 k){return AF1((p.x+p.y)&AU1_(1))*k-AF1_(0.5*k);}
#endif
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 // 16-bit does not have enough precision for this computation.
 // TODO: Now that this is 32-bit, reoptimize!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // TODO: Pattern seems strange!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // Note 'f.y=f.x+8', this is so 2nd tile offset is factored into constant for dither base.
 AH2 CpfDitH(AW2 p,AW2 f){
  AF2 x=AF2_(AW2_(p.x)+f);
  AF1 y=AF1_(p.y);
  AF1 a=AF1_((1.0+sqrt(5.0))/2.0);
  AF1 b=AF1_(1.0/3.69);
  x=x*AF2_(a)+(AF2_(y*b));
  return AH2(AFractF2(x));}
//------------------------------------------------------------------------------------------------------------------------------
 // TODO: Double check this has enough precision for maximum motion vector length!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // This is only used for motion vector encoding, and the 'c' input must be >=0.
 AH2 CpfDit2H(AH2 c,AH2 dit){
  #if 0
   // TODO: Remove me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   c=abs(c);
  #endif
  AH2 n=sqrt(c);
  #if (CPF_DMV==0)
   return n;
  #else
   n=floor(n);
   AH2 a=n*n;
   AH2 b=n+AH2_(1.0);b=b*b;
   AH2 r=(c-b)*APrxMedRcpH2(a-b);
   return n+AGtZeroH2(dit-r);
  #endif
 }
//------------------------------------------------------------------------------------------------------------------------------
 // 36 op clk for a pair (18 op clk/item).
 AH2 CpfDit3H(AH2 c,AH2 dit){
  AH2 n=pow(c,AH2_(1.0/3.0));
  n=AH2_(1.0/255.0)*floor(n*AH2_(255.0));
  AH2 a=n*n*n;
  AH2 b=n+AH2_(1.0/255.0);b=b*b*b;
  AH2 r=(c-b)*APrxMedRcpH2(a-b);
  return n+AH2_(1.0/255.0)*AGtZeroH2(dit-r);}
//------------------------------------------------------------------------------------------------------------------------------
 void CpfDitCH(out AH2 x,out AH2 y,AH2 v){v=v*AH2_(2.0)-AH2_(1.0);x=APCosH2(v);y=APSinH2(v);}
//------------------------------------------------------------------------------------------------------------------------------
 AH2 CpfDitDH(AW2 p){return APSinCosH1(AH1((p.x+p.y+p.y)&AW1_(3))*AH1_(0.5)+AH1_(-0.75));}
//------------------------------------------------------------------------------------------------------------------------------
 // This is the same for both images.
 AH1 CpfDitMH(AW2 p,AH1 k){return AH1((p.x+p.y)&AW1_(1))*k-AH1_(0.5*k);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                              [CPF] [MDR] MEDIUM DYNAMIC RANGE
//------------------------------------------------------------------------------------------------------------------------------
// In order to manage color in only 8-bits per channel (so alpha can have 8-bit circle of confusion), 
// range is reduced from CPF_HDR to CPF_MDR for inputs to the reconstruction pass.
// Range is later expanded prior to store to 16-bit per channel in the reconstruction pass.
// This does a color ratio preserving mapping to avoid desaturation artifacts.
//------------------------------------------------------------------------------------------------------------------------------
// TODO: Can this use APrxMedRcp*()?????????????????????????????????????????????????????????????????????????????????????????????
//==============================================================================================================================
#if defined(A_GPU)
 // Input is {0 to CPF_HDR}, output is {0 to 1} where 1 represents CPF_MDR.
 // 10 op clk.
 void CpfMdrFromHdr(inout AF1 r,inout AF1 g,inout AF1 b){
  AF1 m=AF1_(1.0/(CPF_MDR))*ARcpF1(AF1_(1.0/(CPF_MDR))*AMax3F1(r,g,b)+AF1_(1.0));r*=m;g*=m;b*=m;}
//------------------------------------------------------------------------------------------------------------------------------
 // Input is {0 to 1} where 1 represents CPF_MDR, output is {0 to CPF_HDR}.
 // The min makes sure 1 maps to at most HDR/MDR.
 // 10 op clk.
 void CpfMdrToHdr(inout AF3 c){
  AF1 m=min(AF1_((CPF_HDR)),ARcpF1(AF1_(-1.0/(CPF_MDR))*AMax3F1(c.r,c.g,c.b)+AF1_(1.0/(CPF_MDR))));c*=AF3_(m);}
#endif
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 // 15 op clk for a pair (7.5 op clk/item).
 void CpfMdrFromHdrH(inout AH2 r,inout AH2 g,inout AH2 b){
  AH2 m=AH2_(1.0/(CPF_MDR))*ARcpH2(AH2_(1.0/(CPF_MDR))*AMax3H2(r,g,b)+AH2_(1.0));r*=m;g*=m;b*=m;}
//------------------------------------------------------------------------------------------------------------------------------
 // This runs without packed loop unrolling.
 void CpfMdrToHdrH(inout AH3 c){
  AH1 m=min(AH1_((CPF_HDR)),ARcpH1(AH1_(-1.0/(CPF_MDR))*AMax3H1(c.r,c.g,c.b)+AH1_(1.0/(CPF_MDR))));c*=AH3_(m);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                             [CPF] [MOV] MOTION VECTOR PACKING
//------------------------------------------------------------------------------------------------------------------------------
// 16-bit motion vector 16-bit.
// Want this to stay packed in VGPRs, and also enables easy way to find mv for nearest (see code).
//------------------------------------------------------------------------------------------------------------------------------
// 0000000000000000
// fedcba9876543210
// ================
// yyyyyyyyxxxxxxxx  {x,y} motion vector -/+ 127 output pixels via dither signed gamma 2 and then [BSC] conversion. 
//==============================================================================================================================
#if defined(A_GPU)
 // Limit motion vector to maximum dims, and scale for dither.
 // The {x,y} units into this function are in pixels.
 void CpfMovLim(inout AF1 x,inout AF1 y){
  // TODO: APrxLoRsqF1() won't work here yet (returns stuff out of range), fix that!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Zero handling:
  //  - A '1/sqrt(0)' can introduce +INF on rsqD2.
  //  - Then 'd2:=0 * rsqD2:=+INF' -> yields NaN.
  //  - Then 'min(x,NaN)=x' so need to transform NaN into zero before min with minimum length.
  //  - Then '0 * rsqD2:=+INF' -> yields NaN, and thus need a saturate.
  #if 0
   // TODO: Remove me, old broken code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AF1 d2=x*x+y*y;AF1 rsqD2=ARsqF1(d2);AF1 d=min(AF1_(CPF_MOV_MAX),d2*rsqD2)*rsqD2*AF1_(128.0);x*=d;y*=d;
  #else
   // TODO: Validate possible workaround!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AF1 d2=x*x+y*y;AF1 rsqD2=ARsqF1(d2);
   AF1 d=ASatF1(min(AF1_(CPF_MOV_LIM),max(AF1_(0.0),d2*rsqD2))*rsqD2)*AF1_(128.0);x*=d;y*=d;
  #endif
  }
//------------------------------------------------------------------------------------------------------------------------------
 // Pack for store, this will limit motion vector, and dither.
 // The {x,y} units into this function are in pixels.
 AU1 CpfMovPck(AF1 x,AF1 y,AF1 dit){
  CpfMovLim(x,y);
  // Dither abs and restore sign.
  x=ACpySgnF1(CpfDit2(x,dit),x);
  y=ACpySgnF1(CpfDit2(y,dit),y);
  // Encode.
  return ABsc1ToU1(ABsc0ToU1(AU1_(0),x),y);}
//------------------------------------------------------------------------------------------------------------------------------
 // Unpack a component, multiplier setup to avoid precision loss.
 AF1 CpfMovX(AU1 p){AF1 v=ABsc0FromU1(p);return abs(v)*v*ARcpF1(128.0);}
 AF1 CpfMovY(AU1 p){AF1 v=ABsc1FromU1(p);return abs(v)*v*ARcpF1(128.0);}
#endif
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 // TODO: Validate this works!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 // This is a special version which works only with >=0 inputs.
 void CpfMovLimH(inout AH2 x,inout AH2 y){
  // Scale so maximum input of around 64K is at most 128, so length^2 won't overflow.
  AH2 ax=x*AH2_(1.0/512.0);AH2 ay=y*AH2_(1.0/512.0);
  AH2 d2=ax*ax+ay*ay;
  // A '1/sqrt(0)' can introduce +INF on rsqD2.
  AH2 rsqD2=ARsqH2(d2);
  // Then 'd2:=0 * rsqD2:=+INF' -> yields NaN.
  rsqD2*=AH2_(CPF_MOV_LIM);
  ax*=rsqD2;ay*=rsqD2;
  // NaN for ax and ay will get replaced by input x and y.
  x=min(x,ax);y=min(y,ay);
  x*=AH2_(128.0);y*=AH2_(128.0);}
//------------------------------------------------------------------------------------------------------------------------------
 // TODO: Optimize this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 AW2 CpfMovPckH(AH2 x,AH2 y,AH2 dit){
  AH2 ax=abs(x);
  AH2 ay=abs(y);
  CpfMovLimH(ax,ay);
  x=ACpySgnH2(CpfDit2H(ax,dit),x);
  y=ACpySgnH2(CpfDit2H(ay,dit),y);
  x*=AH2_(A_BSC_16/128.0);
  y*=AH2_(A_BSC_16/128.0);
  return ABsc01ToW2(x,y);}
//------------------------------------------------------------------------------------------------------------------------------
 // Unpack and finish decode in parallel.
 // This uses ABuc<0,1>FromU1() instead of ABsc<0,1>FromU1() so that the -128.0 can be parallelized.
 AH2 CpfMovXYH(AU1 p){AH2 v=AH2(AH1(ABuc0FromU1(p)),AH1(ABuc1FromU1(p)))+AH2_(-128.0);return abs(v)*v*AH2_(1.0/128.0);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                [CPF] [Z] SOFT DEPTH COMPARE
//------------------------------------------------------------------------------------------------------------------------------
// DEPTH COMPARE
// =============
// Depth is converted to Circle of Confusion which ranges max {1 = near, 0 = focus, -1 = infinite far}.
// This is converted to {1 = near, 0.5 = focus, 0 = infinite far} for data going into reconstruction.
// Soft depth compare for motion blur is done with CoC values.
//
//                                          full     coc      limit
//    0                                     far      near     good               1
//    |                                      |        |        |                 |
//    |--------------------------------------|-----|--|--|-----|-----------------|
//                                           .     .  .  .     .
//                    1.0 / CPF_COC_RAMP --->|<--->|  .  |<--->|
//                                           .     .  .  .     .
//  1 ........................................     .  .  .     .
//                                            \    .  .  .     .
//       [far value]                            \  .  .  .     .
//  0 ............................................\.  .  .     .
//                                                 .  .  .     .
//                    1.0 / CPF_COC_SAME --------->|<>|<>|     .
//                                                       .     .
//  1 ....................................................     .
//                                                        \    .
//       [good value]                                       \  .
//  0 ........................................................\.
//==============================================================================================================================
#if defined(A_GPU)
 // These all do 2 operations at once (one for U and one for V images).
 // Compute the good compare base.
 AF2 CpfZG(AF2 coc){return coc*AF2_(CPF_COC_RAMP)+AF2_(1.0+CPF_COC_RAMP/CPF_COC_SAME);}
 // Compute the far compare base.
 AF2 CpfZF(AF2 coc){return coc*AF2_(CPF_COC_RAMP)-AF2_(CPF_COC_RAMP/CPF_COC_SAME);}
 // Do the soft compare.
 AF2 CpfZ(AF2 coc,AF2 base){return ASatF2(coc*AF2_(-CPF_COC_RAMP)+base);}
//------------------------------------------------------------------------------------------------------------------------------
 // These all do one (for noise reduction, 32-bit only).
 AF1 CpfZG1(AF1 coc){return coc*AF1_(CPF_COC_RAMP)+AF1_(1.0+CPF_COC_RAMP/CPF_COC_SAME);}
 AF1 CpfZF1(AF1 coc){return coc*AF1_(CPF_COC_RAMP)-AF1_(CPF_COC_RAMP/CPF_COC_SAME);}
 AF1 CpfZ1(AF1 coc,AF1 base){return ASatF1(coc*AF1_(-CPF_COC_RAMP)+base);}
#endif
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 AH2 CpfZGH(AH2 coc){return coc*AH2_(CPF_COC_RAMP)+AH2_(1.0+CPF_COC_RAMP/CPF_COC_SAME);}
 AH2 CpfZFH(AH2 coc){return coc*AH2_(CPF_COC_RAMP)-AH2_(CPF_COC_RAMP/CPF_COC_SAME);}
 AH2 CpfZH(AH2 coc,AH2 base){return ASatH2(coc*AH2_(-CPF_COC_RAMP)+base);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                      [CPF] DEPACK FP16
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 // Used to convert from packed SOA to AOS for store.
 void CpfDepack3(out AH4 pix0,out AH4 pix1,AH2 pixR,AH2 pixG,AH2 pixB){
  pix0.rgb=AH3(pixR.x,pixG.x,pixB.x);
  pix1.rgb=AH3(pixR.y,pixG.y,pixB.y);
  #ifdef A_HLSL
   // Invoke a slower path for DX only, since it won't allow uninitialized values.
   pix0.a=pix1.a=0.0;
  #endif
 }
//------------------------------------------------------------------------------------------------------------------------------
 void CpfDepack4(out AH4 pix0,out AH4 pix1,AH2 pixR,AH2 pixG,AH2 pixB,AH2 pixA){
  pix0=AH4(pixR.x,pixG.x,pixB.x,pixA.x);
  pix1=AH4(pixR.y,pixG.y,pixB.y,pixA.y);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                               [CPF] [BUG] DEBUG VISUALIZATION
//
//------------------------------------------------------------------------------------------------------------------------------
// This is here to provide visual validation of aspects of the code.
//=============================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                         32-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)
 void CpfBug(inout AF1 colR,inout AF1 colG,inout AF1 colB,AU2 p){
  #if CPF_BUG==1
   colR=CpfDit(p>>CPF_BUG_ZOM,0);colR*=colR;colG=colB=colR;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==2
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constDit=const1.y&AU1_(65535);
   colR=colG=colB=CpfDit((p>>CPF_BUG_ZOM),constDit);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==3
   AF2 d=CpfDitD(p>>CPF_BUG_ZOM);
   colR=d.x*AF1_(2.0)+AF1_(1.0);
   colB=d.y*AF1_(2.0)+AF1_(1.0);
   colG=AF1_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==4
   AF1 d=CpfDitM(p>>CPF_BUG_ZOM,AF1_(1.0));
   d+=AF1_(1.0);
   colR=colG=colB=AF1_(d);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==5
   AF4 c=CpfClnLd(p>>CPF_BUG_ZOM);
   colR=c.r;colG=c.g;colB=c.b;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==6
   AF4 c=CpfClnLd(p>>CPF_BUG_ZOM);
   colR=colG=colB=c.a;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==7
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AF4 c=CpfColLd(constIdx,p>>CPF_BUG_ZOM);
   colR=c.r;colG=c.g;colB=c.b;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==8
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AF4 c=CpfColLd(constIdx,p>>CPF_BUG_ZOM);
   colR=colG=colB=c.a;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==9
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 c0=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   colR=AF1_(c0>>8)*AF1_(1.0/255.0);
   colB.x=AF1_(c0&AU1_(255))*AF1_(1.0/255.0);
   colG=AF1_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==10
   AH2 c0=CpfNozLd(p>>CPF_BUG_ZOM);
   AH2 c1=CpfNozLd((p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=AH2(c0.r,c1.r);
   colB=AH2(c0.g,c1.g);
   colG=AH2_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==11
   AF4 c=CpfDfuDwn0Ld(p>>2);
   colR=c.r;colG=c.g;colB=c.b;
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==12
   AF4 c=CpfDfuDwn0Ld(p>>2);
   colR=colG=colB=c.a;
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==13
   AF4 ca=CpfColLd(0,p>>CPF_BUG_ZOM);
   AF4 cb=CpfColLd(1,p>>CPF_BUG_ZOM);
   colR=abs(ca.r-cb.r);
   colG=abs(ca.g-cb.g);
   colB=abs(ca.b-cb.b);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==14
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 c=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   colG=AF1_(0.0);
   colR=AF1(abs(CpfMovX(c))*ARcpF1(CPF_MOV_MAX)*1024.0);
   colB=AF1(abs(CpfMovY(c))*ARcpF1(CPF_MOV_MAX)*1024.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==15
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 m=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   AF2 mxy=AF2(CpfMovX(m),CpfMovY(m));
   AF4 c0a=CpfColLd(constIdx,p>>CPF_BUG_ZOM);
   AU4 const0=CpfGet(CPF_C32_PRE0);
   AF2 constPMul=AF2_AU2(const0.xy);
   AF2 constPAdd=AF2_AU2(const0.zw);
   AF2 p0=AF2(p>>CPF_BUG_ZOM)*constPMul+constPAdd-mxy*constPMul;
   AF4 c0b=CpfColSm(constIdx^AU1_(1),p0);
   colR=abs(c0a.r-c0b.r);
   colG=abs(c0a.g-c0b.g);
   colB=abs(c0a.b-c0b.b);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
 }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                         16-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)
 void CpfBugH(inout AH2 colR,inout AH2 colG,inout AH2 colB,AW2 p){
  #if CPF_BUG==1
   colR=CpfDitH(p>>CPF_BUG_ZOM,AW2(0,8));colR*=colR;colG=colB=colR;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==2
   AU4 const1=CpfGet(CPF_C16_PRE1);
   AW2 constDit=AW2_AU1(const1.z);
   colR=CpfDitH(p>>CPF_BUG_ZOM,constDit);colR*=colR;colG=colB=colR;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==3
   AH2 d=CpfDitDH(p>>CPF_BUG_ZOM);
   colR=d.x*AH2_(2.0)+AH2_(1.0);
   colB=d.y*AH2_(2.0)+AH2_(1.0);
   colG=AH2_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==4
   AH1 d=CpfDitMH(p>>CPF_BUG_ZOM,AH1_(1.0));
   d+=AH1_(1.0);
   colR=colG=colB=AH2_(d);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==5
   AH4 c0=CpfClnLdH(p>>CPF_BUG_ZOM);
   AH4 c1=CpfClnLdH((p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=AH2(c0.r,c1.r);colG=AH2(c0.g,c1.g);colB=AH2(c0.b,c1.b);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==6
   AH4 c0=CpfClnLdH(p>>CPF_BUG_ZOM);
   AH4 c1=CpfClnLdH((p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=colG=colB=AH2(c0.a,c1.a);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==7
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AH4 c0=CpfColLdH(constIdx,p>>CPF_BUG_ZOM);
   AH4 c1=CpfColLdH(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=AH2(c0.r,c1.r);colG=AH2(c0.g,c1.g);colB=AH2(c0.b,c1.b);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==8
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AH4 c0=CpfColLdH(constIdx,p>>CPF_BUG_ZOM);
   AH4 c1=CpfColLdH(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=colG=colB=AH2(c0.a,c1.a);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==9
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 c0=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   AU1 c1=CpfMovLd(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   colR.x=AH1_(c0>>8)*AH1_(1.0/255.0);
   colR.y=AH1_(c1>>8)*AH1_(1.0/255.0);
   colB.x=AH1_(c0&AU1_(255))*AH1_(1.0/255.0);
   colB.y=AH1_(c1&AU1_(255))*AH1_(1.0/255.0);
   colG=AH2_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==10
   AH2 c0=CpfNozLd(p>>CPF_BUG_ZOM);
   AH2 c1=CpfNozLd((p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=AH2(c0.r,c1.r);
   colB=AH2(c0.g,c1.g);
   colG=AH2_(0.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==11
// TODO: Fix me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 0
   AH4 c0=AH4(CpfDfuDwn0Ld(AU2(p>>2)));
   AH4 c1=AH4(CpfDfuDwn0Ld(AU2((p+AW2(8,0))>>2)));
#else
   AH4 c0=AH4(CpfDfuUp0Ld(AU2(p>>2)));
   AH4 c1=AH4(CpfDfuUp0Ld(AU2((p+AW2(8,0))>>2)));
#endif
   colR=AH2(c0.r,c1.r);colG=AH2(c0.g,c1.g);colB=AH2(c0.b,c1.b);
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==12
   AH4 c0=AH4(CpfDfuDwn0Ld(AU2(p>>2)));
   AH4 c1=AH4(CpfDfuDwn0Ld(AU2((p+AW2(8,0))>>2)));
   colR=colG=colB=AH2(c0.a,c1.a);
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==13
   AH4 c0a=CpfColLdH(0,p>>CPF_BUG_ZOM);
   AH4 c1a=CpfColLdH(0,(p+AW2(8,0))>>CPF_BUG_ZOM);
   AH4 c0b=CpfColLdH(1,p>>CPF_BUG_ZOM);
   AH4 c1b=CpfColLdH(1,(p+AW2(8,0))>>CPF_BUG_ZOM);
   colR=abs(AH2(c0a.r-c0b.r,c1a.r-c1b.r));
   colG=abs(AH2(c0a.g-c0b.g,c1a.g-c1b.g));
   colB=abs(AH2(c0a.b-c0b.b,c1a.b-c1b.b));
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==14
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 c0=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   AU1 c1=CpfMovLd(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   colG=AH2_(0.0);
   colR.x=AH1(abs(CpfMovX(c0))*ARcpF1(CPF_MOV_MAX)*1024.0);
   colR.y=AH1(abs(CpfMovX(c1))*ARcpF1(CPF_MOV_MAX)*1024.0);
   colB.x=AH1(abs(CpfMovY(c0))*ARcpF1(CPF_MOV_MAX)*1024.0);
   colB.y=AH1(abs(CpfMovY(c1))*ARcpF1(CPF_MOV_MAX)*1024.0);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_BUG==15
   AU4 const1=CpfGet(CPF_C32_PRE1);
   AU1 constIdx=const1.y>>16;
   AU1 m0=CpfMovLd(constIdx,p>>CPF_BUG_ZOM);
   AU1 m1=CpfMovLd(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   AF2 m0xy=AF2(CpfMovX(m0),CpfMovY(m0));
   AF2 m1xy=AF2(CpfMovX(m1),CpfMovY(m1));
   AH4 c0a=CpfColLdH(constIdx,p>>CPF_BUG_ZOM);
   AH4 c1a=CpfColLdH(constIdx,(p+AW2(8,0))>>CPF_BUG_ZOM);
   AU4 const0=CpfGet(CPF_C16_PRE0);
   AF2 constPMul=AF2_AU2(const0.xy);
   AF2 constPAdd=AF2_AU2(const0.zw);
   AF2 p0=AF2(p>>CPF_BUG_ZOM)*constPMul+constPAdd-m0xy*constPMul;
   AF2 p1=AF2((p+AW2(8,0))>>CPF_BUG_ZOM)*constPMul+constPAdd-m1xy*constPMul;
   AH4 c0b=CpfColSmH(constIdx^AU1_(1),p0);
   AH4 c1b=CpfColSmH(constIdx^AU1_(1),p1);
   colR=abs(AH2(c0a.r-c0b.r,c1a.r-c1b.r));
   colG=abs(AH2(c0a.g-c0b.g,c1a.g-c1b.g));
   colB=abs(AH2(c0a.b-c0b.b,c1a.b-c1b.b));
  #endif
//------------------------------------------------------------------------------------------------------------------------------
 }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                                 [DFU] DIFFUSION (AKA BLOOM)
//
//------------------------------------------------------------------------------------------------------------------------------
// CORE ALGORITHM
// ==============
// Has an 4x4 wave reduction in a prior pass to setup initial source.
// Runs in FP16 with screen edge weighting in alpha and color weighted by alpha.
// Uses black border to avoid including data from off-screen.
// The filter tree down-samples and up-samples with forwarding from down-sampling to up-sampling.
// Filter kernels are simple circles.
// One dispatch runs the entire 4x4 to 4x4 filter tree.
// This is possible because it double buffers all the images, only reading from prior frame.
// So individual stages of the graph can be independently ordered.
// This implies there is a latency of one frame per level for visual feedback.
//------------------------------------------------------------------------------------------------------------------------------
// FILTER TREE
// ===========
//                 render           output - can be upsampled to less than 1x1 pixels compared to source render
//                  1x1              ?x?  
//                   v                ^
//                  4x4 --forward--> 4x4 
//                   v                ^
//                  8x8 -----------> 8x8
//                   v                ^
//  down-sample    16x16 ---------> 16x16    up-sample
//                   v                ^
//                 32x32 ---------> 32x32
//                   v                ^
//                 64x64 ---------> 64x64
//                   v                ^ 
//                128x128 ------------+
//==============================================================================================================================
// Minimum alpha channel value before RCP which prevents NaN problems in all versions of code.
#define CPF_DFU_MIN (1.0/32768.0)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                        32-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(CPF_32BIT)&&CPF_DFU
 // 4x4 down-sample.
 void CpfDfuIn(
 AU2 p, // Integer position in full-resolution image.
 AF1 colR,AF1 colG,AF1 colB,AF1 colA){ // Color (linear RGB, noise weighting).
  // Alpha input needs to range from {0 to 1}. RGB can be full range.
  // Pre-multiply alpha first to avoid going out of range for 16-bit version.
  colA=colA*AF1_(1.0/16.0);colR*=colA;colG*=colA;colB*=colA;
  // 4x4 reduction.
  colR+=AWaveXorF1(colR,1u);colG+=AWaveXorF1(colG,1u);colB+=AWaveXorF1(colB,1u);colA+=AWaveXorF1(colA,1u);
  colR+=AWaveXorF1(colR,2u);colG+=AWaveXorF1(colG,2u);colB+=AWaveXorF1(colB,2u);colA+=AWaveXorF1(colA,2u);
  colR+=AWaveXorF1(colR,4u);colG+=AWaveXorF1(colG,4u);colB+=AWaveXorF1(colB,4u);colA+=AWaveXorF1(colA,4u);
  colR+=AWaveXorF1(colR,8u);colG+=AWaveXorF1(colG,8u);colB+=AWaveXorF1(colB,8u);colA+=AWaveXorF1(colA,8u);
  // This is pre-reduced to avoid overflow later in case 16-bit version is used.
  colR*=AF1_(1.0/CPF_DFU_N);colG*=AF1_(1.0/CPF_DFU_N);colB*=AF1_(1.0/CPF_DFU_N);colA*=AF1_(1.0/CPF_DFU_N);
  CpfDfuDwn0St(p>>AU2_(2),AF4(colR,colG,colB,colA));}
//==============================================================================================================================
 // Compute an immediate offset for circular sampling pattern.
 AF2 CpfDfuCir(
 AF1 i, // Point on curve.
 AF1 n, // Points on curve.
 AF1 r){ // Radius in pixels.
  AF1 a=(i+0.5)*(A_2PI/n);return AF2(r*cos(a),r*sin(a));}
//------------------------------------------------------------------------------------------------------------------------------
 void CpfDfu(AU2 wxy,AU2 gxy){
//------------------------------------------------------------------------------------------------------------------------------
  // Fetch constants.
  AF2 kc=AF2_AU2(CpfGet(CPF_C32_REC0).xy);
  AU2 kd0=CpfGet(CPF_C32_DFU0).xy;
  AU2 kd1=CpfGet(CPF_C32_DFU0).zw;
  AU2 kd2=CpfGet(CPF_C32_DFU1).xy;
  AU2 kd3=CpfGet(CPF_C32_DFU1).zw;
  AU2 kd4=CpfGet(CPF_C32_DFU2).xy;
  AU2 kd5=CpfGet(CPF_C32_DFU2).zw;
  AF4 ks0=AF4_AU4(CpfGet(CPF_C32_DFU3));
  AF4 ks1=AF4_AU4(CpfGet(CPF_C32_DFU4));
  AF4 ks2=AF4_AU4(CpfGet(CPF_C32_DFU5));
  AF4 ks3=AF4_AU4(CpfGet(CPF_C32_DFU6));
  AF4 ks4=AF4_AU4(CpfGet(CPF_C32_DFU7));
  AF4 ks5=AF4_AU4(CpfGet(CPF_C32_DFU8));
//------------------------------------------------------------------------------------------------------------------------------
  AF2 p;
  AF4 c=AF4_(0.0);c.a=AF1_(1.0);
  AF4 c0=AF4_(0.0);
  AF4 c1=AF4_(0.0);
  AF4 c2=AF4_(0.0);
  AU1 i;
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd0.x)||(wxy.y>=kd0.y))return;
  p=AF2(gxy)*ks0.xy+ks0.zw;
  // 4x4 down-sample forwarding.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn0Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_FN),AF1_(CPF_DFU_FR*1.0)));
  #if CPF_NOZ
   // Make sure bad input won't cause NaNs.
   // This only applies when CPF_NOZ is enabled as otherwise alpha is in range.
   c0.a=max(c0.a,AF1_(CPF_DFU_MIN));
  #endif
  c0.rgb*=ARcpF1(c0.a);
  // Blend in part of the unfilted source.
  c2=CpfDfuDwn0Sm(p);
  #if CPF_NOZ
   c2.a=max(c2.a,AF1_(CPF_DFU_MIN));
  #endif
  c2.rgb*=ASatF1(ARcpF1(c2.a));
  c0.rgb=ALerpF3(c2.rgb,c0.rgb,AF3_(AF1_(1.0)-ARcpF1(AF1_(4.0))));
  // 8x8 up-sampled.
  c1=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp1Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_UN),AF1_(CPF_DFU_UR*2.0)));
  c1.rgb*=ARcpF1(c1.a);
  // 4x4 up-sampled out.
  // This has a factor to limit the contribution of the 4x4 down-sampling due to flicker/etc.
  c.rgb=ALerpF3(c0.rgb,c1.rgb,AF3_(AF1_(1.0)-AF1_(1.0/16.0)*pow(AF1_(CPF_DFU_P),AF1_(-5.0))));
  // No reduction in range necessary here because application of diffusion is only one fetch.
  CpfDfuUp0St(gxy,c);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd1.x)||(wxy.y>=kd1.y))return;
  p=AF2(gxy)*ks1.xy+ks1.zw;
  // 8x8 down-sample forwarding.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn1Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_FN),AF1_(CPF_DFU_FR*2.0)));
  c0.rgb*=ARcpF1(c0.a);
  // 16x16 up-sampled.
  c1=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp2Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_UN),AF1_(CPF_DFU_UR*4.0)));
  c1.rgb*=ARcpF1(c1.a);
  // 8x8 up-sampled out.
  c.rgb=ALerpF3(c0.rgb,c1.rgb,AF3_(AF1_(1.0)-pow(CPF_DFU_P,AF1_(-4.0))));
  c.a=AF1_(1.0/CPF_DFU_N);c.rgb*=AF3_(1.0/CPF_DFU_N);CpfDfuUp1St(gxy,c);
  // 8x8 down-sampling and out.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn0Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_DN),AF1_(CPF_DFU_DR*1.0)));
  #if CPF_NOZ
   c0.a=max(c0.a,AF1_(CPF_DFU_MIN));
  #endif
  // This shares the same code as the 16-bit version (pre-reduced to remove the possibility of overflow).
  c0.rgb*=ARcpF1(c0.a)*AF1_(1.0/CPF_DFU_N);c0.a=AF1_(1.0/CPF_DFU_N);CpfDfuDwn1St(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd2.x)||(wxy.y>=kd2.y))return;
  p=AF2(gxy)*ks2.xy+ks2.zw;
  // 16x16 down-sample forwarding.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn2Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_FN),AF1_(CPF_DFU_FR*4.0)));
  c0.rgb*=ARcpF1(c0.a);
  // 32x32 up-sampled.
  c1=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp3Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_UN),AF1_(CPF_DFU_UR*8.0)));
  c1.rgb*=ARcpF1(c1.a);
  // 16x16 up-sampled out.
  c.rgb=ALerpF3(c0.rgb,c1.rgb,AF3_(AF1_(1.0)-pow(AF1_(CPF_DFU_P),AF1_(-3.0))));
  c.a=AF1_(1.0/CPF_DFU_N);c.rgb*=AF3_(1.0/CPF_DFU_N);CpfDfuUp2St(gxy,c);
  // 16x16 down-sampling and out.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn1Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_DN),AF1_(CPF_DFU_DR*2.0)));
  c0.rgb*=ARcpF1(c0.a)*AF1_(1.0/CPF_DFU_N);c0.a=AF1_(1.0/CPF_DFU_N);CpfDfuDwn2St(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd3.x)||(wxy.y>=kd3.y))return;
  p=AF2(gxy)*ks3.xy+ks3.zw;
  // 32x32 down-sample forwarding.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn3Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_FN),AF1_(CPF_DFU_FR*8.0)));
  c0.rgb*=ARcpF1(c0.a);
  // 64x64 up-sampled.
  c1=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp4Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_UN),AF1_(CPF_DFU_UR*16.0)));
  c1.rgb*=ARcpF1(c1.a);
  // 32x32 up-sampled out.
  c.rgb=ALerpF3(c0.rgb,c1.rgb,AF3_(AF1_(1.0)-pow(AF1_(CPF_DFU_P),AF1_(-2.0))));
  c.a=AF1_(1.0/CPF_DFU_N);c.rgb*=AF3_(1.0/CPF_DFU_N);CpfDfuUp3St(gxy,c);
  // 32x32 down-sampling and out.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn2Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_DN),AF1_(CPF_DFU_DR*4.0)));
  c0.rgb*=ARcpF1(c0.a)*AF1_(1.0/CPF_DFU_N);c0.a=AF1_(1.0/CPF_DFU_N);CpfDfuDwn3St(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd4.x)||(wxy.y>=kd4.y))return;
  p=AF2(gxy)*ks4.xy+ks4.zw;
  // 64x64 down-sample forwarding.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn4Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_FN),AF1_(CPF_DFU_FR*16.0)));
  c0.rgb*=ARcpF1(c0.a);
  // 128x128 up-sampled from terminal bottom.
  c1=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuDwn5Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_UN),AF1_(CPF_DFU_UR*32.0)));
  c1.rgb*=ARcpF1(c1.a);
  // 64x64 up-sampled out.
  c.rgb=ALerpF3(c0.rgb,c1.rgb,AF3_(AF1_(1.0)-pow(AF1_(CPF_DFU_P),AF1_(-1.0))));
  c.a=AF1_(1.0/CPF_DFU_N);c.rgb*=AF3_(1.0/CPF_DFU_N);CpfDfuUp4St(gxy,c);
  // 64x64 down-sampling and out.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn3Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_DN),AF1_(CPF_DFU_DR*8.0)));
  c0.rgb*=ARcpF1(c0.a)*AF1_(1.0/CPF_DFU_N);c0.a=AF1_(1.0/CPF_DFU_N);CpfDfuDwn4St(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd5.x)||(wxy.y>=kd5.y))return;
  p=AF2(gxy)*ks5.xy+ks5.zw;
  // 128x128 down-sampling and out.
  c0=AF4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn4Sm(p+kc*CpfDfuCir(AF1(i),AF1_(CPF_DFU_DN),AF1_(CPF_DFU_DR*16.0)));
  c0.rgb*=ARcpF1(c0.a)*AF1_(1.0/CPF_DFU_N);c0.a=AF1_(1.0/CPF_DFU_N);CpfDfuDwn5St(gxy,c0);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                       16-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)&&defined(CPF_16BIT)&&CPF_DFU
 void CpfDfuInH(AW2 p,AH2 colR,AH2 colG,AH2 colB,AH2 colA){
  colA=colA*AH2_(1.0/16.0);colR*=colA;colG*=colA;colB*=colA;
  colR+=AWaveXorH2(colR,1u);colG+=AWaveXorH2(colG,1u);colB+=AWaveXorH2(colB,1u);colA+=AWaveXorH2(colA,1u);
  colR+=AWaveXorH2(colR,2u);colG+=AWaveXorH2(colG,2u);colB+=AWaveXorH2(colB,2u);colA+=AWaveXorH2(colA,2u);
  colR+=AWaveXorH2(colR,4u);colG+=AWaveXorH2(colG,4u);colB+=AWaveXorH2(colB,4u);colA+=AWaveXorH2(colA,4u);
  colR+=AWaveXorH2(colR,8u);colG+=AWaveXorH2(colG,8u);colB+=AWaveXorH2(colB,8u);colA+=AWaveXorH2(colA,8u);
  colR*=AH2_(1.0/CPF_DFU_N);colG*=AH2_(1.0/CPF_DFU_N);colB*=AH2_(1.0/CPF_DFU_N);colA*=AH2_(1.0/CPF_DFU_N);
  AH4 pix0,pix1;CpfDepack4(pix0,pix1,colR,colG,colB,colA);
  p>>=2;CpfDfuDwn0StH(p,pix0);CpfDfuDwn0StH(p+AW2(2,0),pix1);}
//==============================================================================================================================
 AH2 CpfDfuCirH(AH1 i,AH1 n,AH1 r){AH1 a=(i+AH1_(0.5))*(AH1_(A_2PI)/n);return AH2(r*cos(a),r*sin(a));}
//------------------------------------------------------------------------------------------------------------------------------
 // This is using packed mostly for VGPR savings so texture batching can be better.
 void CpfDfuH(AU2 wxy,AW2 gxy){
//------------------------------------------------------------------------------------------------------------------------------
  // Fetch constants is done differently in 16-bit.
  AH2 kc=AH2_AU1(CpfGet(CPF_C16_REC0).w);
  AU2 kd0=CpfGet(CPF_C16_DFU0).xy;
  AH4 ks0=AH4_AU2(CpfGet(CPF_C16_DFU0).zw);
  AU2 kd1=CpfGet(CPF_C16_DFU1).xy;
  AH4 ks1=AH4_AU2(CpfGet(CPF_C16_DFU1).zw);
  AU2 kd2=CpfGet(CPF_C16_DFU2).xy;
  AH4 ks2=AH4_AU2(CpfGet(CPF_C16_DFU2).zw);
  AU2 kd3=CpfGet(CPF_C16_DFU3).xy;
  AH4 ks3=AH4_AU2(CpfGet(CPF_C16_DFU3).zw);
  AU2 kd4=CpfGet(CPF_C16_DFU4).xy;
  AH4 ks4=AH4_AU2(CpfGet(CPF_C16_DFU4).zw);
  AU2 kd5=CpfGet(CPF_C16_DFU5).xy;
  AH4 ks5=AH4_AU2(CpfGet(CPF_C16_DFU5).zw);
//------------------------------------------------------------------------------------------------------------------------------
  AH2 p;
  AH4 c=AH4_(0.0);c.a=AH1_(1.0);
  AH4 c0=AH4_(0.0);
  AH4 c1=AH4_(0.0);
  AH4 c2=AH4_(0.0);
  AU1 i;
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd0.x)||(wxy.y>=kd0.y))return;
  p=AH2(gxy)*ks0.xy+ks0.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)
   c0+=CpfDfuDwn0SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_FN),AH1_(CPF_DFU_FR*1.0)));
  #if CPF_NOZ
   c0.a=max(c0.a,AH1_(CPF_DFU_MIN));
  #endif
  c0.rgb*=ARcpH1(c0.a);
  c2=CpfDfuDwn0SmH(p);
  #if CPF_NOZ
   c2.a=max(c2.a,AH1_(CPF_DFU_MIN));
  #endif
  c2.rgb*=ARcpH1(c2.a);
  c0.rgb=ALerpH3(c2.rgb,c0.rgb,AH3_(AH1_(1.0)-ARcpH1(AH1_(4.0))));
  c1=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp1SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_UN),AH1_(CPF_DFU_UR*2.0)));
  c1.rgb*=ARcpH1(c1.a);
  c.rgb=ALerpH3(c0.rgb,c1.rgb,AH3_(AH1_(1.0)-pow(AH1_(CPF_DFU_P),AH1_(-8.0))));
  CpfDfuUp0StH(gxy,c);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd1.x)||(wxy.y>=kd1.y))return;p=AH2(gxy)*ks1.xy+ks1.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn1SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_FN),AH1_(CPF_DFU_FR*2.0)));
  c0.rgb*=ARcpH1(c0.a);
  c1=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp2SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_UN),AH1_(CPF_DFU_UR*4.0)));
  c1.rgb*=ARcpH1(c1.a);
  c.rgb=ALerpH3(c0.rgb,c1.rgb,AH3_(AH1_(1.0)-pow(AH1_(CPF_DFU_P),AH1_(-4.0))));
  c.a=AH1_(1.0/CPF_DFU_N);c.rgb*=AH3_(1.0/CPF_DFU_N);CpfDfuUp1StH(gxy,c);
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn0SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_DN),AH1_(CPF_DFU_DR*1.0)));
  #if CPF_NOZ
   c0.a=max(c0.a,AH1_(CPF_DFU_MIN));
  #endif
  c0.rgb*=ARcpH1(c0.a)*AH1_(1.0/CPF_DFU_N);c0.a=AH1_(1.0/CPF_DFU_N);CpfDfuDwn1StH(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd2.x)||(wxy.y>=kd2.y))return;p=AH2(gxy)*ks2.xy+ks2.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn2SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_FN),AH1_(CPF_DFU_FR*4.0)));
  c0.rgb*=ARcpH1(c0.a);
  c1=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp3SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_UN),AH1_(CPF_DFU_UR*8.0)));
  c1.rgb*=ARcpH1(c1.a);
  c.rgb=ALerpH3(c0.rgb,c1.rgb,AH3_(AH1_(1.0)-pow(AH1_(CPF_DFU_P),AH1_(-3.0))));
  c.a=AH1_(1.0/CPF_DFU_N);c.rgb*=AH3_(1.0/CPF_DFU_N);CpfDfuUp2StH(gxy,c);
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn1SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_DN),AH1_(CPF_DFU_DR*2.0)));
  c0.rgb*=ARcpH1(c0.a)*AH1_(1.0/CPF_DFU_N);c0.a=AH1_(1.0/CPF_DFU_N);CpfDfuDwn2StH(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd3.x)||(wxy.y>=kd3.y))return;p=AH2(gxy)*ks3.xy+ks3.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn3SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_FN),AH1_(CPF_DFU_FR*8.0)));
  c0.rgb*=ARcpH1(c0.a);
  c1=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuUp4SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_UN),AH1_(CPF_DFU_UR*16.0)));
  c1.rgb*=ARcpH1(c1.a);
  c.rgb=ALerpH3(c0.rgb,c1.rgb,AH3_(AH1_(1.0)-pow(AH1_(CPF_DFU_P),AH1_(-2.0))));
  c.a=AH1_(1.0/CPF_DFU_N);c.rgb*=AH3_(1.0/CPF_DFU_N);CpfDfuUp3StH(gxy,c);
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn2SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_DN),AH1_(CPF_DFU_DR*4.0)));
  c0.rgb*=ARcpH1(c0.a)*AH1_(1.0/CPF_DFU_N);c0.a=AH1_(1.0/CPF_DFU_N);CpfDfuDwn3StH(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd4.x)||(wxy.y>=kd4.y))return;p=AH2(gxy)*ks4.xy+ks4.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_FN);i++)c0+=CpfDfuDwn4SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_FN),AH1_(CPF_DFU_FR*16.0)));
  c0.rgb*=ARcpH1(c0.a);
  c1=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_UN);i++)c1+=CpfDfuDwn5SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_UN),AH1_(CPF_DFU_UR*32.0)));
  c1.rgb*=ARcpH1(c1.a);
  c.rgb=ALerpH3(c0.rgb,c1.rgb,AH3_(AH1_(1.0)-pow(AH1_(CPF_DFU_P),AH1_(-1.0))));
  c.a=AH1_(1.0/CPF_DFU_N);c.rgb*=AH3_(1.0/CPF_DFU_N);CpfDfuUp4StH(gxy,c);
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn3SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_DN),AH1_(CPF_DFU_DR*8.0)));
  c0.rgb*=ARcpH1(c0.a)*AH1_(1.0/CPF_DFU_N);c0.a=AH1_(1.0/CPF_DFU_N);CpfDfuDwn4StH(gxy,c0);
//------------------------------------------------------------------------------------------------------------------------------
  if((wxy.x>=kd5.x)||(wxy.y>=kd5.y))return;p=AH2(gxy)*ks5.xy+ks5.zw;
  c0=AH4_(0.0);for(i=0u;i<AU1(CPF_DFU_DN);i++)c0+=CpfDfuDwn4SmH(p+kc*CpfDfuCirH(AH1(i),AH1_(CPF_DFU_DN),AH1_(CPF_DFU_DR*16.0)));
  c0.rgb*=ARcpH1(c0.a)*AH1_(1.0/CPF_DFU_N);c0.a=AH1_(1.0/CPF_DFU_N);CpfDfuDwn5StH(gxy,c0);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                                [CPF] [PRE] INLINE PRE-PASS
//
//------------------------------------------------------------------------------------------------------------------------------
// This pass does inline noise reduction using wave ops and temporal feedback.
// Does a reduction from 4x4:1 to feed macro-diffusion.
// Reduces from HDR to MDR (reversible), dithers and packs into 32-bit {rgb,coc} for reconstruction.
// Dithers and packs motion vectors into 16-bit.
//==============================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                       32-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(CPF_32BIT)
 void CpfPre(
 AU2 p, // Integer pixel position.
 AF1 colR, // Color.
 AF1 colG,
 AF1 colB,
 AF1 z, // Circle of confusion out of CpfCoc*().
 AF1 mX, // Motion vector (where 1 is a full screen movement).
 AF1 mY){
//------------------------------------------------------------------------------------------------------------------------------
  // CoC is {-1 to 1} pack to {1/255 to 1}, the zero value is reserved for off-screen.
  // Loads produce zero for off-image access.
  z=z*AF1_((254.0/255.0)/2.0)+AF1_(128.0/255.0);
//------------------------------------------------------------------------------------------------------------------------------
  // Grabing const1 here because it is used in/out of defines.
  AU4 const1=CpfGet(CPF_C32_PRE1);
  AF1 constAmt=AF1_AU1(const1.x);
  AU1 constDit=const1.y&AU1_(65535);
  AU1 constIdx=const1.y>>16;
  AF2 constXY=AF2_AU2(const1.zw);
//------------------------------------------------------------------------------------------------------------------------------
  // Noise reduction on inputs.
  #if CPF_NOZ
   // Setup for z testing.
   AF1 biasG=CpfZG1(z);
   AF1 biasF=CpfZF1(z);
   // Registration factor.
   AU4 const0=CpfGet(CPF_C32_PRE0);
   AF2 constPMul=AF2_AU2(const0.xy);
   AF2 constPAdd=AF2_AU2(const0.zw);
   // Working in 2x2 quad.
   //  D V
   //  H(S)
   // Compute {0 to CPF_HDR} luma.
   AF1 lumS=colR*AF1_(0.25)+colG*AF1_(0.5)+colB*AF1_(0.25);
   // Fetch neighbors in other lanes.
   AF1 lumH=AWaveXorF1(lumS,1u);
   AF1 lumV=AWaveXorF1(lumS,2u);
   AF1 lumD=AWaveXorF1(lumV,1u);
   // Normalized float position.
   AF2 pN=AF2(p)*constPMul+constPAdd;
   // Fetch reprojection.
   AF2 m0=AF2(-mX,-mY);
   AF2 lumR=CpfNozSm(pN+m0);
   // Store new and reprojected luma.
   CpfNozSt(p,AF2(lumS,lumR.x));
   // Quad center position x4.
   AF2 pQ4=pN+AWaveXorF2(pN,1u);
   pQ4=pQ4+AWaveXorF2(pQ4,2u);
   // Use quad center to compute edge position.
   //  E---+---E
   //  |   |   |
   //  +---+---+
   //  |   |   |
   //  E---+---E
   AF2 pE=AF2_(2.0)+pN+AF2_(-0.25)*pQ4;
   // Use quad edge to gather 4 other luma values from prior frame (reprojected).
   // This provides a neighborhood of 8 values to use for noise check.
   //  D  . V
   //  .    .
   //  H  (S)+E  E
   //       .    .
   //       E  . E
   AF4 lumE=CpfNoz4R(pE+m0);
   // Fetch prior reprojection at quad center.
   AF4 lumF=CpfNoz4G(pQ4*AF2_(0.25)+m0);
   // Rename for 32-bit and interleave for 16-bit.
   AF1 lumEX=lumE.x;
   AF1 lumEY=lumE.y;
   AF1 lumEZ=lumE.z;
   AF1 lumEW=lumE.w;
   // Fetch min and max for all and all except (S).
   AF1 minX=AMin3F1(AMin3F1(lumH,lumV,lumD),AMin3F1(lumEX,lumEY,lumEZ),lumEW);
   AF1 maxX=AMax3F1(AMax3F1(lumH,lumV,lumD),AMax3F1(lumEX,lumEY,lumEZ),lumEW);
   // Rename for 32-bit and interleave for 16-bit.
   AF1 lumFX=lumF.x;
   AF1 lumFY=lumF.y;
   AF1 lumFZ=lumF.z;
   AF1 lumFW=lumF.w;
   // Include prior prior.
   minX=AMin3F1(AMin3F1(lumFX,lumFY,lumFZ),lumFW,minX);
   maxX=AMax3F1(AMax3F1(lumFX,lumFY,lumFZ),lumFW,maxX);
   // TODO: Setup a baseline to avoid seeing small differences as noise?????????????????????????????????????????????????????????
   //  - Perhaps something like a configurable: maxX=max(maxX,1.0/256.0);
   AF1 minA=min(minX,lumS);
   AF1 maxA=max(maxX,lumS);
   // Diffusion weighting.
   // TODO: Optimize this???????????????????????????????????????????????????????????????????????????????????????????????????????
   AF1 colW=AF1_(1.0)-ASatF1(abs(lumR.x-lumS)*ARcpF1(max(AF1_(1.0/32768.0),maxA)));
   // Diffs.
   AF1 difX=maxX-minX;
   AF1 difA=maxA-minA;
   // Produce weighting term which approaches zero the more noise found.
   AF1 w=maxA*APrxMedRcpF1(AF1_(constAmt)+difA-difX);
   // Must limit here to avoid precision problems in 16-bit code (make 32-bit and 16-bit the same).
   w=min(w,AF1_(4096.0));
   // Make sure weight is not fully zero.
   w+=AF1_(1.0/32768.0);
   // Push higher weights in 2x2 quad to hole fill.
   AF1 colRH,colGH,colBH,wH,zH;
   colRH=AWaveXorF1(colR,1u);
   colGH=AWaveXorF1(colG,1u);
   colBH=AWaveXorF1(colB,1u);
   wH=AWaveXorF1(w,1u);
   zH=AWaveXorF1(z,1u);
   AF1 colRV,colGV,colBV,wV,zV;
   colRV=AWaveXorF1(colR,2u);
   colGV=AWaveXorF1(colG,2u);
   colBV=AWaveXorF1(colB,2u);
   wV=AWaveXorF1(w,2u);
   zV=AWaveXorF1(z,2u);
   AF1 colRD,colGD,colBD,wD,zD;
   colRD=AWaveXorF1(colRV,1u);
   colGD=AWaveXorF1(colGV,1u);
   colBD=AWaveXorF1(colBV,1u);
   wD=AWaveXorF1(wV,1u);
   zD=AWaveXorF1(zV,1u);
   // Avoid bleeding across different depths.
   wH*=CpfZ1(zH,biasG)-CpfZ1(zH,biasF);
   wV*=CpfZ1(zV,biasG)-CpfZ1(zV,biasF);
   wD*=CpfZ1(zD,biasG)-CpfZ1(zD,biasF);
   w*=CpfZ1(z,biasG)-CpfZ1(z,biasF);
   AF1 b=ASatF1(AF1_(4.0)*w*APrxMedRcpF1(w+wH+wV+wD));
   AF1 bO=AF1_(1.0)-b;
   AF1 bH=ASatF1(wH-w);
   AF1 bV=ASatF1(wV-w);
   AF1 bD=ASatF1(wD-w)*AF1_(0.5);
   AF1 rcpHVD=bO*APrxMedRcpF1(bH+bV+bD);
   bH*=rcpHVD;
   bV*=rcpHVD;
   bD*=rcpHVD;
   colR=colR*b+(colRH*bH+((colRV*bV+(colRD*bD))));
   colG=colG*b+(colGH*bH+((colGV*bV+(colGD*bD))));
   colB=colB*b+(colBH*bH+((colBV*bV+(colBD*bD))));
  #else
   // No noise reducton weighting for diffusion.
   AF1 colW=AF1_(1.0);
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_DFU
   // Store out for diffusion.
   // This unfortunately needs to go before motion blur and reconstruction.
   // The reversible tonemap for MDR is not energy conserving leading to flicker.
   CpfDfuIn(p,colR,colG,colB,colW);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // Dither value.
  AF1 dit=CpfDit(p,constDit);
//------------------------------------------------------------------------------------------------------------------------------
  // Convert to MDR.
  CpfMdrFromHdr(colR,colG,colB);
//------------------------------------------------------------------------------------------------------------------------------
  // Dither to 8-bit gamma 3.0.
  colR=CpfDit3(colR,dit);
  colG=CpfDit3(colG,dit);
  colB=CpfDit3(colB,dit);
//------------------------------------------------------------------------------------------------------------------------------
  // Store color.
  // Not dithering CoC here (would add possible error to depth checks).
  CpfColSt(constIdx,p,AF4(colR,colG,colB,z));
//------------------------------------------------------------------------------------------------------------------------------
  // Store out motion pack.
  mX*=AF1_(constXY.x);
  mY*=AF1_(constXY.y);
  AU1 mp=CpfMovPck(mX,mY,dit);
  CpfMovSt(constIdx,p,mp);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                       16-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)&&defined(CPF_16BIT)
 // This operates on two 8x8 tiles separated horizontally by 8 pixels. 
 void CpfPreH(
 AW2 p,
 AH2 colR,
 AH2 colG,
 AH2 colB,
 AH2 z,
 AH2 mX,
 AH2 mY){
//------------------------------------------------------------------------------------------------------------------------------
  z=z*AH2_((254.0/255.0)/2.0)+AH2_(128.0/255.0);
//------------------------------------------------------------------------------------------------------------------------------
  // This is slightly different than the 32-bit version.
  AU4 const1=CpfGet(CPF_C16_PRE1);
  AF1 constShf=AF1_AU1(const1.x);
  AH1 constAmt=AH2_AU1(const1.y).x;
  AU1 constIdx=AU1_(AW2_AU1(const1.y).y);
  AW2 constDit=AW2_AU1(const1.z);
  AH2 constXY=AH2_AU1(const1.w);
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_NOZ
   AH2 biasG=CpfZGH(z);
   AH2 biasF=CpfZFH(z);
   AU4 const0=CpfGet(CPF_C16_PRE0);
   AF2 constPMul=AF2_AU2(const0.xy);
   AF2 constPAdd=AF2_AU2(const0.zw);
   AH2 lumS=colR*AH2_(0.25)+colG*AH2_(0.5)+colB*AH2_(0.25);
   AH2 lumH=AWaveXorH2(lumS,1u);
   AH2 lumV=AWaveXorH2(lumS,2u);
   AH2 lumD=AWaveXorH2(lumV,1u);
   AF2 pN=AF2(p)*constPMul+constPAdd;
   AF2 m0=AF2(-mX.x,-mY.x);
   AF2 m1=AF2(-mX.y,-mY.y);
   // Placing in tile offset into m1.x.
   m1.x+=constShf;
   AH2 lumR0=CpfNozSmH(pN+m0);
   AH2 lumR1=CpfNozSmH(pN+m1);
   CpfNozStH(p,         AH2(lumS.x,lumR0.x));
   CpfNozStH(p+AW2(8,0),AH2(lumS.y,lumR1.x));
   AF2 pQ4=pN+AWaveXorF2(pN,1u);
   pQ4=pQ4+AWaveXorF2(pQ4,2u);
   AF2 pE=AF2_(2.0)+pN+AF2_(-0.25)*pQ4;
   AH4 lumE0=CpfNoz4RH(pE+m0);
   AH4 lumE1=CpfNoz4RH(pE+m1);
   AH4 lumF0=CpfNoz4GH(pQ4*AF2_(0.25)+m0);
   AH4 lumF1=CpfNoz4GH(pQ4*AF2_(0.25)+m1);
   AH2 lumEX=AH2(lumE0.x,lumE1.x);
   AH2 lumEY=AH2(lumE0.y,lumE1.y);
   AH2 lumEZ=AH2(lumE0.z,lumE1.z);
   AH2 lumEW=AH2(lumE0.w,lumE1.w);
   AH2 minX=AMin3H2(AMin3H2(lumH,lumV,lumD),AMin3H2(lumEX,lumEY,lumEZ),lumEW);
   AH2 maxX=AMax3H2(AMax3H2(lumH,lumV,lumD),AMax3H2(lumEX,lumEY,lumEZ),lumEW);
   AH2 lumFX=AH2(lumF0.x,lumF1.x);
   AH2 lumFY=AH2(lumF0.y,lumF1.y);
   AH2 lumFZ=AH2(lumF0.z,lumF1.z);
   AH2 lumFW=AH2(lumF0.w,lumF1.w);
   minX=AMin3H2(AMin3H2(lumFX,lumFY,lumFZ),lumFW,minX);
   maxX=AMax3H2(AMax3H2(lumFX,lumFY,lumFZ),lumFW,maxX);
   AH2 minA=min(minX,lumS);
   AH2 maxA=max(maxX,lumS);
   AH2 colW=AH2_(1.0)-ASatH2(abs(AH2(lumR0.x,lumR1.x)-lumS)*ARcpH2(max(AH2_(1.0/32768.0),maxA)));
   AH2 difX=maxX-minX;
   AH2 difA=maxA-minA;
   AH2 w=maxA*APrxMedRcpH2(AH2_(constAmt)+difA-difX);
   w=min(w,AH2_(4096.0));
   w+=AH2_(1.0/32768.0);
   AH2 colRH,colGH,colBH,wH,zH;
   colRH=AWaveXorH2(colR,1u);
   colGH=AWaveXorH2(colG,1u);
   colBH=AWaveXorH2(colB,1u);
   wH=AWaveXorH2(w,1u);
   zH=AWaveXorH2(z,1u);
   AH2 colRV,colGV,colBV,wV,zV;
   colRV=AWaveXorH2(colR,2u);
   colGV=AWaveXorH2(colG,2u);
   colBV=AWaveXorH2(colB,2u);
   wV=AWaveXorH2(w,2u);
   zV=AWaveXorH2(z,2u);
   AH2 colRD,colGD,colBD,wD,zD;
   colRD=AWaveXorH2(colRV,1u);
   colGD=AWaveXorH2(colGV,1u);
   colBD=AWaveXorH2(colBV,1u);
   wD=AWaveXorH2(wV,1u);
   zD=AWaveXorH2(zV,1u);
   wH*=CpfZH(zH,biasG)-CpfZH(zH,biasF);
   wV*=CpfZH(zV,biasG)-CpfZH(zV,biasF);
   wD*=CpfZH(zD,biasG)-CpfZH(zD,biasF);
   w*=CpfZH(z,biasG)-CpfZH(z,biasF);
   AH2 b=ASatH2(AH2_(4.0)*w*APrxMedRcpH2(w+wH+wV+wD));
   AH2 bO=AH2_(1.0)-b;
   AH2 bH=ASatH2(wH-w);
   AH2 bV=ASatH2(wV-w);
   AH2 bD=ASatH2(wD-w)*AH2_(0.5);
   AH2 rcpHVD=bO*APrxMedRcpH2(bH+bV+bD);
   bH*=rcpHVD;
   bV*=rcpHVD;
   bD*=rcpHVD;
   colR=colR*b+(colRH*bH+((colRV*bV+(colRD*bD))));
   colG=colG*b+(colGH*bH+((colGV*bV+(colGD*bD))));
   colB=colB*b+(colBH*bH+((colBV*bV+(colBD*bD))));
  #else
   AH2 colW=AH2_(1.0);
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_DFU
   // Special for 16-bit, make sure colors are not infinity.
   colR=min(colR,AH2_(CPF_HDR));
   colG=min(colG,AH2_(CPF_HDR));
   colB=min(colB,AH2_(CPF_HDR));
   CpfDfuInH(p,colR,colG,colB,colW);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  AH2 dit=CpfDitH(p,constDit);
//------------------------------------------------------------------------------------------------------------------------------
  CpfMdrFromHdrH(colR,colG,colB);
//------------------------------------------------------------------------------------------------------------------------------
  colR=CpfDit3H(colR,dit);
  colG=CpfDit3H(colG,dit);
  colB=CpfDit3H(colB,dit);
//------------------------------------------------------------------------------------------------------------------------------
  AH4 pix0,pix1;
  CpfDepack4(pix0,pix1,colR,colG,colB,z);
  CpfColStH(constIdx,p,pix0);
  CpfColStH(constIdx,p+AW2(8,0),pix1);
//------------------------------------------------------------------------------------------------------------------------------
  mX*=AH2_(constXY.x);
  mY*=AH2_(constXY.y);
  AW2 mp=CpfMovPckH(mX,mY,dit);
  CpfMovStH(constIdx,p,mp.x);
  CpfMovStH(constIdx,p+AW2(8,0),mp.y);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                               [CPF] [REC] RECONSTRUCTION PASS
//
//------------------------------------------------------------------------------------------------------------------------------
// This pass composites two frames {current and prior} so that motion blur often has leading and trailing backgrounds.
// The pass also does the 2xTSSAA resolve step.
//  U = even frame.
//  V = odd  frame.
//            ......
//            . v5 .
//       ................
//       . u3 .    . u2 .            ---
//  ..........+---------+.....        ^
//  . v4 .    | v0 .    | v1 .        |  one texel distance for the even input image
//  ..........|....X....|..........   V
//       . u1 |    . u0 |    . u4 .  ---
//       .....+---------+..........
//            . v2 .    . v3 .
//            ................
//                 . u5 .
//                 ......
//==============================================================================================================================
// Filtering kernel.
#if defined(A_GPU)&&(CPF_SMOOTH==0)
 // Simple tight kernel with no negative lobes (no ringing): (x^2-1)^4
 AF2 CpfW(AF2 dX,AF2 dY,AF1 k){AF2 d2=ASatF2((dX*dX+dY*dY)*AF2_(k));d2-=AF2_(1.0);d2*=d2;d2=ASatF2(d2*d2);return d2;}
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if defined(A_GPU)&&defined(A_HALF)&&(CPF_SMOOTH==0)
 AH2 CpfWH(AH2 dX,AH2 dY,AH1 k){AH2 d2=ASatH2((dX*dX+dY*dY)*AH2_(k));d2-=AH2_(1.0);d2*=d2;d2=ASatH2(d2*d2);return d2;}
#endif
//==============================================================================================================================
#if defined(A_GPU)&&(CPF_SMOOTH==1)
 // Simple less tight kernel. 1+x^4-2*x^2
 AF2 CpfW(AF2 dX,AF2 dY,AF1 k){AF2 d2=ASatF2((dX*dX+dY*dY)*AF2_(k));return AF2_(1.0)+d2*d2+AF2_(-2.0)*d2;}
#endif
//------------------------------------------------------------------------------------------------------------------------------
#if defined(A_GPU)&&defined(A_HALF)&&(CPF_SMOOTH==1)
 AH2 CpfWH(AH2 dX,AH2 dY,AF1 k){AH2 d2=ASatH2((dX*dX+dY*dY)*AH2_(k));return AH2_(1.0)+d2*d2+AH2_(-2.0)*d2;}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                   MEM SPEED-OF-LIGHT TEST
//------------------------------------------------------------------------------------------------------------------------------
// This pass does the same amount of loads without the extra ALU logic, to provide a way to know perf limit.
//==============================================================================================================================
// TODO: Remove me!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if defined(A_GPU)&&0
 void CpfRecSol(AU2 p){
  AU4 const0=CpfGet(CPF_C32_REC0);
  AF2 constRcpRes=AF2_AU2(const0.xy);
  AF2 uP4=AF2(p)*constRcpRes;
  AF2 vP4=uP4+constRcpRes;
  AU4 uM4=CpfMov4R(0,uP4).grba;
  AU4 vM4=CpfMov4R(1,vP4).abrg;
  AF4 uZ4=CpfCol4A(0,uP4).grba;
  AF4 vZ4=CpfCol4A(1,vP4).abrg;
  AF4 uC0,uC1,uC2,uC3,uC4,uC5;
  AF4 vC0,vC1,vC2,vC3,vC4,vC5;
  #if CPF_TAP>10
   uC5=CpfColLd(0,p+AU2(ASU2( 0, 1)));
  #endif
  #if CPF_TAP>8
   uC4=CpfColLd(0,p+AU2(ASU2( 1, 0)));
  #endif
  uC3=CpfColLd(0,p+AU2(ASU2(-1,-1)));
  uC2=CpfColLd(0,p+AU2(ASU2( 0,-1)));
  uC1=CpfColLd(0,p+AU2(ASU2(-1, 0)));
  uC0=CpfColLd(0,p+AU2(ASU2( 0, 0)));
  vC0=CpfColLd(1,p+AU2(ASU2( 0, 0)));
  vC1=CpfColLd(1,p+AU2(ASU2( 1, 0)));
  vC2=CpfColLd(1,p+AU2(ASU2( 0, 1)));
  vC3=CpfColLd(1,p+AU2(ASU2( 1, 1)));
  #if CPF_TAP>8
   vC4=CpfColLd(1,p+AU2(ASU2(-1, 0)));
  #endif
  #if CPF_TAP>10
   vC5=CpfColLd(1,p+AU2(ASU2( 0,-1)));
  #endif
  AF4 st=AF4_(0.0);
  st.a+=AF1_AU1(uM4.r)+AF1_AU1(uM4.g)+AF1_AU1(uM4.b)+AF1_AU1(uM4.a);
  st.a+=AF1_AU1(vM4.r)+AF1_AU1(vM4.g)+AF1_AU1(vM4.b)+AF1_AU1(vM4.a);
  st.a+=uZ4.r+uZ4.g+uZ4.b+uZ4.a;
  st.a+=vZ4.r+vZ4.g+vZ4.b+vZ4.a;
  st.a+=uC3.r+uC3.g+uC3.b+uC3.a;
  st.a+=uC2.r+uC2.g+uC2.b+uC2.a;
  st.a+=uC1.r+uC1.g+uC1.b+uC1.a;
  st.a+=uC0.r+uC0.g+uC0.b+uC0.a;
  st.a+=vC0.r+vC0.g+vC0.b+vC0.a;
  st.a+=vC1.r+vC1.g+vC1.b+vC1.a;
  st.a+=vC2.r+vC2.g+vC2.b+vC2.a;
  st.a+=vC3.r+vC3.g+vC3.b+vC3.a;
  #if CPF_TAP>8
   st.a+=uC4.r+uC4.g+uC4.b+uC4.a;
   st.a+=vC4.r+vC4.g+vC4.b+vC4.a;
  #endif
  #if CPF_TAP>10
   st.a+=uC5.r+uC5.g+uC5.b+uC5.a;
   st.a+=vC5.r+vC5.g+vC5.b+vC5.a;
  #endif
  st.a=1.0-ASatF1(st.a);
  st.rgb=uC0.rgb+vC0.rgb;
  CpfClnSt(p,st);}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                        32-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(CPF_32BIT)
 // Reconstruction pass.
 void CpfRec(
 // TODO: Double check this is optimal (workgroup index, vs workitem index)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 AU2 wxy,
 AU2 p){
  // Gather motion vectors. 
  // This is already centered for the 2x2 quad.
  AU4 const0=CpfGet(CPF_C32_REC0);
  AF2 constRcpRes=AF2_AU2(const0.xy);
  AF2 uP4=AF2(p)*constRcpRes;
  // Move one texel over to get center of other quad.
  AF2 vP4=uP4+constRcpRes;
  // Gather 4 ordering.
  //  a b
  //  r g
  // Swizzled so x={u,v}0,y={u,v}1,z={u,v}2,w={u,v}3.
  AU4 uM4=CpfMov4R(0,uP4).grba;
  AU4 vM4=CpfMov4R(1,vP4).abrg;
//------------------------------------------------------------------------------------------------------------------------------
  // Gather associated CoC values.
  AF4 uZ4=CpfCol4A(0,uP4).grba;
  AF4 vZ4=CpfCol4A(1,vP4).abrg;
//------------------------------------------------------------------------------------------------------------------------------
  // Pack CoC in top 16 bits of motion vector.
  uM4.x=(AU1_AH1_AF1(uZ4.x)<<16)|(uM4.x&65535u);
  uM4.y=(AU1_AH1_AF1(uZ4.y)<<16)|(uM4.y&65535u);
  uM4.z=(AU1_AH1_AF1(uZ4.z)<<16)|(uM4.z&65535u);
  uM4.w=(AU1_AH1_AF1(uZ4.w)<<16)|(uM4.w&65535u);
  vM4.x=(AU1_AH1_AF1(vZ4.x)<<16)|(vM4.x&65535u);
  vM4.y=(AU1_AH1_AF1(vZ4.y)<<16)|(vM4.y&65535u);
  vM4.z=(AU1_AH1_AF1(vZ4.z)<<16)|(vM4.z&65535u);
  vM4.w=(AU1_AH1_AF1(vZ4.w)<<16)|(vM4.w&65535u);
//------------------------------------------------------------------------------------------------------------------------------
  // Get maximum to get nearest.
  AU1 uMPck=max(AMax3U1(uM4.x,uM4.y,uM4.z),uM4.w);
  AU1 vMPck=max(AMax3U1(vM4.x,vM4.y,vM4.z),vM4.w);
  // Nearest motion is used to choose blend weights (gradient of motion to still).
  AU1 nMPck=max(uMPck,vMPck);
//------------------------------------------------------------------------------------------------------------------------------
  // Extra motion vectors and CoC.
#if A_HLSL
  // Volkan: Workaround here as there's an issue with motion vector unpacking with HLSL.
  AF2 uM = AF2_(0); // Volkan: ABsc0FromU1() returns different results for HLSL(-128f) vs GLSL (0). This causes HLSL to have broken output.
  AF2 vM = AF2_(0); // Volkan: ABsc0FromU1() returns different results for HLSL(-128f) vs GLSL (0). This causes HLSL to have broken output.
  AF2 nM = AF2_(0); // Volkan: ABsc0FromU1() returns different results for HLSL(-128f) vs GLSL (0). This causes HLSL to have broken output.
#else
  AF2 uM=AF2(CpfMovX(uMPck),CpfMovY(uMPck));
  AF2 vM=AF2(CpfMovX(vMPck),CpfMovY(vMPck));
  AF2 nM=AF2(CpfMovX(nMPck),CpfMovY(nMPck));
#endif
  // TODO: Remove me when verified fixed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  #if 0
   // TODO: Make this not require A_HALF!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AF2 uvZ=AF2(AH2_AU1(uMPck).y,AH2_AU1(vMPck).y);
  #else
   AF2 uvZ;
   uvZ.x=AF2_AH2_AU1(uMPck).y;
   uvZ.y=AF2_AH2_AU1(vMPck).y;
  #endif   
//------------------------------------------------------------------------------------------------------------------------------
  // Moving term.
  //  X := {0=still, 1=0.5 pixel motion or more} -> used to adjust kernel weight.
  //  Y := {0=still, 1=4.0 pixel motion or more} -> used to weight between non-motion and motion resolve.
  AF1 nMax=max(abs(nM.x),abs(nM.y));
  AF2 moving=ASatF2(AF2_(nMax)*AF2(2.0,1.0/4.0));
//------------------------------------------------------------------------------------------------------------------------------
  // Motion sign (this change directions based on which frame is previous vs current). 
  //TODO_UE4_REC: this code is causing serious ghosting effect, need further investigation for its corresponding logic
  AF1 sgn=AF1_AU1(const0.z);
  uM*=AF2_(sgn);
  vM*=AF2_(-sgn);
//------------------------------------------------------------------------------------------------------------------------------
  // Noisy position to offset motion.
  // This uses a simple fixed dither pattern.
  AF1 noz;
  #if CPF_TAP==8
   noz=CpfDitM(p,AF1_(1.0/4.0));
  #endif
  #if CPF_TAP==10
   noz=CpfDitM(p,AF1_(1.0/5.0));
  #endif
  #if CPF_TAP==12
   noz=CpfDitM(p,AF1_(1.0/6.0));
  #endif
  AF2 uP=uM*AF2_(noz);
  AF2 vP=vM*AF2_(noz);
//------------------------------------------------------------------------------------------------------------------------------
  // Positions.
  AF2 uQ0,uQ1,uQ2,uQ3,uQ4,uQ5;
  AF2 vQ0,vQ1,vQ2,vQ3,vQ4,vQ5;
  #if CPF_TAP==8
   uQ3=uM*AF2_(-3.0/4.0)+uP;
   uQ2=uM*AF2_( 3.0/4.0)+uP;
   uQ1=uM*AF2_(-1.0/4.0)+uP;
   uQ0=uM*AF2_( 1.0/4.0)+uP;
   vQ0=vM*AF2_( 1.0/4.0)+vP;
   vQ1=vM*AF2_(-1.0/4.0)+vP;
   vQ2=vM*AF2_( 3.0/4.0)+vP;
   vQ3=vM*AF2_(-3.0/4.0)+vP;
  #endif
  #if CPF_TAP==10
   uQ4=uM*AF2_( 4.0/5.0)+uP;
   uQ3=uM*AF2_(-4.0/5.0)+uP;
   uQ2=uM*AF2_( 2.0/5.0)+uP;
   uQ1=uM*AF2_(-2.0/5.0)+uP;
   uQ0=uM*AF2_( 0.0/5.0)+uP;
   vQ0=vM*AF2_( 0.0/5.0)+vP;
   vQ1=vM*AF2_(-2.0/5.0)+vP;
   vQ2=vM*AF2_( 2.0/5.0)+vP;
   vQ3=vM*AF2_(-4.0/5.0)+vP;
   vQ4=vM*AF2_( 4.0/5.0)+vP;
  #endif
  #if CPF_TAP==12
   uQ5=uM*AF2_( -5.0/6.0)+uP;
   uQ4=uM*AF2_(  5.0/6.0)+uP;
   uQ3=uM*AF2_( -3.0/6.0)+uP;
   uQ2=uM*AF2_(  3.0/6.0)+uP;
   uQ1=uM*AF2_( -1.0/6.0)+uP;
   uQ0=uM*AF2_(  1.0/6.0)+uP;
   vQ0=vM*AF2_(  1.0/6.0)+vP;
   vQ1=vM*AF2_( -1.0/6.0)+vP;
   vQ2=vM*AF2_(  3.0/6.0)+vP;
   vQ3=vM*AF2_( -3.0/6.0)+vP;
   vQ4=vM*AF2_(  5.0/6.0)+vP;
   vQ5=vM*AF2_( -5.0/6.0)+vP;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
#if 0
  // TODO: Is round() necessary?????????????????????????????????????????????????????????????????????????????????????????????????
  uQ5=round(uQ5);
  uQ4=round(uQ4);
  uQ3=round(uQ3);
  uQ2=round(uQ2);
  uQ1=round(uQ1);
  uQ0=round(uQ0);
  vQ0=round(vQ0);
  vQ1=round(vQ1);
  vQ2=round(vQ2);
  vQ3=round(vQ3);
  vQ4=round(vQ4);
  vQ5=round(vQ5);
#endif
//------------------------------------------------------------------------------------------------------------------------------
  // Load colors.
  AF4 uC0,uC1,uC2,uC3,uC4,uC5;
  AF4 vC0,vC1,vC2,vC3,vC4,vC5;
  #if CPF_TAP>10
   uC5=CpfColLd(0,p+AU2(ASU2( 0, 1))+AU2(ASU2(uQ5)));
  #endif
  #if CPF_TAP>8
   uC4=CpfColLd(0,p+AU2(ASU2( 1, 0))+AU2(ASU2(uQ4)));
  #endif
  uC3=CpfColLd(0,p+AU2(ASU2(-1,-1))+AU2(ASU2(uQ3)));
  uC2=CpfColLd(0,p+AU2(ASU2( 0,-1))+AU2(ASU2(uQ2)));
  uC1=CpfColLd(0,p+AU2(ASU2(-1, 0))+AU2(ASU2(uQ1)));
  uC0=CpfColLd(0,p+AU2(ASU2( 0, 0))+AU2(ASU2(uQ0)));
  vC0=CpfColLd(1,p+AU2(ASU2( 0, 0))+AU2(ASU2(vQ0)));
  vC1=CpfColLd(1,p+AU2(ASU2( 1, 0))+AU2(ASU2(vQ1)));
  vC2=CpfColLd(1,p+AU2(ASU2( 0, 1))+AU2(ASU2(vQ2)));
  vC3=CpfColLd(1,p+AU2(ASU2( 1, 1))+AU2(ASU2(vQ3)));
  #if CPF_TAP>8
   vC4=CpfColLd(1,p+AU2(ASU2(-1, 0))+AU2(ASU2(vQ4)));
  #endif
  #if CPF_TAP>10
   vC5=CpfColLd(1,p+AU2(ASU2( 0,-1))+AU2(ASU2(vQ5)));
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // Rename or AOS-to-SOA conversion for 16-bit version.
  AF2 uvC0R,uvC0G,uvC0B,uvC0A;
  AF2 uvC1R,uvC1G,uvC1B,uvC1A;
  AF2 uvC2R,uvC2G,uvC2B,uvC2A;
  AF2 uvC3R,uvC3G,uvC3B,uvC3A;
  AF2 uvC4R,uvC4G,uvC4B,uvC4A;
  AF2 uvC5R,uvC5G,uvC5B,uvC5A;
  uvC0R=AF2(uC0.r,vC0.r);
  uvC1R=AF2(uC1.r,vC1.r);
  uvC2R=AF2(uC2.r,vC2.r);
  uvC3R=AF2(uC3.r,vC3.r);
  uvC4R=AF2(uC4.r,vC4.r);
  uvC5R=AF2(uC5.r,vC5.r);
  uvC0G=AF2(uC0.g,vC0.g);
  uvC1G=AF2(uC1.g,vC1.g);
  uvC2G=AF2(uC2.g,vC2.g);
  uvC3G=AF2(uC3.g,vC3.g);
  uvC4G=AF2(uC4.g,vC4.g);
  uvC5G=AF2(uC5.g,vC5.g);
  uvC0B=AF2(uC0.b,vC0.b);
  uvC1B=AF2(uC1.b,vC1.b);
  uvC2B=AF2(uC2.b,vC2.b);
  uvC3B=AF2(uC3.b,vC3.b);
  uvC4B=AF2(uC4.b,vC4.b);
  uvC5B=AF2(uC5.b,vC5.b);
  uvC0A=AF2(uC0.a,vC0.a);
  uvC1A=AF2(uC1.a,vC1.a);
  uvC2A=AF2(uC2.a,vC2.a);
  uvC3A=AF2(uC3.a,vC3.a);
  uvC4A=AF2(uC4.a,vC4.a);
  uvC5A=AF2(uC5.a,vC5.a);
//------------------------------------------------------------------------------------------------------------------------------
  // Gamma 3.0 to linear.
  uvC0R=uvC0R*uvC0R*uvC0R;uvC0G=uvC0G*uvC0G*uvC0G;uvC0B=uvC0B*uvC0B*uvC0B;
  uvC1R=uvC1R*uvC1R*uvC1R;uvC1G=uvC1G*uvC1G*uvC1G;uvC1B=uvC1B*uvC1B*uvC1B;
  uvC2R=uvC2R*uvC2R*uvC2R;uvC2G=uvC2G*uvC2G*uvC2G;uvC2B=uvC2B*uvC2B*uvC2B;
  uvC3R=uvC3R*uvC3R*uvC3R;uvC3G=uvC3G*uvC3G*uvC3G;uvC3B=uvC3B*uvC3B*uvC3B;
  uvC4R=uvC4R*uvC4R*uvC4R;uvC4G=uvC4G*uvC4G*uvC4G;uvC4B=uvC4B*uvC4B*uvC4B;
  uvC5R=uvC5R*uvC5R*uvC5R;uvC5G=uvC5G*uvC5G*uvC5G;uvC5B=uvC5B*uvC5B*uvC5B;
//------------------------------------------------------------------------------------------------------------------------------
  // Distance weights.
  // Anything at 0.5 pixel motion will have 50% less samples for AA, so amplify kernel size.
  AF2 uvW0,uvW1,uvW2,uvW3,uvW4,uvW5;
  #if CPF_PSL
   AF1 krn=AF1_(0.5)-AF1_(0.375)*moving.x;
   AF2 uvQ0X,uvQ1X,uvQ2X,uvQ3X,uvQ4X,uvQ5X;
   AF2 uvQ0Y,uvQ1Y,uvQ2Y,uvQ3Y,uvQ4Y,uvQ5Y;
   //    v5
   // v4(v0)v1
   //    v2 v3
   // ---------
   // u3 u2
   // u1(u0)u4
   //    u5
   AF1 chk;
   chk=AF1((p.x^p.y)&AU1_(1))*AF1_(2.0)-AF1_(1.0);
   uvQ0X=AF2_(-chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ0Y=AF2_(-chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ3X=AF2_(-chk)*AF2_(0.125)+AF2(-1.0+0.25, 1.0-0.25);
   uvQ3Y=AF2_(-chk)*AF2_(0.125)+AF2(-1.0+0.25, 1.0-0.25);
   uvQ1X=AF2_( chk)*AF2_(0.125)+AF2(-1.0+0.25, 1.0-0.25);
   uvQ1Y=AF2_( chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ2X=AF2_( chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ2Y=AF2_( chk)*AF2_(0.125)+AF2(-1.0+0.25, 1.0-0.25);
   uvQ4X=AF2_( chk)*AF2_(0.125)+AF2( 1.0+0.25,-1.0-0.25);
   uvQ4Y=AF2_( chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ5X=AF2_( chk)*AF2_(0.125)+AF2( 0.0+0.25, 0.0-0.25);
   uvQ5Y=AF2_( chk)*AF2_(0.125)+AF2( 1.0+0.25,-1.0-0.25);
   uvW0=CpfW(uvQ0X,uvQ0Y,krn);
   uvW1=CpfW(uvQ1X,uvQ1Y,krn);
   uvW2=CpfW(uvQ2X,uvQ2Y,krn);
   uvW3=CpfW(uvQ3X,uvQ3Y,krn);
   uvW4=CpfW(uvQ4X,uvQ4Y,krn);
   uvW5=CpfW(uvQ5X,uvQ5Y,krn);
  #else
   // Faster (but lower quality) to interpolate between 2 kernels for non-PSL case.
   // Adapting to kernel size to the amount of motion is important to mask temporal aliasing.
   // The following are immediate constants.
   AF2 uvW0And12a=CpfW(AF2(CPF_JIT,1.0-CPF_JIT),AF2(CPF_JIT,CPF_JIT),AF1_(0.5));
   AF2 uvW3And45a=CpfW(AF2(1.0-CPF_JIT,1.0+CPF_JIT),AF2(1.0-CPF_JIT,CPF_JIT),AF1_(0.5));
   AF2 uvW0And12b=CpfW(AF2(CPF_JIT,1.0-CPF_JIT),AF2(CPF_JIT,CPF_JIT),AF1_(0.125));
   AF2 uvW3And45b=CpfW(AF2(1.0-CPF_JIT,1.0+CPF_JIT),AF2(1.0-CPF_JIT,CPF_JIT),AF1_(0.125));
   // Blend between the two kernels.
   AF2 uvW0And12=ALerpF2(uvW0And12a,uvW0And12b,AF2_(moving.x));
   AF2 uvW3And45=ALerpF2(uvW3And45a,uvW3And45b,AF2_(moving.x));
   // This is setup to share code with PSL.
   uvW0=uvW0And12.xx;
   uvW1=uvW2=uvW0And12.yy;
   uvW3=uvW3And45.xx;
   uvW4=uvW5=uvW3And45.yy;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: Should this be moved later???????????????????????????????????????????????????????????????????????????????????????????
  // Kill anything pulled from off-screen.
  uvW0*=AGtZeroF2(uvC0A);
  uvW1*=AGtZeroF2(uvC1A);
  uvW2*=AGtZeroF2(uvC2A);
  uvW3*=AGtZeroF2(uvC3A);
  uvW4*=AGtZeroF2(uvC4A);
  uvW5*=AGtZeroF2(uvC5A);
//------------------------------------------------------------------------------------------------------------------------------
  // Micro depth of field, grab nearest.
  // Running this early to avoid keeping alphas around later.
  #if CPF_MDF
   // Take maximum of circle of confusion.
   AF1 dof=max(uvC0A.x,uvC0A.y);
   dof=AMax3F1(dof,uvC1A.x,uvC1A.y);
   dof=AMax3F1(dof,uvC2A.x,uvC2A.y);
   dof=AMax3F1(dof,uvC3A.x,uvC3A.y);
   #if CPF_TAP>8
    dof=AMax3F1(dof,uvC4A.x,uvC4A.y);
   #endif
   #if CPF_TAP>10
    dof=AMax3F1(dof,uvC5A.x,uvC5A.y);
   #endif
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // Good weights (as in won't bleed foreground), 1=self or behind.
  AF2 uvZG=CpfZG(uvZ);
  AF2 uvG0,uvG1,uvG2,uvG3,uvG4,uvG5;
  uvG0=CpfZ(uvC0A,uvZG);
  uvG1=CpfZ(uvC1A,uvZG);
  uvG2=CpfZ(uvC2A,uvZG);
  uvG3=CpfZ(uvC3A,uvZG);
  uvG4=CpfZ(uvC4A,uvZG);
  uvG5=CpfZ(uvC5A,uvZG);
  // Sum.
  AF2 uvGSum=(uvG0*uvW0)+(uvG1*uvW1)+(uvG2*uvW2)+(uvG3*uvW3);
  #if CPF_TAP>8
   uvGSum+=uvG4*uvW4;
  #endif
  #if CPF_TAP>10
   uvGSum+=uvG5*uvW5;
  #endif
  // Normalization term.
  AF2 uvGRcp=APrxMedRcpF2(uvGSum);
//------------------------------------------------------------------------------------------------------------------------------
  // Work towards foreground weights for each image.
  // Self, 1=self.
  AF2 uvZF=CpfZF(uvZ);
  AF2 uvS0,uvS1,uvS2,uvS3,uvS4,uvS5;
  uvS0=uvG0-CpfZ(uvC0A,uvZF);
  uvS1=uvG1-CpfZ(uvC1A,uvZF);
  uvS2=uvG2-CpfZ(uvC2A,uvZF);
  uvS3=uvG3-CpfZ(uvC3A,uvZF);
  uvS4=uvG4-CpfZ(uvC4A,uvZF);
  uvS5=uvG5-CpfZ(uvC5A,uvZF);
  // Sum avoiding zero.
  AF2 uvSSum=(uvS0*uvW0+AF2_(1.0/4096.0))+(uvS1*uvW1)+(uvS2*uvW2)+(uvS3*uvW3);
  #if CPF_TAP>8
   uvSSum+=uvS4*uvW4;
  #endif
  #if CPF_TAP>10
   uvSSum+=uvS5*uvW5;
  #endif
  // Normalization term.
  AF2 uvSRcp=APrxMedRcpF2(uvSSum);
  // Foreground amount of each image.
  AF2 uvSAmt=ASatF2(uvSSum*uvGRcp);
  AF2 uvSAmt2=uvSAmt*uvSAmt;
  uvSAmt2*=uvSAmt2;
  uvSAmt=ALerpF2(uvSAmt,uvSAmt2,AF2_(moving.y));
//------------------------------------------------------------------------------------------------------------------------------
  // Compute blend between frames.
  // Behind, 1=behind other self (ie the '.yx').
  AF2 uvB0,uvB1,uvB2,uvB3,uvB4,uvB5;
  uvB0=CpfZ(uvC0A,uvZF.yx);
  uvB1=CpfZ(uvC1A,uvZF.yx);
  uvB2=CpfZ(uvC2A,uvZF.yx);
  uvB3=CpfZ(uvC3A,uvZF.yx);
  uvB4=CpfZ(uvC4A,uvZF.yx);
  uvB5=CpfZ(uvC5A,uvZF.yx);
  // Sums avoiding zero.
  AF2 uvBSum=(uvB0*uvW0+AF2_(1.0/4096.0))+(uvB1*uvW1)+(uvB2*uvW2)+(uvB3*uvW3);
  #if CPF_TAP>8
   uvBSum+=uvB4*uvW4;
  #endif
  #if CPF_TAP>10
   uvBSum+=uvB5*uvW5;
  #endif
  // Normalization terms.
  AF2 uvBRcp=APrxMedRcpF2(uvBSum);
  // Amount of blend between frames.
  // Bring BAmt back to {0 to 1} to maintain precision.
  AF1 rcpBSum=APrxMedRcpF1(uvBSum.x+uvBSum.y);
  AF2 uvBAmt=ASatF2(uvBSum.yx*AF2_(rcpBSum));
//------------------------------------------------------------------------------------------------------------------------------
  // Motion weighting, amount of self.
  AF2 uvS=uvSRcp*uvGSum*uvSAmt*uvBAmt;
  // Motion weighting, pull background from other frame.
  AF2 uvB=uvBRcp*uvGSum.yx*(AF2_(1.0)-uvSAmt.yx)*uvBAmt.yx;
  // Blend between good kernel weights, and motion weighting.
  uvW0*=ALerpF2(uvG0,(uvS0*uvS)+(uvB0*uvB),AF2_(moving.y));
  uvW1*=ALerpF2(uvG1,(uvS1*uvS)+(uvB1*uvB),AF2_(moving.y));
  uvW2*=ALerpF2(uvG2,(uvS2*uvS)+(uvB2*uvB),AF2_(moving.y));
  uvW3*=ALerpF2(uvG3,(uvS3*uvS)+(uvB3*uvB),AF2_(moving.y));
  uvW4*=ALerpF2(uvG4,(uvS4*uvS)+(uvB4*uvB),AF2_(moving.y));
  uvW5*=ALerpF2(uvG5,(uvS5*uvS)+(uvB5*uvB),AF2_(moving.y));
//------------------------------------------------------------------------------------------------------------------------------
  // Weighted average is different for 32-bit version (end pairs early to avoid extra ops).
  AF4 col;
  col.r=(uvC0R.x*uvW0.x)+(uvC1R.x*uvW1.x)+(uvC2R.x*uvW2.x)+(uvC3R.x*uvW3.x);
  col.g=(uvC0G.x*uvW0.x)+(uvC1G.x*uvW1.x)+(uvC2G.x*uvW2.x)+(uvC3G.x*uvW3.x);
  col.b=(uvC0B.x*uvW0.x)+(uvC1B.x*uvW1.x)+(uvC2B.x*uvW2.x)+(uvC3B.x*uvW3.x);
  col.r+=(uvC0R.y*uvW0.y)+(uvC1R.y*uvW1.y)+(uvC2R.y*uvW2.y)+(uvC3R.y*uvW3.y);
  col.g+=(uvC0G.y*uvW0.y)+(uvC1G.y*uvW1.y)+(uvC2G.y*uvW2.y)+(uvC3G.y*uvW3.y);
  col.b+=(uvC0B.y*uvW0.y)+(uvC1B.y*uvW1.y)+(uvC2B.y*uvW2.y)+(uvC3B.y*uvW3.y);
  #if CPF_TAP>8
   col.r+=(uvC4R.x*uvW4.x)+(uvC4R.y*uvW4.y);
   col.g+=(uvC4G.x*uvW4.x)+(uvC4G.y*uvW4.y);
   col.b+=(uvC4B.x*uvW4.x)+(uvC4B.y*uvW4.y);
  #endif
  #if CPF_TAP>10
   col.r+=(uvC5R.x*uvW5.x)+(uvC5R.y*uvW5.y);
   col.g+=(uvC5G.x*uvW5.x)+(uvC5G.y*uvW5.y);
   col.b+=(uvC5B.x*uvW5.x)+(uvC5B.y*uvW5.y);
  #endif
  col.a=AF1(moving.y)*AF1_(0.5);
  AF1 rcpW=uvW0.x+uvW1.x+uvW2.x+uvW3.x+uvW0.y+uvW1.y+uvW2.y+uvW3.y;
  #if CPF_TAP>8
   rcpW+=uvW4.x+uvW4.y;
  #endif
  #if CPF_TAP>10
   rcpW+=uvW5.x+uvW5.y;
  #endif
  rcpW=APrxMedRcpF1(rcpW);
  col.rgb*=rcpW;
//------------------------------------------------------------------------------------------------------------------------------
  // Micro depth of field, apply to alpha.
  #if CPF_MDF
   // Convert back to signed circle of confusion (negative is far).
   dof=dof*AF1_(2.0)-AF1_(1.0);
   col.a=max(col.a,abs(dof));
   col.a=ACpySgnF1(col.a,dof);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // Convert back to HDR range for store to 16-bit/channel surface.
  CpfMdrToHdr(col.rgb);
  CpfClnSt(p,col);
//------------------------------------------------------------------------------------------------------------------------------
  // Optionally run diffusion.  
  #if CPF_DFU
   CpfDfu(wxy,p);
  #endif
 }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                        16-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)&&defined(CPF_16BIT)
 // Half version which works on one 8x8 tile just like the 32-bit version.
 // This is packed unrolled in the access to the prior and current image.
 void CpfRecH(AU2 wxy,AU2 p){
  // Gather motion vectors. 
  // This is already centered for the 2x2 quad.
  AU4 const0=CpfGet(CPF_C16_REC0);
  AF2 constRcpRes=AF2_AU2(const0.xy);
  AF2 uP4=AF2(p)*constRcpRes;
  // Move one texel over to get center of other quad.
  AF2 vP4=uP4+constRcpRes;
  // Gather 4 ordering.
  //  a b
  //  r g
  // Swizzled so x={u,v}0,y={u,v}1,z={u,v}2,w={u,v}3.
  AU4 uM4=CpfMov4R(0,uP4).grba;
  AU4 vM4=CpfMov4R(1,vP4).abrg;
//------------------------------------------------------------------------------------------------------------------------------
  // Gather associated CoC values.
  AH4 uZ4=CpfCol4AH(0,uP4).grba;
  AH4 vZ4=CpfCol4AH(1,vP4).abrg;
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: If ALU bound still, could burn 32-bits for motion vector, pack on store instead!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Pack CoC in top 16 bits of motion vector.
  uM4.x=AU1_AH2(AH2(AH2_AU1(uM4.x).x,uZ4.x));
  uM4.y=AU1_AH2(AH2(AH2_AU1(uM4.y).x,uZ4.y));
  uM4.z=AU1_AH2(AH2(AH2_AU1(uM4.z).x,uZ4.z));
  uM4.w=AU1_AH2(AH2(AH2_AU1(uM4.w).x,uZ4.w));
  vM4.x=AU1_AH2(AH2(AH2_AU1(vM4.x).x,vZ4.x));
  vM4.y=AU1_AH2(AH2(AH2_AU1(vM4.y).x,vZ4.y));
  vM4.z=AU1_AH2(AH2(AH2_AU1(vM4.z).x,vZ4.z));
  vM4.w=AU1_AH2(AH2(AH2_AU1(vM4.w).x,vZ4.w));
//------------------------------------------------------------------------------------------------------------------------------
  // Get maximum to get nearest.
  AU1 uMPck=max(AMax3U1(uM4.x,uM4.y,uM4.z),uM4.w);
  AU1 vMPck=max(AMax3U1(vM4.x,vM4.y,vM4.z),vM4.w);
  // Nearest motion is used to choose blend weights (gradient of motion to still).
  AU1 nMPck=max(uMPck,vMPck);
//------------------------------------------------------------------------------------------------------------------------------
  // Extra motion vectors and CoC.
  #if 0
   // TODO: Remove me after faster code is validated to work correctly!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AH2 uM=AH2(CpfMovX(uMPck),CpfMovY(uMPck));
   AH2 vM=AH2(CpfMovX(vMPck),CpfMovY(vMPck));
   AH2 nM=AH2(CpfMovX(nMPck),CpfMovY(nMPck));
  #else
   AH2 uM=CpfMovXYH(uMPck);
   AH2 vM=CpfMovXYH(vMPck);
   AH2 nM=CpfMovXYH(nMPck);
  #endif
  AH2 uvZ=AH2(AH2_AU1(uMPck).y,AH2_AU1(vMPck).y);
//------------------------------------------------------------------------------------------------------------------------------
  // Moving term.
  //  X := {0=still, 1=0.5 pixel motion or more} -> used to adjust kernel weight.
  //  Y := {0=still, 1=4.0 pixel motion or more} -> used to weight between non-motion and motion resolve.
  AH1 nMax=max(abs(nM.x),abs(nM.y));
  AH2 moving=ASatH2(AH2_(nMax)*AH2(2.0,1.0/4.0));
//------------------------------------------------------------------------------------------------------------------------------
  // Motion sign (this change directions based on which frame is previous vs current). 
  AH1 sgn=AH2_AU1(const0.z).x;
  uM*=AH2_(sgn);
  vM*=AH2_(-sgn);
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: Remove the AW2() around p!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  AH1 noz;
  #if CPF_TAP==8
   noz=CpfDitMH(AW2(p),AH1_(1.0/4.0));
  #endif
  #if CPF_TAP==10
   noz=CpfDitMH(AW2(p),AH1_(1.0/5.0));
  #endif
  #if CPF_TAP==12
   noz=CpfDitMH(AW2(p),AH1_(1.0/6.0));
  #endif
  AH2 uP=uM*AH2_(noz);
  AH2 vP=vM*AH2_(noz);
//------------------------------------------------------------------------------------------------------------------------------
  // Positions.
  AH2 uQ0,uQ1,uQ2,uQ3,uQ4,uQ5;
  AH2 vQ0,vQ1,vQ2,vQ3,vQ4,vQ5;
  #if CPF_TAP==8
   uQ3=uM*AH2_(-3.0/4.0)+uP;
   uQ2=uM*AH2_( 3.0/4.0)+uP;
   uQ1=uM*AH2_(-1.0/4.0)+uP;
   uQ0=uM*AH2_( 1.0/4.0)+uP;
   vQ0=vM*AH2_( 1.0/4.0)+vP;
   vQ1=vM*AH2_(-1.0/4.0)+vP;
   vQ2=vM*AH2_( 3.0/4.0)+vP;
   vQ3=vM*AH2_(-3.0/4.0)+vP;
  #endif
  #if CPF_TAP==10
   uQ4=uM*AH2_( 4.0/5.0)+uP;
   uQ3=uM*AH2_(-4.0/5.0)+uP;
   uQ2=uM*AH2_( 2.0/5.0)+uP;
   uQ1=uM*AH2_(-2.0/5.0)+uP;
   uQ0=uM*AH2_( 0.0/5.0)+uP;
   vQ0=vM*AH2_( 0.0/5.0)+vP;
   vQ1=vM*AH2_(-2.0/5.0)+vP;
   vQ2=vM*AH2_( 2.0/5.0)+vP;
   vQ3=vM*AH2_(-4.0/5.0)+vP;
   vQ4=vM*AH2_( 4.0/5.0)+vP;
  #endif
  #if CPF_TAP==12
   uQ5=uM*AH2_( -5.0/6.0)+uP;
   uQ4=uM*AH2_(  5.0/6.0)+uP;
   uQ3=uM*AH2_( -3.0/6.0)+uP;
   uQ2=uM*AH2_(  3.0/6.0)+uP;
   uQ1=uM*AH2_( -1.0/6.0)+uP;
   uQ0=uM*AH2_(  1.0/6.0)+uP;
   vQ0=vM*AH2_(  1.0/6.0)+vP;
   vQ1=vM*AH2_( -1.0/6.0)+vP;
   vQ2=vM*AH2_(  3.0/6.0)+vP;
   vQ3=vM*AH2_( -3.0/6.0)+vP;
   vQ4=vM*AH2_(  5.0/6.0)+vP;
   vQ5=vM*AH2_( -5.0/6.0)+vP;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
#if 0
  // TODO: Is round() necessary?????????????????????????????????????????????????????????????????????????????????????????????????
  uQ5=round(uQ5);
  uQ4=round(uQ4);
  uQ3=round(uQ3);
  uQ2=round(uQ2);
  uQ1=round(uQ1);
  uQ0=round(uQ0);
  vQ0=round(vQ0);
  vQ1=round(vQ1);
  vQ2=round(vQ2);
  vQ3=round(vQ3);
  vQ4=round(vQ4);
  vQ5=round(vQ5);
#endif
//------------------------------------------------------------------------------------------------------------------------------
  // Load colors.
  AH4 uC0,uC1,uC2,uC3,uC4,uC5;
  AH4 vC0,vC1,vC2,vC3,vC4,vC5;
  AW2 pp=AW2(p);
  #if CPF_TAP>10
   uC5=CpfColLdH(0,pp+AW2(ASW2( 0, 1))+AW2(ASW2(uQ5)));
  #endif
  #if CPF_TAP>8
   uC4=CpfColLdH(0,pp+AW2(ASW2( 1, 0))+AW2(ASW2(uQ4)));
  #endif
  uC3=CpfColLdH(0,pp+AW2(ASW2(-1,-1))+AW2(ASW2(uQ3)));
  uC2=CpfColLdH(0,pp+AW2(ASW2( 0,-1))+AW2(ASW2(uQ2)));
  uC1=CpfColLdH(0,pp+AW2(ASW2(-1, 0))+AW2(ASW2(uQ1)));
  uC0=CpfColLdH(0,pp+AW2(ASW2( 0, 0))+AW2(ASW2(uQ0)));
  vC0=CpfColLdH(1,pp+AW2(ASW2( 0, 0))+AW2(ASW2(vQ0)));
  vC1=CpfColLdH(1,pp+AW2(ASW2( 1, 0))+AW2(ASW2(vQ1)));
  vC2=CpfColLdH(1,pp+AW2(ASW2( 0, 1))+AW2(ASW2(vQ2)));
  vC3=CpfColLdH(1,pp+AW2(ASW2( 1, 1))+AW2(ASW2(vQ3)));
  #if CPF_TAP>8
   vC4=CpfColLdH(1,pp+AW2(ASW2(-1, 0))+AW2(ASW2(vQ4)));
  #endif
  #if CPF_TAP>10
   vC5=CpfColLdH(1,pp+AW2(ASW2( 0,-1))+AW2(ASW2(vQ5)));
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvC0R,uvC0G,uvC0B,uvC0A;
  AH2 uvC1R,uvC1G,uvC1B,uvC1A;
  AH2 uvC2R,uvC2G,uvC2B,uvC2A;
  AH2 uvC3R,uvC3G,uvC3B,uvC3A;
  AH2 uvC4R,uvC4G,uvC4B,uvC4A;
  AH2 uvC5R,uvC5G,uvC5B,uvC5A;
  uvC0R=AH2(uC0.r,vC0.r);
  uvC1R=AH2(uC1.r,vC1.r);
  uvC2R=AH2(uC2.r,vC2.r);
  uvC3R=AH2(uC3.r,vC3.r);
  uvC4R=AH2(uC4.r,vC4.r);
  uvC5R=AH2(uC5.r,vC5.r);
  uvC0G=AH2(uC0.g,vC0.g);
  uvC1G=AH2(uC1.g,vC1.g);
  uvC2G=AH2(uC2.g,vC2.g);
  uvC3G=AH2(uC3.g,vC3.g);
  uvC4G=AH2(uC4.g,vC4.g);
  uvC5G=AH2(uC5.g,vC5.g);
  uvC0B=AH2(uC0.b,vC0.b);
  uvC1B=AH2(uC1.b,vC1.b);
  uvC2B=AH2(uC2.b,vC2.b);
  uvC3B=AH2(uC3.b,vC3.b);
  uvC4B=AH2(uC4.b,vC4.b);
  uvC5B=AH2(uC5.b,vC5.b);
  uvC0A=AH2(uC0.a,vC0.a);
  uvC1A=AH2(uC1.a,vC1.a);
  uvC2A=AH2(uC2.a,vC2.a);
  uvC3A=AH2(uC3.a,vC3.a);
  uvC4A=AH2(uC4.a,vC4.a);
  uvC5A=AH2(uC5.a,vC5.a);
//------------------------------------------------------------------------------------------------------------------------------
  uvC0R=uvC0R*uvC0R*uvC0R;uvC0G=uvC0G*uvC0G*uvC0G;uvC0B=uvC0B*uvC0B*uvC0B;
  uvC1R=uvC1R*uvC1R*uvC1R;uvC1G=uvC1G*uvC1G*uvC1G;uvC1B=uvC1B*uvC1B*uvC1B;
  uvC2R=uvC2R*uvC2R*uvC2R;uvC2G=uvC2G*uvC2G*uvC2G;uvC2B=uvC2B*uvC2B*uvC2B;
  uvC3R=uvC3R*uvC3R*uvC3R;uvC3G=uvC3G*uvC3G*uvC3G;uvC3B=uvC3B*uvC3B*uvC3B;
  uvC4R=uvC4R*uvC4R*uvC4R;uvC4G=uvC4G*uvC4G*uvC4G;uvC4B=uvC4B*uvC4B*uvC4B;
  uvC5R=uvC5R*uvC5R*uvC5R;uvC5G=uvC5G*uvC5G*uvC5G;uvC5B=uvC5B*uvC5B*uvC5B;
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvW0,uvW1,uvW2,uvW3,uvW4,uvW5;
  #if CPF_PSL
   AH1 krn=AH1_(0.5)-AH1_(0.375)*moving.x;
   AH2 uvQ0X,uvQ1X,uvQ2X,uvQ3X,uvQ4X,uvQ5X;
   AH2 uvQ0Y,uvQ1Y,uvQ2Y,uvQ3Y,uvQ4Y,uvQ5Y;
   AH1 chk;
   chk=AH1((p.x^p.y)&AU1_(1))*AH1_(2.0)-AH1_(1.0);
   uvQ0X=AH2_(-chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ0Y=AH2_(-chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ3X=AH2_(-chk)*AH2_(0.125)+AH2(-1.0+0.25, 1.0-0.25);
   uvQ3Y=AH2_(-chk)*AH2_(0.125)+AH2(-1.0+0.25, 1.0-0.25);
   uvQ1X=AH2_( chk)*AH2_(0.125)+AH2(-1.0+0.25, 1.0-0.25);
   uvQ1Y=AH2_( chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ2X=AH2_( chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ2Y=AH2_( chk)*AH2_(0.125)+AH2(-1.0+0.25, 1.0-0.25);
   uvQ4X=AH2_( chk)*AH2_(0.125)+AH2( 1.0+0.25,-1.0-0.25);
   uvQ4Y=AH2_( chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ5X=AH2_( chk)*AH2_(0.125)+AH2( 0.0+0.25, 0.0-0.25);
   uvQ5Y=AH2_( chk)*AH2_(0.125)+AH2( 1.0+0.25,-1.0-0.25);
   uvW0=CpfWH(uvQ0X,uvQ0Y,krn);
   uvW1=CpfWH(uvQ1X,uvQ1Y,krn);
   uvW2=CpfWH(uvQ2X,uvQ2Y,krn);
   uvW3=CpfWH(uvQ3X,uvQ3Y,krn);
   uvW4=CpfWH(uvQ4X,uvQ4Y,krn);
   uvW5=CpfWH(uvQ5X,uvQ5Y,krn);
  #else
   AH2 uvW0And12a=CpfWH(AH2(CPF_JIT,1.0-CPF_JIT),AH2(CPF_JIT,CPF_JIT),AH1_(0.5));
   AH2 uvW3And45a=CpfWH(AH2(1.0-CPF_JIT,1.0+CPF_JIT),AH2(1.0-CPF_JIT,CPF_JIT),AH1_(0.5));
   AH2 uvW0And12b=CpfWH(AH2(CPF_JIT,1.0-CPF_JIT),AH2(CPF_JIT,CPF_JIT),AH1_(0.125));
   AH2 uvW3And45b=CpfWH(AH2(1.0-CPF_JIT,1.0+CPF_JIT),AH2(1.0-CPF_JIT,CPF_JIT),AH1_(0.125));
   AH2 uvW0And12=ALerpH2(uvW0And12a,uvW0And12b,AH2_(moving.x));
   AH2 uvW3And45=ALerpH2(uvW3And45a,uvW3And45b,AH2_(moving.x));
   // TODO: Need to vectorize this, cannot expect the compiler to do it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   uvW0=uvW0And12.xx;
   uvW1=uvW2=uvW0And12.yy;
   uvW3=uvW3And45.xx;
   uvW4=uvW5=uvW3And45.yy;
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  uvW0*=AGtZeroH2(uvC0A);
  uvW1*=AGtZeroH2(uvC1A);
  uvW2*=AGtZeroH2(uvC2A);
  uvW3*=AGtZeroH2(uvC3A);
  uvW4*=AGtZeroH2(uvC4A);
  uvW5*=AGtZeroH2(uvC5A);
//------------------------------------------------------------------------------------------------------------------------------
  // This is different than the 32-bit version (attempt to keep pairs as long as possible).
  #if CPF_MDF
   AH2 dof2=max(uvC0A,uvC1A);
   dof2=max(dof2,uvC2A);
   dof2=max(dof2,uvC3A);
   #if CPF_TAP>8
    dof2=max(dof2,uvC4A);
   #endif
   #if CPF_TAP>10
    dof2=max(dof2,uvC5A);
   #endif
   AH1 dof=max(dof2.x,dof2.y);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvZG=CpfZGH(uvZ);
  AH2 uvG0,uvG1,uvG2,uvG3,uvG4,uvG5;
  uvG0=CpfZH(uvC0A,uvZG);
  uvG1=CpfZH(uvC1A,uvZG);
  uvG2=CpfZH(uvC2A,uvZG);
  uvG3=CpfZH(uvC3A,uvZG);
  uvG4=CpfZH(uvC4A,uvZG);
  uvG5=CpfZH(uvC5A,uvZG);
  AH2 uvGSum=(uvG0*uvW0)+(uvG1*uvW1)+(uvG2*uvW2)+(uvG3*uvW3);
  #if CPF_TAP>8
   uvGSum+=(uvG4*uvW4);
  #endif
  #if CPF_TAP>10
   uvGSum+=(uvG5*uvW5);
  #endif
  AH2 uvGRcp=APrxMedRcpH2(uvGSum);
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvZF=CpfZFH(uvZ);
  AH2 uvS0,uvS1,uvS2,uvS3,uvS4,uvS5;
  uvS0=uvG0-CpfZH(uvC0A,uvZF);
  uvS1=uvG1-CpfZH(uvC1A,uvZF);
  uvS2=uvG2-CpfZH(uvC2A,uvZF);
  uvS3=uvG3-CpfZH(uvC3A,uvZF);
  uvS4=uvG4-CpfZH(uvC4A,uvZF);
  uvS5=uvG5-CpfZH(uvC5A,uvZF);
  AH2 uvSSum=uvS0*uvW0+AH2_(1.0/4096.0);
  uvSSum+=uvS1*uvW1;
  uvSSum+=uvS2*uvW2;
  uvSSum+=uvS3*uvW3;
  #if CPF_TAP>8
   uvSSum+=uvS4*uvW4;
  #endif
  #if CPF_TAP>10
   uvSSum+=uvS5*uvW5;
  #endif
  AH2 uvSRcp=APrxMedRcpH2(uvSSum);
  AH2 uvSAmt=ASatH2(uvSSum*uvGRcp);
  AH2 uvSAmt2=uvSAmt*uvSAmt;
  uvSAmt2*=uvSAmt2;
  uvSAmt=ALerpH2(uvSAmt,uvSAmt2,AH2_(moving.y));
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvB0,uvB1,uvB2,uvB3,uvB4,uvB5;
  uvB0=CpfZH(uvC0A,uvZF.yx);
  uvB1=CpfZH(uvC1A,uvZF.yx);
  uvB2=CpfZH(uvC2A,uvZF.yx);
  uvB3=CpfZH(uvC3A,uvZF.yx);
  uvB4=CpfZH(uvC4A,uvZF.yx);
  uvB5=CpfZH(uvC5A,uvZF.yx);
  AH2 uvBSum=uvB0*uvW0+AH2_(1.0/4096.0);
  uvBSum+=uvB1*uvW1;
  uvBSum+=uvB2*uvW2;
  uvBSum+=uvB3*uvW3;
  #if CPF_TAP>8
   uvBSum+=uvB4*uvW4;
  #endif
  #if CPF_TAP>10
   uvBSum+=uvB5*uvW5;
  #endif
  AH2 uvBRcp=APrxMedRcpH2(uvBSum);
  AH1 rcpBSum=APrxMedRcpH1(uvBSum.x+uvBSum.y);
  AH2 uvBAmt=ASatH2(uvBSum.yx*AH2_(rcpBSum));
//------------------------------------------------------------------------------------------------------------------------------
  AH2 uvS=uvSRcp*uvGSum*uvSAmt*uvBAmt;
  AH2 uvB=uvBRcp*uvGSum.yx*(AH2_(1.0)-uvSAmt.yx)*uvBAmt.yx;
  uvW0*=ALerpH2(uvG0,(uvS0*uvS)+(uvB0*uvB),AH2_(moving.y));
  uvW1*=ALerpH2(uvG1,(uvS1*uvS)+(uvB1*uvB),AH2_(moving.y));
  uvW2*=ALerpH2(uvG2,(uvS2*uvS)+(uvB2*uvB),AH2_(moving.y));
  uvW3*=ALerpH2(uvG3,(uvS3*uvS)+(uvB3*uvB),AH2_(moving.y));
  uvW4*=ALerpH2(uvG4,(uvS4*uvS)+(uvB4*uvB),AH2_(moving.y));
  uvW5*=ALerpH2(uvG5,(uvS5*uvS)+(uvB5*uvB),AH2_(moving.y));
//------------------------------------------------------------------------------------------------------------------------------
  // Weighted average is different for 16-bit, runs pars as long as possible.
  AH2 colR2=(uvC0R*uvW0)+(uvC1R*uvW1)+(uvC2R*uvW2)+(uvC3R*uvW3);
  AH2 colG2=(uvC0G*uvW0)+(uvC1G*uvW1)+(uvC2G*uvW2)+(uvC3G*uvW3);
  AH2 colB2=(uvC0B*uvW0)+(uvC1B*uvW1)+(uvC2B*uvW2)+(uvC3B*uvW3);
  #if CPF_TAP>8
   colR2+=(uvC4R*uvW4);
   colG2+=(uvC4G*uvW4);
   colB2+=(uvC4B*uvW4);
  #endif
  #if CPF_TAP>10
   colR2+=(uvC5R*uvW5);
   colG2+=(uvC5G*uvW5);
   colB2+=(uvC5B*uvW5);
  #endif
  AH4 col;
  col.r=colR2.x+colR2.y;
  col.g=colG2.x+colG2.y;
  col.b=colB2.x+colB2.y;
  col.a=AH1(moving.y)*AH1_(0.5);
  AH2 rcpW2=uvW0+uvW1+uvW2+uvW3;
  #if CPF_TAP>8
   rcpW2+=uvW4;
  #endif
  #if CPF_TAP>10
   rcpW2+=uvW5;
  #endif
  AH1 rcpW=rcpW2.x+rcpW2.y;
  rcpW=APrxMedRcpH1(rcpW);
  col.rgb*=rcpW;
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_MDF
   dof=dof*AH1_(2.0)-AH1_(1.0);
   col.a=max(col.a,abs(dof));
   col.a=ACpySgnH1(col.a,dof);
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  CpfMdrToHdrH(col.rgb);
  CpfClnSt(p,AF4(col)); // TODO: Make me use the 16-bit version.
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_DFU
   CpfDfuH(wxy,AW2(p));
  #endif
 }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//                                                  [CPF] [CLN] FRAME CLEANER
//
//------------------------------------------------------------------------------------------------------------------------------
// Purpose of this pass.
//  - Composite in bloom.
//  - Dither cleaner for {24-bit encoding, motion blur, and PSL} from prior pass.
//  - Does Directional Contrast Adaptive Sharpening (DCAS).
//==============================================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                        32-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(CPF_32BIT)
 void CpfCln(
 out AF1 colR, // Output colors. 
 out AF1 colG,
 out AF1 colB,
 AU2 p){ // Integer pixel position.
//------------------------------------------------------------------------------------------------------------------------------
  //                      d0 v0 d2 
  // lane in  -> s0 .. -> h0 s0 h1 -> d2=horizontal, d3=vertical
  // 2x2 quad    .. ..    d3 v1 d1
  AU2 pH;pH.x=p.x+(((p.x&AU1_(1))<<1)-AU1_(1));pH.y=p.y;
  AU2 pV;pV.y=p.y+(((p.y&AU1_(1))<<1)-AU1_(1));pV.x=p.x;
  AU2 pD=AU2(pH.x,pV.y);
  AF4 cS0=CpfClnLd(p);
  AF4 cH0=CpfClnLd(pH);
  AF4 cV0=CpfClnLd(pV);
  AF4 cD0=CpfClnLd(pD);
//------------------------------------------------------------------------------------------------------------------------------
  // Rename or AOS-to-SOA conversion for 16-bit version.
  AF1 cS0R=cS0.r;AF1 cS0G=cS0.g;AF1 cS0B=cS0.b;AF1 cS0A=cS0.a;
  AF1 cH0R=cH0.r;AF1 cH0G=cH0.g;AF1 cH0B=cH0.b;AF1 cH0A=cH0.a;
  AF1 cV0R=cV0.r;AF1 cV0G=cV0.g;AF1 cV0B=cV0.b;AF1 cV0A=cV0.a;
  AF1 cD0R=cD0.r;AF1 cD0G=cD0.g;AF1 cD0B=cD0.b;AF1 cD0A=cD0.a;
//------------------------------------------------------------------------------------------------------------------------------
  // Luma.
  AF1 cS0L=cS0G*AF1_(0.5)+(cS0R*AF1_(0.25)+(cS0B*AF1_(0.25)));
  AF1 cH0L=cH0G*AF1_(0.5)+(cH0R*AF1_(0.25)+(cH0B*AF1_(0.25)));
  AF1 cV0L=cV0G*AF1_(0.5)+(cV0R*AF1_(0.25)+(cV0B*AF1_(0.25)));
  AF1 cD0L=cD0G*AF1_(0.5)+(cD0R*AF1_(0.25)+(cD0B*AF1_(0.25)));
//------------------------------------------------------------------------------------------------------------------------------
  // HDR weighting.
  AF1 wS0=APrxMedRcpF1(cS0L+AF1_(1.0));
  AF1 wH0=APrxMedRcpF1(cH0L+AF1_(1.0));
  AF1 wV0=APrxMedRcpF1(cV0L+AF1_(1.0));
  AF1 wD0=APrxMedRcpF1(cD0L+AF1_(1.0));
//------------------------------------------------------------------------------------------------------------------------------
  #ifdef A_WAVE
   // Gather other neighbors via subgroup ops.
   // TODO: Make sure compiler does the right thing with these!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AF1 cH1R=AWaveXorF1(cS0R,1u);
   AF1 cV1R=AWaveXorF1(cS0R,2u);
   AF1 cD1R=AWaveXorF1(cH1R,2u);
   AF1 cD2R=AWaveXorF1(cV0R,1u);
   AF1 cD3R=AWaveXorF1(cH0R,2u);
   AF1 cH1G=AWaveXorF1(cS0G,1u);
   AF1 cV1G=AWaveXorF1(cS0G,2u);
   AF1 cD1G=AWaveXorF1(cH1G,2u);
   AF1 cD2G=AWaveXorF1(cV0G,1u);
   AF1 cD3G=AWaveXorF1(cH0G,2u);
   AF1 cH1B=AWaveXorF1(cS0B,1u);
   AF1 cV1B=AWaveXorF1(cS0B,2u);
   AF1 cD1B=AWaveXorF1(cH1B,2u);
   AF1 cD2B=AWaveXorF1(cV0B,1u);
   AF1 cD3B=AWaveXorF1(cH0B,2u);
   AF1 cH1A=AWaveXorF1(cS0A,1u);
   AF1 cV1A=AWaveXorF1(cS0A,2u);
   AF1 cD1A=AWaveXorF1(cH1A,2u);
   AF1 cD2A=AWaveXorF1(cV0A,1u);
   AF1 cD3A=AWaveXorF1(cH0A,2u);
   AF1 cH1L=AWaveXorF1(cS0L,1u);
   AF1 cV1L=AWaveXorF1(cS0L,2u);
   AF1 cD1L=AWaveXorF1(cH1L,2u);
   AF1 cD2L=AWaveXorF1(cV0L,1u);
   AF1 cD3L=AWaveXorF1(cH0L,2u);
   AF1 wH1=AWaveXorF1(wS0,1u);
   AF1 wV1=AWaveXorF1(wS0,2u);
   AF1 wD1=AWaveXorF1(wH1,2u);
   AF1 wD2=AWaveXorF1(wV0,1u);
   AF1 wD3=AWaveXorF1(wH0,2u);
  #else
   // More complex path for either broken compilers or DX which lacks the subgroupShuffleXor() functionality.
   AU2 pH1;pH1.x=p.x-(((p.x&AU1_(1))<<1)-AU1_(1));pH1.y=p.y;
   AU2 pV1;pV1.y=p.y-(((p.y&AU1_(1))<<1)-AU1_(1));pV1.x=p.x;
   AU2 pD1=AU2(pH1.x,pV1.y);
   AU2 pD2=AU2(pH1.x,pV.y);
   AU2 pD3=AU2(pH.x,pV1.y);
   AF4 cH1=CpfClnLd(pH1);
   AF4 cV1=CpfClnLd(pV1);
   AF4 cD1=CpfClnLd(pD1);
   AF4 cD2=CpfClnLd(pD2);
   AF4 cD3=CpfClnLd(pD3);
   AF1 cH1R=cH1.r;AF1 cH1G=cH1.g;AF1 cH1B=cH1.b;AF1 cH1A=cH1.a;
   AF1 cV1R=cV1.r;AF1 cV1G=cV1.g;AF1 cV1B=cV1.b;AF1 cV1A=cV1.a;
   AF1 cD1R=cD1.r;AF1 cD1G=cD1.g;AF1 cD1B=cD1.b;AF1 cD1A=cD1.a;
   AF1 cD2R=cD2.r;AF1 cD2G=cD2.g;AF1 cD2B=cD2.b;AF1 cD2A=cD2.a;
   AF1 cD3R=cD3.r;AF1 cD3G=cD3.g;AF1 cD3B=cD3.b;AF1 cD3A=cD3.a;
   AF1 cH1L=cH1G*AF1_(0.5)+(cH1R*AF1_(0.25)+(cH1B*AF1_(0.25)));
   AF1 cV1L=cV1G*AF1_(0.5)+(cV1R*AF1_(0.25)+(cV1B*AF1_(0.25)));
   AF1 cD1L=cD1G*AF1_(0.5)+(cD1R*AF1_(0.25)+(cD1B*AF1_(0.25)));
   AF1 cD2L=cD2G*AF1_(0.5)+(cD2R*AF1_(0.25)+(cD2B*AF1_(0.25)));
   AF1 cD3L=cD3G*AF1_(0.5)+(cD3R*AF1_(0.25)+(cD3B*AF1_(0.25)));
   AF1 wH1=APrxMedRcpF1(cH1L+AF1_(1.0));
   AF1 wV1=APrxMedRcpF1(cV1L+AF1_(1.0));
   AF1 wD1=APrxMedRcpF1(cD1L+AF1_(1.0));
   AF1 wD2=APrxMedRcpF1(cD2L+AF1_(1.0));
   AF1 wD3=APrxMedRcpF1(cD3L+AF1_(1.0));
  #endif
//------------------------------------------------------------------------------------------------------------------------------
  // Get minimum of HDR weighting (used for micro-diffusion later).
  // The full 3x3 minimum (vs the 5 tap minimum) seemed to help for scalilng.
  AF1 wMin=AMin3F1(AMin3F1(wS0,wH0,wV0),AMin3F1(wH1,wV1,wD0),AMin3F1(wD1,wD2,wD3));
//------------------------------------------------------------------------------------------------------------------------------
  // Get directional contrasts.
  // This worked best with simple 3 tap in a 5 tap neighborhood instead of the full 3x3.
  AF1 lConH=AMax3F1(cS0L,cH0L,cH1L)-AMin3F1(cS0L,cH0L,cH1L);
  AF1 lConV=AMax3F1(cS0L,cV0L,cV1L)-AMin3F1(cS0L,cV0L,cV1L);
//------------------------------------------------------------------------------------------------------------------------------
  // Convert to a weighting term.
  lConH+=AF1_(1.0/32768.0);
  lConV+=AF1_(1.0/32768.0);
  AF1 rcpCHV=APrxMedRcpF1(lConH+lConV);
  AF1 wDH=lConV*rcpCHV;
  AF1 wDV=lConH*rcpCHV;
  // This saturate is necessary for the 16-bit version to avoid overflow.
  wDH=ASatF1(wDH*wDH);
  wDV=ASatF1(wDV*wDV);
//------------------------------------------------------------------------------------------------------------------------------
  // Directional CAS working with HDR inputs.
  // The micro-diffusion fixes up the high-end (disables CAS for bright).
  // Saturated content had problems with green-as-luma, or luma itself.
  // Instead this computes contrast for all channels and uses the minimum (conservative).
  // TODO: Optimize this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  AF1 lMinR=AMin3F1(AMin3F1(cS0R,cH0R,cV0R),cH1R,cV1R)*AF1_(1.0/CPF_HDR);
  AF1 lMinG=AMin3F1(AMin3F1(cS0G,cH0G,cV0G),cH1G,cV1G)*AF1_(1.0/CPF_HDR);
  AF1 lMinB=AMin3F1(AMin3F1(cS0B,cH0B,cV0B),cH1B,cV1B)*AF1_(1.0/CPF_HDR);
  AF1 lMaxR=AMax3F1(AMax3F1(cS0R,cH0R,cV0R),cH1R,cV1R)*AF1_(1.0/CPF_HDR);
  AF1 lMaxG=AMax3F1(AMax3F1(cS0G,cH0G,cV0G),cH1G,cV1G)*AF1_(1.0/CPF_HDR);
  AF1 lMaxB=AMax3F1(AMax3F1(cS0B,cH0B,cV0B),cH1B,cV1B)*AF1_(1.0/CPF_HDR);
  AF1 lRcpMaxR=APrxLoRcpF1(lMaxR);
  AF1 lRcpMaxG=APrxLoRcpF1(lMaxG);
  AF1 lRcpMaxB=APrxLoRcpF1(lMaxB);
  AF1 lAmpR=ASatF1(min(lMinR,AF1_(1.0)-lMaxR)*lRcpMaxR);
  AF1 lAmpG=ASatF1(min(lMinG,AF1_(1.0)-lMaxG)*lRcpMaxG);
  AF1 lAmpB=ASatF1(min(lMinB,AF1_(1.0)-lMaxB)*lRcpMaxB);
  AF1 wR=AMin3F1(lAmpR,lAmpG,lAmpB);
  #if CDF_CAS_MIC
   wR*=wR;
  #endif
  #if CDF_CAS_MAC
   wR=APrxLoSqrtF1(wR);
  #endif
  wR=AF1_(CDF_CAS_LOB)*wR;
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: Optimize the logic below!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Convert HDR weighting to {0 to 1} and set micro-diffusion.
  wMin=ASatF1(APrxMedRcpF1(wMin)-AF1_(1.0));
  wMin*=wMin;
  wMin*=wMin;
  wR=ALerpF1(wR,AF1_(0.5),wMin);
  AF1 wDD=ALerpF1(AF1_(0.0),AF1_(0.25),wMin*wMin);
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: Optimize the logic below!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // Increase blur by amount in alpha (set by motion or micro-DOF).
  // Motion uses {0 to 0.5}, and micro-DOF uses the full range {0 to 1}.
  // On direction of lower contrast: increase blur in the low contrast direction to maximum as a function of motion.
  AF1 mMax=abs(AMax3F1(AMax3F1(cS0A,cH0A,cH1A),cV0A,cV1A)); 
  AF1 wR2=AF1_(0.33333)+ASatF1(mMax*AF1_(2.0))*AF1_(0.66666);
  wR2=max(wR,wR2);
  wDH=ALerpF1(wR,wR2,wDH);
  wDV=ALerpF1(wR,wR2,wDV);
  // After alpha of 0.5, directional negative lobe is removed, and blur is maximized.
  AF1 wR3=ASatF1(mMax*AF1_(2.0)-AF1_(1.0));
  wDH=ALerpF1(wDH,AF1_(1.0),wR3);
  wDV=ALerpF1(wDV,AF1_(1.0),wR3);
  wDD=ALerpF1(wDD,AF1_(0.25),wR3*wR3);
//------------------------------------------------------------------------------------------------------------------------------
  wH0*=wDH;wH1*=wDH;wV0*=wDV;wV1*=wDV;
  colR=(cS0R*wS0)+(cH0R*wH0)+(cH1R*wH1)+(cV0R*wV0)+(cV1R*wV1);
  colG=(cS0G*wS0)+(cH0G*wH0)+(cH1G*wH1)+(cV0G*wV0)+(cV1G*wV1);
  colB=(cS0B*wS0)+(cH0B*wH0)+(cH1B*wH1)+(cV0B*wV0)+(cV1B*wV1);
  // Corner taps are only used for micro-diffusion and micro-DOF.
  // Corner taps are important to get rid of HDR dithering.
  wD0*=wDD;wD1*=wDD;wD2*=wDD;wD3*=wDD;
  colR+=(cD0R*wD0)+(cD1R*wD1)+(cD2R*wD2)+(cD3R*wD3);
  colG+=(cD0G*wD0)+(cD1G*wD1)+(cD2G*wD2)+(cD3G*wD3);
  colB+=(cD0B*wD0)+(cD1B*wD1)+(cD2B*wD2)+(cD3B*wD3);
  AF1 rcpW=APrxMedRcpF1(wS0+wH0+wV0+wH1+wV1+wD0+wD1+wD2+wD3);
  colR*=rcpW;colG*=rcpW;colB*=rcpW;
//------------------------------------------------------------------------------------------------------------------------------
  // Optionally blend in diffusion.
  #if CPF_DFU
   // Constants.
   AU4 const0=CpfGet(CPF_C32_CLN0);
   AU4 const1=CpfGet(CPF_C32_CLN1);
   AF2 constM=AF2_AU2(const0.xy);
   AF2 constK=AF2_AU2(const0.zw);
   AF2 constL=AF2_AU2(const1.xy);
   AF2 ditC=CpfDitD(p);
   AF3 dfu=CpfDfuOutSm(AF2(p)*constM+ditC*constK).rgb;
   // Rename for 32-bit or AOS TO SOA transform for 16-bit.
   AF1 dfuR=dfu.r;
   AF1 dfuG=dfu.g;
   AF1 dfuB=dfu.b;
   colR=AF1_(constL.y)*colR+AF1_(constL.x)*dfuR;
   colG=AF1_(constL.y)*colG+AF1_(constL.x)*dfuG;
   colB=AF1_(constL.y)*colB+AF1_(constL.x)*dfuB;
  #endif
 }
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                        16-BIT VERSION
//==============================================================================================================================
#if defined(A_GPU)&&defined(A_HALF)&&defined(CPF_16BIT)
 // See the 32-bit version for comments.
 // This works on two 8x8 tiles in parallel with an 8 pixel offset between tiles.
 void CpfClnH(
 out AH2 colR,
 out AH2 colG,
 out AH2 colB,
 AW2 p){
//------------------------------------------------------------------------------------------------------------------------------
  AW2 pH;pH.x=p.x+(((p.x&AW1_(1))<<1)-AW1_(1));pH.y=p.y;
  AW2 pV;pV.y=p.y+(((p.y&AW1_(1))<<1)-AW1_(1));pV.x=p.x;
  AW2 pD=AW2(pH.x,pV.y);
  AH4 cS0a=CpfClnLdH(p);
  AH4 cH0a=CpfClnLdH(pH);
  AH4 cV0a=CpfClnLdH(pV);
  AH4 cD0a=CpfClnLdH(pD);
  AH4 cS0b=CpfClnLdH(p +AW2(8,0));
  AH4 cH0b=CpfClnLdH(pH+AW2(8,0));
  AH4 cV0b=CpfClnLdH(pV+AW2(8,0));
  AH4 cD0b=CpfClnLdH(pD+AW2(8,0));
//------------------------------------------------------------------------------------------------------------------------------
  AH2 cS0R=AH2(cS0a.r,cS0b.r);AH2 cS0G=AH2(cS0a.g,cS0b.g);AH2 cS0B=AH2(cS0a.b,cS0b.b);AH2 cS0A=AH2(cS0a.a,cS0b.a);
  AH2 cH0R=AH2(cH0a.r,cH0b.r);AH2 cH0G=AH2(cH0a.g,cH0b.g);AH2 cH0B=AH2(cH0a.b,cH0b.b);AH2 cH0A=AH2(cH0a.a,cH0b.a);
  AH2 cV0R=AH2(cV0a.r,cV0b.r);AH2 cV0G=AH2(cV0a.g,cV0b.g);AH2 cV0B=AH2(cV0a.b,cV0b.b);AH2 cV0A=AH2(cV0a.a,cV0b.a);
  AH2 cD0R=AH2(cD0a.r,cD0b.r);AH2 cD0G=AH2(cD0a.g,cD0b.g);AH2 cD0B=AH2(cD0a.b,cD0b.b);AH2 cD0A=AH2(cD0a.a,cD0b.a);
//------------------------------------------------------------------------------------------------------------------------------
  AH2 cS0L=cS0G*AH2_(0.5)+(cS0R*AH2_(0.25)+(cS0B*AH2_(0.25)));
  AH2 cH0L=cH0G*AH2_(0.5)+(cH0R*AH2_(0.25)+(cH0B*AH2_(0.25)));
  AH2 cV0L=cV0G*AH2_(0.5)+(cV0R*AH2_(0.25)+(cV0B*AH2_(0.25)));
  AH2 cD0L=cD0G*AH2_(0.5)+(cD0R*AH2_(0.25)+(cD0B*AH2_(0.25)));
//------------------------------------------------------------------------------------------------------------------------------
  AH2 wS0=APrxMedRcpH2(cS0L+AH2_(1.0));
  AH2 wH0=APrxMedRcpH2(cH0L+AH2_(1.0));
  AH2 wV0=APrxMedRcpH2(cV0L+AH2_(1.0));
  AH2 wD0=APrxMedRcpH2(cD0L+AH2_(1.0));
//------------------------------------------------------------------------------------------------------------------------------
  #ifdef A_WAVE
   AH2 cH1R=AWaveXorH2(cS0R,1u);
   AH2 cV1R=AWaveXorH2(cS0R,2u);
   AH2 cD1R=AWaveXorH2(cH1R,2u);
   AH2 cD2R=AWaveXorH2(cV0R,1u);
   AH2 cD3R=AWaveXorH2(cH0R,2u);
   AH2 cH1G=AWaveXorH2(cS0G,1u);
   AH2 cV1G=AWaveXorH2(cS0G,2u);
   AH2 cD1G=AWaveXorH2(cH1G,2u);
   AH2 cD2G=AWaveXorH2(cV0G,1u);
   AH2 cD3G=AWaveXorH2(cH0G,2u);
   AH2 cH1B=AWaveXorH2(cS0B,1u);
   AH2 cV1B=AWaveXorH2(cS0B,2u);
   AH2 cD1B=AWaveXorH2(cH1B,2u);
   AH2 cD2B=AWaveXorH2(cV0B,1u);
   AH2 cD3B=AWaveXorH2(cH0B,2u);
   AH2 cH1A=AWaveXorH2(cS0A,1u);
   AH2 cV1A=AWaveXorH2(cS0A,2u);
   AH2 cD1A=AWaveXorH2(cH1A,2u);
   AH2 cD2A=AWaveXorH2(cV0A,1u);
   AH2 cD3A=AWaveXorH2(cH0A,2u);
   AH2 cH1L=AWaveXorH2(cS0L,1u);
   AH2 cV1L=AWaveXorH2(cS0L,2u);
   AH2 cD1L=AWaveXorH2(cH1L,2u);
   AH2 cD2L=AWaveXorH2(cV0L,1u);
   AH2 cD3L=AWaveXorH2(cH0L,2u);
   AH2 wH1=AWaveXorH2(wS0,1u);
   AH2 wV1=AWaveXorH2(wS0,2u);
   AH2 wD1=AWaveXorH2(wH1,2u);
   AH2 wD2=AWaveXorH2(wV0,1u);
   AH2 wD3=AWaveXorH2(wH0,2u);
  #else
   AW2 pH1;pH1.x=p.x-(((p.x&AW1_(1))<<1)-AW1_(1));pH1.y=p.y;
   AW2 pV1;pV1.y=p.y-(((p.y&AW1_(1))<<1)-AW1_(1));pV1.x=p.x;
   AW2 pD1=AW2(pH1.x,pV1.y);
   AW2 pD2=AW2(pH1.x,pV.y);
   AW2 pD3=AW2(pH.x,pV1.y);
   AH4 cH1a=CpfClnLdH(pH1);
   AH4 cV1a=CpfClnLdH(pV1);
   AH4 cD1a=CpfClnLdH(pD1);
   AH4 cD2a=CpfClnLdH(pD2);
   AH4 cD3a=CpfClnLdH(pD3);
   AH4 cH1b=CpfClnLdH(pH1+AW2(8,0));
   AH4 cV1b=CpfClnLdH(pV1+AW2(8,0));
   AH4 cD1b=CpfClnLdH(pD1+AW2(8,0));
   AH4 cD2b=CpfClnLdH(pD2+AW2(8,0));
   AH4 cD3b=CpfClnLdH(pD3+AW2(8,0));
   AH2 cH1R=AH2(cH1a.r,cH1b.r);AH2 cH1G=AH2(cH1a.g,cH1b.g);AH2 cH1B=AH2(cH1a.b,cH1b.b);AH2 cH1A=AH2(cH1a.a,cH1b.a);
   AH2 cV1R=AH2(cV1a.r,cV1b.r);AH2 cV1G=AH2(cV1a.g,cV1b.g);AH2 cV1B=AH2(cV1a.b,cV1b.b);AH2 cV1A=AH2(cV1a.a,cV1b.a);
   AH2 cD1R=AH2(cD1a.r,cD1b.r);AH2 cD1G=AH2(cD1a.g,cD1b.g);AH2 cD1B=AH2(cD1a.b,cD1b.b);AH2 cD1A=AH2(cD1a.a,cD1b.a);
   AH2 cD2R=AH2(cD2a.r,cD2b.r);AH2 cD2G=AH2(cD2a.g,cD2b.g);AH2 cD2B=AH2(cD2a.b,cD2b.b);AH2 cD2A=AH2(cD2a.a,cD2b.a);
   AH2 cD3R=AH2(cD3a.r,cD3b.r);AH2 cD3G=AH2(cD3a.g,cD3b.g);AH2 cD3B=AH2(cD3a.b,cD3b.b);AH2 cD3A=AH2(cD3a.a,cD3b.a);
   AH2 cH1L=cH1G*AH2_(0.5)+(cH1R*AH2_(0.25)+(cH1B*AH2_(0.25)));
   AH2 cV1L=cV1G*AH2_(0.5)+(cV1R*AH2_(0.25)+(cV1B*AH2_(0.25)));
   AH2 cD1L=cD1G*AH2_(0.5)+(cD1R*AH2_(0.25)+(cD1B*AH2_(0.25)));
   AH2 cD2L=cD2G*AH2_(0.5)+(cD2R*AH2_(0.25)+(cD2B*AH2_(0.25)));
   AH2 cD3L=cD3G*AH2_(0.5)+(cD3R*AH2_(0.25)+(cD3B*AH2_(0.25)));
   AH2 wH1=APrxMedRcpH2(cH1L+AH2_(1.0));
   AH2 wV1=APrxMedRcpH2(cV1L+AH2_(1.0));
   AH2 wD1=APrxMedRcpH2(cD1L+AH2_(1.0));
   AH2 wD2=APrxMedRcpH2(cD2L+AH2_(1.0));
   AH2 wD3=APrxMedRcpH2(cD3L+AH2_(1.0));
  #endif 
//------------------------------------------------------------------------------------------------------------------------------
  AH2 wMin=AMin3H2(AMin3H2(wS0,wH0,wV0),AMin3H2(wH1,wV1,wD0),AMin3H2(wD1,wD2,wD3));
//------------------------------------------------------------------------------------------------------------------------------
  AH2 lConH=AMax3H2(cS0L,cH0L,cH1L)-AMin3H2(cS0L,cH0L,cH1L);
  AH2 lConV=AMax3H2(cS0L,cV0L,cV1L)-AMin3H2(cS0L,cV0L,cV1L);
//------------------------------------------------------------------------------------------------------------------------------
  lConH+=AH2_(1.0/32768.0);
  lConV+=AH2_(1.0/32768.0);
  AH2 rcpCHV=APrxMedRcpH2(lConH+lConV);
  AH2 wDH=lConV*rcpCHV;
  AH2 wDV=lConH*rcpCHV;
  wDH=ASatH2(wDH*wDH);
  wDV=ASatH2(wDV*wDV);
//------------------------------------------------------------------------------------------------------------------------------
  AH2 lMinR=AMin3H2(AMin3H2(cS0R,cH0R,cV0R),cH1R,cV1R)*AH2_(1.0/CPF_HDR);
  AH2 lMinG=AMin3H2(AMin3H2(cS0G,cH0G,cV0G),cH1G,cV1G)*AH2_(1.0/CPF_HDR);
  AH2 lMinB=AMin3H2(AMin3H2(cS0B,cH0B,cV0B),cH1B,cV1B)*AH2_(1.0/CPF_HDR);
  AH2 lMaxR=AMax3H2(AMax3H2(cS0R,cH0R,cV0R),cH1R,cV1R)*AH2_(1.0/CPF_HDR);
  AH2 lMaxG=AMax3H2(AMax3H2(cS0G,cH0G,cV0G),cH1G,cV1G)*AH2_(1.0/CPF_HDR);
  AH2 lMaxB=AMax3H2(AMax3H2(cS0B,cH0B,cV0B),cH1B,cV1B)*AH2_(1.0/CPF_HDR);
  AH2 lRcpMaxR=APrxLoRcpH2(lMaxR);
  AH2 lRcpMaxG=APrxLoRcpH2(lMaxG);
  AH2 lRcpMaxB=APrxLoRcpH2(lMaxB);
  AH2 lAmpR=ASatH2(min(lMinR,AH2_(1.0)-lMaxR)*lRcpMaxR);
  AH2 lAmpG=ASatH2(min(lMinG,AH2_(1.0)-lMaxG)*lRcpMaxG);
  AH2 lAmpB=ASatH2(min(lMinB,AH2_(1.0)-lMaxB)*lRcpMaxB);
  AH2 wR=AMin3H2(lAmpR,lAmpG,lAmpB);
  #if CDF_CAS_MIC
   wR*=wR;
  #endif
  #if CDF_CAS_MAC
   wR=APrxLoSqrtH2(wR);
  #endif
  wR=AH2_(CDF_CAS_LOB)*wR;
//------------------------------------------------------------------------------------------------------------------------------
  wMin=ASatH2(APrxMedRcpH2(wMin)-AH2_(1.0));
  wMin*=wMin;
  wMin*=wMin;
  wR=ALerpH2(wR,AH2_(0.5),wMin);
  AH2 wDD=ALerpH2(AH2_(0.0),AH2_(0.25),wMin*wMin);
//------------------------------------------------------------------------------------------------------------------------------
  AH2 mMax=abs(AMax3H2(AMax3H2(cS0A,cH0A,cH1A),cV0A,cV1A)); 
  AH2 wR2=AH2_(0.33333)+ASatH2(mMax*AH2_(2.0))*AH2_(0.66666);
  wR2=max(wR,wR2);
  wDH=ALerpH2(wR,wR2,wDH);
  wDV=ALerpH2(wR,wR2,wDV);
  AH2 wR3=ASatH2(mMax*AH2_(2.0)-AH2_(1.0));
  wDH=ALerpH2(wDH,AH2_(1.0),wR3);
  wDV=ALerpH2(wDV,AH2_(1.0),wR3);
  wDD=ALerpH2(wDD,AH2_(0.25),wR3*wR3);
//------------------------------------------------------------------------------------------------------------------------------
  // TODO: Factor this into prior computations??????????????????????????????????????????????????????????????????????????????????
  // Specific for 16-bit to avoid overflow during weighted average.
  AH1 down=AH1_(1.0/64.0);
  wS0*=AH2_(down);
  wDH*=AH2_(down);
  wDV*=AH2_(down);
  wDD*=AH2_(down);
//------------------------------------------------------------------------------------------------------------------------------
  wH0*=wDH;wH1*=wDH;wV0*=wDV;wV1*=wDV;
  colR=(cS0R*wS0)+(cH0R*wH0)+(cH1R*wH1)+(cV0R*wV0)+(cV1R*wV1);
  colG=(cS0G*wS0)+(cH0G*wH0)+(cH1G*wH1)+(cV0G*wV0)+(cV1G*wV1);
  colB=(cS0B*wS0)+(cH0B*wH0)+(cH1B*wH1)+(cV0B*wV0)+(cV1B*wV1);
  wD0*=wDD;wD1*=wDD;wD2*=wDD;wD3*=wDD;
  colR+=(cD0R*wD0)+(cD1R*wD1)+(cD2R*wD2)+(cD3R*wD3);
  colG+=(cD0G*wD0)+(cD1G*wD1)+(cD2G*wD2)+(cD3G*wD3);
  colB+=(cD0B*wD0)+(cD1B*wD1)+(cD2B*wD2)+(cD3B*wD3);
  AH2 rcpW=APrxMedRcpH2(wS0+wH0+wV0+wH1+wV1+wD0+wD1+wD2+wD3);
  colR*=rcpW;colG*=rcpW;colB*=rcpW;
//------------------------------------------------------------------------------------------------------------------------------
  #if CPF_DFU
   AU4 const0=CpfGet(CPF_C16_CLN0);
   AH2 constM=AH2_AU1(const0.x);
   AH2 constK=AH2_AU1(const0.y);
   AH2 constL=AH2_AU1(const0.z);
   AH2 ditC=CpfDitDH(p);
   AH3 dfu0=CpfDfuOutSmH(AH2(p)*constM+ditC*constK).rgb;
   // TODO: Optimize this better!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   AH3 dfu1=CpfDfuOutSmH(AH2(p+AW2(8,0))*constM+ditC*constK).rgb;
   AH2 dfuR=AH2(dfu0.r,dfu1.r);
   AH2 dfuG=AH2(dfu0.g,dfu1.g);
   AH2 dfuB=AH2(dfu0.b,dfu1.b);
   colR=AH2_(constL.y)*colR+AH2_(constL.x)*dfuR;
   colG=AH2_(constL.y)*colG+AH2_(constL.x)*dfuG;
   colB=AH2_(constL.y)*colB+AH2_(constL.x)*dfuB;
  #endif
 }
#endif
