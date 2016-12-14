#include "eigen.hh"
#include "node.hh"

#include <iostream>

NAN_METHOD(values) {
  auto array = info[0].As<v8::Array>();
  const size_t size = array->Length();
  Eigen::MatrixXd matrix(size, size);

  for (size_t row = 0; row < size; ++row) {
    auto rowArray = Nan::Get(array, row).ToLocalChecked().As<v8::Array>();
    for (size_t col = 0; col < size; ++col) {
      matrix(row, col) =
          Nan::To<double>(Nan::Get(rowArray, col).ToLocalChecked()).FromJust();
    }
  }

  Eigen::EigenSolver<Eigen::MatrixXd> solver(matrix);
  const auto &values = solver.eigenvalues();

  const size_t outSize = values.size();
  v8::Local<v8::Array> outArray = Nan::New<v8::Array>(outSize);
  for (size_t i = 0; i < outSize; ++i) {
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Nan::Set(outArray, i, obj);
    Nan::Set(obj, Nan::New("real").ToLocalChecked(),
             Nan::New(values[i].real()));
    Nan::Set(obj, Nan::New("imag").ToLocalChecked(),
             Nan::New(values[i].imag()));
  }
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cholesky) {
  auto array = info[0].As<v8::Array>();
  const size_t size = array->Length();
  Eigen::MatrixXd matrix(size, size);

  for (size_t row = 0; row < size; ++row) {
    auto rowArray = Nan::Get(array, row).ToLocalChecked().As<v8::Array>();
    for (size_t col = 0; col < size; ++col) {
      matrix(row, col) =
          Nan::To<double>(Nan::Get(rowArray, col).ToLocalChecked()).FromJust();
    }
  }

  Eigen::MatrixXd L = matrix.llt().matrixU();

  const size_t outRows = L.rows();
  const size_t outColumns = L.cols();

  v8::Local<v8::Array> outMatrix = Nan::New<v8::Array>(outRows);
  for (size_t i = 0; i < outRows; ++i) {
    v8::Local<v8::Array> row = Nan::New<v8::Array>(outColumns);

    for (size_t j = 0; j < outColumns; ++j) {
      Nan::Set(row, j, Nan::New(L(i,j)));
    }

    Nan::Set(outMatrix, i, row);
  }
  info.GetReturnValue().Set(outMatrix);
}

NAN_MODULE_INIT(target) {
  Nan::Set(target, Nan::New("values").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(values))
               .ToLocalChecked());
  Nan::Set(target, Nan::New("cholesky").ToLocalChecked(),
           Nan::GetFunction(Nan::New<v8::FunctionTemplate>(cholesky))
               .ToLocalChecked());
}

NODE_MODULE(eigen, target)