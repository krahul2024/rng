#include <napi.h>
#include "rng/rng.h"

class RNGWrapper : public Napi::ObjectWrap<RNGWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  RNGWrapper(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  Napi::Value GetRandomValue(const Napi::CallbackInfo& info);
  Napi::Value GetMultiplier(const Napi::CallbackInfo& info);
  rng* rngInstance;
};

Napi::FunctionReference RNGWrapper::constructor;

Napi::Object RNGWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "RNG", {
    InstanceMethod("getRandomValue", &RNGWrapper::GetRandomValue),
    InstanceMethod("getMultiplier", &RNGWrapper::GetMultiplier),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("RNG", func);
  return exports;
}

RNGWrapper::RNGWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<RNGWrapper>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 2 && info[0].IsNumber() && info[1].IsNumber()) {
    double rtp = info[0].As<Napi::Number>().DoubleValue();
    unsigned long long max_multiplier = info[1].As<Napi::Number>().Int64Value();
    this->rngInstance = new rng(rtp, max_multiplier);
  } else {
    this->rngInstance = new rng();
  }
}

Napi::Value RNGWrapper::GetRandomValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, this->rngInstance->get_random_value());
}

Napi::Value RNGWrapper::GetMultiplier(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, this->rngInstance->get_multiplier());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return RNGWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
