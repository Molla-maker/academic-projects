import eslintPluginN from 'eslint-plugin-n';

/** @type {import("eslint").Linter.FlatConfig[]} */
export default [
  {
    files: ['**/*.js'],
    languageOptions: {
      ecmaVersion: 'latest',
      sourceType: 'module'
    },
    plugins: {
      n: eslintPluginN
    },
    rules: {
      // Node.js specific rules
      ...eslintPluginN.configs['flat/recommended-module'].rules,
      
      // Possible Problems
      'no-template-curly-in-string': 'error',
      'no-use-before-define': ['error', { functions: false }],
      'no-useless-assignment': 'error',
      
      // Suggestions
      'accessor-pairs': 'error',
      'arrow-body-style': ['error', 'as-needed'],
      'camelcase': 'error',
      'curly': 'error',
      'eqeqeq': ['error', 'always'],
      'no-alert': 'error',
      'no-nested-ternary': 'error',
      'no-return-assign': 'error',
      'no-shadow': ['error', { hoist: 'all' }],
      'no-unneeded-ternary': 'error',
      'no-unused-expressions': 'error',
      'no-useless-concat': 'error',
      'no-useless-return': 'error',
      'no-var': 'error',
      'prefer-arrow-callback': 'error',
      'prefer-const': 'error',
      'prefer-template': 'error',
      'radix': 'error'
    }
  },
];
