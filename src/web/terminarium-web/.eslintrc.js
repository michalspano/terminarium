module.exports = {
    // The current vue project is running in the browser; not in a node environment
    // The es2021 environment is added to support the latest javascript features
    "env": {
        "browser": true,
        "es2021": true
    },
    // Add the Vue recommended rules
    "extends": [
        "eslint:recommended",
        "plugin:vue/vue3-essential"
    ],
    "overrides": [],
    "parserOptions": {
        "ecmaVersion": "latest",
        "sourceType": "module"
    },
    // Add the Vue plugin for the linting job
    "plugins": [
        "vue"
    ],
    "rules": {
        // Ignore the vue convention of multi-word component names
        'vue/multi-word-component-names': 'off',

        /* Ignore the error when a variable is declared but not used
         * Reason: the project is currently in development and not all variables are used
         * TODO: disable this rule when the project is ready for production */   
        'no-unused-vars': 'off'
    }
}
