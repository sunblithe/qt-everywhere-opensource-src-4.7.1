/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(SVG) && ENABLE(FILTERS)

#include "JSSVGFECompositeElement.h"

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedEnumeration.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedNumber.h"
#include "JSSVGAnimatedString.h"
#include "SVGFECompositeElement.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFECompositeElement);

/* Hash table */

static const HashTableValue JSSVGFECompositeElementTableValues[16] =
{
    { "in1", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementIn1), (intptr_t)0 },
    { "in2", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementIn2), (intptr_t)0 },
    { "operator", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementOperator), (intptr_t)0 },
    { "k1", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementK1), (intptr_t)0 },
    { "k2", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementK2), (intptr_t)0 },
    { "k3", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementK3), (intptr_t)0 },
    { "k4", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementK4), (intptr_t)0 },
    { "x", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementX), (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementY), (intptr_t)0 },
    { "width", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementWidth), (intptr_t)0 },
    { "height", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementHeight), (intptr_t)0 },
    { "result", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementResult), (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementClassName), (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementStyle), (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFECompositeElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGFECompositeElementTableValues, 0 };
#else
    { 34, 31, JSSVGFECompositeElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGFECompositeElementConstructorTableValues[8] =
{
    { "SVG_FECOMPOSITE_OPERATOR_UNKNOWN", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_UNKNOWN), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_OVER", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OVER), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_IN", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_IN), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_OUT", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OUT), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_ATOP", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ATOP), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_XOR", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_XOR), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_ARITHMETIC", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ARITHMETIC), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFECompositeElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFECompositeElementConstructorTableValues, 0 };
#else
    { 16, 15, JSSVGFECompositeElementConstructorTableValues, 0 };
#endif

class JSSVGFECompositeElementConstructor : public DOMConstructorObject {
public:
    JSSVGFECompositeElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSSVGFECompositeElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSSVGFECompositeElementPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSSVGFECompositeElementConstructor::s_info = { "SVGFECompositeElementConstructor", 0, &JSSVGFECompositeElementConstructorTable, 0 };

bool JSSVGFECompositeElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFECompositeElementConstructor, DOMObject>(exec, &JSSVGFECompositeElementConstructorTable, this, propertyName, slot);
}

bool JSSVGFECompositeElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFECompositeElementConstructor, DOMObject>(exec, &JSSVGFECompositeElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSSVGFECompositeElementPrototypeTableValues[9] =
{
    { "SVG_FECOMPOSITE_OPERATOR_UNKNOWN", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_UNKNOWN), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_OVER", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OVER), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_IN", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_IN), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_OUT", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OUT), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_ATOP", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ATOP), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_XOR", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_XOR), (intptr_t)0 },
    { "SVG_FECOMPOSITE_OPERATOR_ARITHMETIC", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ARITHMETIC), (intptr_t)0 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsSVGFECompositeElementPrototypeFunctionGetPresentationAttribute), (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSSVGFECompositeElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 63, JSSVGFECompositeElementPrototypeTableValues, 0 };
#else
    { 17, 15, JSSVGFECompositeElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFECompositeElementPrototype::s_info = { "SVGFECompositeElementPrototype", 0, &JSSVGFECompositeElementPrototypeTable, 0 };

JSObject* JSSVGFECompositeElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFECompositeElement>(exec, globalObject);
}

bool JSSVGFECompositeElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSSVGFECompositeElementPrototype, JSObject>(exec, &JSSVGFECompositeElementPrototypeTable, this, propertyName, slot);
}

bool JSSVGFECompositeElementPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticPropertyDescriptor<JSSVGFECompositeElementPrototype, JSObject>(exec, &JSSVGFECompositeElementPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGFECompositeElement::s_info = { "SVGFECompositeElement", &JSSVGElement::s_info, &JSSVGFECompositeElementTable, 0 };

JSSVGFECompositeElement::JSSVGFECompositeElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGFECompositeElement> impl)
    : JSSVGElement(structure, globalObject, impl)
{
}

JSObject* JSSVGFECompositeElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFECompositeElementPrototype(JSSVGFECompositeElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFECompositeElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFECompositeElement, Base>(exec, &JSSVGFECompositeElementTable, this, propertyName, slot);
}

bool JSSVGFECompositeElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGFECompositeElement, Base>(exec, &JSSVGFECompositeElementTable, this, propertyName, descriptor);
}

JSValue jsSVGFECompositeElementIn1(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->in1Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementIn2(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->in2Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementOperator(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->_operatorAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementK1(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->k1Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementK2(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->k2Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementK3(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->k3Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementK4(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->k4Animated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementX(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementY(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementWidth(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->widthAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementHeight(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedLength> obj = imp->heightAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementResult(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->resultAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementClassName(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    JSValue result =  toJS(exec, castedThis->globalObject(), obj.get(), imp);
    return result;
}

JSValue jsSVGFECompositeElementStyle(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* castedThis = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->style()));
    return result;
}

JSValue jsSVGFECompositeElementConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGFECompositeElement* domObject = static_cast<JSSVGFECompositeElement*>(asObject(slotBase));
    return JSSVGFECompositeElement::getConstructor(exec, domObject->globalObject());
}
JSValue JSSVGFECompositeElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGFECompositeElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsSVGFECompositeElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSSVGFECompositeElement::s_info))
        return throwError(exec, TypeError);
    JSSVGFECompositeElement* castedThisObj = static_cast<JSSVGFECompositeElement*>(asObject(thisValue));
    SVGFECompositeElement* imp = static_cast<SVGFECompositeElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, castedThisObj->globalObject(), WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

// Constant getters

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_UNKNOWN(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OVER(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_IN(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_OUT(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ATOP(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_XOR(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(5));
}

JSValue jsSVGFECompositeElementSVG_FECOMPOSITE_OPERATOR_ARITHMETIC(ExecState* exec, JSValue, const Identifier&)
{
    return jsNumber(exec, static_cast<int>(6));
}


}

#endif // ENABLE(SVG) && ENABLE(FILTERS)
