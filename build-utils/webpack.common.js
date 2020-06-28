const commonPaths = require('./common-paths');

const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const config = {
  
  output: {
    path: commonPaths.outputPath,
    publicPath: '/'
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: `public/index.html`,
      favicon: `public/favicon.ico`,
      inject: 'body'
    })
  ]
};

module.exports = config;
