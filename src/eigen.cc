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

void throwSimpleError (const char * errorMessage) {
  v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(Nan::New(errorMessage).ToLocalChecked()));              
}

NAN_METHOD(cholesky) {
  auto array = info[0].As<v8::Array>();
  const size_t size = array->Length();
  const auto EPSILON = std::numeric_limits<double>::epsilon();
  Eigen::MatrixXd matrix(size, size);

  // ideally we would copy only half of the matrix
  // but it's unclear whether we can assume which half
  // Eigen is reliably going to use.
  for (size_t row = 0; row < size; ++row) {
    auto rowArray = Nan::Get(array, row).ToLocalChecked().As<v8::Array>();
    for (size_t col = 0; col < size; ++col) {
      matrix(row, col) =
          Nan::To<double>(Nan::Get(rowArray, col).ToLocalChecked()).FromJust();
    }
  }

  // check that the resulting matrix is symmetric
  // doing this while loading the matrix seems messy
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i+1; j < size; ++j) {
      if (fabs(matrix(i, j) - matrix(j, i)) > EPSILON) {
        return throwSimpleError("Cholesky requires a symmetric matrix");
      }
    }
  }

  // do Cholesky. Note that Eigen "does" cholesky also
  // for matrices where it shouldn't be possible.
  // We'll have to check those cases now.
  const auto decomposition = matrix.llt();
  
  Eigen::MatrixXd LT = decomposition.matrixU();

  // resulting matrix is square too
  const size_t outRowsAndColumns = LT.rows();

  // the resulting decomposition must have positive elements
  // in the diagonal elements.
  // We check because Eigen gives the wrong results in
  // cases where there should be no decomposition at all, for example
  // [[0,1],[1,0]] .
  for (size_t i = 0; i < outRowsAndColumns; ++i) {
    if (LT(i,i) <= EPSILON) {
      return throwSimpleError("Cholesky requires a positive definite matrix");
    }
  }

  // load back into JS arrays of arrays
  v8::Local<v8::Array> outMatrix = Nan::New<v8::Array>(outRowsAndColumns);
  for (size_t i = 0; i < outRowsAndColumns; ++i) {
    v8::Local<v8::Array> row = Nan::New<v8::Array>(outRowsAndColumns);

    for (size_t j = 0; j < outRowsAndColumns; ++j) {
      Nan::Set(row, j, Nan::New(LT(i,j)));
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