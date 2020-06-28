const commonPaths = require('./common-paths');

const webpack = require('webpack');
const config = {
  mode: 'production',
  entry: {
    app: [`${commonPaths.appEntry}/index.bs.js`],
  },
  output: {
    path: commonPaths.outputPath,
    filename: 'index.js',
  },  
 
};

module.exports = config;
