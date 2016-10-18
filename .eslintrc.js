'use strict';

const fs       = require('fs');
const jshintrc = JSON.parse(fs.readFileSync(`${__dirname}/.jshintrc`, 'utf8'));
const globals  = jshintrc.predef.reduce((acc, v) => { acc[v] = true; return acc; }, {});

module.exports = {
  globals,
  env     : { es6: true, node: true, browser: false },
  extends : [
    "./node_modules/eslint-config-bestpractices/index.js",
    "plugin:stoic/recommended"
  ],
  plugins : [ 'stoic' ],
  rules   : {
    'no-labels'          : 0,
    'no-console'         : 2,
    'no-else-return'     : 2,
    'no-param-reassign'  : 2,
    'prefer-rest-params' : [ 'error' ]
  }
};
