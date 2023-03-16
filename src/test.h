#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H
#include <napi.h>
#include <Windows.h>
#include <sstream>
#include <thread>

using namespace std;

Napi::Value ginit(const Napi::CallbackInfo& info);
// Napi::Value shutdown(const Napi::CallbackInfo& info);

#endif