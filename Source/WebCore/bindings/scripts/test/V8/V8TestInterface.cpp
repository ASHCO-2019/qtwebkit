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
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#include "V8TestInterface.h"

#if ENABLE(Condition1) || ENABLE(Condition2)

#include "BindingState.h"
#include "ContextFeatures.h"
#include "ExceptionCode.h"
#include "Frame.h"
#include "RuntimeEnabledFeatures.h"
#include "TestSupplemental.h"
#include "V8Binding.h"
#include "V8DOMWrapper.h"
#include "V8Node.h"
#include "V8TestObj.h"
#include <wtf/GetPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/RefPtr.h>
#include <wtf/UnusedParam.h>

namespace WebCore {

WrapperTypeInfo V8TestInterface::info = { V8TestInterface::GetTemplate, V8TestInterface::derefObject, V8TestInterface::toActiveDOMObject, 0, 0, WrapperTypeObjectPrototype };

namespace TestInterfaceV8Internal {

template <typename T> void V8_USE(T) { }

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalStaticReadOnlyAttrAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStaticReadOnlyAttr._get");
    return v8Integer(TestSupplemental::supplementalStaticReadOnlyAttr(), info.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalStaticAttrAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStaticAttr._get");
    return v8String(TestSupplemental::supplementalStaticAttr(), info.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static void supplementalStaticAttrAttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStaticAttr._set");
    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK_VOID(V8Parameter<>, v, value);
    TestSupplemental::setSupplementalStaticAttr(v);
    return;
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalStr1AttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStr1._get");
    TestInterface* imp = V8TestInterface::toNative(info.Holder());
    return v8String(TestSupplemental::supplementalStr1(imp), info.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalStr2AttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStr2._get");
    TestInterface* imp = V8TestInterface::toNative(info.Holder());
    return v8String(TestSupplemental::supplementalStr2(imp), info.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static void supplementalStr2AttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalStr2._set");
    TestInterface* imp = V8TestInterface::toNative(info.Holder());
    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK_VOID(V8Parameter<>, v, value);
    TestSupplemental::setSupplementalStr2(imp, v);
    return;
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalNodeAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalNode._get");
    TestInterface* imp = V8TestInterface::toNative(info.Holder());
    return toV8(TestSupplemental::supplementalNode(imp), info.Holder(), info.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static void supplementalNodeAttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestInterface.supplementalNode._set");
    TestInterface* imp = V8TestInterface::toNative(info.Holder());
    Node* v = V8Node::HasInstance(value) ? V8Node::toNative(v8::Handle<v8::Object>::Cast(value)) : 0;
    TestSupplemental::setSupplementalNode(imp, WTF::getPtr(v));
    return;
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalMethod1Callback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestInterface.supplementalMethod1");
    TestInterface* imp = V8TestInterface::toNative(args.Holder());
    TestSupplemental::supplementalMethod1(imp);
    return v8Undefined();
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalMethod2Callback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestInterface.supplementalMethod2");
    if (args.Length() < 2)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    TestInterface* imp = V8TestInterface::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK(V8Parameter<>, strArg, MAYBE_MISSING_PARAMETER(args, 0, DefaultIsUndefined));
    EXCEPTION_BLOCK(TestObj*, objArg, V8TestObj::HasInstance(MAYBE_MISSING_PARAMETER(args, 1, DefaultIsUndefined)) ? V8TestObj::toNative(v8::Handle<v8::Object>::Cast(MAYBE_MISSING_PARAMETER(args, 1, DefaultIsUndefined))) : 0);
    ScriptExecutionContext* scriptContext = getScriptExecutionContext();
    RefPtr<TestObj> result = TestSupplemental::supplementalMethod2(scriptContext, imp, strArg, objArg, ec);
    if (UNLIKELY(ec))
        goto fail;
    return toV8(result.release(), args.Holder(), args.GetIsolate());
    }
    fail:
    return setDOMException(ec, args.GetIsolate());
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

#if ENABLE(Condition11) || ENABLE(Condition12)

static v8::Handle<v8::Value> supplementalMethod4Callback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestInterface.supplementalMethod4");
    TestSupplemental::supplementalMethod4();
    return v8Undefined();
}

#endif // ENABLE(Condition11) || ENABLE(Condition12)

} // namespace TestInterfaceV8Internal

static const V8DOMConfiguration::BatchedAttribute V8TestInterfaceAttrs[] = {
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalStaticReadOnlyAttr' (Type: 'readonly attribute' ExtAttr: 'Conditional ImplementedBy')
    {"supplementalStaticReadOnlyAttr", TestInterfaceV8Internal::supplementalStaticReadOnlyAttrAttrGetter, 0, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalStaticAttr' (Type: 'attribute' ExtAttr: 'Conditional ImplementedBy')
    {"supplementalStaticAttr", TestInterfaceV8Internal::supplementalStaticAttrAttrGetter, TestInterfaceV8Internal::supplementalStaticAttrAttrSetter, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalStr1' (Type: 'readonly attribute' ExtAttr: 'Conditional ImplementedBy')
    {"supplementalStr1", TestInterfaceV8Internal::supplementalStr1AttrGetter, 0, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalStr2' (Type: 'attribute' ExtAttr: 'Conditional ImplementedBy')
    {"supplementalStr2", TestInterfaceV8Internal::supplementalStr2AttrGetter, TestInterfaceV8Internal::supplementalStr2AttrSetter, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalStr3' (Type: 'attribute' ExtAttr: 'CustomSetter CustomGetter Conditional ImplementedBy')
    {"supplementalStr3", V8TestInterface::supplementalStr3AccessorGetter, V8TestInterface::supplementalStr3AccessorSetter, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    // Attribute 'supplementalNode' (Type: 'attribute' ExtAttr: 'Conditional ImplementedBy')
    {"supplementalNode", TestInterfaceV8Internal::supplementalNodeAttrGetter, TestInterfaceV8Internal::supplementalNodeAttrSetter, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
#endif // ENABLE(Condition11) || ENABLE(Condition12)
};

static const V8DOMConfiguration::BatchedCallback V8TestInterfaceCallbacks[] = {
#if ENABLE(Condition11) || ENABLE(Condition12)
    {"supplementalMethod1", TestInterfaceV8Internal::supplementalMethod1Callback},
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    {"supplementalMethod3", V8TestInterface::supplementalMethod3Callback},
#endif
};

static const V8DOMConfiguration::BatchedConstant V8TestInterfaceConsts[] = {
#if ENABLE(Condition11) || ENABLE(Condition12)
    {"SUPPLEMENTALCONSTANT1", static_cast<signed int>(1)},
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
    {"SUPPLEMENTALCONSTANT2", static_cast<signed int>(2)},
#endif
};


#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(1 == TestSupplemental::SUPPLEMENTALCONSTANT1, TestInterfaceEnumSUPPLEMENTALCONSTANT1IsWrongUseDoNotCheckConstants);
#endif
#if ENABLE(Condition11) || ENABLE(Condition12)
COMPILE_ASSERT(2 == TestSupplemental::CONST_IMPL, TestInterfaceEnumCONST_IMPLIsWrongUseDoNotCheckConstants);
#endif

v8::Handle<v8::Value> V8TestInterface::constructorCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestInterface.Constructor");
    
    if (!args.IsConstructCall())
        return throwTypeError("DOM object constructor cannot be called as a function.");

    if (ConstructorMode::current() == ConstructorMode::WrapExistingObject)
        return args.Holder();
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());

    ExceptionCode ec = 0;
    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK(V8Parameter<>, str1, MAYBE_MISSING_PARAMETER(args, 0, DefaultIsUndefined));
    STRING_TO_V8PARAMETER_EXCEPTION_BLOCK(V8Parameter<>, str2, MAYBE_MISSING_PARAMETER(args, 1, DefaultIsUndefined));

    ScriptExecutionContext* context = getScriptExecutionContext();

    RefPtr<TestInterface> impl = TestInterface::create(context, str1, str2, ec);
    v8::Handle<v8::Object> wrapper = args.Holder();
    if (ec)
        goto fail;

    V8DOMWrapper::setDOMWrapper(wrapper, &info, impl.get());
    V8DOMWrapper::setJSWrapperForActiveDOMObject(impl.release(), wrapper, args.GetIsolate());
    return wrapper;
  fail:
    return setDOMException(ec, args.GetIsolate());
}

static v8::Persistent<v8::FunctionTemplate> ConfigureV8TestInterfaceTemplate(v8::Persistent<v8::FunctionTemplate> desc)
{
    desc->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::configureTemplate(desc, "TestInterface", v8::Persistent<v8::FunctionTemplate>(), V8TestInterface::internalFieldCount,
        V8TestInterfaceAttrs, WTF_ARRAY_LENGTH(V8TestInterfaceAttrs),
        V8TestInterfaceCallbacks, WTF_ARRAY_LENGTH(V8TestInterfaceCallbacks));
    UNUSED_PARAM(defaultSignature); // In some cases, it will not be used.
    desc->SetCallHandler(V8TestInterface::constructorCallback);
    v8::Local<v8::ObjectTemplate> instance = desc->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> proto = desc->PrototypeTemplate();
    UNUSED_PARAM(instance); // In some cases, it will not be used.
    UNUSED_PARAM(proto); // In some cases, it will not be used.
    

    // Custom Signature 'supplementalMethod2'
    const int supplementalMethod2Argc = 2;
    v8::Handle<v8::FunctionTemplate> supplementalMethod2Argv[supplementalMethod2Argc] = { v8::Handle<v8::FunctionTemplate>(), V8TestObj::GetRawTemplate() };
    v8::Handle<v8::Signature> supplementalMethod2Signature = v8::Signature::New(desc, supplementalMethod2Argc, supplementalMethod2Argv);
#if ENABLE(Condition11) || ENABLE(Condition12)
    proto->Set(v8::String::NewSymbol("supplementalMethod2"), v8::FunctionTemplate::New(TestInterfaceV8Internal::supplementalMethod2Callback, v8Undefined(), supplementalMethod2Signature));
#endif // ENABLE(Condition11) || ENABLE(Condition12)
#if ENABLE(Condition11) || ENABLE(Condition12)
    desc->Set(v8::String::NewSymbol("supplementalMethod4"), v8::FunctionTemplate::New(TestInterfaceV8Internal::supplementalMethod4Callback, v8Undefined(), v8::Local<v8::Signature>()));
#endif // ENABLE(Condition11) || ENABLE(Condition12)
    V8DOMConfiguration::batchConfigureConstants(desc, proto, V8TestInterfaceConsts, WTF_ARRAY_LENGTH(V8TestInterfaceConsts));

    // Custom toString template
    desc->Set(v8::String::NewSymbol("toString"), V8PerIsolateData::current()->toStringTemplate());
    return desc;
}

v8::Persistent<v8::FunctionTemplate> V8TestInterface::GetRawTemplate()
{
    V8PerIsolateData* data = V8PerIsolateData::current();
    V8PerIsolateData::TemplateMap::iterator result = data->rawTemplateMap().find(&info);
    if (result != data->rawTemplateMap().end())
        return result->second;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ = createRawTemplate();
    data->rawTemplateMap().add(&info, templ);
    return templ;
}

v8::Persistent<v8::FunctionTemplate> V8TestInterface::GetTemplate()
{
    V8PerIsolateData* data = V8PerIsolateData::current();
    V8PerIsolateData::TemplateMap::iterator result = data->templateMap().find(&info);
    if (result != data->templateMap().end())
        return result->second;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ =
        ConfigureV8TestInterfaceTemplate(GetRawTemplate());
    data->templateMap().add(&info, templ);
    return templ;
}

bool V8TestInterface::HasInstance(v8::Handle<v8::Value> value)
{
    return GetRawTemplate()->HasInstance(value);
}

ActiveDOMObject* V8TestInterface::toActiveDOMObject(v8::Handle<v8::Object> object)
{
    return toNative(object);
}      

v8::Handle<v8::Object> V8TestInterface::wrapSlow(PassRefPtr<TestInterface> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    v8::Handle<v8::Object> wrapper;
    Document* document = 0;
    UNUSED_PARAM(document);

    v8::Handle<v8::Context> context;
    if (!creationContext.IsEmpty() && creationContext->CreationContext() != v8::Context::GetCurrent()) {
        // For performance, we enter the context only if the currently running context
        // is different from the context that we are about to enter.
        context = v8::Local<v8::Context>::New(creationContext->CreationContext());
        ASSERT(!context.IsEmpty());
        context->Enter();
    }

    wrapper = V8DOMWrapper::instantiateV8Object(document, &info, impl.get());

    if (!context.IsEmpty())
        context->Exit();

    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;
    v8::Persistent<v8::Object> wrapperHandle = V8DOMWrapper::setJSWrapperForActiveDOMObject(impl, wrapper, isolate);
    if (!hasDependentLifetime)
        wrapperHandle.MarkIndependent();
    return wrapper;
}

void V8TestInterface::derefObject(void* object)
{
    static_cast<TestInterface*>(object)->deref();
}

} // namespace WebCore

#endif // ENABLE(Condition1) || ENABLE(Condition2)
