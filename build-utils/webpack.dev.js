const commonPaths = require("./common-paths");

const webpack = require("webpack");
const BrowserSyncPlugin = require('browser-sync-webpack-plugin')

const port = process.env.PORT || 3100;

const config = {
  mode: "development",
  
  devServer: {   
    port: port,
    contentBase: commonPaths.staticAssetsPath,
    hot: true,
  },
  plugins: [
    new BrowserSyncPlugin(
      // BrowserSync options
      {
        open: "external",
        // browse to http://192.168.178.28:3000/ during development
        host: '192.168.178.28',
        port: 3000,
        // proxy the Webpack Dev Server endpoint
        // (which should be serving on http://localhost:3100/)
        // through BrowserSync
        proxy: 'http://localhost:'+port+'/'
      },
      // plugin options
      {
        // prevent BrowserSync from reloading the page
        // and let Webpack Dev Server take care of this
        reload: false
      }
    )
  ]
};

module.exports = config;
