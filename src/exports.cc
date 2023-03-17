#include <napi.h>
#include "test.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    // exports.Set(Napi::String::New(env, "shutdown"), Napi::Function::New(env, shutdown));    

    exports.Set(Napi::String::New(env, "ginit"), Napi::Function::New(env, ginit));    
    exports.Set(Napi::String::New(env, "asyncMethod"), Napi::Function::New(env, AsyncMethod));
    return exports;
}


NODE_API_MODULE(napi_sample, Init)