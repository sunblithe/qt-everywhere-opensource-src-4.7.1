// qdrawhelper_loongson_p.h
///////////////////////////////////////////////////////////////////////////

#ifndef QDRAWHELPER_LOONGSON_P_H
#define QDRAWHELPER_LOONGSON_P_H

#include <private/qdrawhelper_p.h>
#include <private/qpaintengine_raster_p.h>
#include "loongson.h"

#ifdef QT_HAVE_LOONGSONSIMD

#include "loongson-mmintrin.h"
typedef unsigned int uint;

#define C_FF const __m64 mmx_0x00ff = _mm_set1_pi16(0xff)
#define C_80 const __m64 mmx_0x0080 = _mm_set1_pi16(0x80)
#define C_00 const __m64 mmx_0x0000 = _mm_setzero_si64()

extern __inline __m64 __attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_alpha_unpackhi_pi16(__m64 __m1, __m64 __m2)
{
	 __m64 ret;
	asm("punpckhhw $f0, %1, %2\n\t"
		"punpckhhw %0, $f0, $f0\n\t"
		:"=f"(ret)
		: "f"(__m1), "f"(__m2)
		: "$f0");
	return ret;
}

static inline __m64 alpha(__m64 x) {
	x = _mm_alpha_unpackhi_pi16(x, x);
    return x;
}

static inline __m64 _negate(const __m64 &x, const __m64 &mmx_0x00ff) {
    return _mm_xor_si64(x, mmx_0x00ff);
}

static inline __m64 add(const __m64 &a, const __m64 &b) {
    return  _mm_adds_pu16 (a, b);
}

extern __inline __m64 __attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_ands_srli_pi16(__m64 __m1, __m64 __m2)
{
    __m64 ret; 
    asm(".set noreorder\r\n"
        "paddush $f0, %1, %2\n\t"
        "li      $8, 8\n\t"
        "mtc1    $8, $f2\n\t"
        "psrlh   $f4, $f0, $f2\n\t"
        "paddush %0, $f4,$f0\n\t"
        "psrlh   %0, %0, $f2\n\t"
        ".set reorder\r\n":"=f"(ret)
        :"f"(__m1), "f"(__m2)
        :"$8", "$f0", "$f2", "$f4"
        );   
    return ret; 
}

extern __inline __m64 __attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_danas_byte_mul_pi16(__m32 __m1, __m32 __m2, __m64 __m3, __m64 __m4)
{
    __m64 ret;
    asm(".set noreorder\r\n"
        "mtc1       $0, $f6\n\t"
        "punpcklbh  $f0, %1, $f6\n\t"   //dest64
        "punpcklbh  $f2, %2, $f6\n\t"   //src64

        "punpckhhw  $f4, $f2, $f2\n\t"
        "punpckhhw  $f4, $f4, $f4\n\t"
        "xor        $f4, $f4, %4\n\t"

        "pmullh     $f4, $f0, $f4\n\t"
        "paddush    $f4, $f4, %3\n\t"

        "li         $8, 8\n\t"
        "mtc1       $8, $f6\n\t"
        "psrlh      $f0, $f4, $f6\n\t"
        "paddush    $f0, $f0, $f4\n\t"
        "psrlh      $f0, $f0, $f6\n\t"

        "paddush    %0, $f2, $f0\n\t"   //src64
        ".set reorder\r\n":"=f"(ret)
        :"f"(__m1), "f"(__m2), "f"(__m3), "f"(__m4)
        :"$8", "$f0", "$f2", "$f4", "$f6", "memory"
        );
    return ret;
}

static inline __m64 _byte_mul(const __m64 &a, const __m64 &b,
                            const __m64 &mmx_0x0080)
{
    __m64 res = _mm_mullo_pi16(a, b);
    res = _mm_adds_pu16(res, mmx_0x0080);
    res = _mm_adds_pu16(res, _mm_srli_pi16 (res, 8));
    return _mm_srli_pi16(res, 8);
}

static inline __m64 interpolate_pixel_256(const __m64 &x, const __m64 &a,
                                       const __m64 &y, const __m64 &b)
{
    __m64 res = _mm_adds_pu16(_mm_mullo_pi16(x, a), _mm_mullo_pi16(y, b));
    return _mm_srli_pi16(res, 8);
}
static inline __m64 _interpolate_pixel_255(const __m64 &x, const __m64 &a,
                                         const __m64 &y, const __m64 &b,
                                         const __m64 &mmx_0x0080)
{
    __m64 res = _mm_adds_pu16(_mm_mullo_pi16(x, a), _mm_mullo_pi16(y, b));
    res = _mm_adds_pu16(res, mmx_0x0080);
    res = _mm_adds_pu16(res, _mm_srli_pi16 (res, 8));
    return _mm_srli_pi16(res, 8);
}

static inline __m64 _premul(__m64 x, const __m64 &mmx_0x0080) {
    __m64 a = alpha(x);
    return _byte_mul(x, a, mmx_0x0080);
}

static inline __m64 _load(uint x)
{
    return _mm_loadlo_pi8(&x);
}

static inline __m64 _load_alpha(uint x, const __m64 &) {
    x |= (x << 16);
    return _mm_set1_pi32(x);
}

#define negate(x) _negate(x, mmx_0x00ff)
#define byte_mul(a, b) _byte_mul(a, b, mmx_0x0080)
#define interpolate_pixel_255(x, a, y, b) _interpolate_pixel_255(x, a, y, b, mmx_0x0080)
#define premul(x) _premul(x, mmx_0x0080)
#define load(x) _load(x)
#define load_alpha(x) _load_alpha(x, _mm_setzero_si64())

void qt_memfill32_template_lssimd(uint *dest, uint value, int count)
{
    if (count < 7) { 
        switch (count) {
        case 6: *dest++ = value;
        case 5: *dest++ = value;
        case 4: *dest++ = value;
        case 3: *dest++ = value;
        case 2: *dest++ = value;
        case 1: *dest   = value;
        }    
        return;
    };   

    __m64 *dst64 = reinterpret_cast<__m64*>(dest);
    const __m64 value64 = _mm_set1_pi32(value);
    int count64 = count / 2; 

    int n = (count64 + 3) / 4; 
    switch (count64 & 0x3) {
    case 0: do { _mm_store_si64(dst64++, value64);
    case 3:      _mm_store_si64(dst64++, value64);
    case 2:      _mm_store_si64(dst64++, value64);
    case 1:      _mm_store_si64(dst64++, value64);
    } while (--n > 0);  
    }    

    if (count & 0x1)
        dest[count - 1] = value;
}

void qt_memcopy32_lssimd(uint * dest, const uint * src, int count)
{
    while (((quintptr)dest) & 0x07) {
        *dest++ = *src++;
        --count;
    }
    const int count64 = count / 2;
    if (count64) {
        __m64 *dst64 = reinterpret_cast < __m64 * >(dest);
        const __m64 *src64 = reinterpret_cast < const __m64 * >(src);
        __m64 tmp1, tmp2, tmp3, tmp4;
        int n = (count64 + 3) / 4;
        switch (count64 & 0x3) {
        case 0: do {    tmp1 = _mm_load_si64(src64);
                        _mm_store_si64(dst64++, tmp1);
                        src64++;
        case 3:         tmp2 = _mm_load_si64(src64);
                        _mm_store_si64(dst64++, tmp2);
                        src64++;
        case 2:         tmp3 = _mm_load_si64(src64);
                        _mm_store_si64(dst64++, tmp3);
                        src64++;
        case 1:         tmp4 = _mm_load_si64(src64);
                        _mm_store_si64(dst64++, tmp4);
                        src64++;
                    } while (--n > 0);
        }
    }
    if (count & 0x1) {
        dest[count - 1] = src[count - 1];
    }
}


/* The constant alpha factor describes an alpha factor that gets applied
   to the result of the composition operation combining it with the destination.

   The intent is that if const_alpha == 0. we get back dest, and if const_alpha == 1.
   we get the unmodified operation

   result = src op dest
   dest = result * const_alpha + dest * (1. - const_alpha)

   This means that in the comments below, the first line is the const_alpha==255 case, the
   second line the general one.

   In the lines below:
   s == src, sa == alpha(src), sia = 1 - alpha(src)
   d == dest, da == alpha(dest), dia = 1 - alpha(dest)
   ca = const_alpha, cia = 1 - const_alpha

   The methods exist in two variants. One where we have a constant source, the other
   where the source is an array of pixels.
*/

/*
  result = 0
  d = d * cia
*/
static void QT_FASTCALL comp_func_Clear_impl_lssimd(uint * dest, int length, uint const_alpha)
{
    if (const_alpha == 255) {
//      qt_memfill_mips(static_cast<quint32 *>(dest), quint32(0), length);
        qt_memfill32_template_lssimd(static_cast<quint32 *>(dest), quint32(0), length);
    } else {
        __m64 mmx_0x0080 = _mm_set1_pi16(0x80);
        __m64 mmx_0x00ff = _mm_set1_pi16(0xff);
        __m64 cia = negate(load_alpha(const_alpha));
        for (int i = 0; i < length; ++i) {
            __m64 dest64 = _mm_loadlo_pi8(&dest[i]);
            __m64 dst = _mm_mullo_pi16(dest64, cia);

            dst = _mm_adds_pu16(dst, mmx_0x0080);
            dst = _mm_adds_pu16(dst, _mm_srli_pi16(dst, 8));
            dst = _mm_srli_pi16(dst, 8);

            _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
        }
    }
}

static void QT_FASTCALL comp_func_solid_Clear_lssimd(uint *dest, int length, uint, uint const_alpha)
{
    comp_func_Clear_impl_lssimd(dest, length, const_alpha);
}

static void QT_FASTCALL comp_func_Clear_lssimd(uint *dest, const uint *, int length, uint const_alpha)
{
    comp_func_Clear_impl_lssimd(dest, length, const_alpha);
}

/*
result = s
dest = s * ca + d * cia
*/
static void QT_FASTCALL comp_func_solid_Source_lssimd(uint *dest, int length, uint color, uint const_alpha)
{
    if (const_alpha == 255) {
    qt_memfill32_template_lssimd(dest, color, length);
    }
     else {
        __m64 mmx_0x0080 = _mm_set1_pi16(0x80);
        __m64 mmx_0x00ff = _mm_set1_pi16(0xff);
        __m64 ca = load_alpha(const_alpha);
        __m64 cia = negate(ca);
        __m64 color64 = _mm_loadlo_pi8(&color);
        __m64 s = _mm_mullo_pi16(color64, ca);
        s = _mm_adds_pu16(s, mmx_0x0080);
        s = _mm_adds_pu16(s, _mm_srli_pi16(s, 8));
        s = _mm_srli_pi16(s, 8);
        for (int i = 0; i < length; ++i) {
            __m64 dest64 = _mm_loadlo_pi8(&dest[i]);
            __m64 dst = _mm_mullo_pi16(dest64, cia);
            dst = _mm_ands_srli_pi16(dst, mmx_0x0080);
            dst = _mm_adds_pu16(s, dst);
            _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
        }
    }
}

static void QT_FASTCALL comp_func_Source_lssimd(uint *dest, const uint *src, int length, uint const_alpha)
{
    if (const_alpha == 255) {
        qt_memcopy32_lssimd(dest, src, length);
    } else {
         __m64 mmx_0x0080 = _mm_set1_pi16(0x80);
        __m64 mmx_0x00ff = _mm_set1_pi16(0xff);
        __m64 ca = load_alpha(const_alpha);
        __m64 cia = negate(ca);
        for (int i = 0; i < length; ++i) {
            __m64 src64 = _mm_loadlo_pi8(&src[i]);
            __m64 dest64 = _mm_loadlo_pi8(&dest[i]);
            __m64 dst = _mm_adds_pu16(_mm_mullo_pi16(src64, ca),
                          _mm_mullo_pi16(dest64, cia));
            dst = _mm_ands_srli_pi16(dst, mmx_0x0080);
            _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
        }
    }
}

/*
result = s + d * sia
  dest = (s + d * sia) * ca + d * cia
       = s * ca + d * (sia * ca + cia)
       = s * ca + d * (1 - sa*ca)
*/
static void QT_FASTCALL comp_func_solid_SourceOver_lssimd(uint * dest,
                                                          int length,
                                                          uint color,
                                                          uint const_alpha)
{
    if ((const_alpha & qAlpha(color)) == 255) {
        qt_memfill32_template_lssimd(static_cast<quint32 *>(dest), quint32(color), length);
    } else {
        __m64 mmx_0x0080 = _mm_set1_pi16(0x80);
        __m64 mmx_0x00ff = _mm_set1_pi16(0xff);

        __m64 color64 = _mm_loadlo_pi8(&color);
        if (const_alpha != 255) {
            __m64 ca = load_alpha(const_alpha);
            color64 = _mm_mullo_pi16(color64, ca);
            color64 = _mm_ands_srli_pi16(color64, mmx_0x0080);
        }
        __m64 a = negate(alpha(color64));
        for (int i = 0; i < length; ++i) {
            __m64 dest64 = _mm_loadlo_pi8(&dest[i]);
            __m64 dst = _mm_mullo_pi16(dest64, a);
            dst = _mm_ands_srli_pi16(dst, mmx_0x0080);
            dst = _mm_adds_pu16(color64, dst);
            _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
        }
    }
}

static void QT_FASTCALL comp_func_SourceOver_lssimd(uint * dest, const uint * src, int length, uint const_alpha)
{
    __m64 mmx_0x0080 = _mm_set1_pi16(0x80);
    __m64 mmx_0x00ff = _mm_set1_pi16(0xff);
    if (const_alpha == 255) {
        for (int i = 0; i < length; ++i) {
            const uint alphaMaskedSource = 0xff000000 & src[i];
            if (src[i] == 0)
                continue;
            if (alphaMaskedSource == 0xff000000) {
                dest[i] = src[i];
            } else {
                __m64 dst = _mm_danas_byte_mul_pi16(*(__m32 *)&dest[i], *(__m32 *)&src[i], mmx_0x0080, mmx_0x00ff);
                _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
            }
        }
    } else {
        __m64 ca = load_alpha(const_alpha);
        for (int i = 0; i < length; ++i) {
            if ((src[i]) == 0)
                continue;
            __m64 src64 = load(src[i]);
            src64 = _mm_mullo_pi16(src64, ca);
            src64 = _mm_ands_srli_pi16(src64, mmx_0x0080);
            __m64 cia = negate(alpha(src64));

            __m64 dest64 = _mm_loadlo_pi8(&dest[i]);
            __m64 dst = _mm_mullo_pi16(dest64, cia);
            dst = _mm_ands_srli_pi16(dst, mmx_0x0080);
            dst = _mm_adds_pu16(src64, dst);
            _mm_store_pi32(reinterpret_cast<__m32 *>(&dest[i]), dst);
        }
    }
}


/*
	**raster_##_name_lssimd**
*/
static void QT_FASTCALL rasterop_solid_SourceOrDestination_lssimd(uint * dest,
                                                                int length,
                                                                uint color,
                                                                uint 
                                                                const_alpha)
{
    Q_UNUSED(const_alpha);
    if ((quintptr) (dest) & 0x7) {
        *dest++ |= color;
        --length;
    }    

    const int length64 = length / 2; 
    if (length64) {
        __m64 *dst64 = reinterpret_cast < __m64 * >(dest);
        const __m64 color64 = _mm_set_pi32(color, color);

        int n = (length64 + 3) / 4; 
        switch (length64 & 0x3) {
        case 0:
            do { 
                *dst64 = _mm_or_si64(*dst64, color64);
                ++dst64;
        case 3:
                *dst64 = _mm_or_si64(*dst64, color64);
                ++dst64;
        case 2:
                *dst64 = _mm_or_si64(*dst64, color64);
                ++dst64;
        case 1:
                *dst64 = _mm_or_si64(*dst64, color64);
                ++dst64;
            } while (--n > 0);
        }
    }
    if (length & 0x1) {
        dest[length - 1] |= color;
    }

}

static void QT_FASTCALL rasterop_solid_SourceAndDestination_lssimd(uint * dest,
                                                                    int length,
                                                                    uint color,
                                                                    uint
                                                                    const_alpha)
{
    Q_UNUSED(const_alpha);
    color |= 0xff000000;

    if ((quintptr) (dest) & 0x7) {  // align
        *dest++ &= color;
        --length;
    }

    const int length64 = length / 2;
    if (length64) {
        __m64 *dst64 = reinterpret_cast < __m64 * >(dest);
        const __m64 color64 = _mm_set_pi32(color, color);

        int n = (length64 + 3) / 4;
        switch (length64 & 0x3) {
        case 0: do { *dst64 = _mm_and_si64(*dst64, color64); ++dst64;
        case 3:   	 *dst64 = _mm_and_si64(*dst64, color64); ++dst64;
        case 2:		 *dst64 = _mm_and_si64(*dst64, color64); ++dst64;
        case 1:		 *dst64 = _mm_and_si64(*dst64, color64); ++dst64;
            	} while (--n > 0);
        }
    }

    if (length & 0x1) {
        dest[length - 1] &= color;
    }
}


static void QT_FASTCALL rasterop_solid_SourceXorDestination_lssimd(uint *dest,
                                                            	   int length,
                                                                   uint color,
                                                                   uint const_alpha)
{
    Q_UNUSED(const_alpha);
    color &= 0x00ffffff;

    if ((quintptr)(dest) & 0x7) {
        *dest++ ^= color;
        --length;
    }

    const int length64 = length / 2;
    if (length64) {
        __m64 *dst64 = reinterpret_cast<__m64*>(dest);
        const __m64 color64 = _mm_set_pi32(color, color);

        int n = (length64 + 3) / 4;
        switch (length64 & 0x3) {
        case 0: do { *dst64 = _mm_xor_si64(*dst64, color64); ++dst64;
        case 3:      *dst64 = _mm_xor_si64(*dst64, color64); ++dst64;
        case 2:      *dst64 = _mm_xor_si64(*dst64, color64); ++dst64;
        case 1:      *dst64 = _mm_xor_si64(*dst64, color64); ++dst64;
        } while (--n > 0);
        }
    }

    if (length & 0x1) {
        dest[length - 1] ^= color;
    }

}

static void QT_FASTCALL rasterop_solid_SourceAndNotDestination_lssimd(uint *dest,
                                                               		  int length,
                                                               		  uint color,
                                                               		  uint const_alpha)
{
    Q_UNUSED(const_alpha);

    if ((quintptr)(dest) & 0x7) {
        *dest = (color & ~(*dest)) | 0xff000000;
        ++dest;
        --length;
    }

    const int length64 = length / 2;
    if (length64) {
        __m64 *dst64 = reinterpret_cast<__m64*>(dest);
        const __m64 color64 = _mm_set_pi32(color, color);
        const __m64 mmx_0xff000000 = _mm_set1_pi32(0xff000000);
        __m64 tmp1, tmp2, tmp3, tmp4;

        int n = (length64 + 3) / 4;
        switch (length64 & 0x3) {
        case 0: do { tmp1 = _mm_andnot_si64(*dst64, color64);
                     *dst64++ = _mm_or_si64(tmp1, mmx_0xff000000);
        case 3:      tmp2 = _mm_andnot_si64(*dst64, color64);
                     *dst64++ = _mm_or_si64(tmp2, mmx_0xff000000);
        case 2:      tmp3 = _mm_andnot_si64(*dst64, color64);
                     *dst64++ = _mm_or_si64(tmp3, mmx_0xff000000);
        case 1:      tmp4 = _mm_andnot_si64(*dst64, color64);
                     *dst64++ = _mm_or_si64(tmp4, mmx_0xff000000);
        } while (--n > 0);
        }
    }
    if (length & 0x1) {
        dest[length - 1] = (color & ~(dest[length - 1])) | 0xff000000;
    }

}

static void QT_FASTCALL rasterop_solid_NotSourceAndNotDestination_lssimd(uint *dest,
                                                                  	     int length,
                                                                         uint color,
                                                                         uint const_alpha)
{
    rasterop_solid_SourceAndNotDestination_lssimd(dest, length, ~color, const_alpha);
}

static void QT_FASTCALL rasterop_solid_NotSourceOrNotDestination_lssimd(uint *dest,
                          		                                        int length,
                                  		                                uint color,
                                         		                        uint const_alpha)
{
    Q_UNUSED(const_alpha);
    color = ~color | 0xff000000;
	if ((quintptr) (dest) & 0x7) {  // align
        *dest++ &= color;
        --length;
    }
	
	const int length64 = length / 2;
    if (length64) {
        __m64 *dst64 = reinterpret_cast < __m64 * >(dest);
        const __m64 color64 = _mm_set_pi32(color, color);

        int n = (length64 + 3) / 4;
        switch (length64 & 0x3) {
        case 0:
            do {
                *dst64 = _mm_and_si64(*dst64, color64);
                ++dst64;
        case 3:
                *dst64 = _mm_and_si64(*dst64, color64);
                ++dst64;
        case 2:
                *dst64 = _mm_and_si64(*dst64, color64);
                ++dst64;
        case 1:
                *dst64 = _mm_and_si64(*dst64, color64);
                ++dst64;
            } while (--n > 0);
        }
    }

    if (length & 0x1) {
        dest[length - 1] &= color;
    }
}

static void QT_FASTCALL rasterop_solid_NotSourceXorDestination_lssimd(uint *dest,
                                                               		  int length,
                                                               		  uint color,
                                                                	  uint const_alpha)
{
    rasterop_solid_SourceXorDestination_lssimd(dest, length, ~color, const_alpha);
}

static void QT_FASTCALL rasterop_solid_NotSource_lssimd(uint *dest, 
														int length,
                                                        uint color, 
														uint const_alpha)
{
    Q_UNUSED(const_alpha);
    qt_memfill((quint32*)dest, ~color | 0xff000000, length);
}

static void QT_FASTCALL rasterop_solid_NotSourceAndDestination_lssimd(uint *dest,
                                                           			  int length,
                                                               		  uint color,
                                                                      uint const_alpha)
{
    rasterop_solid_SourceAndDestination_lssimd(dest, length, ~color, const_alpha);
}

/*
extern CompositionFunction qt_functionForMode_LSSIMD[];
extern CompositionFunctionSolid qt_functionForModeSolid_LSSIMD[];
*/
#endif // QT_HAVE_LOONGSONSIMD

#endif // QDRAWHELPER_LOONGSON_P_H

