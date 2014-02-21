// qdrawhelper_loongson.cpp
////////////////////////////////////////////////////////////////////

#include <private/qdrawhelper_p.h>
#include "qdrawhelper_loongson_p.h"

#ifdef QT_HAVE_LOONGSONSIMD

QT_BEGIN_NAMESPACE

CompositionFunctionSolid qt_functionForModeSolid_LSSIMD[numCompositionFunctions] = {
    comp_func_solid_SourceOver_lssimd,
    0,	//comp_func_solid_DestinationOver_lssimd,
    comp_func_solid_Clear_lssimd,
    comp_func_solid_Source_lssimd,
    0,
    0,	//comp_func_solid_SourceIn_lssimd,
    0,	//comp_func_solid_DestinationIn_lssimd,
    0,	//comp_func_solid_SourceOut_lssimd,
    0,	//comp_func_solid_DestinationOut_lssimd,
    0,	//comp_func_solid_SourceAtop_lssimd,
    0,	//comp_func_solid_DestinationAtop_lssimd,
    0,	//comp_func_solid_XOR_lssimd,
    0,0,0,0,0,0,0,0,0,0,0,0,   // svg 1.2 modes
    rasterop_solid_SourceOrDestination_lssimd,
    rasterop_solid_SourceAndDestination_lssimd,
    rasterop_solid_SourceXorDestination_lssimd,
    rasterop_solid_NotSourceAndNotDestination_lssimd,
    rasterop_solid_NotSourceOrNotDestination_lssimd,
    rasterop_solid_NotSourceXorDestination_lssimd,
    rasterop_solid_NotSource_lssimd,
    rasterop_solid_NotSourceAndDestination_lssimd,
    rasterop_solid_SourceAndNotDestination_lssimd
};

CompositionFunction qt_functionForMode_LSSIMD[numCompositionFunctions] = {
	comp_func_SourceOver_lssimd,
	0,	//comp_func_DestinationOver_lssimd,
	comp_func_Clear_lssimd,
	comp_func_Source_lssimd,
	comp_func_Destination,
    0,	//comp_func_SourceIn_lssimd,
    0,	//comp_func_DestinationIn_lssimd,
    0,	//comp_func_SourceOut_lssimd,
    0,	//comp_func_DestinationOut_lssimd,
    0,	//comp_func_SourceAtop_lssimd,
    0,	//comp_func_DestinationAtop_lssimd,
    0,	//comp_func_XOR_lssimd,
    comp_func_Plus,
    comp_func_Multiply,
    comp_func_Screen,
    comp_func_Overlay,
    comp_func_Darken,
    comp_func_Lighten,
    comp_func_ColorDodge,
    comp_func_ColorBurn,
    comp_func_HardLight,
    comp_func_SoftLight,
    comp_func_Difference,
    comp_func_Exclusion,
    rasterop_SourceOrDestination,
    rasterop_SourceAndDestination,
    rasterop_SourceXorDestination,
    rasterop_NotSourceAndNotDestination,
    rasterop_NotSourceOrNotDestination,
    rasterop_NotSourceXorDestination,
    rasterop_NotSource,
    rasterop_NotSourceAndDestination,
    rasterop_SourceAndNotDestination
};

QT_END_NAMESPACE

#endif // QT_HAVE_LOONGSONSIMD

