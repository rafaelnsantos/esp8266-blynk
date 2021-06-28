export default {
  /**
   * Function that mutates the original webpack config.
   * Supports asynchronous changes when a promise is returned (or it's an async function).
   *
   * @param {object} config - original webpack config.
   * @param {object} env - options passed to the CLI.
   * @param {WebpackConfigHelpers} helpers - object with useful helpers for working with the webpack config.
   * @param {object} options - this is mainly relevant for plugins (will always be empty in the config), default to an empty object
   **/

  webpack(config, env, helpers, options) {
    // for tsconfig paths
    config.resolve.alias['~'] = env.src;

    config.output.filename = '[name].js';

    const { plugin: cssExtractPlugin } = helpers.getPluginsByName(config, 'MiniCssExtractPlugin')[0];
    cssExtractPlugin.options.filename = 'style.css';

    if (env.isProd) {
      config.devtool = false; // disable sourcemaps
    }

    // remove console....
    config.optimization.minimizer[0].options.terserOptions.extractComments = 'all';
    config.optimization.minimizer[0].options.terserOptions.compress['drop_console'] = true;

    // remove css comments, not working!
    config.optimization.minimizer[1].options.cssProcessorPluginOptions.preset = [
      'default',
      { discardComments: { removeAll: true } }
    ];
  }
};
