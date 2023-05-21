import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  // List plugins to use
  plugins: [vue()],
  resolve: {
    alias: {
      // Define entry point for custom aliases
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  }, 
  test: {
    /* For building web-based applications: 'jsdom'/'happy-dom';
     * Reference: https://vitest.dev/config/#environment */
    environment: 'happy-dom'
  },
  build: {
    // Enlarge the warning of single file size
    chunkSizeWarningLimit: 1000,
    rollupOptions: {
      // Preserve file names in the build directory
      output: {
        entryFileNames: `assets/[name].js`,
        chunkFileNames: `assets/[name].js`,
        assetFileNames: `src/assets/[name].[ext]`
      }
    }
  }
})
