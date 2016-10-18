#include <node.hh>

NAN_METHOD(execute) {
  info.GetReturnValue().Set(Nan::New("This is a thing.").ToLocalChecked());
}

NAN_MODULE_INIT(target) {
  Nan::Set(target, Nan::New("execute").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(execute))
               .ToLocalChecked());
}

NODE_MODULE(eigen, target)