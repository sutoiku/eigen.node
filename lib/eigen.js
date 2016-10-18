'use strict';

const native = require('./native');

module.exports.values = (matrix) => {
  if(!matrix) {
    throw new Error('Matrix cannot be null');
  }
  if(!Array.isArray(matrix)) {
    throw new Error('Bad matrix type');
  }
  const size = matrix.length;
  for(const item of matrix) {
    if(!Array.isArray(item)) {
      throw new Error('Bad matrix type');
    }
    if(item.length !== size) {
      throw new Error('Bad matrix dimensions');
    }
  }

  return native.values(matrix);
};