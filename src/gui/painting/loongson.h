// loongson.h
///////////////////////////////////////////////////////////////////////////
//#ifndef QDRAWHELPER_MIPS_P_H
//#define QDRAWHELPER_MIPS_P_H

//#ifndef QDRAWHELPER_LOONGSON_P_H
//#define QDRAWHELPER_LOONGSON_P_H

#ifndef __LOONGSON_H__
#define __LOONGSON_H__

#include <private/qdrawhelper_p.h>

QT_BEGIN_NAMESPACE

#define QT_HAVE_LOONGSONSIMD

#ifdef QT_HAVE_LOONGSONSIMD

static const int numCompositionFunctions = 33;

extern CompositionFunction qt_functionForMode_LSSIMD[];
extern CompositionFunctionSolid qt_functionForModeSolid_LSSIMD[];

void qt_memfill32_lssimd(quint32 *dest, quint32 value, int count);
void qt_blend_color_argb_lssimd(int count, const QSpan *spans, void *userData);

void qt_blend_argb32_on_argb32_lssimd(uchar *destPixels, int dbpl,
                                    const uchar *srcPixels, int sbpl,
                                    int w, int h,
                                    int const_alpha);
void qt_blend_rgb32_on_rgb32_lssimd(uchar *destPixels, int dbpl,
                                 const uchar *srcPixels, int sbpl,
                                 int w, int h,
                                 int const_alpha);
#endif //QT_LOONGSONSIMD

QT_END_NAMESPACE

#endif // __LOONGSON_H__

