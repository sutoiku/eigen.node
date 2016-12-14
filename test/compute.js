'use strict';

const chai   = require('chai');
const expect = chai.expect;
chai.use(require('chai-shallow-deep-almost-equal'));

describe('Compute', function() {

  it('Should properly compute eigen values (1)', function() {
    const module = require('../index.js');

    const A = [
      [ 1.0000, 0.5000, 0.3333, 0.2500 ],
      [ 0.5000, 1.0000, 0.6667, 0.5000 ],
      [ 0.3333, 0.6667, 1.0000, 0.7500 ],
      [ 0.2500, 0.5000, 0.7500, 1.0000 ]
    ];

    const e = module.values(A);

    expect(e).to.shallowDeepAlmostEqual([
      { real: 2.5362, imag: 0 },
      { real: 0.8482, imag: 0 },
      { real: 0.4078, imag: 0 },
      { real: 0.2078, imag: 0 }
    ]);
  });

  it('Should properly compute eigen values (2)', function() {
    const module = require('../index.js');

    const A = [
      [   0.68,   -0.33,   -0.27,  -0.717,  -0.687,  0.0259 ],
      [ -0.211,   0.536,  0.0268,   0.214,  -0.198,   0.678 ],
      [  0.566,  -0.444,   0.904,  -0.967,   -0.74,   0.225 ],
      [  0.597,   0.108,   0.832,  -0.514,  -0.782,  -0.408 ],
      [  0.823, -0.0452,   0.271,  -0.726,   0.998,   0.275 ],
      [ -0.605,   0.258,   0.435,   0.608,  -0.563,  0.0486 ]
    ];

    const e = module.values(A);

    expect(e).to.shallowDeepAlmostEqual([
      { real: 0.0488, imag: 1.0597  },
      { real: 0.0488, imag: -1.0597 },
      { real: 0.9687, imag: 0       },
      { real: 0.3428, imag: 0       },
      { real: 0.6217, imag: 0.137   },
      { real: 0.6217, imag: -0.137  }
    ]);
  });

  it('Should properly compute cholesky of [[25, 15, -5], [15, 18, 0], [-5, 0, 11]]', function() {
    const module = require('../index.js');

    const A = [[25, 15, -5], [15, 18, 0], [-5, 0, 11]];

    const e = module.cholesky(A);

    expect(e).to.shallowDeepAlmostEqual([[5,3,-1],[0,3,1],[0,0,3]]);
  });

  it('Should properly compute cholesky of [[4, 12, -16], [12, 37, -43], [-16, -43, 98]]', function() {
    const module = require('../index.js');

    const A = [[4, 12, -16], [12, 37, -43], [-16, -43, 98]];

    const e = module.cholesky(A);

    expect(e).to.shallowDeepAlmostEqual([[2,6,-8],[0,1,5],[0,0,3]]);
  });
});

