'use strict';

const expect = require('chai').expect;

describe('Init', function() {

  it('Should properly load module', function() {
    const module = require('../index.js');
    expect(module).to.exist;
    expect(module.values).to.be.an.instanceof(Function);
  });
});
